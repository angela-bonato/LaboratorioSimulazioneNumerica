#include "lib3.h"

using namespace std;

double EvSdirect(Random& rand, double S0, float r, float sigma, float t){
    double w=rand.Gauss(0, t);
    return S0*exp((r-(1./2.)*(sigma*sigma))*t+(sigma*w));
}

void DataDirect(int N, int L, int k, int S0, float sigma, float r, float T, ofstream& dircout, ofstream& dirpout){
    /*Inizializzazione del generatore di numeri casuali*/
    Random rand;
    InizRandom(rand);

    /*costo call*/
    vector<double> cvaluebs(2, 0.);  /*alla i-esima iterazione, valor medio cumulativo dei primi i blocchi e suo quadrato*/
    vector<double> csumbs(2, 0.);  /*alla i-esima iterazione, somma dei valori medi dei primi i blocchi e dei quadrati*/

    /*costo put*/
    vector<double> pvaluebs(2, 0.);
    vector<double> psumbs(2, 0.); 

    for(int i=0; i<N; i++){     /*ciclo sui blocchi*/
        double cvalue=0;    /*costo call*/
        double pvalue=0;    /*costo put*/
        for(int j=0; j<L; j++){
            double S=EvSdirect(rand, S0, r, sigma, T);  /*calolo direttamente S(T)*/
            cvalue+=exp(-r*T)*max(0., (S-k));
            pvalue+=exp(-r*T)*max(0., (k-S));
        }

        cvalue/=L;  /*valor medio nell'i-esimo blocco*/
        BlockMean(cvalue, csumbs, cvaluebs, i);     /*calolo media a blocchi*/
        if(dircout.is_open()){
            dircout << cvaluebs[0] << " " << BlockError(cvaluebs, i) << endl;  /*uso BlockError per calcolare la barra d'errore con il metodo a blocchi*/
        } 
        else cerr << "Errore: impossibile aprire directcall.dat" << endl;

        pvalue/=L;
        BlockMean(pvalue, psumbs, pvaluebs, i);     /*calolo media a blocchi*/
        if(dirpout.is_open()){
            dirpout << pvaluebs[0] << " " << BlockError(pvaluebs, i) << endl;  /*uso BlockError per calcolare la barra d'errore con il metodo a blocchi*/
        } 
        else cerr << "Errore: impossibile aprire directput.dat" << endl;
    }

    rand.SaveSeed();
}

double EvSdiscrete(Random& rand, double St, float r, float sigma, float t, float tnext){
    double z=rand.Gauss(0, 1);
    return St*exp((r-(1./2.)*(sigma*sigma))*(tnext-t)+(sigma*z*sqrt(tnext-t)));
}

void DataDiscrete(int N, int L, int k, int S0, int nt, float sigma, float r, float T, ofstream& discout, ofstream& dispout){
    /*Inizializzazione del generatore di numeri casuali*/
    Random rand;
    InizRandom(rand);

    /*costo call*/
    vector<double> cvaluebs(2, 0.);  /*alla i-esima iterazione, valor medio cumulativo dei primi i blocchi e suo quadrato*/
    vector<double> csumbs(2, 0.);  /*alla i-esima iterazione, somma dei valori medi dei primi i blocchi e dei quadrati*/

    /*costo put*/
    vector<double> pvaluebs(2, 0.);
    vector<double> psumbs(2, 0.); 

    for(int i=0; i<N; i++){     /*ciclo sui blocchi*/
        double cvalue=0;    /*costo call*/
        double pvalue=0;    /*costo put*/
        for(int j=0; j<L; j++){
            double S=S0;    /*inizializzo al tempo 0*/
            float it=T/nt;     /*intervallo di tempo fra un saltino e l'altro*/
            for(int k=1; k<=nt; k++){
                S=EvSdiscrete(rand, S, r, sigma, (k-1)*it, k*it);      /*alla fine del ciclo avrò S(T)*/
            }
            cvalue+=exp(-r*T)*max(0., (S-k));
            pvalue+=exp(-r*T)*max(0., (k-S));
        }

        cvalue/=L;  /*valor medio nell'i-esimo blocco*/
        BlockMean(cvalue, csumbs, cvaluebs, i);     /*calolo media a blocchi*/
        if(discout.is_open()){
            discout << cvaluebs[0] << " " << BlockError(cvaluebs, i) << endl;  /*uso BlockError per calcolare la barra d'errore con il metodo a blocchi*/
        } 
        else cerr << "Errore: impossibile aprire discretecall.dat" << endl;

        pvalue/=L;
        BlockMean(pvalue, psumbs, pvaluebs, i);     /*calolo media a blocchi*/
        if(dispout.is_open()){
            dispout << pvaluebs[0] << " " << BlockError(pvaluebs, i) << endl;  /*uso BlockError per calcolare la barra d'errore con il metodo a blocchi*/
        } 
        else cerr << "Errore: impossibile aprire directput.dat" << endl;
    }

    rand.SaveSeed();
}