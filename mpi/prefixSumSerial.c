#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned int S;
  long long N;

  // Lê a semente S e o tamanho N do vetor da entrada padrão
  if (scanf("%u %lld", &S, &N) != 2) {
      return 1;
  }

  // Alimenta o gerador de números aleatórios com a semente fornecida
  srand(S);

  long long sum = 0;

  // Gera N números aleatórios com a operação mod 100 e acumula a soma
  for (long long i = 0; i < N; i++) {
      int val = rand() % 100;
      sum += val;
  }

  // Imprime o resultado final da soma
  printf("%lld\n", sum);

  return 0;
}
