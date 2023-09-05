/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turno: Noturno
*/
/*
    Implemente as operacoes basicas (1) pesquisa, (2) insercao e (3) remocao
    para uma Tabela Hash. Escreva procedimentos separados para cada operacao.
    Alem disso, utilize o metodo da divisao como funcao de hash e a estrategia de
    encadeamento para tratar colisoes.
    Se necessario, na operacao de insercao, coloque o
    novo item apos todos os itens demais, ou seja, no final.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct T
{
    int x; // chave
    struct T *prox;
} Tno_T;
typedef Tno_T *Pno_T;
typedef Pno_T *Matriz;

// tabela representada por uma matriz esparsa ou densa
void inicializar_tabela(Matriz T, int N);
Pno_T criar_no(int x);
int hash(int k, int N);
void inserir(Matriz T, int x, int N);
int buscar(Matriz T, int x, int N);
void remover(Matriz T, Pno_T ant, Pno_T p, int k);
void exibir_linha(Matriz T, int k);
void liberar_tabela(Matriz T, int N);

void inicializar_tabela(Matriz T, int N)
{
    int i;

    for (i = 0; i < N; i++)
        T[i] = NULL;
}

Pno_T criar_no(int x)
{
    Pno_T p;

    p = (Pno_T)malloc(sizeof(Tno_T));
    if (p == NULL)
        return NULL;

    p->x = x;
    p->prox = NULL;

    return p;
}

// utilize o metodo da divisao como funcao de hash
int hash(int k, int N)
{
    // h(k) = k mod m, em que k eh a chave e m o numero de posicoes da tabela hash
    return (k % N);
}

// inserir elemento x no conjunto T
void inserir(Matriz T, int x, int N)
{
    int k;
    Pno_T p;

    k = hash(x, N);

    if (T[k] == NULL)
        T[k] = criar_no(x);
    else
    {
        for (p = T[k]; p->prox != NULL; p = p->prox)
            ;

        p->prox = criar_no(x);
    }
}

// retornar elemento x no conjunto T, quando x pertencer ao conjunto T
int buscar(Matriz T, int x, int N)
{
    Pno_T p, ant;
    int k;

    k = hash(x, N);

    ant = NULL;
    for (p = T[k]; p != NULL && p->x != x; p = p->prox)
        ant = p;

    // retorna -1 se nao encontrou e k se encontrou
    if (p == NULL)
        return -1;

    // remover elemento x do conjunto T
    remover(T, ant, p, k);

    return k;
}

void remover(Matriz T, Pno_T ant, Pno_T p, int k)
{
    if (ant == NULL)
        // valor encontrado no inicio da lista
        T[k] = p->prox;
    else
        // valor encontrado no meio/ fim da lista
        ant->prox = p->prox;

    free(p);
}

void exibir_linha(Matriz T, int k)
{
    Pno_T p;

    for (p = T[k]; p != NULL; p = p->prox)
        printf(" %d", p->x);
}

void liberar_tabela(Matriz T, int N)
{
    Pno_T p, aux;
    int i;

    for (i = 0; i < N; i++)
    {
        p = T[i];
        while (p != NULL)
        {
            aux = p;
            p = p->prox;
            free(aux);
        }
    }
}

int main()
{
    int N, i, x, k;
    Matriz T;

    // A primeira linha contem um unico numero inteiro positivo indicando o tamanho da tabela de Hash a ser utilizada
    scanf("%d", &N);

    T = (Matriz)malloc(N * sizeof(Tno_T));
    if (T == NULL)
        return 0;

    inicializar_tabela(T, N);

    /*
    A segunda linha contem uma lista de numeros inteiros nao negativos, separados por espacos, que devem ser inseridos na tabela Hash.
    O final dessa lista e marcado pela presenca do valor -1, que nao deve ser inserido
    */
    do
    {
        scanf("%d", &x);
        if (x != -1)
            inserir(T, x, N);
    } while (x != -1);

    /*
    A terceira linha contem um numero inteiro a ser utilizado como chave de pesquisa na tabela.
    No caso de uma pesquisa com sucesso, ou seja, o valor esta na tabela, tal valor devera ser removido da tabela.
    Caso contrario, ou seja, o valor nao esta na tabela, apresente "Valor nao encontrado"
    */
    scanf("%d", &x);
    // i pode ser a linha k ou zero (significa que nao encontrou a chave na tabela)
    i = buscar(T, x, N);

    // A quarta linha contem um numero inteiro positivo que indica a linha da tabela Hash a ser exibida na saida
    scanf("%d", &x);

    if (i == -1)
        printf("Valor nao encontrado\n");

    printf("[%d]", x);
    exibir_linha(T, x);

    liberar_tabela(T, N);
    free(T);

    return 0;
}
/*
7
3 4 9 2 5 1 8 1 2 -1
1
1

10
3 4 9 2 11 8 2 0 9 12 13 5 1 8 2 -1
12
2

6
3 2 1 5 1 8 4 1 6 2 -1
2
2

7
3 4 9 2 5 1 8 1 2 -1
10
6
*/