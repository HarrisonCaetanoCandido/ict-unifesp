#include <stdio.h>

_Bool strings_igualdade(char string1[],char string2[]);

int main(){
    char string1[20];
    char string2[20];

    printf("Digite a string1: ");
    scanf("%s",&string1);

    printf("Digite a string2: ");
    scanf("%s",&string2);

    if(strings_igualdade(string1,string2)==1){
        printf("As strings sao iguais!");
    }else{
        printf("As string nao sao iguais!");
    }

    return 0;
}

_Bool strings_igualdade(char string1[],char string2[]){
    int i;

    while(string1[i]==string2[i] && string1[i] != '\0' && string2[i] != '\0'){
        i++;
    }
    if(string1[i]=='\0' && string2[i]=='\0'){
        return 1; // sao iguais
    }else{
        return 0; // nao sao iguais
    }

}