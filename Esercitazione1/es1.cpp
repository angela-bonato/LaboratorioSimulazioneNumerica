#include "lib1.h"
#include "../RandomGenerator/random.h"
#include "../libGen.h"

using namespace std;
 
int main (int argc, char *argv[]){

   /*Esercizio 1.1*/
   /*Calcolo dei dati utilizzati nell'esercizio 1.1 figure 1 e 2*/
   int Mav=10000;   /*numero totale di estrazioni*/
   int Nav=100;  /*numero di blocchi*/
   int Lav=Mav/Nav;  /*numero di estrazioni per ogni blocco*/
   ofstream aout; /*file su cui scriverò i dati per la figura 1*/
   ofstream vout; /*file su cui scriverò i dati per la figura 2*/
   aout.open("average.dat");
   vout.open("variance.dat");
   DataAveVar(Nav, Lav, aout, vout);  /*racchiudo tutto il calcolo in una funzione apposita*/
   aout.close();
   vout.close();
   cout << "Parte dedicata a valor medio e varianza completata." << endl;

   /*Calcolo dei dati utilizzati per la parte dell'esercizio 1.1 dedicata al chi quadro*/
   int Mchi=100;  /*numero intervalli considerati*/
   int Nchi=10000;   /*numero estrazioni per ogni intervallo*/
   ofstream chiout;  /*file su cui scriverò i dati*/
   chiout.open("chiquad.dat");
   DataChiQuad(Mchi, Nchi, chiout);  /*racchiudo tutto il calcolo in una funzione apposita*/
   chiout.close();
   cout << "Parte dedicata al chi quadro completata." << endl;

   /*Esercizio 1.2*/
   vector<int> Ndists={1, 2, 10, 100};    /*per ogni distribuzione calcolo somme Sn con questi valori di n*/
   int Mdist=10000;  /*numero di calcoli di Sn richiesti per ogni n, per ogni distribuzione*/
   ofstream uniout;  /*file di dati per la figura 1*/
   ofstream expout;  /*file di dati per la figura 2*/
   ofstream lorout;  /*file di dati per la figura 3*/
   uniout.open("unifdist.dat");
   expout.open("expdist.dat");
   lorout.open("lordist.dat");
   DataDistr(Mdist, Ndists, uniout, expout, lorout);  /*racchiudo tutto il calcolo in una funzione apposita*/
   uniout.close();
   expout.close();
   lorout.close();
   cout << "Parte dedicata al teorema del limite centrale completata." << endl;


/*DA SISTEMAREEE*/
   /*Esercizio 1.3*/
   int Lbuf=1;   /*lunghezza dell'ago*/
   int Dbuf=10;   /*distanza fra le linee del piano*/
   int Pbuf=100;   /*massimo valore di x e y nel piano*/
   int Mbuf=10000;   /*numero di tiri*/
   int Bbuf=100;  /*numero blocchi*/
   int Tbuf=Mbuf/Bbuf;  /*numero di tiri per ogni blocco*/
   ofstream bufout;  /*file dati test di Buffon*/
   bufout.open("buffon.dat");
   DataBuffon(Lbuf, Dbuf, Bbuf, Tbuf, Pbuf, bufout);  /*racchiudo tutto il calcolo in una funzione apposita*/
   bufout.close();
   cout << "Parte dedicata al test di Buffon completata." << endl;

   return 0;
}