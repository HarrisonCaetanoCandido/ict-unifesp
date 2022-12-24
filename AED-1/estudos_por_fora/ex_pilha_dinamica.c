#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    char info;
    struct no *prox;
} Tno;

typedef Tno *Pno;

typedef struct pilha
{
    Pno topo;
} Tpilha;

typedef Tpilha *Ppilha;

Ppilha inicializar(Ppilha p);
Pno push(Ppilha p, char caractere);
char pop(Ppilha p);
void imprimir(Pno p);
Pno liberar(Pno p);

Ppilha inicializar(Ppilha p)
{
    p = (Ppilha)malloc(sizeof(Tpilha));
    if (p == NULL)
        return;
    p->topo = NULL;
    return p;
}

Pno push(Ppilha p, char caractere)
{
    Pno novo;

    novo = (Pno)malloc(sizeof(Tno));
    if (novo == NULL)
        return NULL;

    novo->info = caractere;
    novo->prox = p->topo;
    return novo;
}

char pop(Ppilha p)
{
    Pno q;
    char caractere;

    q = p->topo;
    caractere = p->topo->info;
    p->topo = p->topo->prox;
    free(q);
    return caractere;
}

void imprimir(Pno p)
{
    if (p == NULL)
        printf("Pilha vazia!\n");
    else
    {
        printf("%c", p->info);
        if (p->prox == NULL)
            return;
        imprimir(p->prox);
    }
}

Pno liberar(Pno p)
{
    if (p != NULL)
    {
        p->prox = liberar(p->prox);
        free(p);
    }
    return NULL;
}

int main()
{
    Ppilha pilha;
    char menu;

    pilha = inicializar(pilha);

    do
    {
        printf("Digite um caractere: ");
        scanf(" %c", &menu);

        if (menu != '!')
            pilha->topo = push(pilha, menu);

    } while (menu != '!');

    do
    {
        printf("Deseja remover algum caractere? (Digite 's' caso queira ou '!' caso nao queira): ");
        scanf(" %c", &menu);

        if (menu != '!')
            printf("Caractere removido: %c\n", pop(pilha));

    } while (menu != '!');

    imprimir(pilha->topo);

    pilha->topo = liberar(pilha->topo);
    free(pilha);

    return 0;
}