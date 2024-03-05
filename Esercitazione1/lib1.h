#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include "../libGen.h"
#include "../RandomGenerator/random.h"

using namespace std;

float Rarandom();

float BlockError(float, float, int);    /*calcolo della media a blocchi*/
void DataAveVar(int, int, ofstream&, ofstream&);  /*calcolo dei dati usati per le figure 1 e 2 dell'esercizio 1.1*/

int BinSearchInt(int, int, float, float*, int);  /*con approccio divide et impera cerca l'indice dell'estremo superiore del sottointervallo in cui si trova il numero estratto esaminando un array con i massimi di tutti gli intervalli*/
void SearchInt(int, float, float*, int*);   /*cerca il sottointervallo a cui appartiene il numero estratto e aggiorna il conteggio relativo*/
float ChiSqu(int, int, int*);  /*calcola il chi quadro*/
void DataChiQuad(int, int, ofstream&);   /*calcolo dei dati usati per la statistica sul chi quadro*/

void DataDistr(int, int*, ofstream&, ofstream&, ofstream&);    /*calcolo dei dati usati per l'esercizio 1.2*/

void EndNeedle(float*, float, int, float*);   /*date le codinate del punto iniziale dell'ago e l'angolo di inclinazione e la lunghezza, restituisce le coordinate dell'estremo finale dell'ago*/
bool TouchLine(float*, float*, float*, int);    /*true se l'ago interseca una linea*/
void DataBuffon(int, int, int, int, int, ofstream&);    /*calcolo dei dati usati per l'esercizio 1.3*/
