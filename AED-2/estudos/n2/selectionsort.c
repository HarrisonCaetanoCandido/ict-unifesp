#include <stdio.h>
#include <stdlib.h>

void selection_sort(int *A, int n);

void selection_sort(int *A, int n)
{
    int i, j, min_j, aux;

    for(i = 0; i < n; i++) // n + 1
    {
        min_j = i;
        for(j = i + 1; j < n; j++) // n - 1 + 1
        {
            if(A[min_j] > A[j])
                min_j = j;          // vira uma pa eu acho, n(n+1)/2

            aux = A[min_j];
            A[min_j] = A[i];
            A[i] = aux;
        }
    }
}

int main()
{
    int *A, i, n;

    scanf("%d", &n);

    A = (int*)malloc(n * sizeof(int));
    if(A == NULL)
        return 0;

    for(i = 0; i < n; i++)
        scanf("%d", &A[i]);
    
    selection_sort(A, n);

    for(i = 0; i < n; i++)
        printf("%d ", A[i]);

    free(A);

    return 0;
}