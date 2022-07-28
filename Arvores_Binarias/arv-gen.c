#include <stdio.h>
#include <stdlib.h>

typedef struct arvgen
{
    char info;
    struct arvgen *prim;
    struct arvgen *prox;
} Tarvgen;

typedef Tarvgen *Parvgen;

Parvgen cria(char c);
void insere(Parvgen a, Parvgen sa);
void imprime(Parvgen a);
Parvgen existe(Parvgen a, char c);
Parvgen libera(Parvgen a);

Parvgen cria(char c) // criar folhas
{
    Parvgen a = (Parvgen)malloc(sizeof(Tarvgen));
    if (a == NULL)
        return NULL;
    a->info = c;
    a->prim = a->prox = NULL;
    return a;
}

void insere(Parvgen a, Parvgen sa) // no pai, no filho
{
    sa->prox = a->prim;
    a->prim = sa;
}

void imprime(Parvgen a)
{
    while(a != NULL)
    {
        printf("%c\n",a->info);
        imprime(a->prim);
        imprime(a->prox);
    }
}

Parvgen existe(Parvgen a, char c)
{
    if(a != NULL && a->info != c)
    {
        a->prim = existe(a->prim, c);
        a->prox = existe(a->prox, c);
    }
    
    if(a != NULL && a->info == c)
        return a;
}

Parvgen libera(Parvgen a)
{
    if(a != NULL)
    {
        a->prim = libera(a->prim);
        a->prox = libera(a->prox);
        free(a);
    }
    return NULL;
}

int main()
{
    /*
        Criando a seguinte arvore generica:


             a
           / | \
          b  f  g
         / \   / \
        c   e h   i
        |         |
        d         j

        Temos o esquema:

        a
        |
        b -> f -> g
        |         |
        c -> e    h -> i
        |              |
        d              j

    */

    // Cria os nos como folhas
    Parvgen a = cria('a');
    Parvgen b = cria('b');
    Parvgen c = cria('c');
    Parvgen d = cria('d');
    Parvgen e = cria('e');
    Parvgen f = cria('f');
    Parvgen g = cria('g');
    Parvgen h = cria('h');
    Parvgen i = cria('i');
    Parvgen j = cria('j');

    Parvgen busca = NULL;

    // Montar a hierarquia

    insere(c, d);
    insere(b, e);
    insere(b, c);
    insere(i, j);
    insere(g, i);
    insere(g, h);
    insere(a, g);
    insere(a, f);
    insere(a, b);

    imprime(a);
    printf("\n");

    busca = existe(a, 'j');

    if(busca != NULL)
        printf("Caractere encontrado: %c",busca->info);
    else
        printf("Caractere nao encontrado!");

    a = libera(a);

    return 0;
}