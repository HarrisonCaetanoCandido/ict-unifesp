#include <stdio.h>
#include <stdlib.h>

typedef struct no // Mesma estrutura de um no de uma lista
{
    int info;
    struct no *prox;
}TNo;
typedef TNo *PNo;

typedef struct pilha_dinamica{
    PNo topo;
}Tpilha;
typedef Tpilha *Ppilha;

Ppilha cria_pilha();
void inserir(Ppilha pilha, int v);
void remover(Ppilha pilha);
void imprimir(Ppilha pilha);
Ppilha liberar(Ppilha pilha);

Ppilha cria_pilha(){
    Ppilha p;
    p = (Ppilha)malloc(sizeof(Tpilha));
    p->topo = NULL;
    return p;
}

void inserir(Ppilha pilha, int v){
    PNo novo;
    
    novo = (PNo)malloc(sizeof(TNo));

    novo->info = v;

    novo->prox = pilha->topo;
    pilha->topo = novo;
}

void remover(Ppilha pilha){
    PNo p;

    if(pilha->topo == NULL) return;

    p = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(p);
}

void imprimir(Ppilha pilha){
    PNo p;

    for(p = pilha->topo; p!=NULL; p = p->prox)
        printf("%d\n",p->info);
        
}

Ppilha liberar(Ppilha pilha){
    PNo p;

    while(p!=NULL){
        p = pilha->topo;
        pilha->topo = pilha->topo->prox;
        free(p);
    }
    return NULL;
}

int main(){
    Ppilha pilha = cria_pilha();
    int op = 0;


    while(op != -1){
        scanf("%d",&op); // -1 para sair
        inserir(pilha,op);
    }

    op = 0;

    while(op != -1){
        printf("Deseja remover? (1 = sim |-1 = nao): ");
        scanf("%d",&op);
        if(op == 1){
            remover(pilha);
        }
    }

    imprimir(pilha);

    pilha = liberar(pilha);

    return 0;
}