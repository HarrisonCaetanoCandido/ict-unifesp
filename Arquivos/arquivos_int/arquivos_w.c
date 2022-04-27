#include <stdio.h>

/*
--------------------------------------------------------------------------------------------
    modo de abertura de arquivos:
    r - read/ler          | rb - read binary/leitura    | rb+ - leitura e escrita
    w - write/escrever    | wb - write binary/escrita   | wb+ - leitura e escrita (apaga o conteudo caso o arquivo exista)
    a - apend/alterar     | ab - apend binary/anexar    | ab+ - leitura e escrita (adiciona ao final do arquivo)

----------------------------------------------------------------------------------------------
    Obs: O modo 'w' serve para escrever em arquivos, porem, sempre que ele for chamado, 
    ira apagar os dados daquele arquivo e recria-lo. 
    
    Geralmente se usa 'a' quando queremos criar um programa que vai inserir informacoes
    conforme o codigo eh executado.
----------------------------------------------------------------------------------------------
*/

int main(){
    FILE *file; // Cria um ponteiro que aponta para variaveis ou tipos de dados do tipo de dado FILE

    file=fopen("arquivos_w.txt","w"); // ponteiro aponta para o endereco do nosso arquivo, fopen("endereco_arquivo ou nome_arquivo","modo_abertura");

    fprintf(file,"Pao com mortadela"); // printa dentro do arquivo
    fclose(file);

    return 0;
}