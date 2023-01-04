#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *A, int n);

void bubble_sort(int *A, int n)
{
    int i, j, aux;

    for(i = 0; i < n; i++)          // n + 1 
        for(j = 0; j < n; j++)      // n + 1
            if(A[j] > A[j + 1])     // n
            {
                aux = A[j];         // pa no pior caso
                A[j] = A[j + 1];    // pa no pior caso
                A[j + 1] = aux;     // pa no pior caso
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
    
    bubble_sort(A, n);

    for(i = 0; i < n; i++)
        printf("%d ", A[i]);

    free(A);

    return 0;
}