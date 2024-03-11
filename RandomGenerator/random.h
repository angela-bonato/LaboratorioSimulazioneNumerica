#ifndef __Random__
#define __Random__

// This class contains functions for generating random numbers using the RANNYU algorithm
class Random {

private:
  int m1,m2,m3,m4,l1,l2,l3,l4,n1,n2,n3,n4;

protected:

public:
  // Default constructor
  Random();
  // Destructor
  ~Random();
  // Method to set the seed for the RNG
  void SetRandom(int * , int, int);
  // Method to save the seed to a file
  void SaveSeed();
  // Method to generate a random number in the range [0,1)
  double Rannyu(void);
  // Method to generate a random number in the range [min,max)
  double Rannyu(double min, double max);
  // Method to generate a random number with a Gaussian distribution
  double Gauss(double mean, double sigma);
  //Metodo per generare distribuzione esponenziale
  double Exp(double lambda);
  //Metodo per generare distribuzione Cauchy-Lorentz
  double Lorentz(double mu, double gamma);
  //Metodo per generare distribuzione un angolo con metodo accept&reject
  double arTheta(double xmin, double xmax, double ymin, double ymax);
  //Metodo per generare distribuzione per l'importance sampling dell'esercizio 2.1
  double arImpSampling();
};

#endif // __Random__
