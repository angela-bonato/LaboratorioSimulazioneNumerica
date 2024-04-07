#include "lib5.h"

using namespace std;

vector<double> GenerateStep(Random& rand, vector<double> pos, int t, double delta){
    vector<double> ret(3, 0.);      /*qua metterò il punto generato*/
    if(t!=0 && t!=3){
        cerr << "Errore: distribuzione della generazione invalida." << endl;
    }
    if(t==0){   /*genero uniformemente attorno al punto dato con raggio delta*/
        ret[0]=rand.Rannyu(pos[0]-delta, pos[0]+delta);
        ret[1]=rand.Rannyu(pos[1]-delta, pos[1]+delta);
        ret[2]=rand.Rannyu(pos[2]-delta, pos[2]+delta);
    }
    if(t==3){   /*genero gaussianamente attorno al punto dato usando delta come sigma della gaussiana*/
        ret[0]=rand.Gauss(pos[0], delta);
        ret[1]=rand.Gauss(pos[1], delta);
        ret[2]=rand.Gauss(pos[2], delta);
    }
    return ret;
}

double EvaluateRadius(vector<double> pos){
    return sqrt((pos[0]*pos[0])+(pos[1]*pos[1])+(pos[2]*pos[2]));
}

double TargetDistribution(vector<double> pos, int p){
    if(p!=1 && p!=2){
        cerr << "Errore: distribuzione target invalida." << endl;
        return -1;
    }
    double r=EvaluateRadius(pos);     /*da coordinate cartesiane ricavo il raggio*/
    if(p==1){   /*flag che indica che voglio fare il sample di psi100*/
        double psi=abs(exp(-r)/sqrt(M_PI));
        return psi*psi;
    }
    if(p==2){
        double ct=pos[0]/sqrt((pos[0]*pos[0])+(pos[1]*pos[1]));     /*da coordinate cartesiane ricavo il coseno di theta*/
        double psi=abs((1./8.)*sqrt(2./M_PI)*r*exp(-r/2.)*ct);
        return psi*psi;
    }
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

void CheckMeanAcceptance(vector<double> start, int p, int t, double delta){
    Random rand;
    InizRandom(rand);    /*inizializzo il generatore*/

    double tarprec=TargetDistribution(start, p);    /*inizializzo il valore della distribuzione target al passo iniziale*/   
    vector<double> prec(3, 0.);    /*posizione al passo precedente, all'inizio è start ma poi la aggiorno ad ogni passo*/
    prec[0]=start[0];

    vector<double> pres(3, 0.);     /*qua di volta in volta genero il passo presente*/

    int A=10000;    /*step su cui medio*/
    double meanacc=0;   /*media accettazione*/ 

    for(int i=0; i<A; i++){     /*ciclo piccolo tanto è solo per vedere il valor medio di accettazione*/
        Acc a;
        pres=MetropolisStep(rand, prec, p, t, a, delta, tarprec);  /*genero un punto in R^3 secondo la distribuzione target*/
        meanacc+=a.alpha;
    }

    cout << "Dopo " << A << " passi con delta=" << delta << " si ha <alpha>=" << meanacc/A << endl;

    rand.SaveSeed();
}

void PrintPosition(vector<double> pos, ofstream& out){
    out << setw(18) << scientific << pos[0] 
        << setw(18) << scientific << pos[1]
        << setw(18) << scientific << pos[3] << endl;
}

void DataAnalysis(vector<double> start, int N, int L, int p, int t, double delta, ofstream& u1pout, ofstream& u1rout){
    Random rand;
    InizRandom(rand);    /*inizializzo il generatore*/

    vector<double> valuebs(2, 0.);  /*valor medio a blocchi e suo quadrato*/
    vector<double> sumbs(2, 0.);  /*somma a blocchi e suo quadrato*/

    double tarprec=TargetDistribution(start, p);    /*inizializzo il valore della distribuzione target al passo iniziale*/   
    vector<double> prec(3, 0.);    /*posizione al passo precedente, all'inizio è start ma poi la aggiorno ad ogni passo*/
    prec[0]=start[0];

    vector<double> pres(3, 0.);     /*qua di volta in volta genero il passo presente*/

    for(int i=0; i<N; i++){     /*ciclo sui blocchi*/
        double sumr=0.;  /*somma cumulativa di r nel blocco*/
        for(int j=0; j<L; j++){     /*ciclo che svolge il blocco*/
            Acc a;
            pres=MetropolisStep(rand, prec, p, t, a, delta, tarprec);  /*genero un punto in R^3 secondo la distribuzione target*/
            if(u1pout.is_open()){
                PrintPosition(pres, u1pout);
            }
            else cerr << "Errore: impossibile aprire unif1pos.dat" << endl;

            sumr+=EvaluateRadius(pres);  /*calcolo il valore r corrispondente aggiornando la somma del blocco*/
        }
        double rmean=sumr/L;    /*<r> nell'i-esimo blocco*/

        BlockMean(rmean, sumbs, valuebs, i);   /*aggiorno la media a blocchi*/
        if(u1rout.is_open()){
            u1rout << setw(18) << scientific << valuebs[0] 
                << setw(18) << scientific << BlockError(valuebs, i) << endl;    /*variabili da plottare*/
        }
        else cerr << "Errore: impossibile aprire unif1rad.dat" << endl;

    }

    rand.SaveSeed();
}