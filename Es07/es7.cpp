#include <iostream>
#include "SOURCE/system.h"
#include "lib7.h"

using namespace std;

/*
Il programma, in base all'input char dell'utente da linea di comando, esegue sempre l'equilibrazione e poi o 
l'analisi istantanea per la parte dell'esercizio sul data blocking ('b'), oppure tutta la parte sulla
gofr ('g'). Attenzione che, mentre le proprietà le gestisce il programma anche cambiando il tipo di simulazione,
la durata dell'equilibrazione può cambiare in base allo stato analizzato e al tipo di simulazione. 
Il tipo di simulazione va gestito dal file input.dat .
*/
int main (int argc, char *argv[]){

    // Verifico che sia stato passato almeno un parametro
    if(argc < 2) {
        cerr << "Errore: per l'ultilizzo digita " << argv[0] << " <parametro_char>" << std::endl;
        return 1; 
    }

    // Leggi il parametro passato dall'utente che definisce il tipo di analisi
    char param=argv[1][0];
    if (param != 'b' && param != 'g'){
        cerr << "Errore: il <parametro_char> inserito può essere b oppure g." << std::endl;
        return 1; 
    }

    System syst;
    syst.initialize();
    syst.block_reset(0);

    //Equilibrazione
    syst.set_EqProperties();    //inizializzo a mano le proprietà, con simtype=1 è energia potenziale mentre con simtype=0 è temperatura
    syst.set_SymDuration(6, 100);   //lunghezza equilibrazione, il numero dei blocchi non mi interessa tanto guardo misure istantanee
    ofstream eqout; 
    eqout.open("OUTPUT/eq_penergy.dat");  //file dove metto i dati per l'analisi
    InstEnergy(syst, eqout);    //ciclo di equilibrazione, eventualmente con raccolta dati per plot
    eqout.close();
    cout << "Equilibrazione conclusa." << endl;

    if(param == 'b'){
        //Esercizio 7.2
        syst.set_SymDuration(1, 500000);   //lunghezza analisi, il numero dei blocchi non mi interessa tanto guardo misure istantanee
        ofstream anout; 
        anout.open("OUTPUT/inst_penergy.dat");  //file dove metto i dati per l'analisi
        InstEnergy(syst, anout);
        anout.close();
        cout << "Analisi per esercizio 7.2 conclusa." << endl;
    }

    if(param == 'g'){
        //Esercizio 7.4
        syst.initialize_properties();   //ora devo simulare tutto
        syst.set_SymDuration(50, 200);
        GofrAnalysis(syst);
        cout << "Analisi per esercizio 7.4 conclusa." << endl;
    }

    syst.finalize();

    return 0;
}
