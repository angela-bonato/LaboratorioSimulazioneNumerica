#include "lib8.h"

using namespace std;

double PsiSqNorm(double x, double mu, double sigma){
    double psi = exp((-(x-mu)*(x-mu))/(2*sigma*sigma))+exp((-(x+mu)*(x+mu))/(2*sigma*sigma));   //funzione d'onda
    double integral = 2*sigma*sqrt(M_PI)*(1+exp(-(mu*mu)/(sigma*sigma)));     //integrale del modulo quadro della funzione d'onda calcolato analiticamente
    return (psi*psi)/integral;
}

double LocalEnergy(double x, double mu, double sigma){
      //uses natural constants
    double derivative=((1/(sigma*sigma))*exp((-(x-mu)*(x-mu))/(2*sigma*sigma))*(-1+((x-mu)*(x-mu))/(sigma*sigma)))+((1/(sigma*sigma))*exp((-(x+mu)*(x+mu))/(2*sigma*sigma))*(-1+((x+mu)*(x+mu))/(sigma*sigma))); 
    double v=pow(x, 4)-(5./2.)*x*x;
    double psi=exp((-(x-mu)*(x-mu))/(2*sigma*sigma))+exp((-(x+mu)*(x+mu))/(2*sigma*sigma));
    return v+((-(1./2.)*derivative)/psi);
}

double BoltzWeight(double beta, double h_1, double h_2){
    return exp(-beta*(h_2-h_1));
}

double GenerateStep(Random& rand, double x, double delta){
    //genero uniformemente attorno al punto dato con raggio delta
    return rand.Rannyu(x-delta, x+delta);
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

double MetropolisStep1(Random& rand, double prec, Acc& a, double delta, double mu, double sigma, double& tarprec){
    double pres=GenerateStep(rand, prec, delta);    /*candidato punto per lo step presente*/
    double tarpres=PsiSqNorm(pres, mu, sigma);
    Acceptance(rand, a, tarprec, tarpres);
    if(a.accept){
        tarprec=tarpres;    /*il candidato viene accettato come punto dello step presente ergo sarà la partenza del prossimo step*/
        return pres;
    }
    else{
        return prec;    /*il candidato non viene accettato ergo lo step presente resta uguale a quello precedente*/
    }
}

void BestVal(vector<double>& bests, MS2 pres){
    if(pres.hmean<bests[2]){
        bests[0]=pres.mu;
        bests[1]=pres.sigma;
        bests[2]=pres.hmean;
        bests[3]=pres.herror;
    }
}

void EvalH(Random& rand, MS2& pres, double delta){
    int Nh=80;
    int Lh=1000;       /*faccio 50 blocchi da 1000 passi*/
    
    vector<double> hvaluebs(2, 0.);  /*valor medio a blocchi e suo quadrato*/
    vector<double> hsumbs(2, 0.);  /*somma a blocchi e suo quadrato*/

    double xprec=3.;    /*posizione al passo precedente, all'inizio è start ma poi la aggiorno ad ogni passo*/
    double tarprec=PsiSqNorm(xprec, pres.mu, pres.sigma);    /*inizializzo il valore della distribuzione target al passo iniziale*/   
    double xpres;     /*qua di volta in volta genero il passo presente*/

    for(int i=0; i<Nh; i++){     /*ciclo sui blocchi*/
        double hsumle=0.;  /*somma cumulativa dell'energia locale nel blocco*/
        for(int j=0; j<Lh; j++){     /*ciclo che svolge il blocco*/
            Acc a;
            xpres=MetropolisStep1(rand, xprec, a, delta, pres.mu, pres.sigma, tarprec);  /*genero un punto in R secondo la distribuzione target*/
            
            xprec=xpres;  /*aggiorno il passo*/

            hsumle+=LocalEnergy(xpres, pres.mu, pres.sigma);  /*calcolo il valore dell'energia locale corrispondente aggiornando la somma del blocco*/
        }
        double rmean=hsumle/Lh;    /*<H> nell'i-esimo blocco*/

        BlockMean(rmean, hsumbs, hvaluebs, i);   /*aggiorno la media a blocchi*/
        if(i==Nh-1){
            pres.hmean=hvaluebs[0];
            pres.herror=BlockError(hvaluebs, i);
        }
    }
}

MS2 MetropolisStep2(Random& rand, MS2 prec, Acc& a, double delta, double beta){
    MS2 pres;   /*candidato punto per lo step presente*/
    pres.mu=GenerateStep(rand, prec.mu, delta);
    pres.sigma=GenerateStep(rand, prec.sigma, delta);
    EvalH(rand, pres, delta);
    Acceptance(rand, a, 1., BoltzWeight(beta, prec.hmean, pres.hmean)); /*Calcolo già il BoltzWeight il rapporto utile per l'accettazione ma per non scrivere una nuova variabile semplicemente do ad Acceptance un denominatore pari a 1*/
    if(a.accept){
        if((prec.hmean > (pres.hmean-pres.herror)) &&  (prec.hmean < (pres.hmean+pres.herror)) && (pres.hmean > (prec.hmean-prec.herror)) &&  (pres.hmean < (prec.hmean+prec.herror))){
            pres.stop=true;     /*ho saturato la precisione ergo fermo il ciclo*/
        }
        else pres.stop=false;
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
    double tarprec=PsiSqNorm(prec, mu, sigma);    /*inizializzo il valore della distribuzione target al passo iniziale*/   

    double pres=0;     /*qua di volta in volta genero il passo presente*/

    double meanacc=0;   /*media accettazione*/ 

    for(int i=0; i<A; i++){     /*ciclo piccolo tanto è solo per vedere il valor medio di accettazione*/
        Acc a;
        pres=MetropolisStep1(rand, prec, a, delta, mu, sigma, tarprec);  /*genero un punto in R^3 secondo la distribuzione target*/
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
    double tarprec=PsiSqNorm(prec, mu, sigma);    /*inizializzo il valore della distribuzione target al passo iniziale*/   

    double pres=0;     /*qua di volta in volta genero il passo presente*/

    for(int i=0; i<N; i++){     /*ciclo sui blocchi*/
        double sumle=0.;  /*somma cumulativa dell'energia locale nel blocco*/
        for(int j=0; j<L; j++){     /*ciclo che svolge il blocco*/
            Acc a;
            pres=MetropolisStep1(rand, prec, a, delta, mu, sigma, tarprec);  /*genero un punto in R secondo la distribuzione target*/
            if(xout.is_open()){
                xout << pres << endl;
            }    
            else cerr << "Errore: impossibile aprire il file di output delle x generate." << endl;    
            
            prec=pres;  /*aggiorno il passo*/

            sumle+=LocalEnergy(pres, mu, sigma);  /*calcolo il valore dell'energia locale corrispondente aggiornando la somma del blocco*/
        }
        double hmean=sumle/L;    /*<H> nell'i-esimo blocco*/

        BlockMean(hmean, sumbs, valuebs, i);   /*aggiorno la media a blocchi*/
        if(eout.is_open()){
            eout << setw(18) << scientific << valuebs[0] 
                << setw(18) << scientific << BlockError(valuebs, i) << endl;    /*variabili da plottare*/
        }
        else cerr << "Errore: impossibile aprire il file di output dei valori medi di energia locale." << endl;

    }

    rand.SaveSeed();
}

void InitFiles(ofstream& pout, ofstream& bout, ofstream& hout, ofstream& finxout, ofstream& fineout){
    if(pout.is_open()){
        pout << "#  LAST MU         LAST SIGMA" << endl;
    }
    if(bout.is_open()){
        bout << "#  BETA         STEPS      MEANACC" << endl;
    }
    if(hout.is_open()){
        hout << "#  LAST <H>         ERROR" << endl;
    }
    if(finxout.is_open()){
        finxout << "#  GENERATED X OPTIMAL PARAMS" << endl;
    }
    if(fineout.is_open()){
        fineout << "#  <H> OPTIMAL PARAMS       ERROR (BLOCK ANALYSIS)" << endl;
    }
}

void SimAnnealing(double delta, double mu_start, double sigma_start, double beta_min, double beta_max, double beta_step, ofstream& pout, ofstream& bout, ofstream& hout, ofstream& finxout, ofstream& fineout){
    Random rand;
    InizRandom(rand);    /*inizializzo il generatore*/

    MS2 prec;    /*posizione al passo precedente, all'inizio è start ma poi la aggiorno ad ogni passo*/
    prec.mu=mu_start;
    prec.sigma=sigma_start;
    EvalH(rand, prec, delta);    /*inizializzo il valore della distribuzione target al passo iniziale*/
    prec.stop=false;   

    MS2 pres;     /*qua di volta in volta genero il passo presente*/

    vector<double> best_values(4, 0.);  /*parametri migliori di tutta l'analisi*/
    
    int n=0;    /*valori di beta visitati (i.e. blocchi per l'analisi di mu e sigma)*/
    int m=0;    /*conta passi totali*/
    if(n%5==0 && n!=0){
        delta-=int(n/5)*0.01;     /*ogni tot aggiusto delta per avere meanacc circa 0.5*/
    }

    for(double b=beta_min; b<=beta_max; b+=beta_step){     /*ciclo sui blocchi*/
        int l=0;    /*passi effettuati per ogni beta*/
        double meanacc=0.;   /*accettazione media a beta fissata*/
        while(prec.stop == false){     /*ciclo che svolge il blocco a beta costante*/
            Acc a;
            pres=MetropolisStep2(rand, prec, a, delta, b);  /*genero un punto in R secondo la distribuzione target*/
            meanacc+=a.alpha;

            if(l==0&&n==0){   /*iniziaizzo i parametri al primo passo di ogni blocco a beta costante*/
                best_values[0]=pres.mu;
                best_values[1]=pres.sigma;
                best_values[2]=pres.hmean;
                best_values[3]=pres.herror;
            }
            BestVal(best_values, pres);     /*se l'energia calcolata è minore della precedente aggiorno i best_params*/

            /*ogni 20 passi totali registro il valore di mu e sigma*/
            if((m+1)%5==0){
                if(pout.is_open()){
                    pout << setw(18) << (m+1)
                        << setw(18) << scientific << pres.mu 
                        << setw(18) << scientific << pres.sigma << endl;    /*variabili da plottare*/
                }
                else cerr << "Errore: impossibile aprire il file di output dei parametri." << endl;
            }

            prec=pres;  /*aggiorno il passo*/
            l++;
            m++;
        }
        
        /*per ogni valore di beta registro la media a blocchi finale (cioè all'ultimo valore di mu,sigma) di H con errore*/
        if(hout.is_open()){
            hout << setw(18) << scientific << pres.hmean 
                << setw(18) << scientific << pres.herror << endl;    /*variabili da plottare*/
        }
        else cerr << "Errore: impossibile aprire il file di output dei valori medi di H." << endl;

        /*per ogni valore di beta registro beta e il numero di passi fatto per trovare mu, sigma*/
        if(bout.is_open()){
            bout << setw(18) << scientific << b 
                << setw(18) << l 
                << setw(18) << scientific << meanacc/l << endl;
        }

        cout << "Finita analisi per beta= " << b << endl;
        prec.stop=false;
        n++;
    }
     rand.SaveSeed();

    /*qua sono arrivata all'ultimo beta*/
    if(pout.is_open()){
                pout << "#"
                    << setw(18) << scientific << best_values[0] 
                    << setw(18) << scientific << best_values[1] << endl;    /*variabili da plottare*/
            }
    double start=Equilibration(3., 5000, 2.7, best_values[0], best_values[1]);
    EnergyAnalysis(start, 50, 200, 2.7, best_values[0], best_values[1], finxout, fineout);
}