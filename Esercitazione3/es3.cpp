#include "lib3.h"
#include "../RandomGenerator/random.h"
#include "../libGen.h"

using namespace std;
 
int main (int argc, char *argv[]){

    /*Esercizio 3*/
    
    /*variabili comuni a entrambi i sampling*/
    int M=100000;   /*numero totale di estrazioni*/
    int N=100;  /*numero di blocchi*/
    int L=M/N;  /*numero di estrazioni per ogni blocco*/

    int k=100;   /*strike price*/
    int S0=100;  /*prezzo iniziale*/
    float sigma=0.25;  /*volatilità*/
    float r=0.1;   /*tasso d'interesse*/
    float T=1.;     /*tempo finale*/

    /*Calcolo dei dati utilizzati per il sampling diretto*/
    ofstream dircout;
    ofstream dirpout;
    dircout.open("directcall.dat");
    dirpout.open("directput.dat");
    DataDirect(N, L, k, S0, sigma, r, T, dircout, dirpout);  /*racchiudo tutto il calcolo in una funzione apposita*/
    dircout.close();
    dirpout.close();
    cout << "Parte dedicata al sampling diretto completata." << endl;

    /*Calcolo dei dati utilizzati per il sampling diretto*/
    int nt=100;  /*numero di saltellini temporali che uso per andare da 0 a T*/
    ofstream discout;
    ofstream dispout;
    discout.open("discretecall.dat");
    dispout.open("discreteput.dat");
    DataDiscrete(N, L, k, S0, nt, sigma, r, T, discout, dispout);  /*racchiudo tutto il calcolo in una funzione apposita*/
    discout.close();
    dispout.close();
    cout << "Parte dedicata al sampling discreto completata." << endl;

}