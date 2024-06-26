#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <fstream>
#include <string>
#include <sstream>
#include "city.h"
#include "path.h"
#include "../libGen.h"
#include "../RandomGenerator/random.h"

using namespace std;

//leggo solo la riga i di un file
bool ReadIthLine(ifstream& inprimes, int i, int& p1, int& p2);

//funzione che ritorna un vettore di città con posizioni nel file di input
vector<City> InitCities(ifstream& infile);

//scambia fra loro gli elementi in posizione a e b di path._order
void Swap(Path& path, int a, int b);
//inizializza una popolazione di path randomici
vector<Path> InitRandomPop(Random& rand, int N, int P);

//operatore di crossover come descritto nel notebook del prof
void CrossoverOperator(Random& rand, Path p1, Path p2, Path& s1, Path& s2, double pc);
//operatore di mutazione con le 4 mutazioni descritte nel notebook del prof
void MutationOperator(Random& rand, Path& path, double pm1, double pm2, double pm3, double pm4);

//dà regola a sort per ordinare
bool ComparePaths(Path a, Path b);
//funzione che scrive nei files di output tutti i dati richiesti
void WriteBest(vector<Path> population, int s, ofstream& bout, ofstream& bhout);
//operatore di selezione, fa già tutte le operazioni necessarie per restituire la nuova popolazione
vector<Path> ReplaceGeneration(Random& rand, vector<Path> old_population, vector<City> cities, int N, double pc, double pm1, double pm2, double pm3, double pm4, int s, ofstream& bout, ofstream& bhout, Path& best_path);
