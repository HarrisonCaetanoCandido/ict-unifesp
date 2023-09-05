#include <stdio.h>

int somar_vetor(int vetor[],const int n);

int somar_vetor(int vetor[],const int n){
    int soma=0,*p;
    int finalvetor=vetor+n; // endereco de memoria do primeiro, mais n posicoes a frente

    for(p=vetor;p<finalvetor;p++){
        soma+=*p;
    }
    return soma;
}

int main(){
    int tam;
    printf("Digite o tamanho do vetor: ");
    scanf("%d",&tam);
    int vetor[tam];

    for(int i=0;i<tam;i++){
        printf("Digite um valor na posicao %d do vetor: ",i);
        scanf("%d",&vetor[i]);
    }

    printf("Soma das posicoes do vetor: %d",somar_vetor(vetor,tam));

    return 0;
}