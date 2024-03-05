#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../libGen.h"
#include "../RandomGenerator/random.h"

using namespace std;

int BinSearchInt(int, int, double, vector<double>&, int);  /*con approccio divide et impera cerca l'indice dell'estremo superiore del sottointervallo in cui si trova il numero estratto esaminando un array con i massimi di tutti gli intervalli*/

void DataAveVar(int, int, ofstream&, ofstream&);  /*calcolo dei dati usati per le figure 1 e 2 dell'esercizio 1.1*/

void SearchInt(int, double, vector<double>&, vector<int>&);   /*cerca il sottointervallo a cui appartiene il numero estratto e aggiorna il conteggio relativo*/
double ChiSqu(int, int, vector<int>&);  /*calcola il chi quadro*/
void DataChiQuad(int, int, ofstream&);   /*calcolo dei dati usati per la statistica sul chi quadro*/

void DataDistr(int, vector<int>&, ofstream&, ofstream&, ofstream&);    /*calcolo dei dati usati per l'esercizio 1.2*/

void EndNeedle(vector<double>&, double, int, vector<double>&);   /*date le codinate del punto iniziale dell'ago e l'angolo di inclinazione e la lunghezza, restituisce le coordinate dell'estremo finale dell'ago*/
bool TouchLine(double, double, vector<double>&, int);    /*true se l'ago interseca una linea*/
void DataBuffon(int, int, int, int, int, ofstream&);    /*calcolo dei dati usati per l'esercizio 1.3*/