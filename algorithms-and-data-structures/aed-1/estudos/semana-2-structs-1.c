/*
➢Faça um programa que use uma estrutura do tipo
CD e faça a leitura de 10 cds (use um vetor de
estrutura do tipo cd). A estrutura CD deve conter
os seguintes campos:
Nome da banda

Data do lançamento do cd: dia, mês e ano
Data da contratação da empresa: dia, mês e ano
Valor do cd
Número de membros da banda
Produtora do cd
*/

#include <stdio.h>
#define tam 2

struct data
{
    int dia;
    int mes;
    int ano;
};

struct CD
{
    char Nome_da_banda[20];
    struct data dl, dc;
    float preco;
    int n_membros;
    char produtora[20];
};

int main()
{
    struct CD cd[10];

    for (int i = 0; i < tam; i++)
    {
        system("clear||cls");
        printf("\nBanda %d | Digite o nome da banda: ", i + 1);
        scanf("%s", &cd[i].Nome_da_banda);

        printf("\nBanda %d | Digite abaixo a data de lancamento da banda", i + 1);
        printf("\nDia: ");
        scanf("%d", &cd[i].dl.dia);
        printf("Mes: ");
        scanf("%d", &cd[i].dl.mes);
        printf("Ano: ");
        scanf("%d", &cd[i].dl.ano);

        printf("\nBanda %d | Digite abaixo a data de contratacao da empresa", i + 1);
        printf("\nDia: ");
        scanf("%d", &cd[i].dc.dia);
        printf("Mes: ");
        scanf("%d", &cd[i].dc.mes);
        printf("Ano: ");
        scanf("%d", &cd[i].dc.ano);

        printf("\nBanda %d | Digite o nome da produtora do cd: ", i + 1);
        scanf("%s", &cd[i].produtora);
    }
    system("clear||cls");

    for (int i = 0; i < tam; i++)
    {
        printf("Banda %d | Nome da banda %s\n", i + 1, cd[i].Nome_da_banda);
        printf("Banda %d | Data de lancamento da banda: %d/%d/%d\n", i + 1, cd[i].dl.dia, cd[i].dl.mes, cd[i].dl.ano);
        printf("Banda %d | Data de contratacao da banda: %d/%d/%d\n", i + 1, cd[i].dc.dia, cd[i].dc.mes, cd[i].dc.ano);
        printf("Banda %d | Valor do cd: %.1f\n", i + 1, cd[i].preco);
        printf("Banda %d | Numero de membros da banda: %d\n", i + 1, cd[i].n_membros);
        printf("Banda %d | Nome da produtora do cd: %s\n\n", i + 1, cd[i].produtora);
    }

    return 0;
}