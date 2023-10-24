/*
Suponha dois vetores, um de registros de estudantes e outro de
registros de funcionários. Cada registro de estudante contém
campos para o último nome, o primeiro nome e um índice de
pontos de graduação. Cada registro de funcionário contém
membros para o último nome, primeiro nome e o salário. Ambos
os vetores são classificados em ordem alfabética pelo último e
pelo primeiro nome. Dois registros com o último e o primeiro
nome iguais não aparecem no mesmo vetor. Faça um programa
em C para conceder um aumento de 10% a todo funcionário
que tenha um registro de estudante cujo índice de pontos de
graduação seja maior que 3.0.

Obs: Não é necessário implementar a ordenação. Considere
que os dados já são entrados pelo usuário na ordem correta.
*/

#include <stdio.h>
#include <stdlib.h>
#define str 30

typedef struct ESTUDANTES
{
    char first_name[str];
    char last_name[str];
    int pnts_grad;
} Estudantes;

typedef struct FUNCIONARIOS
{
    char first_name[str];
    char last_name[str];
    float salario;
} Funcionarios;

void desaloca(Estudantes *estudante[], Funcionarios *funcionario[], int index);

// dois vetores
// um pra funcionarios
// um pra estudantes => (ultimo_nome,primeiro_nome,salario)
// ambos os vetores sao classificados em ordem alfabetica
/* Faça um programa em C para conceder um aumento de 10% a todo funcionário
que tenha um registro de estudante cujo índice de pontos de
graduação seja maior que 3.0.*/

int main()
{
    Estudantes *estudante[3];     // vetor de ponteiros do tipo Estudantes
    Funcionarios *funcionario[3]; // vetor de ponteiros do tipo Funcionarios
    int index = 0, selecione;

    int ps;
    for (ps = 0; ps < 3; ps++)
    {
        estudante[ps] = (Estudantes *)malloc(sizeof(Estudantes));
        fflush(stdin);
        printf("Estudante %d | First_name: ", ps);
        fgets(estudante[ps]->first_name, str, stdin);
        fflush(stdin);
        printf("Estudante %d | Last_name: ", ps);
        fgets(estudante[ps]->last_name, str, stdin);
        printf("Estudante %d | Pontos graduacao: ", ps);
        scanf("%d", &estudante[ps]->pnts_grad);
    }

    for (ps = 0; ps < 3; ps++)
    {
        funcionario[ps] = (Funcionarios *)malloc(sizeof(Funcionarios));
        fflush(stdin);
        printf("Funcionario %d | First_name: ", ps);
        fgets(funcionario[ps]->first_name, str, stdin);
        fflush(stdin);
        printf("Funcionario %d | Last_name: ", ps);
        fgets(funcionario[ps]->last_name, str, stdin);
        printf("Funcionario %d | Salario: ", ps);
        scanf("%f", &funcionario[ps]->salario);
    }

    int i, j, k, first_iguais, last_iguais, fsenao = 0, lsenao = 0, efirst_iguais, ffirst_iguais, elast_iguais, flast_iguais;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            k = 0;
            while (estudante[i]->first_name[k] == funcionario[j]->first_name[k] && estudante[i]->first_name[k] != '\0' && funcionario[j]->first_name[k] != '\0')
            {
                k++;
            }
            if (estudante[i]->first_name[k] == '\0' && funcionario[j]->first_name[k] == '\0')
            {
                efirst_iguais = i;
                ffirst_iguais = j;
            }
            else
            {
                fsenao++;
            }
        }
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            k = 0;
            while (estudante[i]->last_name[k] == funcionario[j]->last_name[k] && estudante[i]->last_name[k] != '\0' && funcionario[j]->last_name[k] != '\0')
            {
                k++;
            }
            if (estudante[i]->last_name[k] == '\0' && funcionario[j]->last_name[k] == '\0')
            {
                elast_iguais = i;
                flast_iguais = j;
            }
            else
            {
                lsenao++;
            }
        }
    }

    float salario = (((funcionario[ffirst_iguais]->salario) * 10) / 100) + funcionario[ffirst_iguais]->salario;
    if (fsenao == 3 && lsenao == 3)
    {
        printf("Nenhum dos nomes nos dois vetores recebeu aumento!\n");
    }
    else
    {
        if (estudante[efirst_iguais]->pnts_grad > 3)
        {
            printf("Estudante: %s %s", estudante[efirst_iguais]->first_name, estudante[elast_iguais]->last_name);
            printf("Funcionario: %s %s", funcionario[ffirst_iguais]->first_name, funcionario[flast_iguais]->last_name);
            printf("Salario: %.3f\n\n", salario);
        }
    }

    desaloca(estudante, funcionario, index);

    return 0;
}

void desaloca(Estudantes *estudante[], Funcionarios *funcionario[], int index)
{
    int i;
    for (i = 0; i < index; i++)
    {
        free(estudante[i]);
        free(funcionario[i]);
    }
}