/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turno: Noturno
*/
/*
    Um grupo de amigos resolveu criar uma brincadeira chamada "Brincando com as palavras ordenadas".
    Cada participante tem um papel no jogo. O jogo comeca com um dos
    participantes sorteando um numero inteiro positivo N que representa a quantidade
    de palavras. Depois, o segundo participante escreve as N palavras em um papel sem
    qualquer criterio, ou seja, usando letras, numeros, caracteres especiais etc. O terceiro
    especifica uma quantidade M (M < N) de palavras a serem escolhidas do conjunto
    original, e o quarto jogador seleciona M posicoes distintas no intervalo [0, N[ referente
    as palavras a serem selecionadas. Finalmente, o quinto jogador devera ter a funcao de
    ordenar um conjunto de M palavras selecionadas, usando para isso o algoritmo de
    ordenacao Heap-Sort, o qual tambem devera comprovar exibindo o heap montado a
    partir do conjunto selecionado
*/

#include <ctype.h> // biblioteca que fornece diversas rotinas de classificacao de caracteres
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados
{
    char palavra[20];
} Tdados;
typedef Tdados *Pdados;

void max_heapify(Pdados heap, int i, int n);
void build_max_heap(Pdados heap, int n);
void heap_extract_max(Pdados heap, char *max, int n);
void heap_sort(Pdados heap, int n);

void max_heapify(Pdados heap, int i, int n) // procedimento que deve ser usado de baixo pra cima pelo build-max-heap
{
    int left, right, max;
    char aux[20];

    left = 2 * i + 1;  // 2 * i
    right = 2 * i + 2; // 2 * i + 1
    max = i;

    /*
    strcmp:
        if Return value < 0 then it indicates str1 is less than str2.
        if Return value > 0 then it indicates str2 is less than str1.
        if Return value = 0 then it indicates str1 is equal to str2.
    */

    if (left < n && strcmp(heap[left].palavra, heap[i].palavra) > 0)
        max = left;

    if (right < n && strcmp(heap[right].palavra, heap[max].palavra) > 0)
        max = right;

    if (max != i)
    {
        strcpy(aux, heap[i].palavra);
        strcpy(heap[i].palavra, heap[max].palavra);
        strcpy(heap[max].palavra, aux);
        max_heapify(heap, max, n);
    }
}

void build_max_heap(Pdados heap, int n) // ajuda a ordenar a arvore usando o max_heapify em todos os nos internos
{
    int i;

    for (i = (n - 2) / 2; i > -1; i--)
        max_heapify(heap, i, n);

    printf("build_heap: ");
    for (i = 0; i < n; i++)
    {
        printf("%s", heap[i].palavra);
        if (i != n - 1)
            printf(" ");
    }
    printf("\n");
}

/*
    A ordenacao final eh iniciada aqui, em que eh feita a troca do no raiz com a ultima folha (mais a direita).
    Em seguida eh necessario arrumar o heap (excluindo a ultima folha)
    Repetir o procedimento ate que o heap contenha somente um no
*/
void heap_extract_max(Pdados heap, char *max, int n) // retira o maior valor de um vetor na forma de um heap
{
    int last;

    if (n < 0)
        return;

    strcpy(max, heap[0].palavra);
    last = n - 1;
    strcpy(heap[0].palavra, heap[last].palavra);
    (--n);
    max_heapify(heap, 0, n);
}

void heap_sort(Pdados heap, int n)
{
    char max[20];

    build_max_heap(heap, n); // corrige a arvore para a logica do heap maximo, TRANSFORMA ele para a estrutura de um Heap

    while (n > 0) // enquanto o tamanho de heap for maior que zero, vamos extraindo o maior numero do heap e guardando num novo vetor
    {
        heap_extract_max(heap, max, n);
        strcpy(heap[n - 1].palavra, max); // entao vamos sempre extrair o maior valor do heap, rearranjar pelo max-heapify ate que todo o vetor seja percorrido
        (--n);
    }
}

int main()
{
    int n, i, j, x, indice;
    Pdados vet, heap;

    // O jogo comeca com um dos participantes sorteando um numero inteiro positivo N que representa a quantidade de palavras
    scanf("%d", &n);

    // vetor entrada
    vet = (Pdados)malloc(n * sizeof(Tdados));
    if (vet == NULL)
        return 0;

    for (i = 0; i < n; i++)
        scanf("%s", vet[i].palavra);

    scanf("%d", &x); // O terceiro jogador informa a quantidade de palavras para formar o conjunto resultante

    // vetor utilizado pelo algoritmo
    heap = (Pdados)malloc(x * sizeof(Tdados)); // Importante notar que apenas o novo conjunto (vetor) com as palavras selecionadas deve ser ordenado
    if (heap == NULL)
        return 0;

    i = 0;
    do
    {
        scanf("%d", &indice);
        strcpy(heap[i].palavra, vet[indice].palavra);
        (++i);
    } while (i < x);

    for (i = 0; i < n; i++)
        for (j = 0; vet[i].palavra[j] != '\0'; j++)
            if (vet[i].palavra[j] < 'a' || vet[i].palavra[j] > 'z')
            {
                printf("a palavra %s eh invalida", vet[i].palavra);
                free(vet);
                free(heap);

                return 0;
            }

    heap_sort(heap, x);

    // Importante lembrar que a ultima palavra nao deve ter um espaco apos a mesma
    printf("palavras: ");
    for (i = 0; i < x; i++)
    {
        printf("%s", heap[i].palavra);
        if (i != x - 1)
            printf(" ");
    }

    free(vet);
    free(heap);

    return 0;
}
/*
7
programar vamos palavra eh futebol computador legal
3
0 3 6

6
banana tomate amora laranja limao jabuticaba
3
1 2 5

5
todos estes que aí estao
2
0 1

8
banana tomate amora laranja ameixa limao jabuticaba jade
8
0 2 1 3 4 7 6 5
*/