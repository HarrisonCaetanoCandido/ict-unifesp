#include <stdio.h>

int main(){
    FILE *file;
    file=fopen("arquivos_rstring.txt","r");

    if(file==NULL){
        printf("O arquivo nao pode ser aberto!\n");
        return 0;
    }

    char frase[100]; // cria uma string que vai receber os caracteres digitados no arquivo 

    while(fgets(frase,100,file)!=NULL){ // enquanto: file-get-string(ender_string,tamanho,ender_arquivo) nao for VAZIO, ou seja enquanto nao terminar
        printf("%s",frase);
    } // fgets le uma linha ate encontrar uma quebra de linha, '\n', usar while diferente de VAZIO ajuda ele printar ate encerrar as linhas

    fclose(file);

    return 0;
}