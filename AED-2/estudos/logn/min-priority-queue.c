#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void heap_insert_min(int *A, int *i, int key);
int parent(int i);
void heap_decrease_key(int *A, int i, int key);
int heap_minimum(int *A);
int heap_extract_min(int *A, int *n);
void min_heapify(int *A, int i, int n);

void heap_insert_min(int *A, int *i, int key)
{
    ++(*i);
    A[*i] = INT_MAX;
    heap_decrease_key(A, *i, key);
}

int parent(int i)
{
    return (i - 1) / 2;
}

void heap_decrease_key(int *A, int i, int key)
{
    int aux;

    if (A[i] < key)
        return;

    A[i] = key;

    while (i > 0 && A[parent(i)] > A[i])
    {
        aux = A[parent(i)];
        A[parent(i)] = A[i];
        A[i] = aux;
        i = parent(i);
    }
}

int heap_minimum(int *A)
{
    return A[0];
}

int heap_extract_min(int *A, int *n)
{
    int min;

    if (*n < 1)
        return -1;

    min = heap_minimum(A);

    A[0] = A[*n - 1];
    --(*n);

    min_heapify(A, 0, *n);

    return min;
}

void min_heapify(int *A, int i, int n)
{
    int left, right, min, aux;
    left = 2 * i + 1;
    right = 2 * i + 2;
    min = i;

    if (left < n && A[left] < A[min])
        min = left;

    if (right < n && A[right] < A[min])
        min = right;

    if (min != i)
    {
        aux = A[i];
        A[i] = A[min];
        A[min] = aux;
        min_heapify(A, min, n);
    }
}

int main()
{
    int *A, n, i, x, m;

    scanf("%d", &n);

    A = (int *)malloc(n * sizeof(int));
    if (A == NULL)
        return 0;

    i = -1;
    while (i < n - 1)
    {
        scanf("%d", &x);
        heap_insert_min(A, &i, x);
    }

    scanf("%d", &m);

    i = 0;
    while (i < m)
    {
        printf("heap min extracted: %d\n", heap_extract_min(A, &n));
        ++i;
    }

    i = 0;
    while (i < n)
    {
        printf("%d ", A[i]);
        ++i;
    }

    free(A);

    return 0;
}