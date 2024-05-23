#ifndef __City__
#define __City__

using namespace std;

class City {
    private:
        //Coordinate della città
        double _x;   
        double _y;
        //Nome della città
        int _n;      
    
    public:
        //Funzioni di accesso ai membri privati(in lettura o scrittura)
        double get_x();     
        double get_y();
        int get_n();
        void set_x(double myx);
        void set_y(double myy);
        void set_n(int myn);
};

#endif