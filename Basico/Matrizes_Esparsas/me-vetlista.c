#include <stdio.h>
#include <stdlib.h>
#define MAX_LINHAS 50

typedef struct no *pme; // ponteiro do tipo struct no (elemento)

struct no
{
    int col, val;
    pme prox;
};

typedef pme matriz[MAX_LINHAS];

void inicializar(matriz m, int lin);
void inserir(matriz m, int i, int j, int val);
void imprimir(matriz m, int lin, int col);
void liberar(matriz m, int lin);

void inicializar(matriz m, int lin) // inicializa todas as n-linhas com valor NULL
{
    int i;
    for (i = 0; i < lin; i++)
        m[i] = NULL;
}

void inserir(matriz m, int i, int j, int val)
{
    pme novo, p;
    novo = (pme)malloc(sizeof(struct no));
    novo->val = val;
    novo->col = j;
    novo->prox = NULL;

    if (m[i] == NULL) // se linha da posicao i for vazia, iniciaremos uma lista
    {
        m[i] = novo;
    }
    else // se a linha da posicao i nao for vazia, percorreremos a lista daquela posicao ate achar NULL
    {
        for (p = m[i]; p->prox != NULL; p = p->prox);

        p->prox = novo; // tendo achado o ultimo no da lista daquela linha da matriz, iremos encadear o elemento na posicao requerida
    }
}

void imprimir(matriz m, int lin, int col)
{
    pme p;
    int i, j;

    for (i = 0; i < lin; i++) // linhas
    {             
        p = m[i]; // p na posicao i-linha
        for (j = 0; j < col; j++) // colunas
        { 
            if (p != NULL && p->col == j)
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
    matriz m; // variavel do tipo matriz[MAX_LINHAS] com tamanho maximo definido, eh o vetor que guarda todas as listas por linha
    int lin, col, i, j, val;

    do
    {
        printf("Digite a quantidade de linhas da matriz: ");
        scanf("%d", &lin);
    } while (lin < 0 && lin > MAX_LINHAS + 1);

    printf("Digite a quantidade de colunas da matriz: ");
    scanf("%d", &col);

    inicializar(m, lin); // inicializa todas as posicoes com NULL

    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("matriz[%d][%d]: ", i, j);
            scanf("%d", &val);

            if (val != 0)
                inserir(m, i, j, val);
        }
    }

    imprimir(m, lin, col);

    liberar(m, lin);

    return 0;
}