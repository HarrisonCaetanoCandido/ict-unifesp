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
#include <math.h>

typedef struct Aluno{
    float n[4];
    float media;
    char nome[30];
}ALUNO;

typedef struct Turma{
    ALUNO *a[5];
}TURMA;

void aloca(TURMA *turma[],int index);
void desaloca(TURMA *turma[],int index,int *aindex);
int inserir(TURMA *turma,int index,int *aindex);
float media(TURMA *turma,int aindex);
void busca(TURMA *turma[],int index,int *aindex);
void imprimir(TURMA *turma[],int index,int *aindex);
TURMA excluir(TURMA *turma[],int index,int *aindex);
void pressione();

int main(){
    TURMA *turma[3];
    int selecione, index=0,*aindex;

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
                aloca(turma,index);
                inserir(turma[index],index,aindex);
                index++;
                printf("aindex: %d",*aindex);pressione();
            break;
            case 2:
                system("clear||cls");
                busca(turma,index,aindex);
                pressione();
            break;
            case 3:
                system("clear||cls");
                imprimir(turma,index,aindex);
                pressione();
            break;
            case 4:
                excluir(turma,index,aindex);
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

    desaloca(turma,index,aindex);

    return 0;
}

void aloca(TURMA *turma[],int index){
    turma[index]=(TURMA*)malloc(sizeof(TURMA));
    if(turma[index]==NULL){
        printf("Nao foi possivel alocar memoria!\n");
        return 0;
    }
}

void desaloca(TURMA *turma[],int index,int *aindex){
    int i,j;
    for(i=0;i<index;i++){
        for(j=0;j<aindex;j++){
            free(turma[i]->a[j]);
        }
        free(turma[i]);
    }
}

int inserir(TURMA *turma,int index,int *aindexx){
    char caractere;
    int i,j,aindex;

    printf("Digite quantos alunos deseja registrar: ");
    scanf("%d",&aindex);

    for(j=0;j<aindex;j++){
        turma->a[j]=(ALUNO*)malloc(sizeof(ALUNO));
        i=0;
        printf("\nA%d | Digite o Nome: ",j);
        fflush(stdin);
        do{
            caractere=getchar();
            turma->a[j]->nome[i]=caractere;
            i++;
        }while(caractere!='\n');
        turma->a[j]->nome[i-1]='\0';

        for(i=0;i<4;i++){
            printf("A%d | Insira a nota %d: ",j,i);
            scanf("%f",&turma->a[j]->n[i]);
        }
    }
    media(turma,aindex);

    return aindexx=&aindex;
}

float media(TURMA *turma,int aindex){
    float soma;
    float *pi,*pf;
    for(int i=0;i<aindex;i++){
        soma=0;
        pf=turma->a[i]->n+4;
        for(pi=turma->a[i]->n;pi<pf;pi++){
            soma+=*pi;
        }
        turma->a[i]->media=soma/4;
    }
}

void busca(TURMA *turma[],int index,int *aindex){
    char nome_aluno[30],caractere;
    int i=0,j=0,k=0,senao=0;

    printf("Digite o nome do aluno: ");
    fflush(stdin);
    do{
        caractere=getchar();
        nome_aluno[i]=caractere;
        i++;
    }while(caractere!='\n');
    nome_aluno[i-1]='\0';
    i=0;

    while(i<index){
        while(j<*aindex){
            while(turma[i]->a[j]->nome[k]==nome_aluno[k] && turma[i]->a[j]->nome[k]!='\0' && nome_aluno[k]!='\0'){
                k++;
            }
            if(turma[i]->a[j]->nome[k]=='\0' && nome_aluno[k]=='\0'){
                printf("Turma %d\n",i);
                printf("Nome: %s\n",turma[i]->a[j]->nome);
                for(k=0;k<4;k++){
                    printf("N%d: %.1f\n",k,turma[i]->a[j]->n[k]);
                }
                printf("Media: %.1f\n",turma[i]->a[j]->media);
            }else{
                senao++;
            }
            j++;
        }
        i++;
    }
    if(senao==index+1*5){
        printf("Nenhum registro de aluno com esse nome foi encontrado!");
    }
}

void imprimir(TURMA *turma[],int index,int *aindex){
    int i,j,k;
    for(i=0;i<index;i++){
        printf("\nTurma %d\n",i);
        for(j=0;j<*aindex;j++){
            printf("\nNome: %s\n",turma[i]->a[j]->nome);
            for(k=0;k<4;k++){
                printf("N%d: %.1f\n",k,turma[i]->a[j]->n[k]);
            }
            printf("Media: %.1f\n",turma[i]->a[j]->media);
        }
    }
}

TURMA excluir(TURMA *turma[],int index,int *aindex){
    char nome_aluno[30];
    int i=0,j=0,k=0,l,m;
    printf("Digite o nome do aluno");
    scanf("%s",&nome_aluno);

    while(i<index){
        while(j<*aindex){
            while(turma[i]->a[j]->nome[k]==nome_aluno[k] && turma[i]->a[j]->nome[k]!='\0' && nome_aluno[k]!='\0'){
                k++;
            }
            if(turma[i]->a[j]->nome[k]=='\0' && nome_aluno[k]=='\0'){
                l=j;
                for(l=j;l<*aindex;l++){
                    for(m=l+1;m<*aindex;m++){
                        turma[i]->a[l]=turma[i]->a[m]; // l=2,l+1=3;l=3,l+1=4;
                        *aindex--;
                    }
                }
            }
            j++;
            }
            i++;
        }
}

void pressione(){printf("\nPressione qualquer tecla para continuar...");getch();}
