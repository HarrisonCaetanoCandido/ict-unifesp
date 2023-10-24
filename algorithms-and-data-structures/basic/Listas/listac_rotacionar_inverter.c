#include <stdio.h>
#include <stdlib.h>

typedef struct lista
{
    char letra;
    struct lista *prox;
} Tlista;
typedef Tlista *Plista;

Plista inserir(Plista ultimo, char v);
Plista rotacionar(Plista ultimo);
Plista inverter(Plista ultimo);
void imprimir(Plista ultimo);
Plista liberar(Plista ultimo);

int main()
{
    Plista ultimo = NULL;
    int i = 0;
    char v;

    while (i != -1)
    {
        printf("i:: ");
        scanf("%d", &i);
        if (i == 1)
        {
            printf("v:: ");
            scanf(" %c", &v);
            ultimo = inserir(ultimo, v);
        }
    }

    i = 0;

    while (i != -1)
    {
        imprimir(ultimo);
        printf("\ni:: ");
        scanf("%d", &i);
        if (i == 1)
        {
            ultimo = rotacionar(ultimo);
        }
    }

     i = 0;

    while (i != -1)
    {
        imprimir(ultimo);
        printf("\ni:: ");
        scanf("%d", &i);
        if (i == 1)
        {
            ultimo = inverter(ultimo);
        }
    }

    ultimo = liberar(ultimo);

    return 0;
}

Plista inserir(Plista ultimo, char v)
{
    Plista novo;

    novo = (Plista)malloc(sizeof(Tlista));

    if (novo == NULL)
        return NULL;

    novo->letra = v;

    if (ultimo == NULL)
    {
        novo->prox = novo;
    }
    else
    {
        novo->prox = ultimo->prox;
        ultimo->prox = novo;
    }
    return novo;
}

Plista rotacionar(Plista ultimo)
{
    Plista ini, ant = NULL, p;

    p = ini = ultimo->prox;

    do
    {
        //       1     , 2,  3  , 4
        // ultimo->prox      ant   ultimo
        do
        {
            ant = p;
            p = p->prox;
        } while (p != ultimo->prox);

        ultimo = ant;

    } while (ini != ultimo); // enquanto os ponteiros apontam para enderecos diferentes

    return ultimo;
}

Plista inverter(Plista ultimo){
    Plista ant, p, seg, r;

    r = p = ultimo->prox;
    ant = ultimo;

    do{

        seg = p->prox;
        p->prox = ant;
        ant = p;
        p = seg;    

    }while(seg != r);

    return seg;
}

void imprimir(Plista ultimo)
{
    Plista p;

    p = ultimo->prox;

    do
    {
        printf("%c", p->letra);
        p = p->prox;
    } while (p != ultimo->prox);
}

Plista liberar(Plista ultimo)
{
    Plista p;

    while (p != NULL)
    {
        p = ultimo->prox;
        ultimo->prox = p->prox;
        free(p);
    }
    return p;
}