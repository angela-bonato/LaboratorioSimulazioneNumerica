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

//struct che serve per immagazzinare un passo di Metropolis2
struct MS2{
    double mu;  /*valore di mu corrente (candidato o accettato)*/
    double sigma;      /*valore di sigma (candidato o accettato)*/
    double hmean;      /*<H>_T al passo presente*/
    double herror;      /*errore di hmean*/
    bool stop;  /*=true se la precisione del Metropolis è tc posso fermarla*/
};

//valuta la densità di probabilità target nel punto dato, calcolata come il modulo quadro di psi normalizzato
double PsiSqNorm(double x, double mu, double sigma);
//calcola il valore dell'energia locale nel punto x generato con Metropolis
double LocalEnergy(double x, double mu, double sigma);
//funzione di accettazione del Metropolis che usa come target il peso di Boltzmann, h_1 è l'energia al passo precedente mentre h_2 è quella del nuovo punto
double BoltzWeight(double beta, double h_1, double h_2);

//genera lo step successivo al punto dato con probabilità di transizione uniforme
double GenerateStep(Random& rand, double x, double delta);
//valuta l'accettazione, data dal minimo fra 1 e il rapporto fra TargetDistribution del passo precedente e del punto candidato per il passo presente (che sono i due argomenti della funzione), poi decide se accettare (true) o rifiutare (false) il punto proposto da GenerateStep
void Acceptance(Random& rand, Acc& a, double prec, double pres);
//genera un punto in R secondo Metropolis prendendo in ingresso il punto precedente, ha PsiSqNorm come densità di probabilità target
double MetropolisStep1(Random& rand, double prec, Acc& a, double delta, double mu, double sigma, double& tarprec);

//controlla quali parametri minimizzano l'energia
void BestVaal(vector<double>& best_params, MS2 pres);
//esegue un ciclo con il MetropolisStep1 dando in output (scrivendo su pres) valor medio e errore a blocchi di <H>_T utile a valutare l'accettazione di MetropolisStep2
void EvalH(Random& rand, MS2& pres, double delta);
//genera un punto in R^2 secondo Metropolis prendendo in ingresso il punto precedente, ha il peso di Boltzman come densità di probabilità target
MS2 MetropolisStep2(Random& rand, MS2 prec, Acc& a, double delta, double beta);

//fa un po' di passi del metropolis e valuta l'accettazione, utile a capire se la delta impostata è corretta e a dare il punto di partenza per l'analisi
double Equilibration(double start, int A, double delta, double mu, double sigma);
//fa effettivamente l'analisi dati dell'esercizio 8.1 (Variational Monte Carlo con parametri fissi)
void EnergyAnalysis(double start, int N, int L, double delta, double mu, double sigma, ofstream& xout, ofstream& eout);

//scrive l'intestazione dei files di output (sono troppi...)
void InitFiles(ofstream& pout, ofstream& bout, ofstream& hout, ofstream& finxout, ofstream& fineout);
//esegue l'esercizio 8.2 (simulated annealing) 
void SimAnnealing(double delta, double mu_start, double sigma_start, double beta_min, double beta_max, double beta_step, ofstream& pout, ofstream& bout, ofstream& hout, ofstream& finxout, ofstream& fineout);