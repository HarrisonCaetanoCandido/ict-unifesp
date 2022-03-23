#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int valor;
    struct lista *proximo; //Passa o endereco de memoria de uma outra estrutura lista
}Lista;

int main(){
    Lista m1,m2,m3; // Membros da lista, diferentes estruturas
    Lista *gancho=&m1;

    m1.valor=10;
    m2.valor=20;
    m3.valor=30;

    m1.proximo=&m2;
    m2.proximo=&m3;
    m3.proximo= NULL; // Struct-lista-ponteiro_vazio (Representa Nulo para *proximo de m3)

    while(gancho!=NULL){
        printf("%d\n",gancho->valor);
        gancho=gancho->proximo; // Gancho eh igual ao proximo de gancho
    }

    return 0;
}