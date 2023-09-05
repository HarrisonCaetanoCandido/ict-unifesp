#include <stdio.h>
#include <stdlib.h>
#define Max_el 10

typedef struct{
    int vet[Max_el]; // Pilha nada mais eh do que o vetor vet[Max_el]
    int topo; // cursor que indica onde esta na pilha
}Tpilha;

Tpilha* cria_pilha();
void push(Tpilha *p,int v);
void pop(Tpilha *p);
void ler_pilha(Tpilha *p);
int desempilhar(Tpilha *p,int conf);
int top(Tpilha *p); // consulta topo
int top_pop(Tpilha *p); // desempilhamento com retorno do valor que estava em topo

int main(){
    Tpilha *p;
    int op,v,inteiro[Max_el],i,j,conf,top_P;
    p=cria_pilha();
    if(p==NULL){
        printf("Nao foi possivel alocar memoria!\n");
        return 0;
    }
    do{
        printf("1 | Push\n");
        printf("2 | Pop\n");
        printf("3 | Top Pop\n");
        printf("4 | Inverter Pilha\n");
        printf("5 | Ler Pilha\n");
        printf("6 | Sair\n");
        printf("Selecione: ");
        scanf("%d",&op);
        switch(op){
            case 1: // push
                printf("Digite um valor que deseja inserir: ");
                scanf("%d",&v);
                push(p,v);
            break;
            case 2: // pop
                pop(p);
            break;
            case 3: // top pop
            if(p->topo == -1){
                printf("Pilha vazia!\n");
            }else{
                top_P=top_pop(p);
                if(p->topo == -1){
                    printf("Pilha vazia!\n");
                }else{
                    printf("val no vet: %d\n",top_P);
                    }
            }
            break;
            case 4: // inverter pilha
            if(p->topo == -1){
                printf("Pilha vazia!\n");
            }else{
                conf=0;
                for(i=0;i<=p->topo;i++){
                    inteiro[i]=desempilhar(p,conf); // do topo para 0, vetor vai ter os valores ja invertidos
                    conf=1;
                }
                j=p->topo;
                p->topo=-1;
                for(i=0;i<=j;i++){
                    push(p,inteiro[i]); // vou inserir os valores invertidos no vetor de maneira invertida na pilha
                }
            }
            break;
            case 5: // ler pilha
                ler_pilha(p);
            break;
            case 6: // sair
                printf("Programa encerrado!");
            break;
            default:
                printf("Opcao invalida!\n");
            break;
        }
    }while(op!=6);

    free(p);

    return 0;
}

Tpilha* cria_pilha(){
    Tpilha *p;
    p=(Tpilha*)malloc(sizeof(Tpilha));
    p->topo=-1;
    return p;
}

void push(Tpilha *p,int v){
    if(p->topo == Max_el-1){
        printf("Pilha cheia!\n");
    }else

    p->vet[++(p->topo)]=v;
}

int top(Tpilha *p){
    if(p->topo == -1){
        printf("Pilha vazia!\n");
    }else

    return p->vet[p->topo];
}

void pop(Tpilha *p){

    if(p->topo == -1){
        printf("Pilha vazia!\n");
    }else{(p->topo)--;}
}

int top_pop(Tpilha *p){
    
    return p->vet[--(p->topo)];
}

void ler_pilha(Tpilha *p){
    int i;
    if(p->topo == -1){
        printf("Pilha vazia!\n");
    }else
    for(i=p->topo; i>=0;i--){
        printf("vet[%d]: %d\n",i,p->vet[i]);
    }
}

int desempilhar(Tpilha *p,int conf){
    int retorno,*topo;
    if(conf==0){
        *topo=p->topo;
        retorno=p->vet[*topo];
        --(*topo);
    }else{
        retorno=p->vet[*topo];
        --(*topo);
    }
    return retorno;
}