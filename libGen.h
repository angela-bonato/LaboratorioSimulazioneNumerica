#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <vector>
#include "RandomGenerator/random.h"

using namespace std;

//funzione che inizializza il generatore di numeri casuali di Galli
void InizRandom(Random&);
//altro generatore per prove
double Rarandom();

//aggiorna il calcolo della media a blocchi
void BlockMean(double, vector<double>&, vector<double>&, int);
//calcolo dell'errore sulla media a blocchi
double BlockError(vector<double>&, int);