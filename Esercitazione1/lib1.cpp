#include "lib1.h"

using namespace std;


float Rarandom(){
    random_device rd;  // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(0., 1.);
    return dis(gen);
}


float BlockError(float val, float val2, int B){
    if(B==0){   /*il primo blocco ha errore 0*/
        return 0;
    }
    else{
        return sqrt((val2-(val*val))/B);   /*barra d'errore sul B-esimo blocco*/
    }
}

void DataAveVar(int N, int L, ofstream& aout, ofstream& vout){
    /*Inizializzazione del generatore di numeri casuali*/
    Random rand;
    InizRandom(rand);

    /*variabili usate per la figura 1 (grafico relativo al valor medio)*/
    float avb;  /*alla i-esima iterazione, valor medio cumulativo dei primi i blocchi*/
    float av2b;  /*alla i-esima iterazione, quadrato del valor medio cumulativo dei primi i blocchi*/
    float sumb=0;  /*alla i-esima iterazione, somma dei valori medi dei primi i blocchi*/
    float sum2b=0;  /*alla i-esima iterazione, somma dei quadrati dei valori medi dei primi i blocchi*/
    /*variabili usate per la figura 2 (grafico relativo alla varianza)*/
    float vavb;   /*corrispettivo di avb per la figura 2*/
    float vav2b;   /*corrispettivo di av2b per la figura 2*/
    float vsumb=0; /*corrispettivo di sumb per la figura 2*/
    float vsum2b=0;   /*corrispettivo di sum2bb per la figura 2*/
    
    for(int i=0; i<N; i++){    /*itero sui blocchi*/
        /*variabili per la figura 1*/
        float av=0;   /*valor medio dell'i-esimo blocco*/
        /*variabili per la figura 2*/
        float vav=0;   /*valor medio delle varianze calcolate per l'i-esimo blocco*/
        for(int j=0; j<L; j++){    /*ogni iterazione completa l'i-esimo blocco*/
            float r=Rarandom();
            av+=r;
            vav+=(r-0.5)*(r-0.5);
        }
        /*dati figura 1*/
        av/=L;
        sumb+=av;
        sum2b+=av*av;
        avb=sumb/(i+1);
        av2b=sum2b/(i+1);
        aout << avb << " " << BlockError(avb, av2b, i) << endl;  /*uso BlockError per calcolare la barra d'errore con il metodo a blocchi*/
        /*dati figura 2*/
        vav/=L;
        vsumb+=vav;
        vsum2b+=vav*vav;
        vavb=vsumb/(i+1);
        vav2b=vsum2b/(i+1);
        vout << vavb << " " << BlockError(vavb, vav2b, i) << endl;
    }
      
    rand.SaveSeed();
}

int BinSearchInt(int l, int r, float k, float* maxs, int M){
    if(l==0 && 0.<=k && k<maxs[0]){  /*maxs[0] contiene il massimo del primo intervallo quindi se k sta nel primo intervallo serve un caso a parte*/
        return l;
    }
    if(r==M && k==maxs[r]){    /*devo esaminare [0, M] ma sto valutando insiemi aperti [a, b) ergo l'ultimo sottointervallo lo valuto a parte in modo che sia chiuso e copro tutto*/
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

void SearchInt(int M, float r, float* maxs, int* counts){
    int ind=BinSearchInt(0, M, r, maxs, M);
    counts[ind]++;
}

float ChiSqu(int M, int N, int* counts){
    int E=N/M;
    float chi=0.;
    for(int i=0; i<M; i++){
        chi+=(counts[i]-E)*(counts[i]-E);
    }
    chi/=E;
    return chi;
}

void DataChiQuad(int M, int N, ofstream& chiout){
    
    Random rand;   /*Inizializzazione del generatore di numeri casuali*/
    InizRandom(rand);

    float I=1./M;   /*ampiezza di ogni sottointervallo*/
    float maxs[M]; /*contiene l'estremo superiore di ogni intervallo*/
    for(int m=0; m<M; m++){
        maxs[m]=(m+1)*I;
    }
    
    for(int i=0; i<M; i++){
        int counts[M]={0};  /*conteggio delle estrazioni contenute in ogni intervallo*/
        for(int j=0; j<N; j++){
            float r=Rarandom();
            SearchInt(M, r, maxs, counts);    /*funzione che cerca il sottointervallo a cui appartiene il numero estratto e aggiorna il conteggio relativo*/
        }
        float chi=ChiSqu(M, N, counts);  /*i-esimo chi quadro calcolato con una funzione apposita*/
        chiout << chi << endl;  /*dato che poi plotterò*/
    }

    rand.SaveSeed();
}

void DataDistr(int M, int* Ns, ofstream& uniout, ofstream& eout, ofstream& lorout){
    Random rand;   /*Inizializzazione del generatore di numeri casuali*/
    InizRandom(rand);

    for(int i=0; i<M; i++){
        float unifs[4]={0.};
        float exps[4]={0.}; 
        float lors[4]={0.};   
        for(int j=0; j<4; j++){
            int k=0;
            while(k<Ns[j]){
                float r=Rarandom();
                unifs[j]+=1+(5*r);   /*distribuzione uniforme fra 1 e 6*/
                exps[j]+=-log(1-r);     /*distribuzione esponenziale con lambda=1*/
                lors[j]+=tan(M_PI*(r-0.5));   /*distribuzione lorentziana con mu=0 e Gamma=1*/
                k++;
            }
        }
        uniout << unifs[0] << " " << unifs[1] << " " << unifs[2] << " " << unifs[3] << " " << endl;
        eout << exps[0] << " " << exps[1] << " " << exps[2] << " " << exps[3] << " " << endl;
        lorout << lors[0] << " " << lors[1] << " " << lors[2] << " " << lors[3] << " " << endl;
    }

    rand.SaveSeed();    
}

void EndNeedle(float* starts, float t, int L, float* ends){
    ends[0]=starts[0]+(L*cos(t));
    ends[1]=starts[1]+(L*sin(t));
}

bool TouchLine(float* starts, float* ends, float* maxs, int Nl){
    /*suppongo linee parallele a x ergo guardo solo in che intervallo cadono la coordinata y di inizio e fine ago*/
    int s=BinSearchInt(0, Nl, starts[1], maxs, Nl);   /*indice che identifica in maxs il max dell'intervallo in cui cade la y della punta iniziale dell'ago*/
    int e=BinSearchInt(0, Nl, ends[1], maxs, Nl);   /*come s ma per la y della punta finale dell'ago*/
    /*una parte dell'ago tocca una linea se le due punte giacciono in intervalli diversi oppure una delle punte tocca una linea*/
    if(s!=e){   
        return true;
    }
    if(s-1>=0 && starts[1]==maxs[s-1]){
        return true;
    }
    if(s==Nl && starts[1]==maxs[s]){
        return true;
    }
    if(e-1>=0 && ends[1]==maxs[e-1]){
        return true;
    }
    if(e==Nl && ends[1]==maxs[e]){
        return true;
    }
    return false;
}

void DataBuffon(int L, int D, int B, int T, int P, ofstream& bout){
    /*Inizializzazione del generatore di numeri casuali*/
    Random rand;
    InizRandom(rand);

/*SE P/L NON é INTERO?*/
    int Nl=P/D;   /*numero di linee nel piano*/
    float maxs[Nl]; /*contiene l'estremo superiore di ogni intervallo*/
    for(int m=0; m<Nl; m++){
        maxs[m]=(m+1)*D;
    }

    float sumb=0;   /*somma a blocchi della stima*/
    float sum2b=0;  /*somma a blocchi della stima quadratica*/
    float valueb; /*stima a blocchi*/
    float value2b;    /*stima a blocchi al quadrato*/
    for(int j=0; j<B; j++){     /*ciclo sui blocchi*/
        int i=0;    /*numero di aghi validi e analizzati (i.e., cadono interamente del piano) per il j-simo blocco*/
        int Nbuf=0;    /*numero di aghi del j-simo blocco che intersecano una linea*/
        while(i<T){     /*analisi del j-simo blocco*/
            float starts[2];
            starts[0]=P*Rarandom();   /*genero coordinata x della punta dell'ago, distribuita uniformemente nel piano*/
            starts[1]=P*Rarandom();   /*genero coordinata y della punta dell'ago, distribuita uniformemente nel piano*/
    /*DA CAMBIARE*/
            float t=(M_PI/2)*Rarandom();    /*genero angolo theta fra asse x e ago, distribuito uniformemente fra 0 e pigreco mezzi*/
    /*DA CAMBIARE*/
            float ends[2];
            EndNeedle(starts, t, L, ends);    /*calcola coordinate dell'altra punta dell'ago*/
            if(ends[0]<=P && ends[1]<=P){   /*rigetto punti tc la fine dell'ago esce dal piano*/
                i++;
                if(TouchLine(starts, ends, maxs, Nl)){  /*OnLine()=true se l'ago tocca una linea*/
                    Nbuf++;     /*conteggio aghi che toccano le linee*/
                }
            }
        }
        float value=(2*L*T)/(Nbuf*D);   /*stima del pigreco data dal solo j-simo blocco*/
        sumb+=value;
        sum2b+=(value)*(value);
        valueb=sumb/(j+1);
        value2b=sum2b/(j+1);
        bout << valueb << " " << BlockError(valueb, value2b, j) << endl;
    }

    rand.SaveSeed();   
}