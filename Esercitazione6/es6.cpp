#include <iostream>
#include "SOURCE/system.h"

using namespace std;

int main (int argc, char *argv[]){

    int Nconf = 1;
    System syst;
    syst.initialize();
    syst.initialize_properties();
    syst.block_reset(0);

    // Equilibrazione non necessaria ogni volta
    /*ofstream eqenpout; 
    eqenpout.open("OUTPUT/eqtenergy.dat");*/ 

    for(int i=0; i < syst.get_nbl(); i++){ //loop over blocks
        for(int j=0; j < syst.get_nsteps(); j++){ //loop over steps in a block
            syst.step();
            syst.measure();

            //eqenpout << scientific << syst.get_EnMeasure() << endl;

            if(j%10 == 0){
            Nconf++;
            }
        }
        syst.averages(i+1);
        syst.block_reset(i+1);
    }
    syst.finalize();

    return 0;
}