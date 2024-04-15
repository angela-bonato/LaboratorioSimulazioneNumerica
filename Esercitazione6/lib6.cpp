#include "lib6.h"

using namespace std;

void Equilibration(System& syst, bool p){
    syst.set_EqProperties();    /*per l'equilibrazione del sistema misuro solo energia tot ergo inizializzo a mano le proprietà*/
    syst.set_SymDuration(1, 150);    /*setto dimensioni blocchi per l'equilibrazione, 150 senza campo e 650 con dovrebbe bastare*/

    ofstream eqenout; 
    eqenout.open("OUTPUT/eqtenergy.dat");  /*file dove metto i dati per plottare l'equilibrazione se p==true*/

    // Ciclo praticamente a vuoto per equilibrare
    for(int i=0; i < syst.get_nbl(); i++){ //loop over blocks
        for(int j=0; j < syst.get_nsteps(); j++){ //loop over steps in a block
            
            syst.step();
            syst.measure();
            
            if(p){
                eqenout << scientific << syst.get_EnMeasure() << endl;
            }  
        }
        syst.block_reset(i+1);
    }
    syst.block_reset(0);
}


void Analysis(System& syst){
    syst.initialize_properties();   /*qua inizializzo le proprietà da misurare effettivamente*/
    syst.set_SymDuration(20, 20000);    /*setto dimensioni blocchi per la simulazione*/
    for(int i=0; i < syst.get_nbl(); i++){ //loop over blocks
        for(int j=0; j < syst.get_nsteps(); j++){ //loop over steps in a block
        
            syst.step();
            syst.measure();
        }
        syst.averages(i+1);
        syst.block_reset(i+1);
    }
    syst.block_reset(0);
}