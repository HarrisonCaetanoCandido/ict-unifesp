#include <stdio.h>

int main()
{

    const int bimanuais = 4;
    const int numalunos = 4;

    float notas[numalunos][bimanuais];
    float medias[numalunos], soma = 0;

    for (int aluno = 0; aluno < 4; aluno++)
    { // linha
        printf("\nInsira as 4 notas do aluno %d\n", aluno + 1);
        for (int bim = 0; bim < 4; bim++)
        { // coluna
            printf("Nota %d: ", bim + 1);
            scanf("%f", &notas[aluno][bim]);
            soma += notas[aluno][bim];
        }
        medias[aluno] = soma / bimanuais;
        soma = 0;
    }

    for (int aluno = 0; aluno < 4; aluno++)
    {
        printf("|  ");
        for (int bim = 0; bim < 4; bim++)
        {
            printf("%.1f ", notas[aluno][bim]);
        }
        printf(" |\n");
    }
    printf("\n");

    for (int aluno = 0; aluno < 4; aluno++)
    {
        printf("aluno %d | Media: %.1f\n", aluno + 1, medias[aluno]);
    }
    printf("\n");

    return 0;
}