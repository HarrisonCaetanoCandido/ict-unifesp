/*
Faça um programa que leia duas filas numéricas
ordenadas crescentemente a partir do início da fila e
que contenham uma função que transfira os
elementos dessas filas para uma terceira fila,
inicialmente vazia, de modo que ela também fique
ordenada crescentemente com o menor valor no
início da fila.
*/

#include <stdio.h>
#include <stdlib.h>
#define max 10

typedef struct FILA{
    int vet[max];
    int n;
    int ini;
}Tfila;

Tfila* cria_fila();
void inserir(Tfila *f1,Tfila *f2,int v1,int v2);
int retira(Tfila *p);
int incr_indice(int i);
void criar_terc(Tfila *f1,Tfila* f2,Tfila *f3);
void listar_duasf(Tfila *f1,Tfila *f2);
int remover(Tfila *p);

int main(){
    Tfila *f1,*f2,*f3;
    f1=cria_fila();
    f2=cria_fila();
    f3=cria_fila();

    if(f1==NULL||f2==NULL||f3==NULL){
        printf("Nao foi possivel alocar memoria!\n");
        return 0;
    }

    int op,v1,v2,i;

    do{
        printf("1 | Inserir na Fila 1 e 2\n");
        printf("2 | Criar Fila 3\n");
        printf("3 | Sair\n");
        printf("Selecione: ");
        scanf("%d",&op);
        switch(op){
            case 1: // inserir
                printf("Digite o valor de v1: ");
                scanf("%d",&v1);
                printf("Digite o valor de v2: ");
                scanf("%d",&v2);
                inserir(f1,f2,v1,v2);
            break;
            case 2: // listar as 3 filas && criar fila 3 
                criar_terc(f1,f2,f3);
            break;
            case 3: // sair
                printf("Programa encerrado!");
            break;
            default:
                printf("Opcao invalida!\n");
            break;
        }
    }while(op!=3);
    free(f1);
    free(f2);
    free(f3);
    return 0;
}

Tfila* cria_fila(){
    Tfila *p;
    p=(Tfila*)malloc(sizeof(Tfila));
    p->ini=0;
    p->n=0;
}

void inserir(Tfila *f1,Tfila *f2,int v1,int v2){
    int fim1,fim2,fim3,i=0;
    if(f1->n==max || f2->n==max){
        printf("Fila 1 esta cheia\n");
    }else{
        fim1=(f1->ini+f1->n)%max;
        f1->vet[fim1]=v1;
        f1->n++;
        fim2=(f2->ini+f2->n)%max;
        f2->vet[fim2]=v2;
        f2->n++;
    }
    printf("fim2: %d\n",fim2);
    printf("f2->ini(fim): %d\n",f2->ini);
    printf("f2->n++: %d\n",f2->n);
}

void listar_duasf(Tfila *f1,Tfila *f2){
    int i,fim;
    if(f1->n==0 || f2->n==0){
            printf("Fila vazia!\n");
        }else{
            fim=f1->ini+f1->n;
            if(f1->ini>0 && f1->n==max){
                for(i=0;i<f1->ini;i++){
                    printf("vet[%d]: %d\n",i,f1->vet[i]);
                }
                for(i=f1->ini;i<fim-1;i++){
                    printf("vet[%d]: %d\n",i,f1->vet[i]);
                }
                }else{
                    for(i=f1->ini;i<fim;i++){
                        printf("Fila 1 | vet[%d]: %d\n",i,f1->vet[i]);
                    }
                }
                fim=f2->ini+f2->n;
                if(f2->ini>0 && f2->n==max){
                    for(i=0;i<f2->ini;i++){
                        printf("vet[%d]: %d\n",i,f2->vet[i]);
                    }
                    for(i=f2->ini;i<fim-1;i++){
                        printf("vet[%d]: %d\n",i,f2->vet[i]);
                    }
                    }else{
                        for(i=f2->ini;i<fim;i++){
                            printf("Fila 2 | vet[%d]: %d\n",i,f2->vet[i]);
                        }
                    }
        }
}

int remover(Tfila *p){
    int inicio;
    inicio=p->ini;
    p->ini=incr_indice(p->ini);
    --(p->n);
    return p->vet[inicio];
}

int incr_indice(int i){
    return (i+1)%max;
}

void criar_terc(Tfila *f1,Tfila* f2,Tfila *f3){
    listar_duasf(f1,f2);

    int fim,i,nf1,nf2,inicio;
    if(f1->n==0||f2->n==0){
        printf("As filas 1 e 2 estao vazias!\n");
        return 0;
    }else{
    inicio=f1->ini;
    fim=f1->ini+f1->n;
    for(i=inicio;i<fim;i++){
        i=(f3->ini+f3->n)%max;
        nf1=remover(f1);
        nf2=remover(f2);
        f3->vet[i]=nf1+nf2;
        ++(f3->n);
        }
        fim=f3->ini+f3->n;
        for(i=f3->ini;i<fim;i++){
            printf("Fila 3 | vet[%d]: %d\n",i,f3->vet[i]);
        }
    }
}