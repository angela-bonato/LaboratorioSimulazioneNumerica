#include "lib2.h"
#include "../RandomGenerator/random.h"
#include "../libGen.h"

using namespace std;
 
int main (int argc, char *argv[]){

    /*Esercizio 2.1*/
    /*Calcolo dei dati utilizzati per le figure 1 (integrale con sampling uniforme in [0, 1]) e 2 (importance sampling)*/
    int Mint=1000000;   /*numero totale di estrazioni*/
    int Nint=100;  /*numero di blocchi*/
    int Lint=Mint/Nint;  /*numero di estrazioni per ogni blocco*/
    ofstream usout; /*file su cui scriverò i dati per la figura 1*/
    ofstream isout; /*file su cui scriverò i dati per la figura 2*/
    usout.open("unifintegral.dat");
    isout.open("importintegral.dat");
    DataInteg(Nint, Lint, usout, isout);  /*racchiudo tutto il calcolo in una funzione apposita*/
    usout.close();
    isout.close();
    cout << "Parte dedicata all'integrale completata." << endl;

    /*Esercizio 2.2*/
    /*Calcolo dei dati utilizzati per la figure 1 (rw discreto)*/
    int Mrw=10000;   /*numero totale di estrazioni*/
    int Nrw=100;  /*numero di blocchi*/
    int Lrw=Mrw/Nrw;  /*numero di ripetizioni per ogni blocco*/
    int Srw=100;    /*numero di passi che il walker deve effettuare*/
    float Arw=1;  /*larghezza del passo del reticolo discreto*/
    ofstream drwout; /*file su cui scriverò i dati per la figura 1*/
    drwout.open("descreterw.dat");
    DataDRw(Nrw, Lrw, Srw, Arw, drwout);  /*racchiudo tutto il calcolo in una funzione apposita*/
    drwout.close();
    cout << "Parte dedicata al random walk discreto completata." << endl;

    return 0;
}