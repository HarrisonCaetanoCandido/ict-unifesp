#include <stdio.h>
#include <stdlib.h>

typedef struct lista2{
    int info;
    struct lista2 *prox,*ant;
}TLista2;

typedef TLista2 *PLista2;

PLista2 inserir(PLista2 l, int val)
{
    PLista2 novo;

    novo = (PLista2)malloc(sizeof(TLista2));

    novo->info = val;

    if(l == NULL)
    {
        novo->prox = novo->ant = novo;
        l = novo;
        return l;
    }

    novo->prox = l->prox;
    novo->ant = l;
    l->prox->ant = novo;
    l->prox = novo;
    novo = l;
    return l;
}

PLista2 remocao(PLista2 l, int v){
    PLista2 p;

    p = l;

    do{
        if(p->info != v){
            p = p->prox;
        }
    }while(p != l && p->info != v);

    if(p->info == v){
        if(p == l){ // primeiro
            l = l->prox;
            l->ant = p->ant;
            l->ant->prox = l;
            free(p);
            return l;
        }

        if(p == l->ant){ // ultimo
            p->ant->prox = l;
            l->ant = p->ant;
            free(p);
            return l;
        }

        p->ant->prox = p->prox;
        p->prox->ant = p->ant;
        free(p);
    }

    return l;
}

void imprimir(PLista2 l){
    PLista2 p;
    p = l;
    do{
        printf("%d",p->info);
        p = p->prox;
    }while(p != l);
}

PLista2 liberar(PLista2 l)
{
    PLista2 p;

    if (l == NULL) return NULL;

    if (l->prox == l)
    {
        free(l);
        return NULL;
    }

    p = l->prox;
    l->prox = p->prox;
    free(p);
    liberar(l);
}

PLista2 inserir(PLista2 l, int val);
PLista2 remocao(PLista2 l, int v);
void imprimir(PLista2 l);
PLista2 liberar(PLista2 l);

int main(){
    PLista2 l=NULL;
    int i, r;

    i=0;
    while(i < 3){
        scanf("%d",&r);
        l = inserir(l,r);
        i++;
    }

    imprimir(l); 
    printf("\n");

    i = 0;
    while(i<2){
        scanf("%d",&r);
        l = remocao(l,r);
        i++;
    }

    imprimir(l);

    l = liberar(l);
}