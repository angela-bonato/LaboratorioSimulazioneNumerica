#include <iostream>
#include "SOURCE/system.h"
#include "lib6.h"

using namespace std;

/*Codice modificato in modo che, a SIMULATION TYPE J H fissati, vengano analizzate e simulate tutte le grandezze richieste.
Per fare ciò, ho definito nuovi metodi e anche modificato il modo in cui average stampa su files i risultati dell'analisi.*/

int main (int argc, char *argv[]){

    System syst;
    syst.initialize();  /*nel file di input metto prima temperatura da guardare (la più alta)*/
    syst.block_reset(0);

    bool p=true;   /*flag che se==true fa sì che si salvino i dati necessari a fare il plot della fase di equilibrazione*/

    while(syst.get_Temp()>=0.5){    /*ciclo sulle temperature da simulare che vanno da 2 a 0.5 a passo 0.15*/

        Equilibration(syst, p);    /*ciclo di equilibrazione, eventualmente con raccolta dati per plot*/
        cout << "Equilibrazione per T=" << syst.get_Temp() << " conclusa." << endl;

        Analysis(syst);     /*ciclo di analisi*/
        cout << "Analisi per T=" << syst.get_Temp() << " conclusa." << endl;

        syst.set_Temp(syst.get_Temp() - 0.15);   /*aumento di un passo la temperatura del sistema e ripeto tutto*/
    }

    syst.finalize();

    return 0;
}
