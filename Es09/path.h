#ifndef __Path__
#define __Path__

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "city.h"

using namespace std;

class Path{
    private:
        //non tengo in memoria un vector di città ma solo gli int che identificano le città
        vector<int> _order;  
        //lunghezza di _order
        int _L;
        //valore della loss function calcolato 
        double _loss;  
        //probabilità di selezione calcolata dall'apposito operatore
        double _ps; 
        //numero di città considerate
        int _Nc; 

    public:
        //accesso a order completo
        vector<int> get_ord();  
        void set_ord(vector<int> myord);
        //accesso a order per componente
        int get_ord(int index);  
        void set_ord(int index, int value);  
        //setta Nc
        void set_Nc(int N);
        //restituisce L
        int get_length();
        //setta la probabilità di selezione  
        void set_p(double myp); 
        //controlla che il path rispetti tutti i vincoli imposti dal problema  
        bool IsValid();  
        //calcola la loss function del percorso, prende in ingresso il vettore delle città da analizzare secondo l'ordine che ha il path come membro   
        void EvalLoss(vector<City> cities);  
        //accesso alla loss
        double get_loss();  
};

#endif