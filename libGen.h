#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <vector>
#include "RandomGenerator/random.h"

using namespace std;

//funzione che inizializza il generatore di numeri casuali di Galli
void InizRandom(Random& rnd);
//altro generatore per prove
double Rarandom();

//aggiorna il calcolo della media a blocchi
void BlockMean(double av, vector<double> &sumbs, vector<double> &avbs, int B);
//calcolo dell'errore sulla media a blocchi
double BlockError(vector<double> &vals, int B);

//con approccio divide et impera cerca l'indice dell'estremo superiore del sottointervallo in cui si trova il numero estratto esaminando un array con i massimi di tutti gli intervalli
int BinSearchInt(int l, int r, double k, vector<double> &maxs, int M);  

