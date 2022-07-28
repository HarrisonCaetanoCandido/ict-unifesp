#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char nome[10][80]; // dez nomes de 80 caracteres cada

void ordenacao();

void ordenacao(){
    int x,y,r;
    char aux[80];

    for(x=0; x<=9; x++){
        for(y=x+1;y<=80;y++){
            r=strcmp(nome[x],nome[y]);
            if(r>0){
                strcpy(aux,nome[x]);
                strcpy(nome[x],nome[y]);
                strcpy(nome[y],aux);
            }
        }
    }
}

int main(){
    int x;

    printf("Digite 10 nomes: ");
    for(x=0;x<=9;x++){
        gets(nome[x]);
    }

    ordenacao();

    printf("Nomes ordenados: \n");
    for(x=0;x<=9;x++){
        printf("%s",nome[x]);
    }

    return 0;
}
