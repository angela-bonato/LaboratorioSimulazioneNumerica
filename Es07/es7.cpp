#include <iostream>
#include "SOURCE/system.h"
#include "lib7.h"

using namespace std;

/*Codice modificato in modo che, a SIMULATION TYPE J H fissati, vengano analizzate e simulate tutte le grandezze richieste.
Per fare ciò, ho definito nuovi metodi e anche modificato il modo in cui average stampa su files i risultati dell'analisi.*/

int main (int argc, char *argv[]){

    System syst;
    syst.initialize();
    syst.block_reset(0);

    //Esercizio 7.2
    //Equilibrazione
    syst.set_PotProperties();    //per l'esercizio misuro solo energia potenziale ergo inizializzo a mano le proprietà
    syst.set_SymDuration(1, 600);   //lunghezza equilibrazione, il numero dei blocchi non mi interessa tanto guardo misure istantanee
    ofstream eqout; 
    eqout.open("OUTPUT/eq_penergy.dat");  //file dove metto i dati per l'analisi
    InstEnergy(syst, eqout);    //ciclo di equilibrazione, eventualmente con raccolta dati per plot
    eqout.close();
    cout << "Equilibrazione per esercizio 7.2 conclusa." << endl;
    
    /*
    syst.set_SymDuration(1, 500000);   //lunghezza analisi, il numero dei blocchi non mi interessa tanto guardo misure istantanee
    ofstream anout; 
    anout.open("OUTPUT/inst_penergy.dat");  //file dove metto i dati per l'analisi
    InstEnergy(syst, anout);
    anout.close();
    cout << "Analisi per esercizio 7.2 conclusa." << endl;

    */

    //Esercizio 7.4
    //Attenzione: va bene farlo in una parte diversa del codice? vanno bene i blocchi gestiti così? va bene fare pochi step o ne devo fare 5*10^5?
    syst.initialize_properties();   /*ora devo simulare tutto*/
    syst.set_SimType(0);    /*simulazione dinamica molecolare*/
    syst.set_SymDuration(20, 2000);
    GofrAnalysis(syst);
    cout << "Analisi gofr con SimType=0 conclusa." << endl;
    syst.set_SimType(1);    /*simulazione monte carlo*/
    GofrAnalysis(syst);
    cout << "Analisi gofr con SimType=1 conclusa." << endl;

    syst.finalize();

    return 0;
}
