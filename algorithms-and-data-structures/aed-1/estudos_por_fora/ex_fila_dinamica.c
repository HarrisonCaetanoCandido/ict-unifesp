#include <stdio.h>
#include <stdlib.h>
#define MAX 20

typedef struct no
{
    int info;
    struct no *prox;
} Tno;

typedef Tno *Pno;

typedef struct fila
{
    Pno ini;
    Pno fim;
    int n;
} Tfila;

typedef Tfila *Pfila;

Pno cria_no(int valor);
Pno inserir(Pfila fila, int valor);
Pno remover(Pfila fila);
void imprimir(Pfila fila, Pno fno);
Pno liberar(Pno ini, Pno fim);

Pno cria_no(int valor)
{
    Pno p;
    p = (Pno)malloc(sizeof(Tno));
    if (p == NULL)
        return NULL;
    p->info = valor;
    p->prox = NULL;
    return p;
}

Pno inserir(Pfila fila, int valor)
{
    Pno novo;

    if (fila->n == MAX)
        printf("Fila esta cheia!\n");
    else
    {
        novo = cria_no(valor);
        if (novo == NULL)
            return NULL;

        if (fila->fim == NULL)
        {
            novo->prox = novo;
            fila->ini = novo;
        }
        else
        {
            novo->prox = fila->fim->prox;
            fila->fim->prox = novo;
        }
        ++(fila->n);
        return novo; // retorno para fila->fim
    }
    return fila->fim;
}

Pno remover(Pfila fila)
{
    Pno p;
    if (fila->ini == NULL || fila->fim == NULL)
        return NULL;

    p = fila->ini;
    fila->ini = fila->ini->prox;
    fila->fim->prox = fila->ini;
    --(fila->n);
    if (fila->n == 0 && fila->fim == fila->ini)
    {
        free(p);
        return NULL;
    }
    free(p);
    return fila->fim;
}

void imprimir(Pfila fila, Pno fno)
{
    if (fila->ini != NULL || fila->fim != NULL)
    {
        printf("%d ", fno->info);
        if (fno != NULL && fila->ini == fno->prox)
            return;
        imprimir(fila, fno->prox);
    }
    else
        printf("Fila vazia!");
}

Pno liberar(Pno ini, Pno fim)
{
    if (ini == NULL || fim == NULL)
        return NULL;

    if (ini != fim)
        ini->prox = liberar(ini->prox, fim);

    free(ini);
    return NULL;
}

int main()
{
    int x;
    Pfila fila;
    fila = (Pfila)malloc(sizeof(Tfila));
    if (fila == NULL)
        return 0;
    fila->ini = fila->fim = NULL;
    fila->n = 0;

    do
    {
        printf("Digite um valor inteiro(Numero de Itens na fila %d): ", fila->n);
        scanf("%d", &x);
        if (x != -1)
            fila->fim = inserir(fila, x);
    } while (x != -1);

    do
    {
        printf("------------------------\nNumero de Itens na fila %d\nDeseja remover algum item da fila? (Digite 1 para sim e -1 para nao): ", fila->n);
        scanf("%d", &x);
        if (x != -1)
            fila->fim = remover(fila);
    } while (x != -1);

    imprimir(fila, fila->ini);

    fila->ini = fila->fim = liberar(fila->ini, fila->fim);

    fila->ini == NULL && fila->fim == NULL
        ? printf("\nFila liberada!")
        : printf("\nFila nao liberada!");
    free(fila);

    return 0;
}