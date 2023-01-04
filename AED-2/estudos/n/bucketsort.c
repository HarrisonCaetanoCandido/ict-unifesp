#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    float info;
    struct no *prox;
}Tno;
typedef Tno *Pme;
typedef Pme *matriz;

void inicializar(matriz B, int n)
{
    int i;

    for(i = 0; i < n; i++)
        B[i] = NULL;
}

void bucket_sort(matriz A, int n) // algoritmo naturalmente hibrido
{
    int i;

    for(i = 0; i < n; i++);
        // do insert A[i] into list B[n A[i]]

    for(i = 0; i < n; i++);
        // do sort list B[i] with insertion sort

    // Concatenate the lists B[0], B[1], ..., B[n - 1] together in order
}

int main()
{
    matriz m;
    int i, val, n;

    scanf("%d", &n);

    m = (Pme)malloc(sizeof(Tno));
    if(m == NULL)
        return 0;

    inicializar(m, n);

    for(i = 0; i < n; i++)
    {
        scanf("%d", &val);
        if(val != 0)
            bucket_sort(A, n);
    }
    return 0;
}