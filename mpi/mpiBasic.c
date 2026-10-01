#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída para a função printf
#include <mpi.h>   // Inclui a biblioteca MPI necessária para funções e constantes paralelas

int main(int argc, char** argv) { // Função principal que recebe os argumentos da linha de comandos

    int rank; // Variável para guardar o identificador único (ID) do processo atual
    int size; // Variável para guardar o total de processos criados pelo mpirun

    MPI_Init(&argc, &argv); // Inicializa o ambiente de comunicação paralelo do MPI

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtém o identificador (0 até size-1) do processo atual

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtém a quantidade total de processos a executar

    int valor_local = (rank + 1) * 10; // Cada processo gera um número individual baseado no seu rank (ex: 10, 20, 30...)

    int soma_total = 0; // Variável que receberá o resultado acumulado final no processo líder

    // Junta os valores de todos os processos e realiza a soma no Rank 0
    MPI_Reduce(
        &valor_local,   // Ponteiro para o dado individual que este processo enviará
        &soma_total,    // Ponteiro para a variável onde o resultado final será guardado
        1,              // Quantidade de dados a enviar por cada processo (1 elemento)
        MPI_INT,        // Tipo do dado no MPI correspondente ao int do C
        MPI_SUM,        // Operação coletiva a realizar (Soma)
        0,              // Rank do processo destino que receberá a soma acumulada
        MPI_COMM_WORLD  // Comunicador padrão que engloba todos os processos
    );

    if (rank == 0) { // Apenas o processo de Rank 0 entra neste bloco condicional
        printf("Soma total acumulada dos %d processos: %d\n", size, soma_total); // Imprime o resultado final no ecrã
    }

    MPI_Finalize(); // Finaliza as comunicações MPI e liberta os recursos do sistema

    return 0; // Termina o programa informando sucesso ao sistema operativo
}
