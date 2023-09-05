/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turno: Noturno
*/
/*
    E N T R A D A:
    A primeira linha contem a quantidade N de elementos a serem inseridos na fila de
    prioridade.
    As N linhas seguintes contem pares (chave, id) que indicam elementos a serem inseridos na fila de prioridade.
    A linha N + 1 contem a quantidade M de elementos que terao suas prioridades
    alteradas.

    As M linhas seguintes contem pares (ındice, chave) que indicam quais elementos
    devem ter suas prioridades alteradas. ındice indica o ındice do elemento na heap que
    deve ter a chave atualizada (desde que o novo valor da chave seja menor que o valor
    da atual).
    A linha M + 1 contem a quantidade K ≤ N de remocoes que devem ser feitas.

    S A I D A:
    A primeira linha apresenta a heap apos a insercao de cada um dos N elementos.
    Apenas os ids devem ser apresentados.
    A segunda pinha apresenta a heap apos a alteracao de prioridades. Apenas os ids
    devem ser apresentados.
    A terceira linha apresenta a heap apos as K remocoes. Apenas os ids devem ser
    apresentados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct no
{
    int chave;
    int id;
} Tno;
typedef Tno *Pno;

void heap_insert_min(Pno A, int *j, Tno key);
int parent(int j);
void heap_decrease_key(Pno A, int j, Tno key);
void heap_extract_min(Pno A, int *n);
void min_heapify(Pno A, int i, int n);

void heap_insert_min(Pno A, int *j, Tno key)
{
    ++(*j);
    A[*j].chave = INT_MAX;
    A[*j].id = *j;
    heap_decrease_key(A, *j, key); // O(log n)
}

int parent(int j)
{
    return (j - 1) / 2;
}

void heap_decrease_key(Pno A, int j, Tno key)
{
    int caux, iaux;

    if (A[j].chave < key.chave) // T(1)
        return;

    // Para evitar problemas na alteracao de prioridade dos elementos, o id nao deve ser alterado nesta funcao
    A[j].chave = key.chave;

    while (j > 0 && A[parent(j)].chave > A[j].chave) // T(n/2)
    {
        caux = A[parent(j)].chave;
        iaux = A[parent(j)].id;
        A[parent(j)].chave = A[j].chave;
        A[parent(j)].id = A[j].id;
        A[j].chave = caux;
        A[j].id = iaux;
        j = parent(j);
    }
}

void heap_extract_min(Pno A, int *n)
{
    if (*n == 0)
        return;

    A[0] = A[*n - 1];
    --(*n);

    min_heapify(A, 0, *n); // O(log n)
}

void min_heapify(Pno A, int i, int n)
{
    int esq, dir, min;
    Tno aux;

    esq = 2 * i + 1;
    dir = 2 * i + 2;
    min = i;

    if (esq < n && A[esq].chave < A[min].chave)
        min = esq;

    if (dir < n && A[dir].chave < A[min].chave)
        min = dir;

    if (min != i)
    {
        aux = A[min];
        A[min] = A[i];
        A[i] = aux;
        min_heapify(A, min, n);
    }
}

int main()
{
    int n, i, j, m, k, id, nt;
    Pno heap_a, heap_b, heap_c;
    Tno key;

    // A primeira linha contem a quantidade N de elementos a serem inseridos na fila de prioridade
    scanf("%d", &n);

    // nt guarda o valor de n antes da chamada da heap_extract_min, que reduz o valor da variavel a cada chamada. seu uso se dara na impressao das heaps b e c
    nt = n;
  
    heap_a = (Pno)malloc(n * sizeof(Tno));
    if (heap_a == NULL) 
        return 0;

    heap_b = (Pno)malloc(n * sizeof(Tno));
    if (heap_b == NULL) 
        return 0;

    heap_c = (Pno)malloc(n * sizeof(Tno));
    if (heap_c == NULL) 
        return 0;

    // As N linhas seguintes contem pares (chave, id) que indicam elementos a serem inseridos na fila de prioridade
    j = -1;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &key.chave);
        scanf("%d", &key.id);
        heap_insert_min(heap_a, &j, key);
    }

    // Salvo os valores da primeira operação na heap no primeiro vetor de saida
    for (i = 0; i < n; i++)
        heap_b[i] = heap_a[i];   

    // A linha N + 1 contem a quantidade M de elementos que terao suas prioridades alteradas
    scanf("%d", &m);

    /*
    As M linhas seguintes contem pares (chave, indice) que indicam quais elementos
    devem ter suas prioridades alteradas. Indice indica o ındice do elemento na heap que
    deve ter a chave atualizada (desde que o novo valor da chave seja menor que o valor
    da atual)
    */
    for (i = 0; i < m; i++)
    {
        scanf("%d", &key.chave);
        scanf("%d", &key.id);
        heap_decrease_key(heap_a, key.id, key);
    }

    // Salvo os valores da segunda operação na heap no segundo vetor de saida
    for (i = 0; i < n; i++)
        heap_c[i] = heap_a[i];  

    // A linha M + 1 contem a quantidade K <= N de remocoes que devem ser feitas
    scanf("%d", &k);

    for (i = 0; i < k; i++)
        heap_extract_min(heap_a, &n);

    // A primeira linha apresenta a heap apos a insercao de cada um dos N elementos. Apenas os ids devem ser apresentados
    for (i = 0; i < nt; i++)
    {
        printf("%d", heap_b[i].id);
        if(i != nt - 1)
            printf(" ");
    }
    printf("\n");

    // A segunda linha apresenta a heap apos a alteracao de prioridades. Apenas os ids devem ser apresentados.
    for (i = 0; i < nt; i++)
    {
        printf("%d", heap_c[i].id);
        if(i != nt - 1)
            printf(" ");
    }
    printf("\n");
  
    // A terceira linha apresenta a heap apos as K remocoes. Apenas os ids devem ser apresentados.
    for (i = 0; i < n; i++)
    {
        printf("%d", heap_a[i].id);
        if(i != n - 1)
            printf(" ");
    }

    free(heap_a);
    free(heap_b);
    free(heap_c);

    return 0;
}