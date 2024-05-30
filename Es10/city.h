#ifndef __City__
#define __City__

using namespace std;

class City {
    public: //altrimenti casini con MPI
        //Coordinate della città
        double _x;   
        double _y;
        //Nome della città
        int _n;      

        //costruttore
        City(double x=0.0, double y=0.0, int n=0) : _x(x), _y(y), _n(n) {}
        //Funzioni di accesso ai membri privati(in lettura o scrittura)
        double get_x();     
        double get_y();
        int get_n();
        void set_x(double myx);
        void set_y(double myy);
        void set_n(int myn);
};

#endif