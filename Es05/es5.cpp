#include "lib5.h"
#include "../RandomGenerator/random.h"
#include "../libGen.h"

using namespace std;
 
int main (int argc, char *argv[]){

    int M=1000000;   /*numero totale di passi*/
    int N=100;  /*numero di blocchi*/
    int L=M/N;  /*numero di passi per ogni blocco*/
    int A=5000;    /*numero passi per l'equilibrazione*/
    int p;    /*flag per settare la distribuzione target (1=psi100, 2=psi2100)*/
    int t;    /*flag per settare la probabilità di transizione per gli step (0=uniforme, 3=gaussiana)*/
    vector<double> start(3, 0.);    /*punto di parteza del sampling*/
    double delta;   /*parametro che regola la larghezza di ogni passo, settato tc l'accettazione media sia circa 0.5*/

    /*Sample con probabilità di step uniforme su psi100*/
    cout << "Inizio analisi dedicata a psi100 con step uniforme." << endl;
    p=1;
    t=0;
    delta=1.2;
    start[0]=100; /*parto in un punto a caso (?) per l'equilibrazione*/
    ofstream u1eout; /*file con i dati a blocchi di r*/
    ofstream u1epout;
    u1eout.open("unif1eq.dat");
    u1epout.open("unif1eqpos.dat");
    start=Equilibration(start, p, t, A, delta, u1eout, u1epout);   /*aggiorno la partenza dell'analisi dati*/
    u1eout.close();
    u1epout.close();
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
    delta=0.7;
    start[0]=100; /*parto in un punto a caso (?) per l'equilibrazione*/
    ofstream g1eout; /*file con i dati a blocchi di r*/
    ofstream g1epout;
    g1eout.open("gaus1eq.dat");
    g1epout.open("gaus1eqpos.dat");
    start=Equilibration(start, p, t, A, delta, g1eout, g1epout);   /*aggiorno la partenza dell'analisi dati*/
    g1eout.close();
    g1epout.close();
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
    delta=3.;
    start[0]=100; /*parto in un punto a caso (?) per l'equilibrazione*/
    ofstream u2eout; /*file con i dati a blocchi di r*/
    ofstream u2epout;
    u2eout.open("unif2eq.dat");
    u2epout.open("unif2eqpos.dat");
    start=Equilibration(start, p, t, A, delta, u2eout, u2epout);   /*aggiorno la partenza dell'analisi dati*/
    u2eout.close();
    u2epout.close();
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
    start[0]=100; /*parto in un punto a caso (?) per l'equilibrazione*/
    ofstream g2eout; /*file con i dati a blocchi di r*/
    ofstream g2epout;
    g2eout.open("gaus2eq.dat");
    g2epout.open("gaus2eqpos.dat");
    start=Equilibration(start, p, t, A, delta, g2eout, g2epout);   /*aggiorno la partenza dell'analisi dati*/
    g2eout.close();
    g2epout.close();
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