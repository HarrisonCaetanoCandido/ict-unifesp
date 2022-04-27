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

//FILE *arquivo;

main(){
    int opcao;
    Contato *contato=(Contato*)malloc(sizeof(Contato));
    int tam, qtd_ctt; tam=QTD_CTTS; qtd_ctt=0;

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

       switch(opcao){
           case 1://Inserir contato
           inserirAgenda(contato);
           break;
           case 2://Remover contato
           remover(contato);
           break;
           case 3://Pesquisar contato pelo nome
           listar(contato);
           break;
           case 4://Listar todos os contatos
           pesquisar(contato);
           break;
           case 5://Imprimir os aniversariantes do mes
           aniv_mes(contato);
           break;
           case 6://Alterar dados do contato
           //alterar_cad(contato);
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

int inserirAgenda(Contato *contato){ // Como estamos trabalhando com vetor de ponteiros, ou seja, vetor de endereços, teremos um ponteiro para ponteiro
    FILE* arquivo; //cria uma variavel do tipo ponteiro que apontara para o endereco de nosso arquivo, FILE indica que a variavel *arquivo é do tipo ARQUIVO 
    arquivo=fopen("arquivo.txt","a"); //(a - acrescentar/se nao existir cria, b - binario)

    if(arquivo==NULL){
        printf("O arquivo nao pode ser aberto!\n");
    }else{

        cabecalho();

            fflush(stdin); //Como vamos usar string temos que limpar o buffer do teclado
            printf("Digite o nome: ");
            fgets(contato->nome,TAM_NOME,stdin); //pega string com espaco

            while(strlen(contato->nome)>20||strlen(contato->nome)<1){
                fflush(stdin);
                printf("Numero de Caracteres Invalido!\nDigite o nome novamente [1:20]: ");
                fgets(contato->nome,TAM_NOME,stdin); //pega string com espaco
            }

            fflush(stdin);
            printf("Digite o fone: ");
            fgets(contato->telefone,TAM_TEL,stdin);

            while(strlen(contato->telefone)>11||strlen(contato->telefone)<10){
                fflush(stdin);
                printf("Numero de Digitos Invalido!\nDigite o fone novamente [1:11]: ");
                fgets(contato->telefone,TAM_TEL,stdin); //pega string com espaco
            }

            printf("Digite a data\n");
            printf("Dia: ");
            scanf("%d",&contato->data.dia);

            while(contato->data.dia>31||contato->data.dia<1){
                printf("Data Invalida!\nDigite o dia novamente [1:31]: ");
                scanf("%d",&contato->data.dia);
            }

            printf("Mes: ");
            scanf("%d",&contato->data.mes);

            while(contato->data.mes>12||contato->data.mes<1){
                printf("Data Invalida!\nDigite o mes novamente [1:12]: ");
                scanf("%d",&contato->data.mes);
            }

            printf("Ano: ");
            scanf("%d",&contato->data.ano);

            while(contato->data.mes==0){
                printf("Data Invalida!\nDigite o ano novamente (ano!=0): ");
                scanf("%d",&contato->data.ano);
            }

            fwrite(contato,sizeof(Contato),1,arquivo); //escrever(endereco, tamanho(struct),n linhas,arquivo)

        fclose(arquivo);
    }
}

void listar(Contato *contato){
    FILE* arquivo; // Abre o arquivo
    
    arquivo=fopen("arquivo.txt","r");

    cabecalho();
    if(arquivo==NULL){
        printf("O arquivo nao pode ser aberto!\n");
    }else{
        while(fread(contato,sizeof(Contato),1,arquivo)==1){ // fread(&endereco,tamanho(STRUCT),n linhas,arquivo)//Se a linha existir entao eh igual a 1
            printf("Nome: %s",contato->nome);
            printf("Fone: %s\n",contato->telefone);
            printf("Aniversario: %d/%d/%d\n",contato->data.dia,contato->data.mes,contato->data.ano);
            printf("------------------------------------------------\n\n");
        }
        fclose(arquivo);
        printf("Pressione qualquer tecla para continuar...\n");
        getch();
    }
}

void pesquisar(Contato *contato){
    FILE* arquivo; // Abre o arquivo
    char nome[TAM_NOME];

    arquivo = fopen("arquivo.txt","r");

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
}

void aniv_mes(Contato *contato){
    FILE *arquivo;
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
}

void remover(Contato *contato){
    FILE *arquivo, *apagar; //Inicializar arquivo

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
}

void alterar_cad(Contato **contato, int qtd_ctt){
    char telefone[TAM_TEL];
    FILE* arquivo;

    if(contato==NULL){
        printf("O Arquivo nao pode ser aberto!\n");
    }else{

        printf("Digite qual contato deseja alterar: ");
        scanf("%s",&telefone);

        for(int i=0;i<qtd_ctt;i++){
            if(strcmp(telefone,contato[i]->telefone)==0){
                printf("Dados encontrados do Registro n %d\n",i+1);
                printf("Nome: %s\n",contato[i]->nome);
                printf("Telefone: %s\n",contato[i]->telefone);
                printf("Data de aniversario %d/%d/%d\n",contato[i]->data.dia,contato[i]->data.mes,contato[i]->data.ano);

                printf("Deseja alterar os dados do Registro acima?(s\n)");

                if(getche()=='s'){
                    //Contato *novo_ctt=(Contato*)malloc(sizeof(Contato));

                    //arquivo=fopen("arquivo.txt","w");

                    fflush(stdin); //Como vamos usar string temos que limpar o buffer do teclado
                    printf("Digite o novo nome do registro: ");
                    fgets(contato[i]->nome,TAM_NOME,stdin); //pega string com espaco
                    //fscanf(arquivo,"%s",novo_ctt->nome);

                    fflush(stdin); //Como vamos usar string temos que limpar o buffer do teclado
                    printf("Digite o novo numero de telefone do registro: ");
                    fgets(contato[i]->telefone,TAM_TEL,stdin); //pega string com espaco
                    //fscanf(arquivo,"%s",novo_ctt->telefone);

                    printf("Digite a nova data\n");
                    printf("Dia: ");
                    scanf("%d",&contato[i]->data.dia);
                    //fscanf(arquivo,"%d",novo_ctt->data.dia);

                    while(contato[i]->data.dia>31||contato[i]->data.dia<1){
                        printf("Data Invalida!\nDigite o dia novamente [1:31]: ");
                        scanf("%d",&contato[i]->data.dia);
                        //fscanf(arquivo,"%d",novo_ctt->data.dia);
                    }

                    printf("Mes: ");
                    scanf("%d",&contato[i]->data.mes);
                    //fscanf(arquivo,"%d",novo_ctt->data.mes);

                    while(contato[i]->data.mes>12||contato[i]->data.mes<1){
                        printf("Data Invalida!\nDigite o mes novamente [1:12]: ");
                        scanf("%d",&contato[i]->data.mes);
                        //fscanf(arquivo,"%d",novo_ctt->data.mes);
                    }

                    printf("Ano: ");
                    scanf("%d",&contato[i]->data.ano);
                    //fscanf(arquivo,"%d",novo_ctt->data.ano);

                    while(contato[i]->data.mes==0){
                        printf("Data Invalida!\nDigite o ano novamente (ano!=0): ");
                        scanf("%d",&contato[i]->data.ano);
                        //fscanf(arquivo,"%d",novo_ctt->data.ano);
                    }
                    fwrite(contato[i],sizeof(Contato),1,arquivo);
                    fclose(arquivo);

                    //contato[i]=novo_ctt;

                }else{
                    printf("\nPressione qualquer tecla para continuar...");
                    getch();
                }
                }else{
                    printf("Registro nao encontrado!\n");
                }
        }
    }
}
