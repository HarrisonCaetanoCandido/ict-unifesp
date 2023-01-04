#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int heap_maximum(int *A, int n);
int heap_extract_max(int *A, int *n);
void heap_increase_key(int *A, int i, int key);
void max_heapify(int *A, int i, int n);
int parent(int i);
void heap_increase_key(int *A, int i, int key);

// Retorna o maior valor da Heap, no caso do Heap Maximo, o no raiz
int heap_maximum(int *A, int n)
{
    return A[0];
}

// Remove e retorna o elemento com a maior chave (na raiz). Complexidade O(log n)
int heap_extract_max(int *A, int *n)
{
    int max;

    // -1 indica erro aqui
    if (*n < 1)
        return -1;

    max = heap_maximum(A, *n); // A[1] no pseudocodigo

    A[0] = A[*n - 1];

    --(*n);

    max_heapify(A, 0, *n);

    return max;
}

void max_heapify(int *A, int i, int n)
{
    int left, right, max, aux;

    left = 2 * i + 1;
    right = 2 * i + 2;

    max = i;

    if (left < n && A[left] > A[max])
        max = left;

    if (right < n && A[right] > A[max])
        max = right;

    if (max != i)
    {
        aux = A[i];
        A[i] = A[max];
        A[max] = aux;
        max_heapify(A, max, n);
    }
}

/*
    Atualiza o valor da chave do elemento na posição i apenas se o novo valor de chave
    for maior do que o antigo
*/
int parent(int i)
{
    /*
    3 4 5 7 8 9
    0 1 2 3 4 5

             3            0
           /   \        /   \
          4     5 =>   1     2
         / \   /      / \   /
        7   8 9      3   4 5
    */
    return (i - 1) / 2;
}

/*
    Complexidade O(log n), pois o caminho traçado desde a posição i até o parent(i) é log n
*/
void heap_increase_key(int *A, int i, int key)
{
    int aux;

    if (A[i] > key)
        return;

    A[i] = key;

    while (i > 0 && A[parent(i)] < A[i])
    {
        aux = A[i];
        A[i] = A[parent(i)];
        A[parent(i)] = aux;
        i = parent(i);
    }
}

void heap_max_insert(int *A, int *heap_length, int key)
{
    (*heap_length)++;

    A[*heap_length] = INT_MIN; // -2147483647 - 1

    heap_increase_key(A, *heap_length, key);
}

/*
Fila de proridade máxima é uma aplicação do algorítmo heapsort para
programação de trabalhos em um computador compartilhado, ou seja, as
atividades de maior prioridade são executadas primeiro pelo uso do
Max-Heap-Extract
*/
int main()
{
    int *A, n, m, i, j, k, key;

    scanf("%d", &n);

    A = (int *)malloc(sizeof(int) * n);
    if (A == NULL)
        return 0;

    k = -1;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &key);
        heap_max_insert(A, &k, key);
    }

    m = n;
    for (i = 0; i < n; i++)
        printf("%d ", heap_extract_max(A, &m));

    free(A);

    return 0;
}