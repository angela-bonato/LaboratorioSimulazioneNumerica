#include "lib10.h"
#include "mpi.h"
#include "parallel.h"

using namespace std;

int main (int argc, char *argv[]){
    //variabili generali
    int Npaths=1000;  //numero path per ogni generazione in ogni processo DEVONO ESSERE PARI
    int Nmigr=100;    //numero generazioni considerate da ogni processo indipendente (i.e., step in un continente)
    int Ncont=10;  //numero di continenti, fra uno e l'altro ci sono degli swap

    double pc=0.6;  //probabilità di crossover
    double pm1=0.07; //probabilità prima mutazione
    double pm2=0.06; //probabilità seconda mutazione
    double pm3=0.05; //probabilità terza mutazione
    double pm4=0.04; //probabilità quarta mutazione

    //inizializzazione città
    ifstream infile;
    infile.open("cap_prov_ita.dat");
    vector<City> Cities=InitCities(infile);
    int Ncities=Cities.size(); //numero città considerate

    //inizializzazione geenratore casuale
    Random rand;   
    InizRandom(rand);
    
    /*
    a questo punto: 
    -[] inizializzo processi
    -[] apro files output(capire quanti e quali e come gesturli) per ogni processo
    -[] per ogni processo inizializzo popolazione iniziale
    -[] a ogni processo do da fare un continente
    -[] swap randomici fra risultati migliori dei continenti
    -[] secondo continente
    -[] vado avanti fino a che non faccio Nmigr continenti
    -[] metto insieme tutti i migliori e trovo il best assoluto e scrivo output
    */

/*
    ofstream bout;  //output loss del best path di ogni generazione
    ofstream bhout;  //output loss media dei primi N/2 best path di ogni generazione
    ofstream pout;  //output miglior percorso in assoluto

    bout.open("cbestloss.dat");
    bhout.open("cbesthalfloss.dat");
    pout.open("cbestpath.dat");
    

    vector<Path> starting_population=InitRandomPop(rand, cities.size(), P);
    vector<Path> new_population;
    Path best_path=starting_population[0];
    best_path.EvalLoss(cities);

    

    for(int s=0; s<S; s++){
        new_population=ReplaceGeneration(rand, starting_population, cities, N, pc, pm1, pm2, pm3, pm4, s, bout, bhout, best_path);
        starting_population=new_population;
        cout << "Rimpiazzata popolazione " << s << endl;
    }

    if(pout.is_open()){
        pout << "#" << scientific << best_path.get_loss() << endl;
        for(int i=0; i<int(best_path.get_ord().size()); i++){
            pout <<  scientific << cities[best_path.get_ord(i)].get_x() << "  " << scientific << cities[best_path.get_ord(i)].get_y() <<  endl;
        }
    }
    else cerr << "Errore: impossibile aprire bestpath.dat" << endl;

    rand.SaveSeed();





    bout.close();
    bhout.close();
    pout.close();

*/


    return 0;
}