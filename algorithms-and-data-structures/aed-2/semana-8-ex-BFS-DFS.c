/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turno: Noturno
*/
/*
    Implemente os algoritmos de Busca em Largura e Busca em Profundidade. Use uma lista de adjacencia para representar o grafo->
    Cada aresta deve ser inserida no final da lista de adjacencia de cada vertice. Utilize os valores 0, 1 e 2 para
    representar as cores preto, cinza e branco, respectivamente.
    A constante NIL deve ser representada pelo valor −1, enquanto a constante INF pelo valor 1000
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int num_vert; // identificar na lista de adjacencia qual vertice eh esse
    int cor;      // representa o status da visita, pode ser 0 (preto), 1 (cinza), 2 (branco)
    int dist;     // para uso do algoritmo de BFS
    int tempo;    // para uso do algoritmo de DFS
    int pred;     // predecessor
    int d;        // tempo de descoberta de um vertice pela primeira vez
    int f;        // tempo de termino do exame da lista de adjacencia de um vertice
} Tno;
typedef Tno *Pno;

// essa struct guarda os vertices em nos, ou seja, estes nos guardam o endereco de cada vertice no vetor de struct
typedef struct no_lista_adj
{
    Pno vertice;
    struct no_lista_adj *prox;
} Tno_ladj;
typedef Tno_ladj *Pnoadj;

void inicializar(Pnoadj A, int N);
void criar_grafo(Pnoadj A, int u, int v);
Pno buscar_vertices(Pnoadj A, int v);
Pnoadj criar_no(Pnoadj A, int v);
Pnoadj inserir_fila(Pnoadj l, Pnoadj A, int v);
Pno remover_fila(Pnoadj *l);
void breadth_first_search(Pnoadj A, int s, int N);
void deapth_first_search(Pnoadj A, int N);
void deapth_first_search_visit(Pnoadj A, Pno p, int *tempo);
void liberar_lista_adj(Pnoadj A, int N);

/*
    funcao que inicializa o vetor de listas
    forcei uma abordagem um pouco diferente de como seria na matriz de adjacencia
*/
void inicializar(Pnoadj A, int N) // O(|V|)
{
    int i;
    Pno p;

    for (i = 0; i < N; i++)
    {
        p = (Pno)malloc(sizeof(Tno));
        if (p == NULL)
            return;

        p->num_vert = i;
        A[i].vertice = p;
        A[i].prox = NULL;
    }
}

// o grafo eh representado por uma lista de adjacencia
void criar_grafo(Pnoadj A, int u, int v) // O(|E|)
{
    Pnoadj padj, p;

    padj = criar_no(A, v);

    if (A[u].prox == NULL)
        A[u].prox = padj;
    else
    {
        // sempre insiro um novo vertice na lista de adjacencia no fim dela
        for (p = &A[u]; p->prox != NULL; p = p->prox)
            ;

        // vale destacar que a cor e o num_vertice nao precisa ter um valor significativo nesse caso
        p->prox = padj;
    }
}

Pno buscar_vertices(Pnoadj A, int v) // O(1)
{
    return A[v].vertice;
}

// criar_no() aqui apenas cria um no que guarda o endereco do vertice no vetor A
Pnoadj criar_no(Pnoadj A, int v) // O(1)
{
    Pnoadj padj;

    padj = (Pnoadj)malloc(sizeof(Tno_ladj));
    if (padj == NULL)
        return NULL;

    padj->vertice = buscar_vertices(A, v);
    padj->prox = NULL;

    return padj;
}

// implementacao da fila usando lista encadeada circular, a cabeca eh o ultimo no teoricamente
Pnoadj inserir_fila(Pnoadj l, Pnoadj A, int v) // O(1)
{
    Pnoadj padj;

    if (l == NULL)
    {
        padj = criar_no(A, v);
        padj->prox = padj;
        return padj;
    }

    padj = l->prox;
    l->prox = criar_no(A, v);
    l->prox->prox = padj;
    return l->prox;
}

Pno remover_fila(Pnoadj *l) // O(1)
{
    Pnoadj padj;
    Pno p;

    if (*l == NULL)
        return NULL;

    if ((*l)->prox == *l)
    {
        p = (*l)->vertice;
        free(*l);
        *l = NULL;
    }
    else
    {
        padj = (*l)->prox;
        (*l)->prox = (*l)->prox->prox;

        // perceba que ainda nao posso liberar a memoria deste no
        p = padj->vertice;

        free(padj);
    }
    return p;
}

// busca em largura iterativa
void breadth_first_search(Pnoadj A, int s, int N) // O(|V| + |E|)
{
    int i;
    Pno p, u, r;
    Pnoadj padj, q;
    q = NULL;

    /*
    Utilize os valores 0, 1 e 2 para representar as cores preto, cinza e branco,
    respectivamente. A constante NIL deve ser representada pelo valor −1,
    enquanto a constante INF pelo valor 1000
    */

    for (i = 0; i < N; i++) // O(|V|)
    {
        p = A[i].vertice;
        p->cor = 2;     // branco
        p->pred = -1;   // NIL
        p->dist = 1000; // INF
    }

    A[s].vertice->cor = 1;   // cinza
    A[s].vertice->pred = -1; // NILL
    A[s].vertice->dist = 0;
    q = inserir_fila(q, A, s);

    while (q != NULL) // O(|E|)
    {
        u = remover_fila(&q);

        for (padj = &A[u->num_vert]; padj != NULL; padj = padj->prox)
        {
            // acesso o vertice que o no guarda e faco as modificacoes nele
            if (padj->vertice->cor == 2) // se for branco
            {
                padj->vertice->cor = 1; // cinza
                padj->vertice->dist = u->dist + 1;
                padj->vertice->pred = u->num_vert;
                q = inserir_fila(q, A, padj->vertice->num_vert);
            }
        }
        u->cor = 0; // preto
    }
}

// busca em profundidade recursiva
void deapth_first_search(Pnoadj A, int N) // O(|V| + |E|)
{
    int i, tempo;
    Pno p;

    for (i = 0; i < N; i++) // O(|V|)
    {
        p = A[i].vertice;
        p->cor = 2;   // branco
        p->pred = -1; // NILL
    }

    tempo = 0;

    for (i = 0; i < N; i++) // O(|V|)
    {
        p = A[i].vertice;

        if (p->cor == 2)
            deapth_first_search_visit(A, p, &tempo); // O(|E|)
    }
}

void deapth_first_search_visit(Pnoadj A, Pno p, int *tempo) // O(|E|)
{
    Pnoadj q;
    Pno r;

    *tempo += 1;
    p->d = *tempo;
    p->cor = 1; // cinza

    // visito os nos adjacentes de u
    for (q = &A[p->num_vert]; q != NULL; q = q->prox) // O(|E|)
    {
        r = q->vertice;

        // chego no no mais proximo de u
        if (r->cor == 2)
        {
            r->pred = p->num_vert;
            deapth_first_search_visit(A, r, tempo);
        }
    }
    p->cor = 0; // preto, pois o no ja foi visitado
    *tempo += 1;
    p->f = *tempo;
}

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
    int N, M, i, u, v, s;
    Pnoadj A;

    // A primeira linha contem dois valores separados por um espaco em branco. O primeiro valor e o numero de vertices (N); ja o segundo e a quantidade de arestas (M)
    scanf("%d %d", &N, &M);

    A = (Pnoadj)malloc(N * sizeof(Tno_ladj));
    if (A == NULL)
        return 0;

    inicializar(A, N);

    // As M linhas seguintes contem arestas (u, v) nas quais pares de vertices sao separados por um espaco em branco
    for (i = 0; i < M; i++)
    {
        scanf("%d %d", &u, &v);

        // grafico eh representado por uma lista de adjacencia
        criar_grafo(A, u, v);
    }

    // A linha M+1 contem um inteiro que representa o vertice fonte usado pelo algoritmo de Busca em Largura
    scanf("%d", &s);

    breadth_first_search(A, s, N);

    /*
    A saıda contem 2N linhas e tres colunas. Nas N primeiras linhas sao referentes ao resultado da Busca em largura.
    Assim, as colunas representam os atributos "cor",
    "distancia" e "predecessor" de cada vertice, nesta ordem. Ja as N linhas seguintes,
    iniciadas na linha N+1, sao referentes ao resultado da Busca em Profundidade. Assim,
    as colunas representam os atributos "predecessor", "tempo de descoberta" e "tempo
    de termino" de cada vertice, nesta ordem
    */
    for (i = 0; i < N; i++)
        printf("%d %d %d\n", A[i].vertice->cor, A[i].vertice->dist, A[i].vertice->pred);

    deapth_first_search(A, N);

    for (i = 0; i < N; i++)
        printf("%d %d %d\n", A[i].vertice->pred, A[i].vertice->d, A[i].vertice->f);

    liberar_lista_adj(A, N);

    free(A);

    return 0;
}