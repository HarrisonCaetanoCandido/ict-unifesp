#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *pHora;
    int *pMinuto;
    int *pSegundo;
} horario;

int main()
{
    horario hoje;
    int hora = 200;
    int minuto = 300;
    int segundo = 400;

    hoje.pHora = &hora; /* Basicamente pega o endereco da variavel 'hora',
                           vai na struct e faz pHora receber esse endereco,
                           que posteriormente sera apontado pelo ponteiro*/
    hoje.pMinuto = &minuto;
    hoje.pSegundo = &segundo;

    printf("Hora: %d\n", *hoje.pHora); // Acessando o valor do ponteiro dentro da struct
    printf("Minuto: %d\n", *hoje.pMinuto);
    printf("Segundo: %d\n", *hoje.pSegundo);

    getch();

    return 0;
}