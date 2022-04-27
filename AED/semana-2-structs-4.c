/*
Considerando a estrutura Aluno definida
anteriormente, escreva um programa que
contenha uma função para inicializar uma tabela
de alunos, uma função que armazena os dados
de um novo aluno numa dada posição do vetor,
uma que mostre as informações do aluno numa
dada posição do vetor (esta função deve prever o
caso de tentar mostrar os dados em uma posição
sem dados) e o programa principal. Utiliza
ponteiro para estrutura para este programa.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    char nome[81];
    int mat;
    char end[121];
    char tel[21];
}Aluno;

Aluno inicializa_vetor(Aluno *tab[], int pos); 
void desalocar(Aluno *tab[], int pos);
Aluno inserir(Aluno *tab,int pos);
void imprimir(Aluno *tab[],int pos);
void buscar(Aluno *tab,int posvet);
void pressione();

int main(){
    Aluno *tab[100];int pos=0,selecione,posvet;char caractere;

    do{
        system("clear||cls");
        printf("1 | Inserir\n");
        printf("2 | Imprimir\n");
        printf("3 | Buscar\n");
        printf("4 | Sair\n");
        printf("Selecione: ");
        scanf("%d",&selecione);
        switch (selecione)
        {
        case 1: // imprimir
        system("clear||cls");
        inicializa_vetor(tab,pos);
        inserir(tab[pos],pos);
        pos++;
        printf("\nDados registrados com sucesso!\n");
        pressione();
            break;
        case 2: // imprimir
        system("clear||cls");
        imprimir(tab,pos);
        pressione();
            break;
        case 3: // buscar
        system("clear||cls");
        printf("Digite a posicao no vetor que deseja ver os dados: ");
        scanf("%d",&posvet);

        if(posvet>=pos||posvet<0){
            printf("\nNao foi possivel encontrar o registro!\n");
        }else{buscar(tab[posvet],posvet);}

        pressione();
            break;
        case 4: // sair
        printf("Saindo");
            break;
        default:
        printf("\nErro, escolha novamente!\n");
            break;
    }
    }while(selecione!=4);

    desalocar(tab,pos);

    return 0;
}

Aluno inicializa_vetor(Aluno *tab[],int pos){
    if(tab[pos]==NULL){
        printf("Nao foi possivel alocar memoria!\n");
        exit(1);
    }
    tab[pos]=(Aluno*)malloc(sizeof(Aluno));
}

void desalocar(Aluno *tab[],int pos){ for(int i=0;i<pos;i++){ free(tab[i]); } }

void pressione(){printf("\nPressione qualquer tecla para continuar...\n");getch();}

Aluno inserir(Aluno *tab,int pos){
    char caractere;int i=0;

    fflush(stdin);
    printf("Registro %d | Digite o nome do aluno: ",pos);
    do{
        caractere=getchar();
        tab->nome[i]=caractere;
        i++;
    }while(caractere!='\n');
    tab->nome[i-1]='\0';
    i=0;

    fflush(stdin);
    printf("Digite a nota: ");
    scanf("%d",&tab->mat);

    fflush(stdin);
    printf("Registro %d | Digite o endereco do aluno: ",pos);
    do{
        caractere=getchar();
        tab->end[i]=caractere;
        i++;
    }while(caractere!='\n');
    tab->end[i-1]='\0';
    i=0;

    fflush(stdin);
    printf("Registro %d | Digite o telefone do aluno: ",pos);
    do{
        caractere=getchar();
        tab->tel[i]=caractere;
        i++;
    }while(caractere!='\n');
    tab->tel[i-1]='\0';
}

void imprimir(Aluno *tab[],int pos){
    for(int i=0;i<pos;i++){
        printf("\nRegistro %d | Nome: %s\n",i,tab[i]->nome);
        printf("Registro %d | Mat: %d\n",i,tab[i]->mat);
        printf("Registro %d | Endereco: %s\n",i,tab[i]->end);
        printf("Registro %d | Telefone: %s\n",i,tab[i]->tel);
    }
}

void buscar(Aluno *tab,int posvet){
        printf("\nRegistro %d | Nome: %s\n",posvet,tab->nome);
        printf("Registro %d | Mat: %d\n",posvet,tab->mat);
        printf("Registro %d | Endereco: %s\n",posvet,tab->end);
        printf("Registro %d | Telefone: %s\n",posvet,tab->tel);
}