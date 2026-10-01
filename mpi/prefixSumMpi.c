#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char** argv) {

    unsigned int S;
    long long N;
    int rank, size;

    int *vetor = NULL;
    int *fatias = NULL;
    int *displs = NULL;

    MPI_Init(&argc, &argv);

    // Descobre o ID (rank) e a quantidade total de processos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Ações do processo zero 
    if (rank == 0) {
        // Lê a semente S e o tamanho N do vetor da entrada padrão
        if (scanf("%u %lld", &S, &N) != 2) {
            MPI_Finalize();
            return 1;
        }

        // Inicializa o vetor principal
        vetor = (int*) malloc(N * sizeof(int));

        // Alimenta o gerador de números aleatórios
        srand(S);
        for (long long i = 0; i < N; i++) {
            vetor[i] = rand() % 100;
        }

        // Aloca os vetores auxiliares do MPI_Scatterv APENAS no Rank 0
        fatias = (int*) malloc(size * sizeof(int));
        displs = (int*) malloc(size * sizeof(int));

        int resto_local = N % size;

        // Preenche o tamanho da fatia de cada rank
        for (int i = 0; i < size; i++) {
            fatias[i] = N / size;
        }
        fatias[size - 1] += resto_local; // A sobra vai para o último rank

        // Calcula os deslocamentos (offsets) no vetor principal
        displs[0] = 0;
        for (int i = 1; i < size; i++) {
            displs[i] = displs[i - 1] + fatias[i - 1];
        }
    }

    // Sincroniza N para que TODOS os ranks conheçam o tamanho do problema
    MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    // Agora que todos possuem N, calculamos o resto e o tamanho local de cada um
    int resto = N % size;
    long long tam_local = N / size;
    if (rank == size - 1) {
        tam_local += resto;
    }

    // Aloca a memória da fatia local recebida
    int *vetor_local = (int*) malloc(tam_local * sizeof(int));

    // Distribui o vetor original com fatias variáveis
    MPI_Scatterv(vetor, fatias, displs, MPI_INT, vetor_local, tam_local, MPI_INT, 0, MPI_COMM_WORLD);

    // Soma a fatia local
    long long sum = 0;
    for (long long i = 0; i < tam_local; i++) {
        sum += vetor_local[i];
    }

    // Reduz todas as somas locais para a soma global no Rank 0
    long long soma_global = 0;
    MPI_Reduce(&sum, &soma_global, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // Exibe a saída e libera a memória
    if (rank == 0) {
        printf("%lld\n", soma_global);
        free(vetor);
        free(fatias);
        free(displs);
    }

    free(vetor_local);
    MPI_Finalize();

    return 0;
}
