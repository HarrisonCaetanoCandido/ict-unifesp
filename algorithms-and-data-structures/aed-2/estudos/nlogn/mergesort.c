#include <stdio.h>
#include <stdlib.h>
#define INFINITY 2147483647 // maior valor representavel em um inteiro (32 bits)

void mergeSort(int *vet, int p, int r);
void merge(int *vet, int p, int q, int r);

void mergeSort(int *vet, int p, int r)
{
    int q;

    if (p < r)
    {
        q = (p + r) / 2;
        mergeSort(vet, p, q);
        mergeSort(vet, q + 1, r);
        merge(vet, p, q, r);
    }
}

void merge(int *vet, int p, int q, int r)
{
    int n1, n2, *L, *R, i, j, k;

    n1 = q - p + 1;
    n2 = r - q;

    L = (int *)malloc((n1 + 1) * sizeof(int));
    if (L == NULL)
        return;

    R = (int *)malloc((n2 + 1) * sizeof(int));
    if (R == NULL)
        return;

    i = 0;
    while (i < n1)
    {
        L[i] = vet[p + i - 1]; // L[i] = vet[p + i - 1];
        //printf("L[%d] = vet[%d + %d] = %d\n", i - 1, p, i, L[i - 1]);
        (++i);
    }

    j = 0;
    while (j < n2)
    {
        R[j] = vet[q + j];
        //printf("R[%d] = vet[%d + %d] = %d\n", j - 1, q, j, R[j - 1]);
        (++j);
    }
    
    L[n1] = INFINITY;
    R[n2] = INFINITY;

    for (k = 0; k < n1; k++)
        printf("Dentro dos vetores => L[%d]: %d\n", k, L[k]);

    for(k = 0; k < n2; k++)
        printf("Dentro dos vetores => R[%d]: %d\n", k, R[k]);

    i = j = 0;
    k = p;

    while (k < r)
    {
        // passa por todo o vetor recebido
        if (L[i] <= R[j])
        {
            vet[k] = L[i];
            (++i);
        }
        else
        {
            vet[k] = R[j];
            (++j);
        }
        (++k);
    }

    free(L);
    free(R);
}

int main()
{
    int *vet, n, i;

    scanf("%d", &n);

    vet = (int *)malloc(n * sizeof(int));
    if (vet == NULL)
        return 0;

    for (i = 0; i < n; i++)
        scanf("%d", &vet[i]);

    mergeSort(vet, 0, n - 1);

    for (i = 0; i < n; i++)
        printf("%d ", vet[i]);

    free(vet);

    return 0;
}