#include "lib1.h"
#include "../libGen.h"

using namespace std;

int BinSearchInt(int l, int r, double k, vector<double> &maxs, int M){
    if(k<l || k>r){
        cerr << "Errore: intervallo invalido esaminato da BinSearchInt." << endl;
        return -1;
    }
    if(l==0 && 0.<=k && k<maxs[0]){  /*maxs[0] contiene il massimo del primo intervallo quindi se k sta nel primo intervallo serve un caso a parte*/
        return l;
    }
    if(r==M && k==maxs[r]){    /*devo esaminare [0, M] ma sto valutando insiemi aperti [a, b) ergo qua chiudo l'ultimo sottointervallo*/
        return r;
    }
    if((r-l)==1 && maxs[l]<=k && k<maxs[r]){     /*caso base dell'algoritmo divide et impera*/
        return r;
    }
    if((r-l)>1){    /*chiamate ricorsive dell'algoritmo*/
        int h=(l+r)/2;
        if(maxs[h]<k){
            return BinSearchInt(h, r, k, maxs, M);
        }
        else{
            return BinSearchInt(l, h, k, maxs, M);
        }
    }
    else{
        return -1;
    }
}

void DataAveVar(int N, int L, ofstream& aout, ofstream& vout){
    /*Inizializzazione del generatore di numeri casuali*/
    Random rand;
    InizRandom(rand);

    /*variabili usate per la figura 1 (grafico relativo al valor medio)*/
    vector<double> avbs(2, 0.);  /*alla i-esima iterazione, valor medio cumulativo dei primi i blocchi e suo quadrato*/
    vector<double> sumbs(2, 0.);  /*alla i-esima iterazione, somma dei valori medi dei primi i blocchi e dei quadrati*/
    /*variabili usate per la figura 2 (grafico relativo alla varianza)*/
    vector<double> vavbs(2, 0.);   /*corrispettivo di avbs per la figura 2*/
    vector<double> vsumbs(2, 0.);; /*corrispettivo di sumbs per la figura 2*/

    for(int i=0; i<N; i++){    /*itero sui blocchi*/
        /*variabili per la figura 1*/
        double av=0;   /*valor medio dell'i-esimo blocco*/
        /*variabili per la figura 2*/
        double vav=0;   /*valor medio delle varianze calcolate per l'i-esimo blocco*/
        
        for(int j=0; j<L; j++){    /*ogni iterazione completa l'i-esimo blocco*/
            double r=rand.Rannyu();
            if(r<0 || r>1){
                cerr << "Errore: estrazione invalida in DataAveVar." << endl;
            }
            av+=r;
            vav+=(r-0.5)*(r-0.5);
        }

        /*dati figura 1*/
        av/=L;
        BlockMean(av, sumbs, avbs, i);
        if(aout.is_open()){
            aout << avbs[0] << " " << BlockError(avbs, i) << endl;  /*uso BlockError per calcolare la barra d'errore con il metodo a blocchi*/
        } 
        else cerr << "Errore: impossibile aprire average.dat" << endl;

        /*dati figura 2*/
        vav/=L;
        BlockMean(vav, vsumbs, vavbs, i);
        if(vout.is_open()){
            vout << vavbs[0] << " " << BlockError(vavbs, i) << endl;
        } 
        else cerr << "Errore: impossibile aprire variance.dat" << endl;
        
        rand.SaveSeed();
    }
}

void SearchInt(int M, double r, vector<double> &maxs, vector<int> &counts){
    int ind=BinSearchInt(0, M, r, maxs, M);
    counts[ind]++;
}

double ChiSqu(int M, int N, vector<int> &counts){
    int E=N/M;  /*valore atteso*/
    double chi=0.;
    for(int i=0; i<M; i++){
        chi+=(counts[i]-E)*(counts[i]-E);   /*calcolo del numeratore del chi2*/
    }
    return chi/E;
}

void DataChiQuad(int M, int N, ofstream& chiout){
    /*Inizializzazione del generatore di numeri casuali*/
    Random rand;   
    InizRandom(rand);

    double I=1./M;   /*ampiezza di ogni sottointervallo*/
    vector<double> maxs(M, 0.); /*contiene l'estremo superiore di ogni intervallo*/
    for(int m=0; m<M; m++){
        maxs[m]=(m+1)*I;
    }
    
    for(int i=0; i<M; i++){
        vector<int> counts(M, 0.);  /*conteggio delle estrazioni contenute in ogni intervallo*/
        
        for(int j=0; j<N; j++){
            double r=rand.Rannyu();
            if(r<0 || r>1){
                cerr << "Errore: estrazione invalida in DataChiQuad." << endl;
            }

            SearchInt(M, r, maxs, counts);    /*funzione che cerca il sottointervallo a cui appartiene il numero estratto e aggiorna il conteggio relativo*/
        }
        double chi=ChiSqu(M, N, counts);  /*i-esimo chi quadro calcolato con una funzione apposita*/

        if(chiout.is_open()){
            chiout << chi << endl;  /*dato che poi plotterò*/
        } 
        else cerr << "Errore: impossibile aprire chiquad.dat" << endl;
        
    }

    rand.SaveSeed();
}

void DataDistr(int M, vector<int> &Ns, ofstream& uniout, ofstream& eout, ofstream& lorout){
    /*Inizializzazione del generatore di numeri casuali*/
    Random rand;   
    InizRandom(rand);

    for(int i=0; i<M; i++){
        vector<double> unifs(4, 0.);
        vector<double> exps(4, 0.); 
        vector<double> lors(4, 0.);   
        for(int j=0; j<4; j++){
            int k=0;
            while(k<Ns[j]){
                unifs[j]+=rand.Rannyu(1., 6.);   /*distribuzione uniforme fra 1 e 6*/
                exps[j]+=rand.Exp(1.);     /*distribuzione esponenziale con lambda=1*/
                lors[j]+=rand.Lorentz(0., 1.);   /*distribuzione lorentziana con mu=0 e Gamma=1*/
                if(unifs[j]<1 || unifs[j]>6 || exps[j]<0 ){
                    cerr << "Errore: estrazione invalida in DataDistr." << endl;
                }
                k++;
            }
        }

        if(uniout.is_open()){
            uniout << unifs[0] << " " << unifs[1] << " " << unifs[2] << " " << unifs[3] << " " << endl;
        } 
        else cerr << "Errore: impossibile aprire unifdist.dat" << endl;
        if(eout.is_open()){
            eout << exps[0] << " " << exps[1] << " " << exps[2] << " " << exps[3] << " " << endl;
        }
        else cerr << "Errore: impossibile aprire expdist.dat" << endl;
        if(lorout.is_open()){
            lorout << lors[0] << " " << lors[1] << " " << lors[2] << " " << lors[3] << " " << endl;
        }
        else cerr << "Errore: impossibile aprire lordist.dat" << endl;
    }

    rand.SaveSeed();    
}

void EndNeedle(vector<double> &starts, double ct, int L, vector<double> &ends){
    if(ct<=(M_PI/2)){
        ends[0]=starts[0]+(L*ct);
    }
    else{
        ends[0]=starts[0]-(L*ct);
    }
    ends[1]=starts[1]+(L*sqrt(1-(ct)*(ct)));
}

bool TouchLine(double start, double end, vector<double> &maxs, int Nl){
    /*suppongo linee parallele a x ergo guardo solo in che intervallo cadono la coordinata y di inizio e fine ago*/
    int s=BinSearchInt(0, Nl, start, maxs, Nl);   /*indice che identifica in maxs il max dell'intervallo in cui cade la y della punta iniziale dell'ago*/
    int e=BinSearchInt(0, Nl, end, maxs, Nl);   /*come s ma per la y della punta finale dell'ago*/
    /*una parte dell'ago tocca una linea se le due punte giacciono in intervalli diversi oppure una delle punte tocca una linea*/
    if(s!=e){   
        return true;
    }
    if(s-1>=0 && start==maxs[s-1]){
        return true;
    }
    if(s==Nl && start==maxs[s]){
        return true;
    }
    if(e-1>=0 && end==maxs[e-1]){
        return true;
    }
    if(e==Nl && end==maxs[e]){
        return true;
    }
    return false;
}

void DataBuffon(int L, int D, int B, int T, int P, ofstream& bout){
    /*Inizializzazione del generatore di numeri casuali*/
    Random rand;
    InizRandom(rand);

    int Nl=P/D;   /*numero di linee nel piano*/
    if(P%D!=0){
        cout << "Attenzione: Nlinee=Pbuf/Dbuf è stato arrotondato." << endl;
    }

    vector<double> maxs(Nl, 0.); /*contiene l'estremo superiore di ogni intervallo*/
    for(int m=0; m<Nl; m++){
        maxs[m]=(m+1)*D;
    }

    vector<double> sumbs(2, 0.);   /*somma a blocchi della stima e del quadrato della stima*/
    vector<double> valuebs(2, 0.); /*stima a blocchi e suo quadrato*/
    for(int j=0; j<B; j++){     /*ciclo sui blocchi*/
        int i=0;    /*numero di aghi validi e analizzati (i.e., cadono interamente del piano) per il j-simo blocco*/
        int Nbuf=0;    /*numero di aghi del j-simo blocco che intersecano una linea*/
        
        while(i<T){     /*analisi del j-simo blocco*/
            vector<double> starts(2, 0.);
            starts[0]=rand.Rannyu(0., P);   /*genero coordinata x della punta dell'ago, distribuita uniformemente nel piano*/
            starts[1]=rand.Rannyu(0., P);   /*genero coordinata y della punta dell'ago, distribuita uniformemente nel piano*/
            double ct=rand.Rannyu(-1, 1);   /*genero coseno dell'angolo theta fra asse x e ago, distribuito uniformemente fra -1 e 1*/
            if(starts[0]<0 || starts[0]>P || starts[1]<0 || starts[1]>P || ct<-1 || ct> 1){
                cerr << "Errore: estrazione invalida in DataBuffon." << endl;
            }

            vector<double> ends(2, 0.);
            EndNeedle(starts, ct, L, ends);    /*calcola coordinate dell'altra punta dell'ago*/
            if(ends[0]<=P && ends[1]<=P){   /*rigetto punti tc la fine dell'ago esce dal piano*/
                i++;
                if(TouchLine(starts[1], ends[1], maxs, Nl)){  /*OnLine()=true se l'ago tocca una linea*/
                    Nbuf++;     /*conteggio aghi che toccano le linee*/
                }
            }
        }
        if(Nbuf==0){
            cerr << "Errore: Nbuf risultante dal blocco " << j << " è nullo, impossibile completare correttamente DataBuffon." << endl;
        }
        double value=(2*L*T)/(Nbuf*D);   /*stima del pigreco data dal solo j-simo blocco*/
        BlockMean(value, sumbs, valuebs, j);
        
        if(bout.is_open()){
            bout << valuebs[0] << " " << BlockError(valuebs, j) << endl;
        }
        else cerr << "Errore: impossibile aprire buffon.dat" << endl;
    }

    rand.SaveSeed();   
}