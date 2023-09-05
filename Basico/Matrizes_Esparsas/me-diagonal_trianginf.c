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
void inserir_seq(matriz m, int val, int lin, int col);
void transposta(matriz m, int L, int C);
void simetrica(matriz m, matriz mtransp, int L, int C);
void diagonal(matriz m, int L, int C);
void triang_inf(matriz m, int L, int C);
void imprimir(matriz m, int L, int C);
void liberar(matriz m, int L);

void inicializar(matriz m, int L)
{
    int i;

    for (i = 0; i < L; i++)
    {
        m[i] = NULL;
    }
}

void inserir_seq(matriz m, int val, int lin, int col)
{
    pme novo, p;

    novo = (pme)malloc(sizeof(struct no));

    if (novo == NULL)
        return;

    novo->col = col;
    novo->info = val;
    novo->prox = NULL;

    if (m[lin] == NULL)
    {
        m[lin] = novo;
    }
    else
    {
        for (p = m[lin]; p->prox != NULL; p = p->prox)
            ; // inserir no final sempre

        p->prox = novo;
    }
}

void transposta(matriz m, int L, int C)
{
    matriz mtransp;
    pme p;
    int i, j;

    mtransp = (pme)malloc(C * sizeof(struct no));

    if (mtransp == NULL)
        return;

    for (i = 0; i < L; i++)
    {
        p = m[i];
        for (j = 0; j < C; j++)
        {
            if (p != NULL)
            {
                inserir_seq(mtransp, p->info, p->col, i);
                p = p->prox;
            }
        }
    }

    imprimir(mtransp, C, L);

    simetrica(m, mtransp, L, C);
}

void simetrica(matriz m, matriz mtransp, int L, int C)
{
    pme p, q;
    int i, j;

    for (i = 0; i < L; i++)
    {
        p = m[i];
        q = mtransp[i];
        for (j = 0; j < C; j++)
        {
                if (p != NULL && q != NULL && p->col == j && q->col == j && p->info != q->info)
                {
                    printf("As matrizes nao sao simetricas!\n");
                    liberar(mtransp, L);
                    return;
                }
                else
                {
                    if(p != NULL && q != NULL)
                    {
                        p = p->prox;
                        q = q->prox;
                    }
                }
        }
    }

    printf("As matrizes sao simetricas!\n");
    liberar(mtransp, L);
}

void diagonal(matriz m, int L, int C)
{
    int i, j;
    pme p;

    for (i = 0; i < L; i++)
    {
        p = m[i];
        for (j = 0; j < C; j++)
        {
            if (i == j && p != NULL && p->col == j && p->info != 0)
                p = p->prox;
            else if (i != j && p != NULL && p->col == j && p->info != 0)
            {
                printf("i: %d | j: %d\n",i,j);
                printf("A matriz nao eh Diagonal!\n");
                return;
            }
        }
    }
    printf("A matriz eh Diagonal!\n");
}

void triang_inf(matriz m, int L, int C)
{
    int i, j;
    pme p;

    for(i = 0; i < L; i++)
    {
        p = m[i];
        for(j = 0; j < C; j++)
        {
            if(i < j && p != NULL && p->col == j) // so de ja ser diferente de NULL significa que o no ali tem valor != 0
            {
                printf("Nao eh Triangular Inferior!\n");
                return;
            }

            if(i >= j && p != NULL && p->col != j)
            {
                printf("Nao eh Triangular Inferior!\n");
                return;
            }

            if(i >= j && p != NULL && p->col == j) 
                p = p->prox;
        }
    }
    printf("Eh Triangular Inferior!\n");
}

void imprimir(matriz m, int L, int C)
{
    int i, j;
    pme p;

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
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void liberar(matriz m, int L)
{
    pme p, q;
    int i;

    for (i = 0; i < L; i++)
    {
        p = m[i];
        while (p != NULL)
        {
            q = p;
            p = p->prox;
            free(q);
        }
    }
}

int main()
{
    matriz m;
    int i, j, L, C, val, op, zerada;

    printf("Digite quantas linhas deseja na matriz: ");
    scanf("%d", &L);

    printf("Digite quantas colunas deseja na matriz: ");
    scanf("%d", &C);

    m = (pme)malloc(L * sizeof(struct no));

    if (m == NULL)
        return 0;

    do
    {
        printf("1 | Inserir uma matriz\n");
        printf("2 | Verificar se a matriz eh Simetrica\n");
        printf("3 | Verificar se a matriz eh Diagonal\n");
        printf("4 | Verificar se a matriz eh Triangular Inferior\n");
        printf("5 | Sair\n");
        printf("Selecione: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            inicializar(m, L); // inicializar toda vez que for inserir

            for (i = 0; i < L; i++)
            {
                for (j = 0; j < C; j++)
                {
                    printf("Digite o valor que deseja inserir na posicao[%d][%d]: ", i, j);
                    scanf("%d", &val);

                    if (val != 0)
                    {
                        inserir_seq(m, val, i, j);
                    }
                }
            }
            imprimir(m, L, C);
            zerada = 1;
            break;

        case 2:
            if (zerada != 0)
            {
                transposta(m, L, C);
                imprimir(m, L, C);
                liberar(m, L);
                zerada = 0;
            }
            else
            {
                printf("Insira na matriz primeiramente!\n");
            }
            break;

        case 3:
            if (zerada != 0)
            {
                diagonal(m, L, C);
                imprimir(m, L, C);
                liberar(m, L);
                zerada = 0;
            }
            else
            {
                printf("Insira na matriz primeiramente!\n");
            }
            break;

        case 4:
            if (zerada != 0)
            {
                triang_inf(m, L, C);
                imprimir(m, L, C);
                liberar(m, L);
                zerada = 0;
            }
            else
            {
                printf("Insira na matriz primeiramente!\n");
            }
            break;

        case 5:
            printf("Programa encerrado!\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (op != 5);

    liberar(m, L);

    return 0;
}