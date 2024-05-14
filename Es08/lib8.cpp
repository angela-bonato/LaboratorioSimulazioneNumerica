#include "lib8.h"

using namespace std;

double GenerateStep(Random& rand, double x, double delta){
    //genero uniformemente attorno al punto dato con raggio delta
    return rand.Rannyu(x-delta, x+delta);
}

double TargetDistribution(double x, double mu, double sigma){
    double psi = exp((-(x-mu)*(x-mu))/(2*sigma*sigma))+exp((-(x+mu)*(x+mu))/(2*sigma*sigma));   //funzione d'onda
    double integral = 2*sigma*sqrt(M_PI)*(1+exp(-(mu*mu)/(sigma*sigma)));     //integrale del modulo quadro della funzione d'onda calcolato analiticamente
    return (psi*psi)/integral;
}

double LocalEnergy(double x, double mu, double sigma){
      //uses natural constants
    double derivative=((1/(sigma*sigma))*exp((-(x-mu)*(x-mu))/(2*sigma*sigma))*(-1+((x-mu)*(x-mu))/(sigma*sigma)))+((1/(sigma*sigma))*exp((-(x+mu)*(x+mu))/(2*sigma*sigma))*(-1+((x+mu)*(x+mu))/(sigma*sigma))); 
    double v=pow(x, 4)-(5./2.)*x*x;
    double psi=TargetDistribution(x, mu, sigma);
    return v+((-(1./2.)*derivative)/psi);
}

void Acceptance(Random& rand, Acc& a, double prec, double pres){
    a.alpha=min(1., pres/prec);    /*evaluate the acceptance*/
    double r=rand.Rannyu(0., 1.);
    if(r<=a.alpha){   /*accept the proposed point with probability alpha*/
        a.accept=true;
    }
    else{
        a.accept=false;
    }
}

double MetropolisStep(Random& rand, double prec, Acc& a, double delta, double mu, double sigma, double& tarprec){
    double pres=GenerateStep(rand, prec, delta);    /*candidato punto per lo step presente*/
    double tarpres=TargetDistribution(pres, mu, sigma);
    Acceptance(rand, a, tarprec, tarpres);
    if(a.accept){
        tarprec=tarpres;    /*il candidato viene accettato come punto dello step presente ergo sarà la partenza del prossimo step*/
        return pres;
    }
    else{
        return prec;    /*il candidato non viene accettato ergo lo step presente resta uguale a quello precedente*/
    }
}

double Equilibration(double start, int A, double delta, double mu, double sigma){
    Random rand;
    InizRandom(rand);    /*inizializzo il generatore*/

    double prec=start;    /*posizione al passo precedente, all'inizio è start ma poi la aggiorno ad ogni passo*/
    double tarprec=TargetDistribution(prec, mu, sigma);    /*inizializzo il valore della distribuzione target al passo iniziale*/   

    double pres=0;     /*qua di volta in volta genero il passo presente*/

    double meanacc=0;   /*media accettazione*/ 

    for(int i=0; i<A; i++){     /*ciclo piccolo tanto è solo per vedere il valor medio di accettazione*/
        Acc a;
        pres=MetropolisStep(rand, prec, a, delta, mu, sigma, tarprec);  /*genero un punto in R^3 secondo la distribuzione target*/
        meanacc+=a.alpha;
        prec=pres;  /*aggiorno il passo*/
    }

    cout << "Dopo " << A << " passi con delta=" << delta << " si ha <alpha>=" << meanacc/A << endl;

    rand.SaveSeed();

    return prec;    /*punto finale che è inizio dell'analisi dati*/
}

void EnergyAnalysis(double start, int N, int L, double delta, double mu, double sigma, ofstream& xout, ofstream& eout){
    Random rand;
    InizRandom(rand);    /*inizializzo il generatore*/

    vector<double> valuebs(2, 0.);  /*valor medio a blocchi e suo quadrato*/
    vector<double> sumbs(2, 0.);  /*somma a blocchi e suo quadrato*/

    double prec=start;    /*posizione al passo precedente, all'inizio è start ma poi la aggiorno ad ogni passo*/
    double tarprec=TargetDistribution(prec, mu, sigma);    /*inizializzo il valore della distribuzione target al passo iniziale*/   

    double pres=0;     /*qua di volta in volta genero il passo presente*/

    for(int i=0; i<N; i++){     /*ciclo sui blocchi*/
        double sumle=0.;  /*somma cumulativa dell'energia locale nel blocco*/
        for(int j=0; j<L; j++){     /*ciclo che svolge il blocco*/
            Acc a;
            pres=MetropolisStep(rand, prec, a, delta, mu, sigma, tarprec);  /*genero un punto in R secondo la distribuzione target*/
            if((i%50)==0){  /*stampo una posizione ogni tot altrimenti mi viene un file pesantissimo*/
                if(xout.is_open()){
                    xout << pres << endl;
                }    
                else cerr << "Errore: impossibile aprire il file di output delle x generate." << endl;    
            }
            
            prec=pres;  /*aggiorno il passo*/

            sumle+=LocalEnergy(pres, mu, sigma);  /*calcolo il valore dell'energia locale corrispondente aggiornando la somma del blocco*/
        }
        double rmean=sumle/L;    /*<H> nell'i-esimo blocco*/

        BlockMean(rmean, sumbs, valuebs, i);   /*aggiorno la media a blocchi*/
        if(eout.is_open()){
            eout << setw(18) << scientific << valuebs[0] 
                << setw(18) << scientific << BlockError(valuebs, i) << endl;    /*variabili da plottare*/
        }
        else cerr << "Errore: impossibile aprire il file di output dei valori medi di energia locale." << endl;

    }

    rand.SaveSeed();
}