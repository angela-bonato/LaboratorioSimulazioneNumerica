#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <vector>
#include "RandomGenerator/random.h"

using namespace std;

void InizRandom(Random&);    /*funzione che inizializza il generatore di numeri casuali di Galli*/
double Rarandom();   /*generatore alternativo*/

void BlockMean(double, vector<double>&, vector<double>&, int);    /*aggiorna il calcolo della media a blocchi*/
double BlockError(vector<double>&, int);    /*calcolo dell'errore sulla media a blocchi*/