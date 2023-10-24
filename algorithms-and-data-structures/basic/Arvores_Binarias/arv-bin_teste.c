#include <stdio.h>
#include <stdlib.h>

typedef struct arv_bin
{
    int info;
    struct arv_bin *esq, *dir;
}Tarv;

typedef Tarv *Parv;

Parv cria_folha(int X);
Parv inserir_ord(Parv a, int X);
void imprimir(Parv a);
Parv liberar(Parv a);

Parv cria_folha(int X)
{
    Parv novo;
    novo = (Parv)malloc(sizeof(Tarv));
    if(novo == NULL)
        return NULL;
    novo->info = X;
    novo->esq = novo->dir = NULL;
    return novo;
}

Parv inserir_ord(Parv a, int X)
{
    if(a == NULL)
    {
        return cria_folha(X);
    }

    if(a->info > X)
        a->esq = inserir_ord(a->esq, X);

    if(a->info < X)
        a->dir = inserir_ord(a->dir, X);

    return a;
}

void imprimir(Parv a) // em ordem INFIXA (Descrescente)
{
    if(a != NULL)
    {
        imprimir(a->esq);
        printf("%d\n", a->info);
        imprimir(a->dir);
    }
}

Parv liberar(Parv a)
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
    int i, n, X;
    Parv a = NULL;

    printf("n: ");
    scanf("%d", &n);
    
    i = 0;
    while(i < n)
    {
        printf("Digite o X[%d]: ", i);
        scanf("%d", &X);

        a = inserir_ord(a, X);
        i++;
    }

    imprimir(a);

    a = liberar(a);

    if(a == NULL)
        printf("Arvore liberada com sucesso!");
    else
        printf("Arvore nao liberada!");

    return 0;
}