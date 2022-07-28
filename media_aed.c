#include <stdio.h>

int main()
{
    float peso1, peso2, p1, p2, atv, p, nota, mediaps, mediat, divisor;
    int i, n, op;

    p1 = 4.00;
    op = 0;

    while (op != -1)
    {
        divisor = nota = 0.00;

        do
        {
            printf("Digite o peso 1(provas): ");
            scanf("%f", &peso1);
        } while (peso1 > 1);

        do
        {
            printf("Digite o peso 2(exercicios): ");
            scanf("%f", &peso2);
        } while (peso2 > 1);

        do
        {
            printf("Nota esperada na p2: ");
            scanf("%f", &p2);
        } while (p2 > 10);

        do
        {
            printf("Digite quantos exercicios quer considerar: ");
            scanf("%d", &n);
        } while (n > 10);

        i = 0;
        while (i < n)
        {
            printf("\n");
            printf("Digite a nota do exercicio %d: ", i + 1);
            scanf("%f", &atv);

            printf("Digite o peso do exercicio %d: ", i + 1);
            scanf("%f", &p);

            nota += (atv * p);
            divisor += p;

            i++;
        }

        mediaps = ((p1 + p2) / 2) * peso1;

        nota = (nota / divisor) / 10 * peso2;

        mediat = mediaps + nota;

        printf("\nmediaps: %f\n", mediaps);
        printf("nota: %f\n", nota);
        printf("Media: %f\n\n", mediat);

        printf("Deseja sair do programa? (sim: -1 | nao: 1): ");
        scanf("%d", &op);
    }

    return 0;
}