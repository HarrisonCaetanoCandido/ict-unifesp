#include <stdio.h>
#include <stdlib.h>

typedef struct no *pme;

struct no
{
    int info, col;
    pme prox;
};

typedef struct linha *plinha;

struct linha
{
    int linha;
    pme cprox;
    plinha lprox;
};

plinha inserir(plinha linha, int val, int lin, int col);
void imprimir(plinha linha, int L, int C);
plinha liberar(plinha linha);

plinha inserir(plinha linha, int val, int lin, int col)
{
    pme cnovo, p;
    plinha lnovo, l, lant = NULL;

    cnovo = (pme)malloc(sizeof(struct no));
    if (cnovo == NULL)
        return NULL;
    cnovo->col = col;
    cnovo->info = val;
    cnovo->prox = NULL;

    lnovo = (plinha)malloc(sizeof(struct linha));
    if (lnovo == NULL)
        return NULL;
    lnovo->linha = lin;
    lnovo->cprox = cnovo;
    lnovo->lprox = NULL;

    if (linha == NULL)
        linha = lnovo;
    else
    {
        for (l = linha; l != NULL && l->linha < lin; l = l->lprox)
            lant = l; // como aqui nao precisa, nao farei o caso de insercao no inicio da lista linha

        if (l == NULL)
            lant->lprox = lnovo;

        if (l != NULL && l->linha == lin)
        {
            free(lnovo);

            for (p = l->cprox; p->prox != NULL; p = p->prox);

            p->prox = cnovo;
        }
    }
    return linha;
}

void imprimir(plinha linha, int L, int C)
{
    int i, j;
    pme p;
    plinha l;

    for(i = 0; i < L; i++)
    {
        p = linha->cprox;
        for(j = 0; j < C; j++)
        {
            if(p != NULL && p->col == j)
            {
                printf("%d ",p->info);
                p = p->prox;
            }
            else
                printf("0 ");
        }
        linha = linha->lprox;
        printf("\n");
    }
}

plinha liberar(plinha linha)
{
    pme p, q;
    plinha l, r;

    l = linha;
    while(l != NULL) // liberar as linhas
    {
        p = l->cprox;
        while(p != NULL) // liberar as colunas
        {
            q = p;
            p = p->prox;
            free(q);
        }
        r = l;
        l = l->lprox;
        free(r);
    }
    return l;
}

int main()
{
    int i, j, val, L, C;
    plinha linha = NULL;

    printf("Digite a dimensao da matriz: ");
    scanf("%d %d", &L, &C);

    for (i = 0; i < L; i++)
    {
        for (j = 0; j < C; j++)
        {
            printf("Digite o valor a ser inserido na posicao[%d][%d]: ", i, j);
            scanf("%d", &val);

            if (val != 0)
                linha = inserir(linha, val, i, j);
        }
    }

    imprimir(linha, L, C);

    linha = liberar(linha);

    if(linha == NULL)
        printf("A matriz foi liberada!");
    else
        printf("Erro ao liberar a matriz!");

    return 0;
}