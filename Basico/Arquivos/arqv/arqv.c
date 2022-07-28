#include <stdio.h>// entrada e saida
#include <stdlib.h>//ponteiros, alocacao dinamica etc
#include <string.h>// strings
#include <conio.h>//usar caracteres etc
#define QTD_CTTS 50
#define TAM_NOME 20
#define TAM_TEL 11

/*
1 - Inserir contato
2 - Remover contato
3 - Pesquisar contato pelo nome
4 - Listar todos os contatos
5 - Listar os contatos cujo nome inicia com uma dada letra
6 - Imprimir os aniversariantes do mes
7 - Sair
*/

typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct{
    char nome[TAM_NOME];
    char telefone[TAM_TEL];
    Data data;
}Contato;

//FILE* arquivo; //cria uma variavel GLOBAL do tipo ponteiro que apontara para o endereco de nosso arquivo, FILE indica que a variavel *arquivo é do tipo ARQUIVO

main(){
    int opcao;
    Contato *contato[QTD_CTTS];
    int tam_max, qtd_ctt; tam_max=QTD_CTTS; qtd_ctt=0;
    char arquiv[]={"agenda.txt"};

   do{
       cabecalho();
       printf("1 | Inserir contato\n");
       printf("2 | Remover contato\n");
       printf("3 | Listar todos os contatos\n");
       printf("4 | Pesquisar contato pelo nome\n");
       printf("5 | Pesquisar os aniversariantes do mes\n");
       printf("6 | Alterar dados do contato\n");
       printf("7 | Sair\n");
       printf("Selecione: ");
       scanf("%d",&opcao);

       qtd_ctt=ler_do_arquivo(contato,arquiv); //Le do arquivo binario, mante-la sempre aqui para quando for necessaria a leitura de um arquivo binario

       switch(opcao){
           case 1://Inserir contato - Teremos uma funcao para enderecar em um ponteiro do tipo vetor e uma outra funcao para escrever no arquivo.txt
           qtd_ctt+=inserirAgenda(contato,qtd_ctt,tam_max); //Incrementa um cadastro, acrescenta um cadastro no vetor de enderecos
           salvar_no_arquivo(contato,qtd_ctt,arquiv);       //Salva o cadastro no arquivo
           break;
           case 2://Remover contato
           //remover(contato);
           break;
           case 3://Pesquisar contato pelo nome
           listar(contato,qtd_ctt,arquiv);
           break;
           case 4://Listar todos os contatos
           //pesquisar(contato);
           break;
           case 5://Imprimir os aniversariantes do mes
           //aniv_mes(contato);
           break;
           case 6://Alterar dados do contato
           alterar_cad(arquiv);
           break;
           case 7://Sair
           printf("Obrigado pela visita!\n");
           break;
           default:
           printf("Opcao invalida!\n");
           printf("Pressione qualquer tecla para continuar...\n");
           getch();
           break;
       }
   }while(opcao!=7);
}

void cabecalho(){
    system("cls");
    printf("------------------------------------------------\n");
    printf("             Agenda Eletronica\n");
    printf("------------------------------------------------\n\n");
}

int inserirAgenda(Contato **contato,int qtd_ctt,int tam_max){ // Como estamos trabalhando com vetor de ponteiros, ou seja, vetor de endereços, teremos um ponteiro para ponteiro

    Contato *novo_ctt=(Contato*)malloc(sizeof(Contato));

    if(novo_ctt==NULL){
        printf("Nao foi possivel alocar memoria!\n");
        getch();
    }else{
        if(qtd_ctt<tam_max){

            cabecalho();

            fflush(stdin); //Como vamos usar string temos que limpar o buffer do teclado
            printf("Digite o nome: ");
            fgets(novo_ctt->nome,TAM_NOME,stdin); //pega string com espaco


            while(strlen(novo_ctt->nome)>20||strlen(novo_ctt->nome)<1){
                fflush(stdin);
                printf("Numero de Caracteres Invalido!\nDigite o nome novamente [1:20]: ");
                fgets(novo_ctt->nome,TAM_NOME,stdin); //pega string com espaco
            }

            fflush(stdin);
            printf("Digite o fone: ");
            fgets(novo_ctt->telefone,TAM_TEL,stdin);

            while(strlen(novo_ctt->telefone)>11||strlen(novo_ctt->telefone)<10){
                fflush(stdin);
                printf("Numero de Digitos Invalido!\nDigite o fone novamente [1:11]: ");
                fgets(novo_ctt->telefone,TAM_TEL,stdin); //pega string com espaco
            }

            printf("Digite a data\n");
            printf("Dia: ");
            scanf("%d",&novo_ctt->data.dia);

            while(novo_ctt->data.dia>31||novo_ctt->data.dia<1){
                printf("Data Invalida!\nDigite o dia novamente [1:31]: ");
                scanf("%d",&novo_ctt->data.dia);
            }

            printf("Mes: ");
            scanf("%d",&novo_ctt->data.mes);

            while(novo_ctt->data.mes>12||novo_ctt->data.mes<1){
                printf("Data Invalida!\nDigite o mes novamente [1:12]: ");
                scanf("%d",&novo_ctt->data.mes);
            }

            printf("Ano: ");
            scanf("%d",&novo_ctt->data.ano);

            while(novo_ctt->data.mes==0){
                printf("Data Invalida!\nDigite o ano novamente (ano!=0): ");
                scanf("%d",&novo_ctt->data.ano);
            }

            contato[qtd_ctt]=novo_ctt; // Salva o endereco do registro no nosso vetor de enderecos

            return 1; //fazer incremento para passarmos para a proxima posicao do vetor de enderecos
        }else{
            printf("A Agenda esta cheia!\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
            return 0;
        }
    }
    free(novo_ctt); //<-----------------------------------------------------------------------------------------------
}

void salvar_no_arquivo(Contato **contato,int qtd_ctt,char arquiv[]){ // Salvar do vetor de enderecos no vetor de enderecos
    FILE* arquivo = fopen(arquiv,"wb"); // E melhor usar binario pq eh mais facil de alterar o arquivo

    for(int i=0;i<qtd_ctt;i++){
        fwrite(contato[i],sizeof(Contato),1,arquivo); //fwrite('posicao-no-vetor-de-enderecos','tamanho-tipo-de-variavel','quantidade-de-insercoes','endereco do arquivo') //fwrite(novo_ctt,sizeof(Contato),1,arquivo); //escrever(endereco, tamanho(struct),n linhas,arquivo)
    }
    fclose(arquivo);
}

int ler_do_arquivo(Contato **contato, char arquiv[]){ // Le o arquivo, para ler precisamos preencher nosso vetor de enderecos com as regioes de memoria com os cadastros do arquivo
    FILE* arquivo=fopen(arquiv,"rb");
    int quantidade=0; // quantidade = 0 pq eu nao sei quantos cadastros tem ali

    Contato *novo_ctt=malloc(sizeof(Contato)); // Alocar memoria para ler o arquivo binario, sem fazer casting

    if(novo_ctt==NULL){
        printf("Nao foi possivel alocar memoria!\n");
        getch();
    }else{
        while(fread(novo_ctt,sizeof(Contato),1,arquivo)==1){
            contato[quantidade]=novo_ctt;
            quantidade++;

            novo_ctt=malloc(sizeof(Contato)); // Aloca nova memoria para trocar de endereco e nao alterar a ultima posicao
        }
        fclose(arquivo);
    }
    return quantidade;
}

void listar(Contato **contato,int qtd_ctt, char arquiv[]){ //Imprimir do arquivo

    cabecalho();

    if(contato==NULL){
        printf("O arquivo nao pode ser aberto!\n");
    }else{
        for(int i=0;i<qtd_ctt;i++){
            printf("Nome: %s",contato[i]->nome);
            printf("Fone: %s\n",contato[i]->telefone);
            printf("Aniversario: %d/%d/%d\n",contato[i]->data.dia,contato[i]->data.mes,contato[i]->data.ano);
            printf("------------------------------------------------\n\n");
            }
        }
        printf("Pressione qualquer tecla para continuar...\n");
        getch();
    }

/*
void pesquisar(Contato *contato){

    char nome[TAM_NOME];

    arquivo[qtd] = fopen("arquivo.txt","r");

    cabecalho();

    if(arquivo==NULL){
        printf("O arquivo nao pode ser aberto!\n");
    }else{
        fflush(stdin);
        printf("Digite o nome do contato a ser pesquisado: ");
        fgets(nome,TAM_NOME,stdin);

        while(fread(contato,sizeof(Contato),1,arquivo)==1){ //Se a linha existir entao eh igual a 1
            if(strcmp(nome,contato->nome)==0){ // compara nome digitado com os nomes das linhas no arquivo
                printf("Nome: %s",contato->nome);
                printf("Fone: %s\n",contato->telefone);
                printf("Aniversario: %d/%d/%d\n",contato->data.dia,contato->data.mes,contato->data.ano);
            }
        }
    }
    fclose(arquivo);
    printf("Pressione qualquer tecla para continuar...\n");
    getch();
}*/

/*
void aniv_mes(Contato *contato){

    int mes;

    arquivo=fopen("arquivo.txt","r");

    cabecalho();
    if(arquivo==NULL){
        printf("O arquivo nao pode ser aberto!\n");
    }else{
        printf("Digite o mes do contato a ser pesquisado: ");
        scanf("%d",&mes);

        while(fread(contato,sizeof(Contato),1,arquivo)==1){ // poderia usar while(!feonf(arquivo)){fscanf(arquivo,"%tipo_variavel",&variavel)}, !feof('file') - enquanto nao for fim do arquivo | Nesse caso eh interessante escrever as linhas usando fpintf(), fprintf(arquivo,%tipo_variavel,variavel)
            if(mes==contato->data.mes){
                printf("Nome: %s",contato->nome);
                printf("Fone: %s\n",contato->telefone);
                printf("Aniversario: %d/%d/%d\n",contato->data.dia,contato->data.mes,contato->data.ano);
            }
            }
        }
    fclose(arquivo);
    printf("Pressione qualquer tecla para continuar...\n");
    getch();
}*/
/*
void remover(Contato *contato){
    FILE *apagar;
    char telefone[TAM_TEL];

    arquivo=fopen("arquivo.txt","r"); //Pega o endereco de arquivo.txt

    apagar=fopen("apagar.txt","w"); // eh como se fosse um arquivo temporario, vai servir apenas para apagar

    cabecalho();
    if(arquivo==NULL){
        printf("O arquivo nao pode ser aberto!\n");
    }else{
        fflush(stdin);//limpa buffer do teclado
        printf("Digite o numero do telefone do contato a ser removido da Agenda: ");
        fgets(telefone,TAM_TEL,stdin);

        while(fread(contato,sizeof(Contato),1,arquivo)==1){
            if(strcmp(telefone,contato->telefone)==0){
                fwrite(contato,sizeof(Contato),1,apagar);
            }
        }
    }
    fclose(arquivo);
    fclose(apagar);
}*/

void alterar_cad(char arquiv[]){
    int i, id;
    FILE* arquivo=fopen(arquiv,"rb+"); // modo de abertura eh rb+, pois queremos ler e imprimir na tela e reescrever no arquivo
    Contato c;

    if(arquivo==NULL){
        printf("O Arquivo nao pode ser aberto!\n");
    }else{
        cabecalho();
        printf("Contatos na Agenda:\n");
        while(fread(&c,sizeof(Contato),1,arquivo)==1){
            printf("\t%d = %2d/%2d/%4d\t%d\t%s\n",i,c.data.dia,c.data.mes,c.data.ano,c.telefone,c.nome);
            i++;
        }
        printf("Digite qual contato deseja alterar: ");
        scanf("%d",&id);
        getchar();
        id--; // pq dentro do vetor temos inicio em 0

            if(id>=0 && id<i-1){

                    printf("\nDigite o nome, data e fone que deseja alterar:\n");
                    printf(""); // <----------------------------------------------------------------------------------------------- PAREI AQUI

                    arquivo=fopen("arquivo.txt","w");

                    fflush(stdin); //Como vamos usar string temos que limpar o buffer do teclado
                    printf("Digite o novo nome do registro: ");
                    fgets(c.nome,TAM_NOME,stdin); //pega string com espaco
                    //fscanf(arquivo,"%s",novo_ctt->nome);

                    fflush(stdin); //Como vamos usar string temos que limpar o buffer do teclado
                    printf("Digite o novo numero de telefone do registro: ");
                    fgets(c.telefone,TAM_TEL,stdin); //pega string com espaco
                    //fscanf(arquivo,"%s",novo_ctt->telefone);

                    printf("Digite a nova data\n");
                    printf("Dia: ");
                    scanf("%d",&c.data.dia);
                    //fscanf(arquivo,"%d",novo_ctt->data.dia);

                    while(c.data.dia>31||c.data.dia<1){
                        printf("Data Invalida!\nDigite o dia novamente [1:31]: ");
                        scanf("%d",&c.data.dia);
                        //fscanf(arquivo,"%d",novo_ctt->data.dia);
                    }

                    printf("Mes: ");
                    scanf("%d",&c.data.mes);
                    //fscanf(arquivo,"%d",novo_ctt->data.mes);

                    while(c.data.mes>12||c.data.mes<1){
                        printf("Data Invalida!\nDigite o mes novamente [1:12]: ");
                        scanf("%d",&c.data.mes);
                        //fscanf(arquivo,"%d",novo_ctt->data.mes);
                    }

                    printf("Ano: ");
                    scanf("%d",&c.data.ano);
                    //fscanf(arquivo,"%d",novo_ctt->data.ano);

                    while(c.data.mes==0){
                        printf("Data Invalida!\nDigite o ano novamente (ano!=0): ");
                        scanf("%d",&c.data.ano);
                        //fscanf(arquivo,"%d",novo_ctt->data.ano);
                    }
                    
                    fclose(arquivo);

                    

                }else{
                    printf("\nPressione qualquer tecla para continuar...");
                    getch();
                }
    }
}

