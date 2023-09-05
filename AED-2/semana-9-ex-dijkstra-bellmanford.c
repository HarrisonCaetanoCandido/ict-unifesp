/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turno: Noturno
*/
/*
    Implemente os algoritmos de Bellman-Ford e Dijkstra. Use uma lista de
    adjacencia para representar o grafo. Cada aresta deve ser inserida no final da lista de
    adjacencia de cada vertice. (Se voce fez o exercicio 8, entao voce j a implementou a lista
    de adjacencia necessaria para este exercicio.) Para o algoritmo de Dijkstra, voce deve
    implementar uma Fila de Prioridades M ́ınimas Indexavel. (Se voce fez o exercicio 7,
    entao voce j a implementou a fila de prioridades minimas. Basta adapta-la para ser
    indexavel, como visto em aula.) A constante NIL deve ser representada pelo valor
    −1, enquanto a constante INF pela constante INT MAX (limits.h). O algoritmo de
    Dijkstra so deve ser executado se o algoritmo de Bellman-Ford apontar ausencia de
    ciclo negativo no grafo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct no_vertice
{
    int d;
    int p;
    int v; // campo usado somente para implementacao da fila de prioridade minima
} Tno_vertice;
typedef Tno_vertice *Pno_vertice;

typedef struct no_ladjacencia
{
    int v;    // vamos precisar desse campo para guardar qual posicao o vertice esta nos vetores de distancia e predecessor
    int peso; // guarda o peso da aresta
    struct no_ladjacencia *prox;
} Tno_ladj;
typedef Tno_ladj *Pno_ladj;

typedef Pno_ladj *Lista_adj;

void inicializar(Lista_adj G, int N);
Pno_ladj criar_no(int peso, int v);
void criar_grafo(Lista_adj G, int peso, int u, int v);
void initialize_single_source(Pno_vertice A, int s, int N);
int bellman_ford(Lista_adj G, Pno_vertice A, int s, int N);
void relax(Pno_vertice A, int peso, int u, int v);
void dijkstra(Lista_adj G, Pno_vertice A, int s, int N);
void build_min_heap(Pno_vertice Q, Pno_vertice A, int N);
Pno_vertice extract_min_heap(Pno_vertice Q, int *M);
void min_heapify(Pno_vertice Q, int i, int N);
void extended_relax(Pno_vertice Q, Pno_vertice A, int *P, int peso, int u, int v);
int parent(int i);
void decrease_key(Pno_vertice Q, int *P, Pno_vertice A, int v);
void liberar_grafo(Lista_adj G, int N);

// ------------------------------------------------ CONSTRUCAO DO GRAFO ------------------------------------------------

// inicializa os ponteiros do vetor como nulos
void inicializar(Lista_adj G, int N)
{
    int i;

    for (i = 0; i < N; i++)
        G[i] = NULL;
}

// o grafo eh representado por uma lista de adjacencia
void criar_grafo(Lista_adj G, int peso, int u, int v)
{
    Pno_ladj p;

    if (G[u] == NULL)
    {
        G[u] = criar_no(peso, v);
    }
    else
    {
        for (p = G[u]; p->prox != NULL; p = p->prox)
            ;

        p->prox = criar_no(peso, v);
    }
}

Pno_ladj criar_no(int peso, int v)
{
    Pno_ladj p;

    p = (Pno_ladj)malloc(sizeof(Tno_ladj));
    if (p == NULL)
        return NULL;

    p->peso = peso;
    p->v = v;
    p->prox = NULL;

    return p;
}

//  --------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------- INITIALIZE SINGLE SOURCE ---------------------------------------------

void initialize_single_source(Pno_vertice A, int s, int N)
{
    int i;

    for (i = 0; i < N; i++)
    {
        A[i].d = INT_MAX; // INFINITO
        A[i].p = -1;      // NIL
        A[i].v = i;       // novamente, campo usado somente para implementacao da fila de prioridade minima
    }

    A[s].d = 0;
}

//  --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------- ALGORITMO DE BELLMAN FORD ---------------------------------------------

int bellman_ford(Lista_adj G, Pno_vertice A, int s, int N) // O(|V||E|)
{
    int i;
    Pno_ladj p;

    initialize_single_source(A, s, N);

    // simplesmente relaxamos todas as arestas do grafo |V| - 1 vezes, passando sempre em todos os nos adjacentes a u primeiro. semelhante ao BFS
    for (i = 0; i < N - 1; i++)                // O(|V|)
        for (p = G[i]; p != NULL; p = p->prox) // O(|E|)
            relax(A, p->peso, i, p->v);

    for (i = 0; i < N - 1; i++)
        for (p = G[i]; p != NULL; p = p->prox)
            if (A[i].d + p->peso < A[p->v].d)
                return 0; // FALSE

    return 1; // TRUE, se e somente se o grafo nao contem nenhum ciclo de peso negativo que seja acessivel a partir da origem
}

void relax(Pno_vertice A, int peso, int u, int v)
{
    if (A[u].d + peso < A[v].d)
    {
        A[v].d = A[u].d + peso;
        A[v].p = u;
    }
}

//  --------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------- ALGORITMO DE DIJKSTRA -----------------------------------------------

void dijkstra(Lista_adj G, Pno_vertice A, int s, int N)
{
    Pno_ladj x;
    Pno_vertice Q, u;
    int *P, i, M, k;

    Q = (Pno_vertice)malloc(N * sizeof(Tno_vertice));
    if (Q == NULL)
        return;

    P = (int *)malloc(N * sizeof(int));
    if (P == NULL)
        return;

    // faz parte do algoritmo, mas praticamente estamos reiniciando o grafo percorrido por bellman ford
    initialize_single_source(A, s, N);

    // ------------------- fila de prioridade minima indexavel -------------------

    for (i = 0; i < N; i++)
        Q[i] = A[i];

    // inserir na fila de prioridades minima usando a funcao de build-min-heap()
    build_min_heap(Q, A, N);

    // pelo que entendi salvo P para usar apenas na decrease-key
    for (i = 0; i < N; i++)
        P[Q[i].v] = i;

    M = N;
    while (M != 0)
    {
        u = extract_min_heap(Q, &M);

        // acessar todos os nos adjacentes a u por meio do grafo
        for (x = G[u->v]; x != NULL; x = x->prox)
            extended_relax(Q, A, P, x->peso, u->v, x->v);
    }
}

void build_min_heap(Pno_vertice Q, Pno_vertice A, int N) // O(log n)
{
    int i;

    for (i = (N - 2) / 2; i > -1; i--)
        min_heapify(Q, i, N);
}

Pno_vertice extract_min_heap(Pno_vertice Q, int *M) // O(log n)
{
    Pno_vertice p;

    p = (Pno_vertice)malloc(sizeof(Tno_vertice));
    if (p == NULL)
        return NULL;

    p->d = Q[0].d;
    p->p = Q[0].p;
    p->v = Q[0].v;

    Q[0] = Q[*M - 1];
    --(*M);

    min_heapify(Q, 0, *M);

    return p;
}

void min_heapify(Pno_vertice Q, int i, int N) // O(log n)
{
    int esq, dir, min, auxd, auxv;
    esq = 2 * i + 1;
    dir = 2 * i + 2;
    min = i;

    if (esq < N && Q[esq].d < Q[min].d)
        min = esq;

    if (dir < N && Q[dir].d < Q[min].d)
        min = dir;

    if (min != i)
    {
        auxv = Q[min].v;
        auxd = Q[min].d;
        Q[min].v = Q[i].v;
        Q[min].d = Q[i].d;
        Q[i].v = auxv;
        Q[i].d = auxd;
        min_heapify(Q, min, N);
    }
}

void extended_relax(Pno_vertice Q, Pno_vertice A, int *P, int peso, int u, int v)
{
    if (A[u].d + peso < A[v].d)
    {
        A[v].d = A[u].d + peso;
        A[v].p = u;
        // como a fila eh apenas uma representacao, nao preciso alterar A
        decrease_key(Q, P, A, v);
    }
}

int parent(int i)
{
    return (i - 1) / 2;
}

void decrease_key(Pno_vertice Q, int *P, Pno_vertice A, int v) // O(1)
{
    Pno_vertice aux;
    int i, j, auxp;

    // acessar P, depois Q por meio de P
    Q[P[v]].d = A[v].d;
    Q[P[v]].v = A[v].v;
    Q[P[v]].p = A[v].p;

    i = P[v];
    while (Q[parent(i)].d > Q[i].d)
    {
        // atualizar Q
        aux = &Q[parent(i)];
        Q[parent(i)] = Q[i];
        Q[i] = Q[parent(i)];

        // atualizar P
        auxp = P[Q[parent(i)].p];
        P[Q[parent(i)].p] = P[Q[i].d];
        P[Q[i].d] = auxp;

        i = parent(i);
    }
}

void liberar_grafo(Lista_adj G, int N)
{
    Pno_ladj p, q;
    int i;

    for (i = 0; i < N; i++)
    {
        p = G[i];

        while (p != NULL)
        {
            q = p;
            p = p->prox;
            free(q);
        }

        G[i] = NULL;
    }
}

//  --------------------------------------------------------------------------------------------------------------------

int main()
{
    int N, M, i, u, v, peso, s, ciclo;
    Pno_vertice A;
    Lista_adj G;

    scanf("%d %d", &N, &M);

    // nosso vetor de vertices
    A = (Pno_vertice)malloc(N * sizeof(Tno_vertice));
    if (A == NULL)
        return 0;

    // nosso grafo
    G = (Lista_adj)malloc(N * sizeof(Tno_ladj));
    if (G == NULL)
        return 0;

    // preparo dos nos para construir a representacao do grafo
    inicializar(G, N);

    /*
    Nas M linhas seguintes, as duas primeiras colunas representam arestas (u, v); ja a
    terceira coluna apresenta o peso w(u, v). Os tres valores sao inteiros separados por
    espacos.
    */
    for (i = 0; i < M; i++)
    {
        scanf("%d %d %d", &u, &v, &peso);
        criar_grafo(G, peso, u, v);
    }

    scanf("%d", &s);

    ciclo = bellman_ford(G, A, s, N);

    if (ciclo == 0)
        printf("Ha um ciclo negativo");
    else
    {
        dijkstra(G, A, s, N);

        for (i = 0; i < N; i++)
            printf("%d %d\n", A[i].d, A[i].p);
    }

    // funcao de liberar listas dos vertices
    liberar_grafo(G, N);

    free(A);
    free(G);

    return 0;
}