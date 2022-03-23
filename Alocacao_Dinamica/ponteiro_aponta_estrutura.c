#include <stdio.h>

typedef struct{
        int minutos;
        int segundos;
    }minutos_segundos;

typedef struct{
        int hora;
        minutos_segundos ms;
    }horario;

int main(){
    horario agora, *depois;
    depois=&agora; /* Atribuindo um valor a *depois veremos que a variavel escrevera esse valor no endereco de memoria apontado, logo
                      se *depois=4, entao agora=4, pois em depois->ms.minutos=10 por exemplo, temos na realidade:

                      depois=>agora=>ms=>minutos  */ 

    depois->hora=19;
    depois->ms.minutos=10;
    depois->ms.segundos=57;

    printf("Horario depois: %dh %dm %ds\n",agora.hora, agora.ms.minutos, agora.ms.segundos); 

    horario antes;
    int somatorio=100;

    antes.hora = somatorio + depois->ms.segundos;
    antes.ms.minutos = agora.hora - depois->ms.minutos;
    antes.ms.segundos = depois->ms.minutos * depois->ms.segundos;

    printf("Horario depois de fazer umas operacoes aleatorias: %dh %dm %ds\n",antes.hora,antes.ms.minutos,antes.ms.segundos);

    return 0;
}