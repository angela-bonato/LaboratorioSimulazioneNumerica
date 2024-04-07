#include "lib5.h"
#include "../RandomGenerator/random.h"
#include "../libGen.h"

using namespace std;
 
int main (int argc, char *argv[]){

    int M=1000000;   /*numero totale di passi*/
    int N=100;  /*numero di blocchi*/
    int L=M/N;  /*numero di passi per ogni blocco*/
    int p;    /*flag per settare la distribuzione target (1=psi100, 2=psi2100)*/
    int t;    /*flag per settare la distribuzione per gli step (0=uniforme, 3=gaussiana)*/
    vector<double> start(3, 0.);    /*punto di parteza del sampling*/
    double delta;   /*parametro che regola la larghezza di ogni passo, settato tc l'accettazione media sia circa 0.5*/

    /*Sample con probabilità di step uniforme su psi100*/
    cout << "Inizio analisi dedicata a psi100 con step uniforme." << endl;
    p=1;
    t=0;
    start[0]=3./2.; /*faccio in modo di partire nei pressi del valore atteso*/
    delta=0.9;
    CheckMeanAcceptance(start, p, t, delta);
    ofstream u1pout; /*file con le coordinate di ogni posizione*/
    ofstream u1rout; /*file con i dati a blocchi di r*/
    u1pout.open("unif1pos.dat");
    u1rout.open("unif1rad.dat");
    DataAnalysis(start, N, L, p, t, delta, u1pout, u1rout);  /*racchiudo tutto il calcolo in una funzione apposita*/
    u1pout.close();
    u1rout.close();
    cout << "Conclusione analisi dedicata a psi100 con step uniforme." << endl;

    /*Sample con probabilità di step gaussiana su psi100*/
    cout << "Inizio analisi dedicata a psi100 con step gaussiano." << endl;
    t=3;
    delta=0.5;
    CheckMeanAcceptance(start, p, t, delta);
    ofstream g1pout; /*file con le coordinate di ogni posizione*/
    ofstream g1rout; /*file con i dati a blocchi di r*/
    g1pout.open("gaus1pos.dat");
    g1rout.open("gaus1rad.dat");
    DataAnalysis(start, N, L, p, t, delta, g1pout, g1rout);  /*racchiudo tutto il calcolo in una funzione apposita*/
    g1pout.close();
    g1rout.close();
    cout << "Conclusione analisi dedicata a psi100 con step gaussiano." << endl;

    /*Sample con probabilità di step uniforme su psi210*/
    cout << "Inizio analisi dedicata a psi210 con step uniforme." << endl;
    p=2;
    t=0;
    delta=3.5;
    CheckMeanAcceptance(start, p, t, delta);
    start[0]=5.;
    ofstream u2pout; /*file con le coordinate di ogni posizione*/
    ofstream u2rout; /*file con i dati a blocchi di r*/
    u2pout.open("unif2pos.dat");
    u2rout.open("unif2rad.dat");
    DataAnalysis(start, N, L, p, t, delta, u2pout, u2rout);  /*racchiudo tutto il calcolo in una funzione apposita*/
    u2pout.close();
    u2rout.close();
    cout << "Conclusione analisi dedicata a psi210 con step uniforme." << endl;

    /*Sample con probabilità di step gaussiana su psi210*/
    cout << "Inizio analisi dedicata a psi210 con step gaussiano." << endl;
    t=3;
    delta=2.;
    CheckMeanAcceptance(start, p, t, delta);
    ofstream g2pout; /*file con le coordinate di ogni posizione*/
    ofstream g2rout; /*file con i dati a blocchi di r*/
    g2pout.open("gaus2pos.dat");
    g2rout.open("gaus2rad.dat");
    DataAnalysis(start, N, L, p, t, delta, g2pout, g2rout);  /*racchiudo tutto il calcolo in una funzione apposita*/
    g2pout.close();
    g2rout.close();
    cout << "Conclusione analisi dedicata a psi210 con step gaussiano." << endl;

    return 0;
}