#include <stdio.h>
#include <stdlib.h>

int main(){
    int *p,tam; // p é uma variável do tipo ponteiro, que guarda enderecos de memoria de outras variaveis do mesmo tipo de dado int. 
    printf("Digite o tamanho do vetor: ");
    scanf("%d",&tam);
    p=(int*)malloc(tam*sizeof(int));

    for(int i=0;i<tam;i++){
        //p[i]=(int*)malloc(sizeof(int)); // p guarda o endereco de memoria do bloco de memoria de 4 bytes alocado
        printf("Digite o valor de p[%d]: ",i);
        scanf("%d",&p[i]);
    }
    for(int i=0;i<tam;i++){
        printf("p: %d ",&p[i]);
        printf("p[%d]: %d\n",i,p[i]);
    }
    printf("sizeof(int): %d",sizeof(int));
    free(p);
    return 0;
}