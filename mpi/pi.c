#include <stdio.h>

int main() {
    long long N;
    
    // Lê o número de retângulos da entrada padrão
    if (scanf("%lld", &N) != 1) {
        return 1;
    }

    double L = 1.0 / N;
    double sum = 0.0;

    // Calcula o somatório linearmente
    for (long long i = 0; i < N; i++) {
        double x = (i + 0.5) * L;
        sum += 4.0 / (1.0 + x * x);
    }

    double pi = sum * L;

    // A saída deve possuir o número aproximado de PI, com 10 casas decimais
    printf("%.10lf\n", pi);

    return 0;
}
