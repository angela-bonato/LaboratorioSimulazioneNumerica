#include "path.h"

using namespace std;

vector<int> Path::get_ord(){
    return _order;
}

void Path::set_ord(vector<int> myord){
    _order=myord;
    _L=_order.size();
}

void Path::set_Nc(int N){
    _Nc=N;
}

int Path::get_ord(int index){
    return _order[index];
} 

void Path::set_ord(int index, int value){
    _order[index]=value;
}


int Path::get_length(){
    return _L;
}
   
bool Path::IsValid(){
    if(int(_order.size())!=(_Nc+1)) {
        cerr << "Path invalido: lunghezza sbagliata." << endl;
        return false;    //tutte le città più la prima ripetuta
    }
    if(_order[0]!=_order[_Nc]){
        cerr << "Path invalido: prima e ultima città non coincidenti." << endl;
        return false;    //la prima e l'ultima città devono essere uguali
    }
    if(_order[0]!=0){
        cerr << "Path invalido: prima città non 0." << endl;
        return false;      //fisso la prima (ergo l'ultima) città come quella con city.n=0
    }
    vector<int> theor_counts(_Nc, 0);
    vector<int> counts(_Nc, 0);
    for(int i=1; i<_Nc; i++){
        theor_counts[i]=1;
        counts[_order[i]]+=1;
    }
    if(counts!=theor_counts){
        cerr << "Path invalido: città ripetute o mancanti." << endl;
        return false;      //ogni città deve esserci una e una sola volta, a parte la 0 che deve esserci solo a inizio e fine
    }
    return true;
}     
         
void Path::EvalLoss(vector<City> cities){      //come metrica per calcolare la distanza in L^1
    double sum=0.;
    for(int i=0; i<_Nc; i++){
        sum+=fabs(cities[_order[i]].get_x() - cities[_order[i+1]].get_x());
        sum+=fabs(cities[_order[i]].get_y() - cities[_order[i+1]].get_y());
    }
    _loss=sum;
}

 double Path::get_loss(){
    return _loss;
 }