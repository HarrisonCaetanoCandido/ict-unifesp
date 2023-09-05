#include <stdio.h>

void alfabetico(char variavel);

main(){
    char nome[20];int i=0;
    printf("Digite uma palavra: ");
    scanf("%s",&nome);

    while(nome[i]!='\0'){
        alfabetico(nome[i]);
        i++;
    }

    return 0;
}

void alfabetico(char variavel){
    if((variavel>='a' && variavel <= 'z')||(variavel >='A' && variavel <= 'Z')){
        printf("A variavel %c eh uma letra\n",variavel);
    }else{
        printf("A variavel %c nao eh uma letra\n",variavel);
    }
}