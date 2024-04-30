#include "SOURCE/system.h"

using namespace std;

// Funzione che esegue il ciclo di equilibrazione del sistema misurando l'energia totale del sistema, flag p serve a capire se registrare o no i dati di equilibrazione per il relativo plot
void Equilibration(System& syst, bool p);
// Funzione che esegue il ciclo di analisi del sistema misurando le proprietà richieste nel file properties.dat
void Analysis(System& syst); 