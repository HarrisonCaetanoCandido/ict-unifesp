#include <stdio.h>

char escrever(char linha[],int tam,int cont);

int main(){
    int tam = 100,cont=0;
    char linha1[tam];
    char linha2[tam];

    escrever(linha1,tam,cont);cont++;

    escrever(linha2,tam,cont);cont++;

    printf("String1: %s\n",linha1);
    printf("String2: %s",linha2);

    return 0;
}

char escrever(char linha[], int tam, int cont){ // Assim eh possivel ler strings com espaco
    int i=0;char caractere;
    printf("String %d | Digite uma string de caracteres: ",cont+1);
    do{
        caractere=getchar();
        linha[i]=caractere;
        i++;
    }while(caractere!='\n'); // enquanto caractere for diferente de 'enter' faca tal..
    linha[i-1]='\0';

    return linha;
}