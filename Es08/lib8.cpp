#include "lib8.h"

using namespace std;

vector<double> GenerateStep(Random& rand, double x, double delta){
    //genero uniformemente attorno al punto dato con raggio delta
    return rand.Rannyu(x-delta, x+delta);
}

double TargetDistribution(double x, double mu, double sigma){
    double psi = 
    return psi*psi;
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

vector<double> MetropolisStep(Random& rand, vector<double> prec, int p, int t, Acc& a, double delta, double& tarprec){
    vector<double> pres(3, 0.);
    pres=GenerateStep(rand, prec, t, delta);    /*candidato punto per lo step presente*/
    double tarpres=TargetDistribution(pres, p);
    Acceptance(rand, a, tarprec, tarpres);
    if(a.accept){
        tarprec=tarpres;    /*il candidato viene accettato come punto dello step presente ergo sarà la partenza del prossimo step*/
        return pres;
    }
    else{
        return prec;    /*il candidato non viene accettato ergo lo step presente resta uguale a quello precedente*/
    }
}

vector<double> Equilibration(vector<double> start, int p, int t, int A, double delta, ofstream& eqout, ofstream& epout){
    Random rand;
    InizRandom(rand);    /*inizializzo il generatore*/

    vector<double> prec(3, 0.);    /*posizione al passo precedente, all'inizio è start ma poi la aggiorno ad ogni passo*/
    prec=start;
    double tarprec=TargetDistribution(prec, p);    /*inizializzo il valore della distribuzione target al passo iniziale*/   

    vector<double> pres(3, 0.);     /*qua di volta in volta genero il passo presente*/

    double meanacc=0;   /*media accettazione*/ 

    for(int i=0; i<A; i++){     /*ciclo piccolo tanto è solo per vedere il valor medio di accettazione*/
        Acc a;
        pres=MetropolisStep(rand, prec, p, t, a, delta, tarprec);  /*genero un punto in R^3 secondo la distribuzione target*/

        eqout << EvaluateRadius(pres) << setw(18) << a.alpha << endl;
        PrintPosition(pres, epout);

        meanacc+=a.alpha;
        prec=pres;  /*aggiorno il passo*/
    }

    cout << "Dopo " << A << " passi con delta=" << delta << " si ha <alpha>=" << meanacc/A << endl;

    rand.SaveSeed();

    return prec;    /*punto finale che è inizio dell'analisi dati*/
}

void PrintPosition(vector<double> pos, ofstream& out){
    out << setw(18) << pos[0] 
        << setw(18) << pos[1]
        << setw(18) << pos[2] << endl;
}

void DataAnalysis(vector<double> start, int N, int L, int p, int t, double delta, ofstream& u1pout, ofstream& u1rout){
    Random rand;
    InizRandom(rand);    /*inizializzo il generatore*/

    vector<double> valuebs(2, 0.);  /*valor medio a blocchi e suo quadrato*/
    vector<double> sumbs(2, 0.);  /*somma a blocchi e suo quadrato*/

    vector<double> prec(3, 0.);    /*posizione al passo precedente, all'inizio è start ma poi la aggiorno ad ogni passo*/
    prec=start;
    double tarprec=TargetDistribution(prec, p);    /*inizializzo il valore della distribuzione target al passo iniziale*/   

    vector<double> pres(3, 0.);     /*qua di volta in volta genero il passo presente*/

    for(int i=0; i<N; i++){     /*ciclo sui blocchi*/
        double sumr=0.;  /*somma cumulativa di r nel blocco*/
        for(int j=0; j<L; j++){     /*ciclo che svolge il blocco*/
            Acc a;
            pres=MetropolisStep(rand, prec, p, t, a, delta, tarprec);  /*genero un punto in R^3 secondo la distribuzione target*/
            if((i%50)==0){  /*stampo una posizione ogni tot altrimenti mi viene un file pesantissimo*/
                if(u1pout.is_open()){
                    PrintPosition(pres, u1pout);
                }    
                else cerr << "Errore: impossibile aprire il file di output delle posizioni" << endl;    
            }
            
            prec=pres;  /*aggiorno il passo*/

            sumr+=EvaluateRadius(pres);  /*calcolo il valore r corrispondente aggiornando la somma del blocco*/
        }
        double rmean=sumr/L;    /*<r> nell'i-esimo blocco*/

        BlockMean(rmean, sumbs, valuebs, i);   /*aggiorno la media a blocchi*/
        if(u1rout.is_open()){
            u1rout << setw(18) << scientific << valuebs[0] 
                << setw(18) << scientific << BlockError(valuebs, i) << endl;    /*variabili da plottare*/
        }
        else cerr << "Errore: impossibile aprire il file di output dei raggi medi" << endl;

    }

    rand.SaveSeed();
}