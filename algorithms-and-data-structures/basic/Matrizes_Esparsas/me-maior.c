#include <stdio.h>
#include <stdlib.h>

typedef struct no *pme;

struct no
{
    int info, col;
    pme prox;
};

typedef pme *matriz;

void inicializar(matriz m, int L);
void inserir(matriz m, int val, int lin, int col);
void imprimir(matriz m, int L, int C);
void maior_valor(matriz m, int L, int C);

void liberar(matriz m, int L);

void inicializar(matriz m, int L)
{
    int i;
    for (i = 0; i < L; i++)
        m[i] = NULL;
}

void liberar(matriz m, int L)
{
    pme p, q;

    while (p != NULL)
    {
        p = q;
        p = p->prox;
        free(q);
    }
}

void inserir(matriz m, int val, int lin, int col)
{
    pme novo, p;

    novo = (pme)malloc(sizeof(struct no));

    if (novo == NULL)
        return;

    novo->col = col;
    novo->info = val;
    novo->prox = NULL;

    if (m[lin] == NULL)
        m[lin] = novo;
    else
    {
        for (p = m[lin]; p->prox != NULL; p = p->prox)
            ;
        p->prox = novo;
    }
}

void imprimir(matriz m, int L, int C)
{
    pme p;
    int i, j;

    for (i = 0; i < L; i++)
    {
        p = m[i];
        for (j = 0; j < C; j++)
        {
            if (p != NULL && p->col == j)
            {
                printf("%d ", p->info);
                p = p->prox;
            }
            else
                printf("0 ");
        }
        printf("\n");
    }
}

void maior_valor(matriz m, int L, int C)
{
    pme p;
    int i, j, lin, col, maior;

    maior = 0;

    for (i = 0; i < L; i++)
    {
        p = m[i];
        if (p != NULL && maior == 0)
        {
            maior = p->info;
            lin = i;
            col = p->col;
        }
        for (j = 0; j < C; j++)
        {
            if (p != NULL && maior != 0 && p->info > maior)
            {
                maior = p->info;
                lin = i;
                col = p->col;
            }
            if (p != NULL)
                p = p->prox;
        }
    }

    if (maior == 0)
        printf("A matriz eh Nula!\n");
    else
    {
        printf("Maior: %d\n", maior);
        printf("Linha: %d\n", lin);
        printf("Coluna: %d\n", col);
    }
}

int main()
{
    matriz m;
    int i, j, L, C, val;

    printf("Digite a quantidade de linhas: ");
    scanf("%d", &L);

    printf("Digite a quantidade de colunas: ");
    scanf("%d", &C);

    m = (pme)malloc(L * sizeof(struct no));

    if (m == NULL)
        return 0;

    inicializar(m, L);

    for (i = 0; i < L; i++)
    {
        for (j = 0; j < C; j++)
        {
            printf("Digite o valor a ser inserido na posicao[%d][%d]: ", i, j);
            scanf("%d", &val);

            if (val != 0)
                inserir(m, val, i, j);
        }
    }

    imprimir(m, L, C);

    maior_valor(m, L, C);

    liberar(m, L);

    return 0;
}