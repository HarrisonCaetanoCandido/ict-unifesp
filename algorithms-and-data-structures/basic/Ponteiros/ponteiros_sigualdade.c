#include <stdio.h>
#define tam 20

void copiarstring(char *copiar,char *colar);

void copiarstring(char *copiar,char *colar){
    while(*copiar!='\0'){
        *colar=*copiar;
        copiar++; //passa para o proximo membro
        colar++; 
    }
}

int main(){
    char string1[tam],string2[tam];

    printf("Digite algo na string1: ");
    scanf("%s",&string1); // ja coloca o caracter nulo

    copiarstring(string1,string2);

    printf("string1: %s\n",string1);
    printf("string2: %s",string2);

    return 0;
}