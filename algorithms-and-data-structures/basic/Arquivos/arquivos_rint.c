#include <stdio.h>

int main(){
    FILE *file;
    file=fopen("arquivos_rint.txt","r"); // modo 'r' nao cria arquivo caso ele nao exista!

    if(file==NULL){
        printf("Arquivo nao pode ser aberto!\n");
        return 0;
    }

    int x,y,z;

    fscanf(file,"%d %d %d",&x,&y,&z); // Escaneia, ou melhor, lê do arquivo e printa no terminal, o problema eh que ele eh muito limitado por requerer formatacao do arquivo

    printf("%d %d %d",x,y,z);

    return 0;
}
