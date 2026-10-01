#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv) {

  long long N;
  int rank, size;


  // Inicializa o ambiente MPI
  MPI_Init(&argc, &argv);

  if(rank == 0){
    scanf("%lld", &N);
  }
  
  // Envia o número de quadrados para todos os processos
  MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

  // Descobre qual é o ID (rank) do processo atual
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  // Descobre a quantidade total de processos criados
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  double L = 1.0 / N;
  double sum = 0.0;
  double soma_global = 0.0;


  // Realiza as operações do PI
  for (long long i = rank; i < N; i = i + size) {
    double x = (i + 0.5) * L;
    sum += 4.0 / (1.0 + x * x);
  }

  // Reduz os valores de sum em uma soma global
  MPI_Reduce(
      &sum,
      &soma_global,
      1, 
      MPI_DOUBLE, 
      MPI_SUM, 
      0, 
      MPI_COMM_WORLD
  );

  if (rank ==0){
    // Calcula pi com as somas realizadas
    double pi = soma_global * L;
    
    // A saída deve possuir o número aproximado de PI, com 10 casas decimais
    printf("%.10lf\n", pi);
  }


  // Finaliza o ambiente MPI
  MPI_Finalize();

  return 0;
}

