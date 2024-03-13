#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../libGen.h"
#include "../RandomGenerator/random.h"

using namespace std;

//valuta la funzione integranda nel punto dato come argomento
double EvIntegrand(double x);
//valuta la distribuzione usata per l'importance sampling nel punto dato dall'argomento
double EvDensity(double x);
//accept and reject per importance sampling
double arImpSampling(Random& rand);
//calcolo dell'integrale dato usando sia uniform che importance sampling
void DataInteg(int N, int L, ofstream& usout, ofstream& isout);

//genero la direzione in cui spostarmi (x, y, z = 0, 1, 2)
int DirectionDice(Random& rand);
//genero dove spostarmi (avanti, indietro = -1, +1)
int StepDice(Random& rand);
//genera uno spostamento per il rw continuo
void SphericalDice(Random& rand, vector<float>& pos, float A);
//calocola la distanza fra quel punto e l'origine
double ComputeDist(vector<float> pos);
//calcolo delle posizioni del random walker nel discreto
void DataRw(int N, int L, int S, float A, ofstream& drwout, ofstream& crwout);