/*
Escreva um trecho de código para fazer a
criação de novos tipos de dados conforme
solicitado a seguir:
✓ Horário: composto de hora, minutos e segundos.
✓ Data: composto de dia, mês e ano.
✓ Compromisso: composto de uma data, horário e
texto que descreve o compromisso.
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

struct compromisso
{
    struct hora hr;
    struct data dt;
    char texto[20];
};

int main()
{
    struct compromisso cr[10];

    for (int i = 0; i < tam; i++)
    {
        printf("\nCompromisso %d | Digite abaixo a hora do compromisso", i + 1);
        printf("\nHora: ");
        scanf("%d", &cr[i].hr.hora);
        printf("Minuto: ");
        scanf("%d", &cr[i].hr.minutos);
        printf("Segundo: ");
        scanf("%d", &cr[i].hr.segundos);

        printf("\nCompromisso %d | Digite abaixo a data do compromisso", i + 1);
        printf("\nDia: ");
        scanf("%d", &cr[i].dt.dia);
        printf("Mes: ");
        scanf("%d", &cr[i].dt.mes);
        printf("Ano: ");
        scanf("%d", &cr[i].dt.ano);

        scanf("%c");
        printf("\nCompromisso %d | Digite a descricao: ", i + 1);
        fgets(&cr[i].texto, 20, stdin);
        system("clear||cls");
    }
    system("clear||cls");

    for (int i = 0; i < tam; i++)
    {
        printf("Compromisso %d | Hora: %d:%d:%d\n", i + 1, cr[i].hr.hora, cr[i].hr.minutos, cr[i].hr.segundos);
        printf("Compromisso %d | Data: %d/%d/%d\n", i + 1, cr[i].dt.dia, cr[i].dt.mes, cr[i].dt.ano);
        printf("Compromisso %d | Descricao: %s\n", i + 1, cr[i].texto);
    }

    return 0;
}