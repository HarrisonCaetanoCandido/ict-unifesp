#include <stdio.h>
#include <stdlib.h>

typedef struct arvbin
{
    char info;
    int chave;
    struct arvbin *esq;
    struct arvbin *dir;
} Tarv;

typedef Tarv *Parv;

Parv cria(char c, int chave);
void insere_ord(Parv a, Parv no);
void imprime(Parv a);
Parv libera(Parv a);

Parv cria(char c, int chave) // criar apenas um no folha
{
    Parv a = (Parv)malloc(sizeof(Tarv));
    if (a == NULL)
        return NULL;
    a->info = c;
    a->chave = chave;
    a->esq = a->dir = NULL;
    return a;
}

void insere_ord(Parv a, Parv no)
{
    if (a->chave > no->chave)
    {
        if (a->esq == NULL)
            a->esq = no;
        else
            insere_ord(a->esq, no);
    }

    if (a->chave < no->chave)
    {
        if (a->dir == NULL)
            a->dir = no;
        else
            insere_ord(a->dir, no);
    }
}

void imprime(Parv a)
{
    if(a == NULL)
        return;

    imprime(a->esq);
    printf("%c e %d\n", a->info, a->chave);
    imprime(a->dir);
}

Parv libera(Parv a)
{
    if (a != NULL)
    {
        a->esq = libera(a->esq);
        a->dir = libera(a->dir);
        free(a);
    }
    return NULL;
}

int main()
{
    Parv a = cria('a', 17);
    Parv b = cria('b', 99);
    Parv c = cria('c', 13);
    Parv d = cria('d', 1);
    Parv e = cria('e', 3);
    Parv f = cria('f', 100);
    Parv g = cria('g', 400);

    insere_ord(a, b);
    insere_ord(a, c);
    insere_ord(a, d);
    insere_ord(a, e);
    insere_ord(a, f);
    insere_ord(a, g);

    imprime(a);

    a = libera(a);

    return 0;
}