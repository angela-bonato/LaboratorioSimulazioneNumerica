#include "lib8.h"
#include "../RandomGenerator/random.h"
#include "../libGen.h"

using namespace std;
 
int main (int argc, char *argv[]){

    int M=100000;   /*numero totale di passi*/
    int N=100;  /*numero di blocchi*/
    int L=M/N;  /*numero di passi per ogni blocco*/
    int A=5000;    /*numero passi per l'equilibrazione*/
    double start=0.;    /*punto di parteza del sampling*/
    double delta;   /*parametro che regola la larghezza di ogni passo, settato tc l'accettazione media sia circa 0.5*/
    double mu, sigma; /*parametri di psi*/

    /*Esercizio 8.1*/
    cout << "Inizio esercizio 8.1." << endl;
    delta=3.5; //DA CAMBIAREE
    mu=1.; //DA CAMBIAREE
    sigma=0.2; //DA CAMBIAREE
    start=1.; /*parto in un punto a caso (?) per l'equilibrazione*/
    start=Equilibration(start, A, delta, mu, sigma);   /*aggiorno la partenza dell'analisi dati*/
    ofstream eout; /*file con i dati a blocchi di energia locale*/
    ofstream xout; /*file con alcuni valori di x generati*/
    eout.open("locenergy.dat");
    xout.open("genpoints.dat");
    EnergyAnalysis(start, N, L, delta, mu, sigma, xout, eout);  /*racchiudo tutto il calcolo in una funzione apposita*/
    eout.close();
    xout.close();
    cout << "Conclusione esercizio 8.1." << endl;

    return 0;
}