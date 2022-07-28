/*
Escreva um trecho de código para fazer a
criação de novos tipos de dados conforme
solicitado a seguir:
✓ Horário: composto de hora, minutos e segundos.
✓ Data: composto de dia, mês e ano.
✓ Compromisso: composto de uma data, horário e
texto que descreve o compromisso.

Refaça o programa anterior da banda de
músicas (exercício 1) utilizando ponteiro para
estrutura e considerando que há dados de n
bandas a serem lidas (n é entrado pelo
usuário).
*/
#include <stdio.h>
#include <string.h>
#define tam 2

struct hora
{
    int hora;
    int minutos;
    int segundos;
};

struct data
{
    int dia;
    int mes;
    int ano;
};

typedef struct
{
    struct hora hr;
    struct data dt;
    char texto[20];
} compromisso;

compromisso escrever_string(compromisso cr[]);

int main()
{
    int qtd;
    printf("Digite quantas bandas deseja registrar: ");
    scanf("%d", &qtd);

    compromisso *cr[qtd]; // vetor de ponteiros com n posicoes, n enderecos desses registros

    for (int i = 0; i < qtd; i++)
    {
        cr[i] = (compromisso *)malloc(sizeof(compromisso)); // aloca memoria suficiente para 1 registro em especifico
        printf("\nCompromisso %d | Digite abaixo a hora do compromisso:", i + 1);
        printf("\n(hh:mm:ss): ");
        scanf("%d:%d:%d", &cr[i]->hr.hora, &cr[i]->hr.minutos, &cr[i]->hr.segundos);

        printf("\nCompromisso %d | Digite abaixo a data do compromisso", i + 1);
        printf("\n(dd/mm/aa): ");
        scanf("%d/%d/%d", &cr[i]->dt.dia, &cr[i]->dt.mes, &cr[i]->dt.ano);

        fflush(stdin);
        printf("\nCompromisso %d | Digite a descricao: ", i + 1);
        // fgets(&cr[i]->texto,20,stdin);
        escrever_string(cr[i]);
        system("clear||cls");
    }
    system("clear||cls");

    for (int i = 0; i < tam; i++)
    {
        printf("Compromisso %d | Hora: %d:%d:%d\n", i + 1, cr[i]->hr.hora, cr[i]->hr.minutos, cr[i]->hr.segundos);
        printf("Compromisso %d | Data: %d/%d/%d\n", i + 1, cr[i]->dt.dia, cr[i]->dt.mes, cr[i]->dt.ano);
        printf("Compromisso %d | Descricao: %s\n\n", i + 1, cr[i]->texto);
    }
    free(cr);
    return 0;
}

compromisso escrever_string(compromisso cr[])
{
    char caractere;
    int i = 0;
    do
    {
        caractere = getchar();
        cr->texto[i] = caractere;
        i++;
    } while (caractere != '\n');
    cr->texto[i - 1] = '\0';
}