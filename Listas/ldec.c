#include <stdio.h>
#include <stdlib.h>

typedef struct lista_dec{
    int info;
    struct lista_dec *prox,*ant;
}Tlista2;

typedef Tlista2 *Plista2;

Plista2 inserir(Plista2 l, int v);
void imprimir(Plista2 l);
Plista2 remover(Plista2 l, int r);
Plista2 liberar(Plista2 l);

Plista2 inserir(Plista2 l, int v)
{
    Plista2 novo;

    novo = (Plista2)malloc(sizeof(Tlista2));

    if(novo == NULL) return NULL;

    novo->info = v;

    if(l == NULL)
    {
        novo->prox = novo->ant = novo;
    }
    else
    {
        novo->prox = l;
        novo->ant = l->ant;
        l->ant->prox = novo;
        l->ant = novo;
    }
    return novo;
}

void imprimir(Plista2 l)
{
    Plista2 p;

    p = l;

    do
    {
        printf("%d\n",p->info);
        p = p->prox;
    } while(p != l);
}

Plista2 remover(Plista2 l, int r)
{
    Plista2 p;

    p = l;

    if(p == NULL) return NULL;

    do
    {
        if(p->info != r)
        {
            p = p->prox;
        }
    } while(p != l && p->info != r);

    if(p == l) // primeiro
    {
        p->ant->prox = p->prox;
        p->prox->ant = p->ant;
        l = p->prox;
        free(p);
        return l;
    }

    if(p == l->ant) // ultimo
    {
        p->ant->prox = l;
        l->ant = p->ant;
        free(p);
        return l;
    }

    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
    free(p);

    return l;
}

Plista2 liberar(Plista2 l)
{
    Plista2 p;

    if(l == NULL) return NULL;

    if(l == l->prox)
    {
        free(l);
        return NULL;
    }

    p = l;
    l = l->prox;
    free(p);
    liberar(l);
}

int main()
{
    Plista2 l;
    int i,v,n;

    l = NULL;

    printf("n: ");
    scanf("%d",&n); // quantidade de nos

    i = 0;
    while(i < n)
    {
        printf("v: ");
        scanf("%d",&v);
        l = inserir(l,v);
        i++;
    }

    printf("lista:\n");
    imprimir(l);

    printf("n: ");
    scanf("%d",&n); // quantidade de nos a serem removidos

    i = 0;
    while(i < n)
    {
        printf("v: ");
        scanf("%d",&v);
        l = remover(l,v);
        i++;
    }

    printf("\nlista:\n");
    imprimir(l);

    l = liberar(l);

    return 0;
}