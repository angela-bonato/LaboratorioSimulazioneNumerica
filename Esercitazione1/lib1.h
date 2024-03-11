#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../libGen.h"
#include "../RandomGenerator/random.h"

using namespace std;

//con approccio divide et impera cerca l'indice dell'estremo superiore del sottointervallo in cui si trova il numero estratto esaminando un array con i massimi di tutti gli intervalli
int BinSearchInt(int l, int r, double k, vector<double> &maxs, int M);  

//calcolo dei dati usati per le figure 1 e 2 dell'esercizio 1.1
void DataAveVar(int N, int L, ofstream& aout, ofstream& vout);  

//cerca il sottointervallo a cui appartiene il numero estratto e aggiorna il conteggio relativo
void SearchInt(int M, double r, vector<double> &maxs, vector<int> &counts);
//calcola il chi quadro
double ChiSqu(int M, int N, vector<int> &counts);
//calcolo dei dati usati per la statistica sul chi quadro  
void DataChiQuad(int M, int N, ofstream& chiout);

//calcolo dei dati usati per l'esercizio 1.2
void DataDistr(int M, vector<int> &Ns, ofstream& uniout, ofstream& eout, ofstream& lorout);

//data la codinata y del punto iniziale dell'ago e il sin dell'angolo di inclinazione e la lunghezza, restituisce la coordinata y dell'estremo finale dell'ago
double EndNeedle(double start, double t, double L);
//true se l'ago interseca una linea
bool TouchLine(double start, double end, vector<double> &maxs, int Nl);
//calcolo dei dati usati per l'esercizio 1.3
void DataBuffon(double L, int D, int B, int T, int P, ofstream& bout);