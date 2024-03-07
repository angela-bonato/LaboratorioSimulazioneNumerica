#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../libGen.h"
#include "../RandomGenerator/random.h"

using namespace std;

//con approccio divide et impera cerca l'indice dell'estremo superiore del sottointervallo in cui si trova il numero estratto esaminando un array con i massimi di tutti gli intervalli
int BinSearchInt(int, int, double, vector<double>&, int);  

//calcolo dei dati usati per le figure 1 e 2 dell'esercizio 1.1
void DataAveVar(int, int, ofstream&, ofstream&);  

//cerca il sottointervallo a cui appartiene il numero estratto e aggiorna il conteggio relativo
void SearchInt(int, double, vector<double>&, vector<int>&);
//calcola il chi quadro
double ChiSqu(int, int, vector<int>&);
//calcolo dei dati usati per la statistica sul chi quadro  
void DataChiQuad(int, int, ofstream&);

//calcolo dei dati usati per l'esercizio 1.2
void DataDistr(int, vector<int>&, ofstream&, ofstream&, ofstream&);

//data la codinata y del punto iniziale dell'ago e il sin dell'angolo di inclinazione e la lunghezza, restituisce la coordinata y dell'estremo finale dell'ago
double EndNeedle(double, double, double);
//true se l'ago interseca una linea
bool TouchLine(double, double, vector<double>&, int);
//calcolo dei dati usati per l'esercizio 1.3
void DataBuffon(double, int, int, int, int, ofstream&);