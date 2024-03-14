#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include "../libGen.h"
#include "../RandomGenerator/random.h"

using namespace std;

//genera S(t)
double EvSdirect(Random& rand, double S0, float r, float sigma, float t);

//calcolo dei dati ottenuti direttamente
void DataDirect(int N, int L, int k, int S0, float sigma, float r, float T, ofstream& dircout, ofstream& dirpout);

//genera S(t_i+1)
double EvSdiscrete(Random& rand, double St, float r, float sigma, float t, float tnext);
//calcolo dei dati ottenuti tramite piccoli passi discreti
void DataDiscrete(int N, int L, int k, int S0, int nt, float sigma, float r, float T, ofstream& discout, ofstream& dispout);