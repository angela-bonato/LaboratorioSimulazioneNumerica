#include "lib7.h"

using namespace std;

void InstEnergy(System& syst, ofstream& out){
    for(int i=0; i < syst.get_nbl(); i++){ //loop over blocks
        for(int j=0; j < syst.get_nsteps(); j++){ //loop over steps in a block
            syst.step();
            syst.measure();
            out << scientific << syst.get_EnMeasure(1) << endl;   //flag=1 è energia potenziale
            if(j%10000==0) cout << j << endl;
        }
        syst.block_reset(i+1);
    }
    syst.block_reset(0);
}


void GofrAnalysis(System& syst){
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
