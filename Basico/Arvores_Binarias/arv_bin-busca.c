#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvbin
{
    char info;
    int chave;
    struct arvbin *esq;
    struct arvbin *dir;
} Tarv;

typedef Tarv *Parv;

Parv cria(char c, int chave);
Parv insereABB(Parv a, char c, int chave);
void imprime(Parv a);
Parv buscaABB(Parv a, int chave);
int iguais(Parv a, Parv b);
void showmenor(Parv a, int X);
Parv remover(Parv a, int X);
Parv menor(Parv a);
//int maior_esq(Parv a, int X);
Parv maior(Parv a);
Parv excluir_folhas(Parv a);
int contar_folhas(Parv a);
Parv remov_descen(Parv a, int X);
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

Parv insereABB(Parv a, char c, int chave)
{
    Parv novo;

    if (a == NULL)
        return cria(c, chave);

    if (a->chave > chave)
        a->esq = insereABB(a->esq, c, chave);
    else
        a->dir = insereABB(a->dir, c, chave);
    return a;
}

void imprime(Parv a) // impressao Em Ordem/Infixa(sae,raiz,sad)
{
    if (a == NULL)
        return;

    imprime(a->esq);
    printf("%c e %d\n", a->info, a->chave);
    imprime(a->dir);
}

Parv buscaABB(Parv a, int chave)
{
    if (a == NULL)
        return NULL; // se a arvore/folha for NULL

    if (a->chave > chave)
        return buscaABB(a->esq, chave);
    else if (a->chave < chave)
        return buscaABB(a->dir, chave);
    else
        return a; // sao iguais
}

int iguais(Parv a, Parv b) // verificar se duas arvores sao iguais
{
    if (a == NULL && b == NULL) // por meio disso verificamos a igualdade
        return 1;

    if (a == NULL || b == NULL)
        return 0;

    return a->chave == b->chave && iguais(a->esq, b->esq) && iguais(a->dir, b->dir);
}

void showmenor(Parv a, int X)
{
    if (a == NULL)
        return;

    if (a->chave != X)
    {
        showmenor(a->esq, X);
        showmenor(a->dir, X);
    }
    else if (a->esq != NULL)
        imprime(a->esq);
}

Parv remover(Parv a, int X)
{
    Parv filho;

    if (a == NULL)
        return NULL;

    if (a->chave > X)
        a->esq = remover(a->esq, X); // 17->esq = (17->esq) => 17->esq = 10, filho = 10->esq, free(10), 17->esq = return filho(10->esq), 17->esq = 1

    if (a->chave < X)
        a->dir = remover(a->dir, X);

    if (a->chave == X)
    {
        if (a->esq == NULL && a->dir == NULL) // significa que ele eh um no folha
        {
            free(a);
            return NULL;
        }

        if (a->esq != NULL && a->dir == NULL) // tem um no filho
        {
            filho = a->esq;
            free(a);
            return filho; // vai retornar em a->esq
        }

        if (a->esq == NULL && a->dir != NULL) // tem um no filho
        {
            filho = a->dir;
            free(a);
            return filho; // vai retornar em a->dir
        }

        if (a->esq != NULL && a->dir != NULL) // tem dois nos filhos
        {
            filho = maior(a->esq); // buscar pelo maior da esquerda nesse caso, aqui em vez de apagar o no raiz vou passar o valor do no com maior valor
                                                  // a esquerda para o no raiz e apagar o no de maior valor

            X = filho->chave;

            a = remover(a, X);

            a->chave = X;
        }
    }
    return a;
}

/*
int maior_esq(Parv a, int X)
{
    if (a->chave > X)
    {
        X = a->chave; // novo maior

        if (a->dir != NULL)
            X = maior_esq(a->dir, X);
    }
    else if (a->dir != NULL)
        X = maior_esq(a->dir, X);

    return X;
}
*/

Parv menor(Parv a)
{
    if (a->esq != NULL)
        a = menor(a->esq);

    return a;
}

Parv maior(Parv a)
{
    if(a->dir != NULL)
        a = maior(a->dir);

    return a;
}

Parv excluir_folhas(Parv a)
{
    if(a == NULL)
        return NULL;
    
    if(a->esq == NULL && a->dir == NULL)
    {
        free(a);
        return NULL;
    }

    a->esq = excluir_folhas(a->esq);
    a->dir = excluir_folhas(a->dir);
    return a;
}

int contar_folhas(Parv a)
{
    if(a == NULL)
        return 0;
    
    if(a->esq == NULL && a->dir == NULL)
        return 1;

    return contar_folhas(a->esq) + contar_folhas(a->dir);
}

Parv remov_descen(Parv a, int X)
{
    if(a == NULL)
        return NULL;
    
    if(a->chave > X)
        a->esq = remov_descen(a->esq, X);

    if(a->chave < X)
        a->dir = remov_descen(a->dir, X);

    if(a->chave == X)
        return libera(a);

    return a;
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
    Parv a = NULL, busca;
    int chave, i, n;
    char info;

    /*
    printf("Digite quantos nos deseja inserir: ");
    scanf("%d", &n);

    i = 0;
    while(i < n)
    {
        /*
        printf("Digite a info do %d no a ser inserido: ", i);
        fflush(stdin);
        info = getchar();
        *//*

        printf("Digite a chave do no %c: ", info);
        scanf("%d", &chave);

        a = insereABB(a, info, chave);

        i++;
    }
    */
    
    a = insereABB(a, 'E', 17);
    a = insereABB(a, 'C', 10);
    a = insereABB(a, 'A', 1);
    a = insereABB(a, 'H', 22);
    a = insereABB(a, 'I', 23);
    a = insereABB(a, 'F', 19);
    a = insereABB(a, 'G', 20);

    imprime(a);

    printf("\n");

    showmenor(a, 22);

    busca = buscaABB(a, 19);

    printf("Chave encontrada: %d\n", busca->chave);
    
    /*
    printf("Digite quantos nos deseja remover: ");
    scanf("%d", &n);

    i = 0;
    while(i < n)
    {
        printf("Digite a chave do no a ser removido: ");
        scanf("%d", &chave);

        a = remover(a, chave);

        i++;
    }
    */

    a = remover(a, 17);

    imprime(a);

    printf("\n");

    showmenor(a, 22);

    busca = menor(a);

    printf("Menor: %d\n", busca->chave);

    printf("\n");

    imprime(a);

    a = excluir_folhas(a);

    printf("\n");

    imprime(a);

    chave = contar_folhas(a);

    printf("Quantidade de nos folha: %d\n", chave);

    a = remov_descen(a, 22);

    printf("\n");

    imprime(a);

    a = libera(a);

    if (a == NULL)
        printf("Arvore liberada!");
    else
        printf("Arvore nao liberada!");

    return 0;
}