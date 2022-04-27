#include <stdio.h>

int tamanho_string(char string[]);

main(){
    int j;
    char string[20];
    printf("Digite uma string de caracteres: ");
    scanf("%s",&string); //fgets(&string,20,stdin); // coloca '\0' no final da string, porem, depois desse caracter nulo ainda tem lixos de memoria no vetor de caracter, que nao sao nulos

    j=tamanho_string(string);

    printf("Numero de letras presentes do alfabeto: %d\n",j);
    printf("Tamanho da string de caracteres: %d",j+1); // j + caracter_nulo

    return 0;
}

int tamanho_string(char string[]){
    int j=0; //j=-1; // para trabalhar com o fgets nesse caso
    /*----------------------------------------ISSO------------------------------------------
    for(int i=0;i<20;i++){
        if(string[i]!='\0'){ // enquanto nao for nulo ele conta da posicao 0 ate achar '\0' colocado pelo compilador ao fim do ultimo caracter colocado manualmente por meio do teclado 
            j++;
        }
        if(string[i]=='\0'){ // quando o laco achar o caracter nulo, ele dara um break
            break;
        }
    }*/
    //---------------------------------------OU ISSO----------------------------------------
    while(string[j]!='\0'){
        j++;
    }
    return j;
}