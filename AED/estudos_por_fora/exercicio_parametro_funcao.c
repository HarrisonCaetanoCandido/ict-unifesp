/*Faça um programa que possua um procedimento para ler 2 notas (chamar um
procedimento para ler 2 notas válidas - menor que 10 pontos - não lendo com scanf no
main), outro procedimento que dadas estas 2 notas vai calcular a média simples -
(n1+n2)/2 - e a média ponderada, onde a nota 2 tem peso 2, isto é ( n1 + n2 *2 ) / 3, e
um último procedimento que vai exibir na tela todos os dados que foram fornecidos e
calculados. Ou seja, seu programa terá 3 procedimentos: le_notas, calc_media e
exibe_dados. (6 pts)*/

#include <stdio.h>

typedef struct{
    float n1;
    float n2;
    float media_aritm;
    float media_pond;
}Notas;

void ler(){
    Notas *notas = (Notas *)malloc(sizeof(Notas)); // Aloca memoria

    printf("Digite a nota 1: ");
    scanf("%f",&notas->n1);

    printf("\nDigite a nota 2: ");
    scanf("%f",&notas->n2);

        if(notas->n1>10){
            while(notas->n1>10){
                printf("Digite a nota 1 novamente: ");
                scanf("%f",&notas->n1);
        }
        if(notas->n2>10){
            while(notas->n2>10){
                printf("\nDigite a nota 2 novamente: ");
                scanf("%f",&notas->n2);
            }
        }
        }
}

float mediaritm(){
    Notas *notas;

    notas->media_aritm=(notas->n1+notas->n2)/2;
}

float mediapond(){
    Notas *notas;
    
    notas->media_pond=(notas->n1+(notas->n2)*2)/3;
}

float exibe_dados(){
    Notas *notas;
    system("clear||cls");
    printf("Nota 1: %.2f, Nota 2: %.2f\n\n",notas->n1,notas->n2);
    printf("Media Aritmetica: %.2f\n\n",notas->media_aritm);
    printf("Media Ponderada: %.2f\n\n",notas->media_pond);
}

int main(){
    
    ler();

    mediaritm();
    
    mediapond();

    exibe_dados();
    return 0;
}