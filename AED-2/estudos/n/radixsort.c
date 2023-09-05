#include <stdio.h>
#include <stdlib.h>

void radixSort(int *A, int d, int n);
void countingSort(int *A, int *B, int k, int n);

void radixSort(int *A, int d, int n)
{
    int i, B[n];

    for (i = 0; i < d; i++)
    {
        // eh necessario usar um metodo de ordenacao estavel para que o array A seja ordenado no digito i
        countingSort(A, B, d, n);
    }

    for (i = 0; i < n; i++)
        printf("%d ", B[i]);
}

void countingSort(int *A, int *B, int k, int n) // metodo de ordenacao estavel, pois a ordem dos itens na entrada nao se altera apos a ordenacao da lista
{
    int i, *C;

    C = (int *)malloc(k * sizeof(int));
    if (C == NULL)
        return;

    // inicializar o vetor de contagem como zero
    for (i = 0; i < k; i++)
        C[i] = 0;

    for (i = 0; i < n; i++) // nao entendi pq no pseudocodigo ele comeca em 1
        C[A[i]] = C[A[i]] + 1;

    for (i = 0; i < k; i++)
        printf("%d", C[i]);
    printf("\n");

    for (i = 1; i < k; i++)
        C[i] = C[i] + C[i - 1]; // vai fazendo soma cumulativa com o valor que estiver atras de i

    for (i = n - 1; i > -1; i--)
    {
        printf("A[%d]: %d | C[A[%d]]: %d | B[C[A[%d]]]: %d\n", i, A[i], i, C[A[i]], i, B[C[A[i]] - 1]);
        B[C[A[i]] - 1] = A[i];
        C[A[i]] = C[A[i]] - 1;
    }
    free(C);
}
/*
    6
    5 2 3 10 0 3
    6
    50 10 13 15 1 11
*/

int main()
{
    int *vet, i, k, n, maior;

    scanf("%d", &n);

    vet = (int *)malloc(n * sizeof(int));
    if (vet == NULL)
        return 0;

    for (i = 0; i < n; i++)
        scanf("%d", &vet[i]);

    maior = vet[0];
    for (i = 1; i < n; i++)
        if (maior < vet[i])
            maior = vet[i];

    printf("maior: %d\n", maior);

    radixSort(vet, maior + 1, n);

    free(vet);

    return 0;
}