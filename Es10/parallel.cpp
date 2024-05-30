#include "parallel.h"

using namespace std;

MPI_Datatype create_mpi_city(){
    MPI_Datatype MPIcity;

    int block_lengths[3] = {1, 1, 1};
    MPI_Datatype types[3] = {MPI_DOUBLE, MPI_DOUBLE, MPI_INT};
    MPI_Aint offsets[3];
    offsets[0] = offsetof(City, _x);
    offsets[1] = offsetof(City, _y);
    offsets[2] = offsetof(City, _n);

    MPI_Type_create_struct(3, block_lengths, offsets, types, &MPIcity);
    MPI_Type_commit(&MPIcity);

    return MPIcity;
}

void sendCityVec(vector<City>& cities, int dest, int tag, MPI_Comm comm) {
    int vec_size = cities.size();
    MPI_Send(&vec_size, 1, MPI_INT, dest, tag, comm);
    MPI_Datatype MPIcity = create_mpi_city();
    MPI_Send(cities.data(), vec_size, MPIcity, dest, tag, comm);
    MPI_Type_free(&MPIcity);
}

void recCityVec(vector<City>& cities, int src, int tag, MPI_Comm comm) {
    int vsize;
    MPI_Recv(&vsize, 1, MPI_INT, src, tag, comm, MPI_STATUS_IGNORE);
    cities.resize(vsize);
    MPI_Datatype MPIcity=create_mpi_city();
    MPI_Recv(cities.data(), vsize, MPIcity, src, tag, comm, MPI_STATUS_IGNORE);
    MPI_Type_free(&MPIcity);
}

void sendPath(Path& path, int dest, int tag, MPI_Comm comm) {
    int order_size=path.get_length();
    double loss=path.get_loss();
    int Nc=path.get_Nc();
    MPI_Send(&order_size, 1, MPI_INT, dest, tag, comm);
    MPI_Send(path.get_ord().data(), order_size, MPI_INT, dest, tag, comm);
    MPI_Send(&loss, 1, MPI_DOUBLE, dest, tag, comm);
    MPI_Send(&Nc, 1, MPI_INT, dest, tag, comm);
}

void recPath(Path& path, int src, int tag, MPI_Comm comm) {
    int order_size;
    double loss;
    int Nc;
    MPI_Recv(&order_size, 1, MPI_INT, src, tag, comm, MPI_STATUS_IGNORE);
    vector<int> order(order_size);
    MPI_Recv(order.data(), order_size, MPI_INT, src, tag, comm, MPI_STATUS_IGNORE);
    MPI_Recv(&loss, 1, MPI_DOUBLE, src, tag, comm, MPI_STATUS_IGNORE);
    MPI_Recv(&Nc, 1, MPI_INT, src, tag, comm, MPI_STATUS_IGNORE);
    path.set_ord(order);
    path.set_loss(loss);
    path.set_Nc(Nc);
}

void sendPathVec(vector<Path>& paths, int dest, int tag, MPI_Comm comm) {
    int num_paths=paths.size();
    MPI_Send(&num_paths, 1, MPI_INT, dest, tag, comm);
    for (auto& path : paths) {
        sendPath(path, dest, tag, comm);
    }
}

void recPathVec(vector<Path>& paths, int src, int tag, MPI_Comm comm) {
    int num_paths;
    MPI_Recv(&num_paths, 1, MPI_INT, src, tag, comm, MPI_STATUS_IGNORE);
    paths.resize(num_paths);
    for (auto& path : paths) {
        recPath(path, src, tag, comm);
    }
}