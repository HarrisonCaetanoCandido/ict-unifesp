#include <stdio.h>

int main(){
    char teste[]={'b','r','a','s','i','l'};
    int texti[]={1,2,3,4,5,6};

    for(int i=0;i<6;i++){
        printf("%c",teste[i]);
    }printf("\n");
    for(int i=0;i<6;i++){
        printf("%d",texti[i]);
    }
    printf("\nTeste: %s",teste);
    //printf("\nTexti: %d",texti); nao funciona por que int nao tem a mesma propriedade que as char tem, que eh o uso de '%s' para printar
    return 0;
}