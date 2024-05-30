#include <cstddef>
#include "mpi.h"
#include "city.h"
#include "path.h"

using namespace std;

//funzioni per gestire le classi con mpi

//crea un tipo MPI analogo a City
MPI_Datatype create_mpi_city();
//permette di inviare un vector<City> ad un altro processo MPI
void sendCityVec(vector<City>& cities, int dest, int tag, MPI_Comm comm);
//permette di ricevere un vector<City> da un altro processo MPI
void recCityVec(vector<City>& cities, int src, int tag, MPI_Comm comm);

//permette di inviare un singolo Path ad un altro processo MPI
void sendPath(Path& path, int dest, int tag, MPI_Comm comm);
//permette di ricevere un singolo Path da un altro processo MPI
void recPath(Path& path, int src, int tag, MPI_Comm comm);
//permette di inviare un vector<Path> ad un altro processo MPI
void sendPathVec(vector<Path>& paths, int dest, int tag, MPI_Comm comm);
//permette di ricevere un vector<Path> da un altro processo MPI
void recPathVec(vector<Path>& paths, int src, int tag, MPI_Comm comm);