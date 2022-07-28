#include <stdio.h>
#include <stdlib.h>

typedef struct arv
{
    char info;
    struct arv *esq;
    struct arv *dir;
} Tarv;

typedef Tarv *PArv;

PArv cria(char c, PArv sae, PArv sad);
void imprimir(PArv a);
PArv liberar(PArv a);

PArv cria(char c, PArv sae, PArv sad)
{
    PArv p = (PArv)malloc(sizeof(Tarv));

    if (p == NULL)
        return NULL;

    p->info = c;
    p->esq = sae;
    p->dir = sad;
    return p;
}

void imprimir(PArv a)
{
    if (a != NULL)
    {
        printf("%c\n", a->info);
        imprimir(a->esq);
        imprimir(a->dir);
    }
}

PArv liberar(PArv a)
{
    if (a != NULL)
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

        De maneira nao recursiva vamos precisar criar a arvore de baixo
        para cima, ou seja, demanda bem mais esforco. Sendo assim:
    */

    PArv d = cria('d', NULL, NULL);
    PArv b = cria('b', NULL, d); // PAI de 'd'
    PArv e = cria('e', NULL, NULL);
    PArv f = cria('f', NULL, NULL);
    PArv c = cria('c', e, f); // PAI de 'e' e 'f'
    PArv a = cria('a', b, c); // PAI dos pais 'b' e 'c'

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

    a = liberar(a);

    if (a == NULL)
        printf("Arvore liberada!");
    else
        printf("Arvore nao liberada!");

    return 0;
}