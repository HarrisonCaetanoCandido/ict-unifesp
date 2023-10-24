#include <stdio.h>
#include <stdlib.h>
#define Max 10

typedef struct pilha{
    int vet[Max];
    int topo;
}Tpilha;

typedef Tpilha *Ppilha;

Ppilha cria_pilha();
int push(Ppilha p,int v);
int pop(Ppilha p, int *val);
void imprimir(Ppilha p);
Ppilha liberar(Ppilha p);

Ppilha cria_pilha(){
    Ppilha p;
    p = (Ppilha)malloc(sizeof(Tpilha));
    p->topo = -1;
    return p;
}

int main(){
    Ppilha pilha;
    int op = 1, situacao,v;
    pilha = cria_pilha();

    while(op != 0 && pilha->topo != Max-1){
        printf("Digite o valor que deseja empilhar: ");
        scanf("%d",&v);

        situacao = push(pilha,v);

        printf("\nsituacao: %d\n",situacao);

        if(pilha->topo == Max-1){
            printf("Pilha cheia!\n");
            op = 0;
        }
    }

    op = 1;

    while(op != 0 && pilha->topo != -1){
        printf("Deseja remover itens? (1 - sim | 0 - nao): ");
        scanf("%d",&op);

        if(op == 1){
            situacao = pop(pilha,&v);
            printf("\nsituacao: %d\n",situacao);
            printf("O valor %d foi removido!\n",v);
        }
    }

    imprimir(pilha);

    pilha = liberar(pilha);

    return 0;
}

int push(Ppilha p, int v){
    if(p->topo == Max-1){
        return -1;
    }

    (p->topo)++;

    p->vet[p->topo] = v;

    return 0;
}

int pop(Ppilha p,int *val){
    if(p->topo == -1){
        return -1;
    }

    *val = p->vet[p->topo];
    
    --(p->topo);
    
    return 0;
}

void imprimir(Ppilha p){
    int i;
    if(p->topo == -1){
        return;
    }

    for(i=p->topo; i>-1; i--){
        printf("%d\n",p->vet[i]);
    }
}

Ppilha liberar(Ppilha p){
    free(p);
    return NULL;
}