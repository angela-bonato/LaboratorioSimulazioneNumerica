#include "city.h"

using namespace std;

double City::get_x(){
    return _x;
}

double City::get_y(){
    return _y;
}

int City::get_n(){
    return _n;
}

void City::set_x(double myx){
    _x=myx;
}

void City::set_y(double myy){
    _y=myy;
}

void City::set_n(int myn){
    _n=myn;
}

