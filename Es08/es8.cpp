#include "lib8.h"
#include "../RandomGenerator/random.h"
#include "../libGen.h"

using namespace std;
 
int main (int argc, char *argv[]){

    /*Esercizio 8.1*/
    cout << "Inizio esercizio 8.1." << endl;

    int M=10000;   /*numero totale di passi*/
    int N=50;  /*numero di blocchi*/
    int L=M/N;  /*numero di passi per ogni blocco*/
    int A=10000;    /*numero passi per l'equilibrazione*/
    double start=5.;    /*punto di parteza del sampling, ora settato a caso per l'equilibrazione*/
    double delta=2.7;   /*parametro che regola la larghezza di ogni passo, settato tc l'accettazione media sia circa 0.5*/
    double mu=0.85;
    double sigma=0.65; /*parametri di psi*/

    start=Equilibration(start, A, delta, mu, sigma);   /*aggiorno la partenza dell'analisi dati*/
    ofstream eout; /*file con i dati a blocchi di energia locale*/
    ofstream xout; /*file con alcuni valori di x generati*/
    eout.open("locenergy.dat");
    xout.open("genpoints.dat");
    EnergyAnalysis(start, N, L, delta, mu, sigma, xout, eout);  /*racchiudo tutto il calcolo in una funzione apposita*/
    eout.close();
    xout.close();
    
    cout << "Conclusione esercizio 8.1." << endl;

    /*Esercizio 8.2*/
    cout << "Inizio esercizio 8.2." << endl;
    
    double beta_min=0.5;    /*temperatura massima del sistema, man mano la abbasso (cioè alzo beta)*/
    double beta_max=81.;
    double beta_step=2.;
    double new_delta=0.3;
    double mu_start=1.5;
    double sigma_start=1.5;

    ofstream pout; /*file con i valori migliori di mu sigma*/
    ofstream bout;  /*valori di beta analizzati e passi fatti per ognuno*/
    ofstream hout;  /*valori a blocchi di H per ogni beta*/
    ofstream finxout;  /*sampling di psi^2 con valori ottimali di mu e sigma*/
    ofstream fineout;  /*valori a blocchi di H con valori ottimali di mu e sigma*/
    pout.open("params.dat");
    bout.open("beta.dat");
    hout.open("hstep.dat");
    finxout.open("finalpoints.dat");
    fineout.open("finalenergies.dat");
    InitFiles(pout, bout, hout, finxout, fineout);
    SimAnnealing(new_delta, mu_start, sigma_start, beta_min, beta_max, beta_step, pout, bout, hout, finxout, fineout);
    pout.close();
    bout.close();
    hout.close();
    finxout.close();
    fineout.close();

    cout << "Conclusione esercizio 8.2." << endl;

    return 0;
}