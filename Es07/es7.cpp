#include <iostream>
#include "SOURCE/system.h"
#include "lib7.h"

using namespace std;

/*Volevo fare tutto in un main ma cambiando dimtype deve ripartire tutto quindi tanto vale modificare l'input direttamente e far girare di nuovo il programma. 
Manca da capire come gestire le 5*1e5 simulazioni di energia potenziale rispetto alla parte dell'esercizio relativa alla gofr, per ora faccio le due cose staccate commentando l'una o l'altra parte, ma va rivisto anche in base a quanti blocchi vanno usati per gofr.*/

int main (int argc, char *argv[]){

    System syst;
    syst.initialize();
    syst.block_reset(0);

    //Esercizio 7.2
    //Equilibrazione
    syst.set_EqProperties();    //inizializzo a mano le proprietà, con simtype=1 è energia potenziale mentre con simtype=0 è temperatura
    syst.set_SymDuration(20, 2000);   //lunghezza equilibrazione, il numero dei blocchi non mi interessa tanto guardo misure istantanee
    ofstream eqout; 
    eqout.open("OUTPUT/eq_penergy.dat");  //file dove metto i dati per l'analisi
    InstEnergy(syst, eqout);    //ciclo di equilibrazione, eventualmente con raccolta dati per plot
    eqout.close();
    cout << "Equilibrazione conclusa." << endl;

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
    syst.initialize_properties();   //ora devo simulare tutto
    syst.set_SymDuration(50, 2000);
    GofrAnalysis(syst);
    cout << "Analisi per esercizio 7.4 conclusa." << endl;

    syst.finalize();

    return 0;
}
