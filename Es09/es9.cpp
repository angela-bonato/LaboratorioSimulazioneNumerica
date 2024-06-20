#include "lib9.h"

using namespace std;

int main (int argc, char *argv[]){
    //variabili generali
    int Ncities=34; //numero città considerate
    int Npaths=900;  //numero path per ogni generazione DEVONO ESSERE PARI
    int Nsteps=200;    //numero generazioni considerate
    double pc=0.6;  //probabilità di crossover
    double pm1=0.07; //probabilità prima mutazione
    double pm2=0.06; //probabilità seconda mutazione
    double pm3=0.05; //probabilità terza mutazione
    double pm4=0.04; //probabilità quarta mutazione
    ofstream bout;  //output loss del best path di ogni generazione
    ofstream bhout;  //output loss media dei primi N/2 best path di ogni generazione
    ofstream pout;  //output miglior percorso in assoluto

    //problema commesso viaggiatore con città su una circonferenza
    cout << "Inizio analisi città circolari" << endl;
    vector<City> CircCities=InitCircularCities(Ncities);
    bout.open("cbestloss.dat");
    bhout.open("cbesthalfloss.dat");
    pout.open("cbestpath.dat");
    TravSalesProb(CircCities, Ncities, Npaths, Nsteps, pc, pm1, pm2, pm3, pm4, bout, bhout, pout);
    bout.close();
    bhout.close();
    pout.close();

    //problema commesso viaggiatore con città in un quadrato
    cout << "Inizio analisi città quadrate" << endl;
    Nsteps=400;  //meno banale, servono più generazioni
    vector<City> SqCities=InitSquareCities(Ncities);
    bout.open("sbestloss.dat");
    bhout.open("sbesthalfloss.dat");
    pout.open("sbestpath.dat");
    TravSalesProb(SqCities, Ncities, Npaths, Nsteps, pc, pm1, pm2, pm3, pm4, bout, bhout, pout);
    bout.close();
    bhout.close();
    pout.close();

    cout << "Fine analisi" << endl;
    return 0;
}