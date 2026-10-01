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

  double sum = 0.0;
  double soma_global = 0.0;

  // Calcula o somatório dos N termos
  for (long long int i = rank; i < N; i = i + size) {
      if (i % 2 == 0) {
          sum += 1.0 / (2.0 * i + 1.0);
      } else {
          sum -= 1.0 / (2.0 * i + 1.0);
      }
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
    double pi = 4.0 * soma_global;
    
    // A saída deve possuir o número aproximado de PI, com 10 casas decimais
    printf("%.11lf\n", pi);
  }


  // Finaliza o ambiente MPI
  MPI_Finalize();

  return 0;
}

/*
int main() {
    long long int N;

    // Lê a quantidade de termos N da entrada padrão
    if (scanf("%lld", &N) != 1) {
        return 1;
    }

    double sum = 0.0;

    // Calcula o somatório dos N termos
    for (long long int i = 0; i < N; i++) {
        if (k % 2 == 0) {
            sum += 1.0 / (2.0 * i + 1.0);
        } else {
            sum -= 1.0 / (2.0 * i + 1.0);
        }
    }

    // A multiplicação por 4 é realizada apenas após a soma de todos os termos
    double pi = 4.0 * sum;

    // A saída deve possuir o valor de PI com 11 casas decimais
    printf("%.11lf\n", pi);
*/
