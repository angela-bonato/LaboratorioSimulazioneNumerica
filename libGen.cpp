#include "libGen.h"

using namespace std;

void InizRandom(Random& rnd){
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

double Rarandom(){
    random_device rd;  // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(0., 1.);
    return dis(gen);
}

void BlockMean(double av, vector<double> &sumbs, vector<double> &avbs, int B){
    sumbs[0]+=av;
    sumbs[1]+=av*av;
    avbs[0]=sumbs[0]/(B+1);     /*uso questa funzione in cicli in cui i blocchi partono da indice 0*/
    avbs[1]=sumbs[1]/(B+1);
}

double BlockError(vector<double> &vals, int B){
    if(B==0){   /*il primo blocco ha errore 0*/
        return 0;
    }
    else{
        return sqrt((vals[1]-(vals[0]*vals[0]))/B);   /*barra d'errore sul B-esimo blocco*/
    }
}      

