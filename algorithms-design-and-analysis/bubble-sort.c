#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

void bubble_sort_i(int *a, int n)
{
    int i, j, alterado, temp; // c = 1

    alterado = TRUE; // c = 1

    for (i = 0; i < n - 1; i++) // c = n
    {
        if (alterado == TRUE)       // c = n - 1
            alterado = FALSE;       // c = n-1
        for (j = 0; j < n - i; j++) // c = n(n + 1)/2 - 1
            if (a[j] > a[j + 1])    // c = n(n - 1)/2
            {
                alterado = TRUE; // c = n(n - 1)/2
                temp = a[j];     // c = n(n - 1)/2
                a[j] = a[j + 1]; // c = n(n - 1)/2
                a[j + 1] = temp; // c = n(n - 1)/2
            }
        if (alterado == FALSE) // c = n - 1
            return;            // c = n - 1
    }
}

void bubble_sort_1(int *a, int n)
{
    int i, j, temp; // c = 1

    for (i = 0; i < n - 1; i++)     // c = n
        for (j = 0; j < n - 1; j++) // c = n * n
            if (a[j] > a[j + 1])    // c = n (n - 1)
            {
                temp = a[j];     // c = n (n - 1)
                a[j] = a[j + 1]; // c = n (n - 1)
                a[j + 1] = temp; // c = n (n - 1)
            }
}

int main()
{
    int n, *a, *b, i;

    scanf("%d", &n);

    a = (int *)malloc(sizeof(int) * n);
    if (a == NULL)
        return 0;

    b = (int *)malloc(sizeof(int) * n);
    if (b == NULL)
        return 0;

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for(i = 0; i < n; i++)
        b[i] = a[i];

    bubble_sort_i(a, n);

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    bubble_sort_1(b, n);

    for (i = 0; i < n; i++)
        printf("%d ", b[i]);

    free(a);
    free(b);

    return 0;
}