#include "SOURCE/system.h"

using namespace std;

//Funzione per esercizio 7.2, essenzialmente plotta misure istantanee di energia potenziale
void InstEnergy(System& syst, ofstream& out);

// Funzione che esegue il ciclo di analisi del sistema misurando le proprietà richieste nel file properties.dat
void GofrAnalysis(System& syst); 