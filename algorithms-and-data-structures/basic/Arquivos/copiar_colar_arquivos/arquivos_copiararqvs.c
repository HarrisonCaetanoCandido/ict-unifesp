#include <stdio.h>

void copiar(FILE *file1, FILE *file2);

int main(){
    FILE *file;
    file=fopen("arqvcopiar.txt","r");

    if(file==NULL){
        printf("O arquivo nao pode ser aberto!\n");
        return 0;
    }

    FILE *filecopia;
    filecopia=fopen("arqvcolar.txt","w");

    copiar(file,filecopia);

    fclose(file);
    fclose(filecopia);

    return 0;
}

void copiar(FILE *file1, FILE *file2){ // recebe o endereco que os ponteiros 'file' e 'filecopia' apontam, ou seja, dos arquivos

    char leitor[1000];

    while(fgets(leitor,1000,file1)!=NULL){
        fputs(leitor,file2);
    }
}