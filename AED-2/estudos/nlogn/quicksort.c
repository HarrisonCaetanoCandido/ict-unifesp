#include <stdio.h>
#include <stdlib.h>

void quickSort(int *vec, int p, int r);
int partition(int *vec, int p, int r);

void quickSort(int *vec, int p, int r)
{
    int q;

    if(p < r)
    {
        q = partition(vec, p, r);
        quickSort(vec, p, q - 1);
        quickSort(vec, q + 1, r);
    }
}

int partition(int *vec, int p, int r)
{
    int i, j, x, assist;
    i = p - 1;
    x = vec[r];

    for(j = p; j < r; j++)
        if(vec[j] <= x)
        {
            i = i + 1;
            assist = vec[i];
            vec[i] = vec[j];
            vec[j] = assist;
        }
    
    assist = vec[i + 1];
    vec[i + 1] = x;
    vec[r] = assist;

    return (i + 1);
}

int main()
{
    int *vec, i, n;

    scanf("%d", &n);

    vec = (int*)malloc(n * sizeof(int));
    if(vec == NULL)
        return 0;

    for(i = 0; i < n; i++)
        scanf("%d", &vec[i]);
    
    quickSort(vec, 0, n - 1);

    for(i = 0; i < n; i++)
        printf("%d ", vec[i]);
    
    free(vec);

    return 0;
}