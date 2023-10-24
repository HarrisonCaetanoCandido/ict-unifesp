#include <stdio.h>
#include <stdlib.h>

/*             INPUT:
                 2                 2                 9               9
               /   \             /   \             /   \           /   \
              9     7   =>      9     8   =>      2     8  =>     6     8
             / \   /           / \   /           / \   /         / \   /
            6   5 8           6   5 7           6   5 7         2   5 7

           | 2 | 9 | 7 | 6 | 5 | 8 |
*/

void maxHeapify(int *vec, int i, int n);
void buildMaxHeap(int *vec, int n);
int heapExtractMax(int *vec, int n);
void heapSort(int *vec, int *v, int n);

void maxHeapify(int *vec, int i, int n) // procedimento que deve ser usado de baixo pra cima no build-max-heap
{
    int left, right, max, assist;

    left = 2 * i + 1;  // 2 * i
    right = 2 * i + 2; // 2 * i + 1
    max = i;

    if (left < n && vec[left] > vec[i])
        max = left;

    if (right < n && vec[right] > vec[max])
        max = right;

    if (max != i)
    {
        assist = vec[i];
        vec[i] = vec[max];
        vec[max] = assist;
        maxHeapify(vec, max, n);
    }
}

void buildMaxHeap(int *vec, int n) // ajuda a ordenar a arvore usando o maxheapify em todos os nos internos
{
    int i;

    for (i = (n - 1) / 2; i > -1; i--)
        maxHeapify(vec, i, n);
}

/*
    A ordenacao final eh iniciada aqui, em que eh feita a troca do no raiz com a ultima folha (mais a direita).
    Em seguida eh necessario arrumar o heap (excluindo a ultima folha)
    Repetir o procedimento ate que o heap contenha somente um no
*/
int heapExtractMax(int *vec, int n) // retira o maior valor de um vetor na forma de um heap
{
    int max, last;

    if (n < 0)
        return -1; // underflow

    max = vec[0];
    last = n - 1;
    vec[0] = vec[last];
    (--n);
    maxHeapify(vec, 0, n);

    return max;
}

void heapSort(int *vec, int *v, int n)
{

    buildMaxHeap(vec, n); // corrige a arvore para a logica do heap maximo, TRANSFORMA ele para a estrutura de um Heap

    while (n > 0) // enquanto o tamanho de vec for maior que zero, vamos extraindo o maior numero do heap e guardando num novo vetor
    {
        v[n - 1] = heapExtractMax(vec, n); // entao vamos sempre extrair o maior valor do heap, rearranjar pelo max-heapify ate que todo o vetor seja percorrido
        (--n);
    }
}

int main()
{
    int n, *vec, i, *v;

    scanf("%d", &n);

    vec = (int *)malloc(n * sizeof(int));
    if (vec == NULL)
        return 0;

    v = (int *)malloc(n * sizeof(int)); // vetor saida
    if (v == NULL)
        return 0;

    for (i = 0; i < n; i++)
        scanf("%d", &vec[i]);

    heapSort(vec, v, n);

    for (i = 0; i < n; i++)
        printf("%d ", v[i]);

    free(vec);
    free(v);

    return 0;
}
/*
6
2 9 7 6 5 8
*/