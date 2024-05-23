#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *a, int n)
{
    int i, j, key;

    for (j = 1; j < n; j++) // c = n
    {
        key = a[j]; // c = n - 1
        i = j - 1;  // c = n - 1

        while (i >= 0 && a[i] > key) // c = n(n + 1)/2 - 1
        {
            a[i + 1] = a[i]; // c = n(n - 1)/2
            i = i - 1;       // c = n(n - 1)/2
        }

        a[i + 1] = key; // c = n - 1
    }
}

int main()
{
    int *a, n, i;

    scanf("%d", &n);

    a = (int *)malloc(sizeof(int) * n);
    if (a == NULL)
        return 0;

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    insertion_sort(a, n);

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    free(a);

    return 0;
}