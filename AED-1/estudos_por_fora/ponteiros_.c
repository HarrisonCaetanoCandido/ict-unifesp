/*
## Teoria - Depende da arquitetura do computador, porém aqui temos um computador de 64 bits

1 bit - Menor tamanho ou espaco de memoria no computador, so pode armazenar 0 ou 1

8 bits = 1 byte

1024 bytes = 1 kilobyte

1024 kilobyte = 1 megabytes

1024 megabytes = 1 gigabyte

## Tipos de Dados

int - 4 bits
float - 4 bits
double - 8 bits

Se quero um endereco de memoria
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{ /*
int x;
x=10;

int *ponteiro; // Declara que é do tipo ponteiro que ira apontar para o valor naquele endereco de memoria atribuido
ponteiro = &x; // variavel ponteiro que foi declarada como sendo do tipo ponteiro aponta para o endereco de memoria de x

/* Dos dois de cima é basicamente:
int *ponteiro; - Aponta para o valor do endereco de memoria recebido
ponteiro = &x - Recebe o endereco de memoria da variavel x

Entao basicamente a variavel ponteiro tem o endereco de x e quando usamos *ponteiro, temos o valor apontado por *ponteiro que aquele endereco de memoria de x guarda
*/

    // printf("%d",&x); //Acessamos o endereco de memoria da variavel dentro do SO
    /*
    int z=10;
    int *ponteiro;
    ponteiro = &z;

    /* Ou entao:

    int z=10;
    int *ponteiro=&z;

    int y=20;
    *ponteiro=y;

    printf("\nz: %d *ponteiro: %d y: %d\n",z,*ponteiro,y);*/

    int t = 90;
    double o = 20.70;
    char z = 'a';

    int *pT = &t;
    double *pO = &o;
    char *pZ = &z;

    printf("Endereco de t: %d, Valor de t: %d\n", pT, *pT);
    printf("Endereco de o: %d, Valor de o: %f\n", pO, *pO);
    printf("Endereco de z: %d, Valor de z: %c\n", pZ, *pZ);

    return 0;
}
