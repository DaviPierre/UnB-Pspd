#include <stdio.h>

int main() {
  long long int N;

  // Lê a quantidade de termos N da entrada padrão
  if (scanf("%lld", &N) != 1) {
      return 1;
  }

  double sum = 0.0;

  // Calcula o somatório dos N termos
  for (long long int i = 0; i < N; i++) {
      if (i % 2 == 0) {
          sum += 1.0 / (2.0 * i + 1.0);
      } else {
          sum -= 1.0 / (2.0 * i + 1.0);
      }
  }

  // A multiplicação por 4 é realizada apenas após a soma de todos os termos
  double pi = 4.0 * sum;

  // A saída deve possuir o valor de PI com 11 casas decimais
  printf("%.11lf\n", pi);

  return 0;
}
