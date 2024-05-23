#include <stdio.h>
#include <stdlib.h>

void selection_sort(int *a, int n)
{
    int i, j, min, temp; // c = 1

    for (i = 0; i < n - 1; i++) // c = n
    {
        min = i;                    // c = n - 1
        for (j = i + 1; j < n; j++) // c = n(n + 1)/2 -1
            if (a[j] < a[min])      // c = n(n-1)/2
                min = j;            // c = n(n - 1)/2

        temp = a[min]; // c = n-1
        a[min] = a[i]; // c = n-1
        a[i] = temp;   // c = n-1
    }
}

int main()
{
    int n, *a, i;

    scanf("%d", &n);

    a = (int *)malloc(sizeof(int) * n);
    if (a == NULL)
        return 0;

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    selection_sort(a, n);

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    free(a);

    return 0;
}