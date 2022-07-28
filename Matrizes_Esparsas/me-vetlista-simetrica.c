/*
Faça uma função que verifique se uma matriz esparsa é simétrica.
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_LINHAS 50

typedef struct no *pme;

struct no
{
    int col, val;
    pme prox;
};

typedef pme matriz[MAX_LINHAS]; // matriz[tamanho_n] (ponteiro do tipo struct no renomeado como pme)
                                // m (variavel do tipo matriz[tamanho_n])

void inicializar(matriz m, int lin);
void inserir(matriz m, int i, int j, int val);
void imprimir(matriz m, int lin, int col);
void transposta(matriz m, matriz mtransp, int lin, int col);
void simetrica(matriz me, matriz metransp, int lin, int col);
void liberar(matriz m, int lin);

void inicializar(matriz m, int lin)
{
    int i;

    for (i = 0; i < lin; i++)
    {
        m[i] = NULL;
    }
}

void inserir(matriz m, int i, int j, int val)
{
    pme novo, p;
    novo = (pme)malloc(sizeof(struct no));
    novo->col = j;
    novo->val = val;
    novo->prox = NULL;

    if (m[i] == NULL)
    {
        m[i] = novo;
    }
    else
    {
        for (p = m[i]; p->prox != NULL; p = p->prox)
            ;

        p->prox = novo;
    }
}

void imprimir(matriz m, int lin, int col)
{
    int i, j;
    pme p;

    for (i = 0; i < lin; i++) // linhas
    {
        p = m[i]; // p == linha
        for (j = 0; j < col; j++)
        {
            if (p != NULL && p->col == j) // colunas
            {
                printf("%d ", p->val);
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

void transposta(matriz me, matriz metransp, int lin, int col)
{
    pme p;
    int i, j;

    if (col > MAX_LINHAS) // como vamos inverter o numero de linhas com o numero de colunas,
                          // col nao pode ser maior do que MAX_LINHAS, ja que col tera o numero de linhas
                          // da matriz transposta
    {
        printf("Estouro de memoria!");
        return;
    }

    inicializar(metransp, col); // inicializa a matriz

    for (i = 0; i < lin; i++)
    {
        for (p = me[i]; p != NULL; p = p->prox) // pega os elementos nao nulos da matriz original e insere na transposta
        {
            inserir(metransp, p->col, i, p->val);
        }
    }
}

void simetrica(matriz me, matriz metransp, int lin, int col)
{
    pme p, q;
    int i,j;

    if(lin != col){
        printf("A Matriz nao eh simetrica!\n");
        return ;
    }

    for(i = 0; i < lin; i++)
    {
        p = me[i];
        q = metransp[i];
        for (j = 0; j < col; j++)
        {
            if (p != NULL && q != NULL && p->col == j && q->col == j) // colunas
            {
                if(p->val != q->val)
                {
                    printf("A Matriz nao eh simetrica!\n");
                    return ;
                }
            }
        }
    }

    printf("Matriz eh simetrica!\n");
}

void liberar(matriz m, int lin)
{
    pme p, q;
    int i;

    for (i = 0; i < lin; i++)
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
    matriz me, metransp;
    int lin, col, val, i, j;

    do
    {
        printf("Digite a quantidade de linhas da matriz: ");
        scanf("%d", &lin);
    } while (lin < 0 && lin > MAX_LINHAS);

    printf("Digite a quantidade de colunas da matriz: ");
    scanf("%d", &col);

    inicializar(me,lin);

    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("matriz[%d][%d]: ", i, j);
            scanf("%d", &val);

            if (val != 0)
            {
                inserir(me, i, j, val);
            }
        }
    }

    printf("Matriz Esparsa Original:\n");
    imprimir(me, lin, col);

    printf("Matriz Esparsa Transposta:\n");
    transposta(me, metransp, lin, col);
    imprimir(metransp, col, lin);

    simetrica(me, metransp, lin, col);

    liberar(me, lin);
    liberar(metransp, col);

    return 0;
}