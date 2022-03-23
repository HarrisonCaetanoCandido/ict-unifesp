/*Faça um programa que possua um procedimento para ler 2 notas (chamar um
procedimento para ler 2 notas válidas - menor que 10 pontos - não lendo com scanf no
main), outro procedimento que dadas estas 2 notas vai calcular a média simples -
(n1+n2)/2 - e a média ponderada, onde a nota 2 tem peso 2, isto é ( n1 + n2 *2 ) / 3, e
um último procedimento que vai exibir na tela todos os dados que foram fornecidos e
calculados. Ou seja, seu programa terá 3 procedimentos: le_notas, calc_media e
exibe_dados. (6 pts)*/

#include <stdio.h>

void ler(float *pN1,float *pN2,float *verificar){
    if(*pN1>10||*pN2>10){
        *verificar=1;
    }
}

float mediaritm(float *pN1, float *pN2){
    float media;
    media=(*pN1+*pN2)/2;
}

float mediapond(float *pN1,float *pN2){
    float mediapond;
    mediapond=(*pN1+*pN2*2)/3;

}

float exibe_dados(float *pN1,float *pN2,float media_aritmetica,float media_ponderada){
    printf("Nota 1: %.2f, Nota 2: %.2f\n",*pN1,*pN2);
    printf("Media Aritmetica: %.2f\n",media_aritmetica);
    printf("Media Ponderada: %.2f\n",media_ponderada);
}

int main(){
    float n1=5,n2=3,verificar=0,media_aritmetica,media_ponderada;
    float *pN1,*pN2,*pVerif;
    pN1=&n1;
    pN2=&n2;
    pVerif=&verificar;

    ler(pN1,pN2,pVerif);

    if(*pVerif==1){
        printf("Erro! Uma das notas eh invalida!\n");
    }else{

    media_aritmetica=mediaritm(pN1,pN2);

    media_ponderada=mediapond(pN1,pN2);

    exibe_dados(pN1, pN2, media_aritmetica, media_ponderada);
    }
    return 0;
}