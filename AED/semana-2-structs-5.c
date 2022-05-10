/*
Elabore um programa em C para calcular a média das
4 notas bimestrais de cada aluno (usando registros),
para um professor que tenha 3 turmas de 5 alunos.
Inclua no programa a possibilidade de procurar um
registro (dentre os digitados) pelo nome da pessoa, e
apresentar seus dados na tela. Inclua também a
possibilidade de excluir um registro que possua o
campo nome igual ao valor passado pelo usuário.
*/

#include <stdio.h>
#include <stdlib.h>
#define aln 3

typedef struct ALUNOS{
    float n[4];
    float media;
    char nome[30];
}Alunos;

void aloca(Alunos *alunos[],int index);
void desaloca(Alunos *alunos[],int index);
Alunos inserir(Alunos *aluno);
float media(Alunos *aluno);
void busca(Alunos *alunos[],int index);
void imprimir(Alunos *alunos[],int index);
Alunos excluir(Alunos *alunos[],int *index);
void pressione();

int main(){
    Alunos *alunos[aln];
    int selecione,index=0;

    // funcao pra fazer a media das 4 notas das posicoes do vetor
    // funcao pra procurar o registro e mostrar o conteudo dos campos por meio de comparacoes com os campos de nome
    // excluir registro que possua campo nome igual ao valor passado pelo usuario

    do{
        system("clear||cls");
        printf("1 | Inserir\n");
        printf("2 | Buscar\n");
        printf("3 | Listar\n");
        printf("4 | Excluir\n");
        printf("5 | Sair\n");
        printf("Selecione: ");
        scanf("%d",&selecione);
        switch(selecione)
        {
            case 1:
                system("clear||cls");
                aloca(alunos,index);
                inserir(alunos[index]);
                index++;
                pressione();
            break;
            case 2:
                system("clear||cls");
                busca(alunos,index);
                pressione();
            break;
            case 3:
                system("clear||cls");
                imprimir(alunos,index);
                pressione();
            break;
            case 4:
                excluir(alunos,&index);
            break;
            case 5:
                printf("\nPrograma encerrado!");
            break;
            default:
                system("clear||cls");
                printf("\nA opcao digitada nao eh valida!\n");
                pressione();
            break;
        }
    }while(selecione!=5);

    desaloca(alunos,index);

    return 0;
}

void aloca(Alunos *alunos[],int index){
    alunos[index]=(Alunos*)malloc(sizeof(Alunos));
    if(alunos[index]==NULL){
        printf("Nao foi possivel alocar memoria!\n");
        return 0;
    }
}

void desaloca(Alunos *alunos[],int index){
    int i=0;
    for(i=0;i<index;i++){
        free(alunos[i]);
    }
}

Alunos inserir(Alunos *alunos){ // acho que nao faz sentido pegar index
    int i;
    char caractere;
    i=0;
    fflush(stdin);
    printf("Digite um nome: ");
    do{
        caractere=getchar();
        alunos->nome[i]=caractere;
        i++;
    }while(caractere!='\n');
    alunos->nome[i-1]='\0';

    for(i=0;i<4;i++){
        printf("Digite a %d nota: ",i+1);
        scanf("%f",&alunos->n[i]);
    }
    media(alunos);
}

float media(Alunos *alunos){
    int *pi,*pf,soma=0,media;
    pf=alunos->n+4;
    for(pi=alunos->n;pi<pf;pi++){
        soma=soma+*pi;
    }
    alunos->media=soma/4;
}

void busca(Alunos *alunos[],int index){
    int i=0,j=0,k=0,senao=0;
    char caractere,nome_aluno[30];
    printf("Digite um nome: ");
    fflush(stdin);
    do{
        caractere=getchar();
        nome_aluno[i]=caractere;
        i++;
    }while(caractere!='\n');
    nome_aluno[i-1]='\0';

    i=0;
    while(i<index){
        while(alunos[i]->nome[j]==nome_aluno[j] && alunos[i]->nome[j]!='\0' && nome_aluno[j]!='\0'){
            j++;
        }
        if(alunos[i]->nome[j]=='\0' && nome_aluno[j]=='\0'){
            printf("Aluno %d | Nome: %s\n",i,alunos[i]->nome);
            k=0;
            while(k<4){
                printf("Aluno %d | Nota %d: %.1f\n",i,k,alunos[i]->n[k]);
                k++;
            }
            return;
        }else{
            senao++; 
        }
        i++;
    }
    if(senao==aln){
        printf("Nao foi possivel encontrar um registro com o nome: %s",nome_aluno);
    }
}

void imprimir(Alunos *alunos[],int index){
    int i,k;
    for(i=0;i<index;i++){
        printf("Aluno %d | Nome: %s\n",i,alunos[i]->nome);
        k=0;
        while(k<4){
            printf("Aluno %d | Nota %d: %.1f\n",i,k,alunos[i]->n[k]);
            k++;
        }
        printf("\n");
    }
}

Alunos excluir(Alunos *alunos[],int *index){
    int i=0,j,k;char caractere,nome_aluno[30];
    printf("Digite o nome do aluno: ");
    fflush(stdin);
    do{
        caractere=getchar();
        nome_aluno[i]=caractere;
        i++;
    }while(caractere!='\n');
    nome_aluno[i-1]='\0';

    i=0,j=0,k=0;
    while(i<*index){
        while(alunos[i]->nome[j]==nome_aluno[j] && alunos[i]->nome[j]!='\0' && nome_aluno[j]!='\0'){
            j++;
        }
        if(alunos[i]->nome[j]=='\0' && nome_aluno[j]=='\0'){
            k=i;
            while(k<*index){
                alunos[k]=alunos[k+1];
                k++;
            }
            (*index)--;
            return;
        }
        i++;
    }
}

void pressione(){printf("\nPressione qualquer tecla para continuar...");getch();}