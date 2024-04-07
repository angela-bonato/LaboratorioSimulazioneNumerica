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

//genera lo step successivo al punto dato, riceve in ingresso anche una flag che gli dice quale probabilità usare (se uniforme=0 o gaussiana=3) e la larghezza di questa probabilità
vector<double> GenerateStep(Random& rand, vector<double> pos, int t, double delta);
//data una posizione cartesiana calcola il raggio delle coordinate sferiche
double EvaluateRadius(vector<double> pos);
//valuta la densità di probabilità target nel punto dato, riceve in ingresso anche una flag che gli dice quale funzione usare (se psi100=1 o psi210=2)
double TargetDistribution(vector<double> pos, int p);
//valuta l'accettazione, data dal minimo fra 1 e il rapporto fra TargetDistribution del passo precedente e del punto candidato per il passo presente (che sono i due argomenti della funzione), poi decide se accettare (true) o rifiutare (false) il punto proposto da GenerateStep
void Acceptance(Random& rand, Acc& a, double prec, double pres);
//genera un punto in R^3 secondo Metropolis prendendo in ingresso il punto precedente, una flag che indica la probabilità target, una flag che indica la probabilità secodno cui accetto gli step, un parametro per la distribuzione step, un double che tiene in memoria TargetDistribution calcolata al punto precedente
vector<double> MetropolisStep(Random& rand, vector<double> prec, int p, int t, Acc& d, double delta, double& tarprec);

//fa un po' di passi del metropolis e valuta l'accettazione media, utile a capire se la delta impostata è corretta
void CheckMeanAcceptance(vector<double> start, int p, int t, double delta);
//stampa le posizioni su file
void PrintPosition(vector<double> pos, ofstream& out);
//fa effettivamente l'analisi dati
void DataAnalysis(vector<double> start, int N, int L, int p, int t, double delta, ofstream& u1pout, ofstream& u1rout);