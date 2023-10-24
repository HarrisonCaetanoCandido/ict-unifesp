#include <stdio.h>

int main(){
    FILE *file;

    file=fopen("arquivos_rstring.txt","a");

    if(file==NULL){
        printf("O arquivo nao pode ser aberto!\n");
        return 0;
    }

    fprintf(file,"\nPrimeira linha\n");

    char frase2[100];

    printf("Digite uma string de caracteres: ");
    scanf("%s",&frase2);

    fputs(frase2,file); // coloca uma string no arquivo

    char caractere = '3';

    fputc(caractere,file); // coloca 1 caractere no arquivo
    fclose(file);

    return 0;
}