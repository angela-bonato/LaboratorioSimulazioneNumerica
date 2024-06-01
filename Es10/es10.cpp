#include "lib10.h"
#include "mpi.h"
#include "parallel.h"

using namespace std;

int main (int argc, char *argv[]){   

    //inizializzazione dei processi e del generatore Random per ogni processo
    int size,rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //dichiaro variabili che il processo 0 inizializza e poi invia
    int seed[4];
    int p1, p2;
    vector<City> Cities;

    if(rank==0){    //ogni processo userà rand inizializzato diversamente in modo da generare numeri diversi però il processo principale gestisce la cosa
        ifstream inprimes;
        inprimes.open("../RandomGenerator/Primes");  
        for(int i=1; i<size; i++){      //il processo 0 passsa agli altri l'inizializzazione
            if(ReadIthLine(inprimes, i+30, p1, p2)){
                MPI_Send(&p1, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&p2, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
                seed[0]=i;
                seed[1]=i*2;
                seed[2]=i*3;
                seed[3]=i*4;
                MPI_Send(seed, 4, MPI_INT, i, 2, MPI_COMM_WORLD);
                cout << "Primes e Seed mandati al processo " << i << endl; //in questo modo ogni processo genera numeri diversi
            }
            else cerr << "Errore nell'invio dei primes e seed al processo " << i << endl;
        }   

        //variabili di inizializzazione per il processo principale
        ReadIthLine(inprimes, 0, p1, p2);
        inprimes.close();  

        ifstream input("../RandomGenerator/seed.in");
        string property;
        if(input.is_open()){
            while(!input.eof() ){
                input >> property;
                if( property == "RANDOMSEED" ){
                    input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
                }
            }
            input.close();
        }
        else cerr << "Errore: impossibile aprire seed" << endl;
    }
    else{
        // Gli altri processi ricevono i valori
        MPI_Recv(&p1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&p2, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(seed, 4, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Dati ricevuti dal processo " << rank << endl;
    }
    if(rank==0){
        //inizializzazione città
        ifstream incity;
        incity.open("cap_prov_ita.dat");
        vector<City> Cities=InitCities(incity);
        //invio le città e Ncities dal processo 0 a tutti gli altri, devo usare le funzioni ridefinite da me ergo non penso di poter usare i protocolli di comunicazione come broadcast o che
        for(int i=1; i<size; i++){
            sendCityVec(Cities, i, 3, MPI_COMM_WORLD);
            cout << "Città mandate al processo " << i << endl;
        }
    }
    else{  
        // Gli altri processi ricevono le città
        recvCityVec(Cities, 0, 3, MPI_COMM_WORLD);
        cout << "Città ricevute dal processo " << rank << endl;
    }

    //ora rimando le città al processo 0 perchè boh sennò non funziona, non so perchè
    if(rank==1) sendCityVec(Cities, 0, 4, MPI_COMM_WORLD);
    else if(rank==0) recvCityVec(Cities, 1, 4, MPI_COMM_WORLD);

    int Ncities=Cities.size();
    cout << rank << " " << Ncities << endl;

    //inizializzazione generatore casuale su ogni processo con Primes diversi
    Random rand;   
    rand.SetRandom(seed, p1, p2);   //ogni processo inizializza il suo rand
    
    //variabili generali, dovrebbero già definirsi in ogni processo scrivendole qui
    int Npaths=2500;  //numero path per ogni generazione in ogni processo DEVONO ESSERE PARI
    int Ntot=3000;     //numero step totali i.e., Nmigr*Ncont (Ncont=numero di migrazioni dopo cui faccio swap)
    int Nmigr=150;    //numero generazioni considerate da ogni processo indipendente (i.e., step in un continente)
    double pc=0.6;  //probabilità di crossover
    double pm1=0.07; //probabilità prima mutazione
    double pm2=0.06; //probabilità seconda mutazione
    double pm3=0.05; //probabilità terza mutazione
    double pm4=0.04; //probabilità quarta mutazione

    //inizializzo la prima popolazione
    vector<Path> starting_population=InitRandomPop(rand, Ncities, Npaths);
    vector<Path> new_population;
    Path best_path=starting_population[0];
    best_path.EvalLoss(Cities);
    
    //apro i files di output
    string afilename="bestloss_" + to_string(rank) + ".dat";     //output loss del best path di ogni generazione per ogni processo
    ofstream bout(afilename);
    string bfilename="besthalfloss_" + to_string(rank) + ".dat";    //output loss media dei primi N/2 best path di ogni generazione per ogni processo
    ofstream bhout(bfilename);
    string cfilename="bestpath_" + to_string(rank) + ".dat";    //output miglior percorso in assoluto per ogni processo
    ofstream pout(cfilename);

    //parto con l'algoritmo genetico
    for(int s=0; s<Ntot; s++){
        new_population=ReplaceGeneration(rand, starting_population, Cities, Ncities, pc, pm1, pm2, pm3, pm4, s, bout, bhout, best_path);

        //alla fine di ogni continente swappo (questa parte va commentata per fare l'analisi indipendente)
/*        if(s!=0 && s%Nmigr==0){
            //il processo principale genera le coppie, ATTENZIONE: QUA FUNZIONA SOLO SE SI AVVIANO ALMENTO 4 PROCESSI
            int inds[4];
            if(rank==0){
                inds[0]=int(rand.Rannyu(0, size));
                inds[1]=int(rand.Rannyu(0, size));
                while(inds[0]==inds[1]) inds[1]=int(rand.Rannyu(0, size));
                inds[2]=int(rand.Rannyu(0, size));
                while(inds[2]==inds[1] || inds[2]==inds[0]) inds[2]=int(rand.Rannyu(0, size));
                inds[3]=int(rand.Rannyu(0, size));
                while(inds[3]==inds[0] || inds[3]==inds[1] || inds[3]==inds[2]) inds[3]=int(rand.Rannyu(0, size));
                //manda a tutti gli indici
                for(int k=1; k<size; k++) MPI_Send(inds, 4, MPI_INT, k, 5, MPI_COMM_WORLD);
            }
            else MPI_Recv(inds, 4, MPI_INT, 0, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            Path send=new_population[0];    //ogni rank si copia il proprio best path in una variabile
            //invio best path e ricezione
            if(rank==inds[0]) sendPath(send, inds[1], 6, MPI_COMM_WORLD);
            if(rank==inds[1]) recvPath(new_population[0], inds[0], 6, MPI_COMM_WORLD);

            if(rank==inds[1]) sendPath(send, inds[0], 6, MPI_COMM_WORLD);
            if(rank==inds[0]) recvPath(new_population[0], inds[1], 6, MPI_COMM_WORLD);

            if(rank==inds[2]) sendPath(send, inds[3], 6, MPI_COMM_WORLD);
            if(rank==inds[3]) recvPath(new_population[0], inds[2], 6, MPI_COMM_WORLD);

            if(rank==inds[3]) sendPath(send, inds[2], 6, MPI_COMM_WORLD);
            if(rank==inds[2]) recvPath(new_population[0], inds[3], 6, MPI_COMM_WORLD);
            
            if(rank==inds[2]) cout << "Swap " << s/Nmigr <<" fatto." << endl;
        }
*/
        //proseguo algoritmo genetico
        starting_population=new_population;
    }

    //ogni continente ha finito la sua analisi e restituisce il suo best path in assoluto
    if(pout.is_open()){
        pout << "#" << scientific << best_path.get_loss() << endl;
        for(int i=0; i<int(best_path.get_ord().size()); i++){
            pout <<  scientific << Cities[best_path.get_ord(i)].get_x() << "  " << scientific << Cities[best_path.get_ord(i)].get_y() <<  endl;
        }
    }
    else cerr << "Errore: impossibile aprire bestpath.dat" << endl;

    rand.SaveSeed();
    bout.close();
    bhout.close();
    pout.close();

    MPI_Finalize();
 
    return 0;
}