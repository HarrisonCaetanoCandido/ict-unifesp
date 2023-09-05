#include <stdio.h>

void ordemcrescente(int vetor[],int n);

int main(){
    int vetor[10],n,ordemc;

    printf("Digite quantas posicoes tera o vetor: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        printf("Digite o valor na posicao %d do vetor: ",i);
        scanf("%d",&vetor[i]);
    }
    
    ordemcrescente(vetor,n);

    printf("Vetor = [ ");
    for(int i=0;i<n;i++){
        printf("%d ",vetor[i]);
    }
    printf("]");

    return 0;
}

void ordemcrescente(int vetor[],int n){
    int temp;

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(vetor[i]>vetor[j]){ // entrada: 5[0],2[1],4[2] => 5[0]>2[1]? se sim => temp=2[0] => 5[0] = 2[1] = 2[0] => 2[1]=5[0] = 5[1]
                temp=vetor[i];
                vetor[i]=vetor[j];
                vetor[j]=temp;
            }
        }
    }
    //return vetor; => posso usar um return, porem quando usamos vetor como argumento de funcoes, nos estamos manipulando o vetor original, na posicao de memoria da variavel original, ou seja, o proprio vetor declarado na funcao main e nao uma copia dele como eh com variavel simples
}