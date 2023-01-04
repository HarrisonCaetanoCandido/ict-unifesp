#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct no
{
    int d;        // distancia estimada do vertice s ao t
    int p;        // predecessor do no em questao ao / predecessor de v no caminho do vertice fonte s a v
    int num_vert; // vamos precisar desse campo para guardar qual posicao o vertice esta no vetor
} Tno;
typedef Tno *Pno;

// essa struct guarda os vertices em nos, ou seja, estes nos guardam o endereco de cada vertice no vetor de struct
typedef struct no_lista_adj
{
    Pno vertice;
    int peso; // guarda o peso da aresta
    struct no_lista_adj *prox;
} Tno_ladj;
typedef Tno_ladj *Pnoadj;

void inicializar(Pnoadj A, int N);
Pnoadj criar_no(Pnoadj A, int peso, int v);
Pno buscar_vertice(Pnoadj A, int v);
void criar_grafo(Pnoadj A, int peso, int u, int v);
void initialize_single_source(Pnoadj A, int s, int N);
void relax(Pnoadj A, int peso, int u, int v);
int bellman_ford(Pnoadj A, int s, int N);
void liberar_lista_adj(Pnoadj A, int N);

/*
    funcao que inicializa o vetor de listas
    forcei uma abordagem um pouco diferente de como seria na matriz de adjacencia
*/
void inicializar(Pnoadj A, int N)
{
    int i;
    Pno p;

    for (i = 0; i < N; i++)
    {
        p = (Pno)malloc(sizeof(Tno));
        if (p == NULL)
            return;

        A[i].vertice = p;
        A[i].vertice->num_vert = i;
        A[i].peso = 0;
        A[i].prox = NULL;
    }
}

// criar_no() aqui apenas cria um no que guarda o endereco do vertice no vetor A
Pnoadj criar_no(Pnoadj A, int peso, int v)
{
    Pnoadj p;
    p = (Pnoadj)malloc(sizeof(Tno_ladj));
    if (p == NULL)
        return NULL;

    p->vertice = buscar_vertice(A, v);
    p->peso = peso;
    p->prox = NULL;

    return p;
}

Pno buscar_vertice(Pnoadj A, int v)
{
    return A[v].vertice;
}

// o grafo eh representado por uma lista de adjacencia
void criar_grafo(Pnoadj A, int peso, int u, int v)
{
    Pnoadj p;

    if (A[u].prox == NULL)
        A[u].prox = criar_no(A, peso, v);
    else
    {
        for (p = &A[u]; p->prox != NULL; p = p->prox)
            ;

        p->prox = criar_no(A, peso, v);
    }
}

void initialize_single_source(Pnoadj A, int s, int N)
{
    int i;

    for (i = 0; i < N; i++)
    {
        A[i].vertice->d = INT_MAX; // INF
        A[i].vertice->p = -1;      // NIL
    }

    A[s].vertice->d = 0; // distancia estimada do no fonte eh zero
}

/*
    o relaxamento de arestas consistem em testar se podemos melhorar o caminho minimo ate v
    passando por u e;
    em caso positivo, atualizar v.d e v.p
*/
void relax(Pnoadj A, int peso, int u, int v)
{
    if (A[u].vertice->d + peso < A[v].vertice->d) // teste para melhorar o caminho minimo
    {
        A[v].vertice->d = A[u].vertice->d + peso; // atualiza a estimativa de distancia de v
        A[v].vertice->p = u;                      // atualiza o predecessor de v
    }
}

int bellman_ford(Pnoadj A, int s, int N) // O(|V|*|E|)
{
    int i, u, v;
    Pnoadj p;

    initialize_single_source(A, s, N); // O(|V|)

    for (i = 0; i < N - 1; i++) // relaxa todas as arestas |V| - 1 vezes
    {
        // LEMBRAR DE VERIFICAR SE A COMPLEXIDADE DO ALGORITMO EH ALTERADA AQUI
        for (u = 0; u < N; u++)
        {
            p = A[u].prox;
            while (p != NULL)
            {
                v = p->vertice->num_vert;
                relax(A, p->peso, u, v);
                p = p->prox;
            }
        }
    } // O(|V|*|E|)

    /*
    o algoritmo de bellmanford nao funciona em grafos que contenham ciclos com peso total negativo (ciclo negativo),
    pois apos as |V| - 1 operacoes de relaxamento nao ha possibilidade de melhora de caminho, caso aparente acontecer,
    esse caminho melhorado resultara em um ciclo negativo, que inclusive pode nao ser o unico, ou seja, nessa situacao
    eh possivel existirem infinitos caminhos melhorados, logo precisaremos detectar ciclos negativos
    */

    // LEMBRAR DE VERIFICAR SE A COMPLEXIDADE DO ALGORITMO EH ALTERADA AQUI
    for (u = 0; u < N; u++) // detectar se ha ciclo com peso negativo em G
    {
        p = A[u].prox;
        while (p != NULL)
        {
            v = p->vertice->num_vert;

            if (A[u].vertice->d + p->peso < A[v].vertice->d)
                return 0; // FALSE

            p = p->prox;
        }
    }         // O(|E|)
    return 1; // TRUE
}

// liberar
void liberar_lista_adj(Pnoadj A, int N)
{
    int i;
    Pnoadj p, q;

    for (i = 0; i < N; i++)
    {
        p = A[i].prox;

        while (p != NULL)
        {
            q = p;
            p = p->prox;
            free(q);
        }
        A[i].prox = NULL;
    }
}

int main()
{
    int N, M, i, u, v, peso, s, ciclo;
    Pnoadj A;

    scanf("%d %d", &N, &M);

    A = (Pnoadj)malloc(N * sizeof(Tno_ladj));
    if (A == NULL)
        return 0;

    // preparo dos nos para construir a representacao do grafo
    inicializar(A, N);

    /*
    Nas M linhas seguintes, as duas primeiras colunas representam arestas (u, v); ja a
    terceira coluna apresenta o peso w(u, v). Os tres valores sao inteiros separados por
    espacos.
    */
    for (i = 0; i < M; i++)
    {
        scanf("%d %d %d", &u, &v, &peso);
        criar_grafo(A, peso, u, v);
    }

    scanf("%d", &s);

    ciclo = bellman_ford(A, s, N);

    if (ciclo == 0)
        printf("Ha um ciclo negativo");
    else
        for (i = 0; i < N; i++)
            printf("%d %d\n", A[i].vertice->d, A[i].vertice->p);

    // funcao de liberar listas dos vertices
    liberar_lista_adj(A, N);

    free(A);

    return 0;
}