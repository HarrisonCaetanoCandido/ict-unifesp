#include <stdio.h>
#include <stdlib.h>

int iterativeBinarySearch(int *vec, int x, int n);
int recursiveBinarySearch(int *vec, int start, int end, int x);

int iterativeBinarySearch(int *vec, int x, int n)
{
    int start, end, med;
    start = 0;
    end = n - 1;

    while (start <= end)
    {
        med = (start + end) / 2;

        if (x > vec[med])
            start = med + 1;

        if (x < vec[med])
            end = med - 1;

        if (x == vec[med])
            return med;
    }
    return -1; // x wasnt found
}

int recursiveBinarySearch(int *vec, int start, int end, int x)
{
    int med;

    if(start <= end)
    {
        med = (start + end) / 2;

        if(x > vec[med])
            return recursiveBinarySearch(vec, med + 1, end, x);

        if(x < vec[med])
            return recursiveBinarySearch(vec, start, med - 1, x);
        
        if(x == vec[med])
            return med;
    }
    return -1; // x wasnt found
}

int main()
{
    int *vec, n, i, x;

    scanf("%d", &n);

    scanf("%d", &x);

    vec = (int*)malloc(n * sizeof(int));
    if (vec == NULL)
        return 0;

    for (i = 0; i < n; i++)
        scanf("%d", &vec[i]); // insert sorted vector

    i = iterativeBinarySearch(vec, x, n);

    (i == -1) ? printf("Value %d was not found by iterative function!\n", x) : printf("%d ", vec[i]);

    i = recursiveBinarySearch(vec, 0, n - 1, x);

    (i == -1) ? printf("Value %d was not found by recursive function!\n", x) : printf("%d ", vec[i]);

    free(vec);

    return 0;
}