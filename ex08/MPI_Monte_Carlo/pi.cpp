#include <iostream>
#include <mpi.h>
#include <random>

using namespace std;

int main(int argc, char *argv[]) {

  /* calculating pi with mpi version 1 */

  int p;                      // number of processes
  int n = atoi(argv[1]);                      // number of samples per processes
  double global_counter;                      // will count all points (by all threads) inside the circle
  double counter;                             // will count points for each processes

  // start parallel environment

  MPI_Init(&argc, &argv);

  int id;                                     // id of thread
  MPI_Comm_rank(MPI_COMM_WORLD, &id);         // give each thread id
  MPI_Comm_size(MPI_COMM_WORLD, &p);         // get number of processesS

  // create random numbers for each thread

  default_random_engine generator;
  generator.seed(id + 1);
  uniform_real_distribution<double> distribution(-1.0, 1.0);

  // loop through the samples

  counter = 0.0;
  for (int i = 0; i < n; i++){

    double x = distribution(generator);
    double y = distribution(generator);

    // if points in circle chnage counter

    if (x * x + y * y <= 1.0){counter += 1.0;}


  }

  // reduction to global global_counter

  MPI_Reduce(&counter, &global_counter, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  // print if process is finished

  cout << "Process " << id << " is finished." << endl;

  MPI_Finalize();

  // print the approximation for pi

  if (id==0) {cout << "Pi is approximately " << 4.0 * global_counter / (n * p) << " based on " << n * p << " samples" << endl;}

  return 0;
}
