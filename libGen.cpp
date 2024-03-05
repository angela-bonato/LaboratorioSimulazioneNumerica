#include "libGen.h"

using namespace std;

void InizRandom(Random rnd){
    int seed[4];
    int p1, p2;
    ifstream Primes("../RandomGenerator/Primes");
    if (Primes.is_open()){
        Primes >> p1 >> p2 ;
    } 
    else cerr << "PROBLEM: Unable to open Primes" << endl;
    Primes.close();

    ifstream input("../RandomGenerator/seed.in");
    string property;
    if (input.is_open()){
        while ( !input.eof() ){
            input >> property;
            if( property == "RANDOMSEED" ){
                input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
                rnd.SetRandom(seed,p1,p2);
            }
        }
        input.close();
    } 
    else cerr << "PROBLEM: Unable to open seed.in" << endl;
}