#include <stdio.h>
#include <stdlib.h>

typedef struct arv
{
    char info;
    struct arv *esq;
    struct arv *dir;
}Tarv;

typedef Tarv *PArv;

PArv cria(char c, PArv sae, PArv sad);
void imprimir(PArv a);
void buscar(PArv a, char c);
int quant_nos(PArv a);
PArv liberar(PArv a);

PArv cria(char c, PArv sae, PArv sad)
{
    PArv p;
    p = (PArv)malloc(sizeof(Tarv));

    if(p == NULL)
        return NULL;

    p->info = c;
    p->esq = sae;
    p->dir = sad;
    
    return p;
}

void imprimir(PArv a) // percurso em arvore binaria do tipo Pre-Fixa
{
    if(a == NULL)
        return; // Arvore vazia

    printf("%c\n",a->info);
    imprimir(a->esq);
    imprimir(a->dir);
}

void buscar(PArv a, char c)
{
    if(a != NULL)
    {
        if(a->info != c)
        {
            buscar(a->esq, c);
            buscar(a->dir, c);
        }
        else
            printf("Caractere encontrado: %c\n",a->info);
    }
}

int quant_nos(PArv a)
{
    if(a != NULL)
        return (1 + quant_nos(a->esq) + quant_nos(a->dir));
    else
        return 0;
}

PArv liberar(PArv a) // percurso em arvore binaria do tipo Pos-Ordem
{
    if(a != NULL)
    {
        a->esq = liberar(a->esq);
        a->dir = liberar(a->dir);
        free(a);
    }
    return NULL;
}

int main()
{
/*
    Vamos supor que queremos criar a arvore:

             a
           /   \
          b     c
           \   / \
            d e   f

    De maneira recursiva temos:
*/

    PArv a = cria('a',
                    cria('b',
                        NULL,
                        cria('d',NULL,NULL)),
                    cria('c',
                        cria('e',NULL,NULL),
                        cria('f',NULL,NULL)));

    imprimir(a);
    printf("\n");

    // Podemos ainda acrescentar nos na arvore da seguinte forma:

    a->esq->esq = cria('x',
                        cria('y',NULL,NULL),
                        cria('z',NULL,NULL));

    imprimir(a);
    printf("\n");

    // Para remover apenas um no da arvore, podemos fazer da seguinte maneira:

    a->dir->esq = liberar(a->dir->esq);

    imprimir(a);
    printf("\n");

    buscar(a, 'z');

    a = liberar(a); // Liberar toda a arvore

    if(a == NULL)
        printf("Arvore liberada!");
    else
        printf("Arvore nao liberada!");

    return 0;
}