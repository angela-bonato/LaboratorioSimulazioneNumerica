#include "lib2.h"

using namespace std;

double EvIntegrand(double x){
    return (M_PI/2.)*cos((M_PI*x)/2.);
}

double EvDensity(double x){
    return ((M_PI/3.)-(x*x))*1./((M_PI/3.)-(1./3.));
}

double arImpSampling(Random& rand){
    int i=0;
    double ret=0;
    while(i==0){
        double x=rand.Rannyu(0., 1.);
        double y=rand.Rannyu(0., EvDensity(0.));    /*il punto di max di density in [0, 1] è 0*/
        if(y<EvDensity(x)){
            i=2;
            ret=x;
        }
    }
    return ret;
}

void DataInteg(int N, int L, ofstream& usout, ofstream& isout){
    /*Inizializzazione del generatore di numeri casuali*/
    Random rand;
    InizRandom(rand);

    /*variabili usate per la figura 1 (grafico con sampling uniforme)*/
    vector<double> usintbs(2, 0.);  /*alla i-esima iterazione, valor medio cumulativo dei primi i blocchi e suo quadrato*/
    vector<double> usumbs(2, 0.);  /*alla i-esima iterazione, somma dei valori medi dei primi i blocchi e dei quadrati*/
    /*variabili usate per la figura 2 (grafico con importance sampling)*/
    vector<double> isintbs(2, 0.);  /*alla i-esima iterazione, valor medio cumulativo dei primi i blocchi e suo quadrato*/
    vector<double> isumbs(2, 0.);  /*alla i-esima iterazione, somma dei valori medi dei primi i blocchi e dei quadrati*/

    for(int i=0; i<N; i++){     /*ciclo sui blocchi*/
        double usum=0;   /*somma di f(xj) per l'i-esimo blocco, serve per valutazione con uniform sampling*/
        double isum=0;  /*somma di f(xj)/d(xj) per l'i-esimo blocco, serve per valutazione con importance sampling*/
        for(int j=0; j<L; j++){
            double ur=rand.Rannyu(0., 1.);   /*sampling uniforme*/
            usum+=EvIntegrand(ur);

            double ir=arImpSampling(rand);    /*importance sampling con la d(x) calcolata (e normalizzata) che è 3/2 (1-x^2)*/
            isum+=EvIntegrand(ir)/EvDensity(ir);
        }

        /*stima con uniform sampling*/
        double usintegral=usum/L;    /*stima dell'integrale calolata nell'i-esimo blocco*/
        BlockMean(usintegral, usumbs, usintbs, i);   /*aggiorno la media a blocchi*/
        if(usout.is_open()){
            usout << usintbs[0] << " " << BlockError(usintbs, i) << endl;    /*variabili da plottare*/
        }
        else cerr << "Errore: impossibile aprire unifintegral.dat" << endl;

        /*stima con importance sampling*/
        double isintegral=isum/L;    /*stima dell'integrale calolata nell'i-esimo blocco*/
        BlockMean(isintegral, isumbs, isintbs, i);   /*aggiorno la media a blocchi*/
        if(isout.is_open()){
            isout << isintbs[0] << " " << BlockError(isintbs, i) << endl;    /*variabili da plottare*/
        }
        else cerr << "Errore: impossibile aprire importintegral.dat" << endl;
    }

    rand.SaveSeed();
}

int DirectionDice(Random& rand){
    double r=rand.Rannyu(0., 3.);
    if(0.<=r && r<1.){  /*discretizzo il mio intervallo di generazione in modo da avere 3 possibili risultati*/
        return 0;
    }
    if(1.<=r && r<2.){
        return 1;
    }
    if(2.<=r && r<=3.){
        return 2;
    }
    cerr << "Risultato di DirectionDice invalido." << endl;
    return -1;
}

int StepDice(Random& rand){
    double r=rand.Rannyu(-1., 1.);
    if(-1<=r && r<0.){  /*discretizzo il mio intervallo di generazione in modo da avere 3 possibili risultati*/
        return -1;
    }
    if(0.<=r && r<=1.){
        return 1;
    }
    cerr << "Risultato di StepDice invalido." << endl;
    return -2;
}

void SphericalDice(Random& rand, vector<float>& pos, float A){
    double t=rand.Rannyu(0, M_PI);     /*angolo theta in [0, pi]*/
    double f=rand.Rannyu(0, 2*M_PI);    /*angolo phi in [0, 2pi]*/
    /*aggiorno pos convertendo in cartesiane*/
    pos[0]+=A*sin(t)*cos(f);
    pos[1]+=A*sin(t)*sin(f);
    pos[2]+=A*cos(t);
}

double ComputeDist(vector<float> pos){
    return (pos[0]*pos[0])+(pos[1]*pos[1])+(pos[2]*pos[2]);     /*modulo quadro del vettore da (0,0,0) a pos*/
}

void DataRw(int N, int L, int S, float A, ofstream& drwout, ofstream& crwout){
    /*Inizializzazione del generatore di numeri casuali*/
    Random rand;
    InizRandom(rand);

    vector<double> dsumbs(S, 0.);  /*alla i-esima iterazione, somma dei cammini medi dei primi i blocchi per il rw discreto*/
    vector<double> csumbs(S, 0);    /*corrispettivo per il rw continuo*/

    for(int i=0; i<N; i++){     /*ciclo sui blocchi*/
        vector<double> dmeans(S, 0.);     /*vettore con la media del cammino medio ad ogni passo per l'i-esimo blocco per il rw discreto*/
        vector<double> cmeans(S, 0.);   /*corrispettivo per il rw continuo*/

        for(int j=0; j<L; j++){     /*ripetizioni nel blocco i-esimo*/
            vector<float> dpos(3, 0.);     /*vettore di coordinate della posizione del walker nel discreto, inizializzato a 0 perchè parte dall'origine*/
            vector<float> cpos(3, 0.);     /*coordinate posizione rw continuo*/
            
            for(int n=0; n<S; n++){     /*passi nella j-sima ripetizione dell'i-esimo blocco*/
                dpos[DirectionDice(rand)]+=A*StepDice(rand);
                dmeans[n]+=ComputeDist(dpos);     /*aggiorno la somma al numeratore del cammino medio al n-simo passo*/

                SphericalDice(rand, cpos, A);    /*estraggo la posizione del rw continuo*/
                cmeans[n]+=ComputeDist(cpos);   /*aggiorno la somma*/
            }
        }
        for(int n=0; n<S; n++){
            dsumbs[n]+=dmeans[n]/L;  /*somma dei cammini medi al passo n dopo L iterazioni all'i-esimo blocco*/
            csumbs[n]+=cmeans[n]/L;
        }
    }


    if(drwout.is_open() && crwout.is_open()){
            for(int n=0; n<S; n++){
                vector<double> dvalues={sqrt(dsumbs[n]/N), sqrt(dsumbs[n]/N)*sqrt(dsumbs[n]/N)};    /*calcolo il valore finale*/
                vector<double> cvalues={sqrt(csumbs[n]/N), sqrt(csumbs[n]/N)*sqrt(csumbs[n]/N)};

                drwout << dvalues[0] << " " << BlockError(dvalues, N) << endl;  /*stampo media a blocchi dopo l'ultimo blocco per ogni passo*/
                crwout << cvalues[0] << " " << BlockError(cvalues, N) << endl;  /*stampo media a blocchi dopo l'ultimo blocco per ogni passo*/
            }
        }

//vanno rivisti gli errori

        else cerr << "Errore: impossibile aprire i files di output" << endl;
    rand.SaveSeed();
}