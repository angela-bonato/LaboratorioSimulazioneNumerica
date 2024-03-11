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
