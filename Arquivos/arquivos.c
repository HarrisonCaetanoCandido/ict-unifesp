#include <stdio.h>

int main(){
    FILE *file; //Cria um ponteiro que aponta para tipos de dados FILE

    /*file=fopen(); <--- Essa linha faz o nosso ponteiro apontar para um arquivo no nosso programa

    fopen trabalha da seguinte maneira:

    fopen("arquivo.tipo","modo")

    modo de abertura de arquivos:
    r - read/ler          | rb - read binary/leitura     | rb+ - leitura e escrita
    w - write/escrever    | wb - write binary/escrita    | wb+ - leitura e escrita (apaga o conteudo caso o arquivo exista)
    a - alterar           | ab - apend binary/anexar   | ab+ - leitura e escrita (adiciona ao final do arquivo)

----------------------------------------------------------------------------------------------
    Obs: O modo 'w' serve para escrever em arquivos, porem, sempre que ele for chamado, 
    ira apagar os dados daquele arquivo e recria-lo. 
    
    Geralmente se usa 'a' quando queremos criar um programa que vai inserir informacoes
    conforme o codigo eh executado.
----------------------------------------------------------------------------------------------
*/

/* ESCREVER EM FORMATO TEXTO (NAO BINARIO):

    void salvar_arquivo(Contato **contato,int qtd_ctt,char arquiv[]){ // Salvar do vetor de enderecos para os arquivos
    FILE* arquivo = fopen(arquiv,"w");

    fprintf(arquivo,"%d\n",qtd_ctt); // escrever a qtd de ctt no arquivo
    for(int i=0;i<qtd_ctt;i++){
        fputs(contato[i]->nome,arquivo);
        fputc('\n',arquivo); // pula linha no arquivo
        fprintf(arquivo,"%d/%d/%d\n",contato[i]->data.dia,contato[i]->data.mes,contato[i]->data.ano);
    }
    //fwrite(novo_ctt,sizeof(Contato),1,arquivo); //escrever(endereco, tamanho(struct),n linhas,arquivo)
    fclose(arquivo);

    cabecalho();
    if(contato==NULL){
        printf("O arquivo nao pode ser aberto!\n");
    }else{
        for(i=0;i<qtd_ctt;i++){
            printf("Nome: %s",contato[i]->nome);
            printf("Fone: %s\n",contato[i]->telefone);
            printf("Aniversario: %d/%d/%d\n",contato[i]->data.dia,contato[i]->data.mes,contato[i]->data.ano);
            printf("------------------------------------------------\n\n");
        }
        }
        fclose(arquivo);
        printf("Pressione qualquer tecla para continuar...\n");
        getch();
    
}
    return 0;
}*/