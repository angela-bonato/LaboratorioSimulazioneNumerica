#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "../libGen.h"
#include "../RandomGenerator/random.h"

using namespace std;

//struct che serve per l'accettazione, membro double dice alpha di accettazione, membro bool dice accettato o no il punto
struct Acc{
    bool accept;
    double alpha;
};

//genera lo step successivo al punto dato con probabilità di transizione uniforme
double GenerateStep(Random& rand, double x, double delta);
//valuta la densità di probabilità target nel punto dato
double TargetDistribution(double x, double mu, double sigma);
//calcola il valore dell'energia locale nel punto x generato con Metropolis
double LocalEnergy(double x, double mu, double sigma);

//valuta l'accettazione, data dal minimo fra 1 e il rapporto fra TargetDistribution del passo precedente e del punto candidato per il passo presente (che sono i due argomenti della funzione), poi decide se accettare (true) o rifiutare (false) il punto proposto da GenerateStep
void Acceptance(Random& rand, Acc& a, double prec, double pres);
//genera un punto in R secondo Metropolis prendendo in ingresso il punto precedente
double MetropolisStep(Random& rand, double prec, Acc& a, double delta, double mu, double sigma, double& tarprec);

//fa un po' di passi del metropolis e valuta l'accettazione, utile a capire se la delta impostata è corretta e a dare il punto di partenza per l'analisi
double Equilibration(double start, int A, double delta, double mu, double sigma);
//fa effettivamente l'analisi dati dell'esercizio 8.1 (Variational Monte Carlo con parametri fissi)
void EnergyAnalysis(double start, int N, int L, double delta, double mu, double sigma, ofstream& xout, ofstream& eout);