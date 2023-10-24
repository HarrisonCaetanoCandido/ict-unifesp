#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *A, int n);

void insertion_sort(int *A, int n)
{
    int i, j, x;

    for(j = 1; j < n; j++) // n - 1 + 1
    {
        x = A[j];
        i = j - 1;

        while(i > -1 && A[i] > x) // 1 + 2 + ... + n - 1 = n(n + 1)/2
        {
            A[i + 1] = A[i];
            i = i - 1;
        }

        A[i + 1] = x;   
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

    insertion_sort(A, n);

    for(i = 0; i < n; i++)
        printf("%d ", A[i]);

    free(A);

    return 0;
}