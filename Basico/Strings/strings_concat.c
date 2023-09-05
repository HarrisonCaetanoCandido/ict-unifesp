#include <stdio.h>

void concatenarStrings(char string1[],int t1, char string2[],int t2,char string3[]);

int main(){
    char palavra1[]={'p','a','o',' '};
    char palavra2[]={'m','o','r','t','a','d','e','l','a'};
    char novapalavra[13];

    concatenarStrings(palavra1,4,palavra2,9,novapalavra);

    for(int i=0;i<13;i++){
        printf("%c",novapalavra[i]);
    }

    return 0;
}

void concatenarStrings(char string1[],int t1, char string2[],int t2,char string3[]){
    int i,j=0;

    for(i=0;i<t1;i++){
        string3[i]=string1[i];
        j++;
    }
    for(i=0;i<t2;i++){
        string3[j+i]=string2[i];
    }
}