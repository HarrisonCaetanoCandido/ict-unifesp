/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turno: Noturno
*/
/*
    Para a atividade desta semana, voce deve implementar o algoritmo merge_sort para
    ordenar chaves em uma lista simplesmente ligada.
    
    De modo geral, os passos computacionais do merge_sort sao os mesmos usados para  ̃
    chaves estruturadas em um vetor:
    1) encontra-se o meio do conjunto de chaves;
    2) ordena-se a metade da esquerda;
    3) ordena-se a metade da direita; e
    4) mescla-se essas duas metades. Esses procedimentos sao aplicados recursivamente ate que todo  ́
    o conjunto esteja ordenado.
    
    No caso de listas simplesmente ligadas, no entanto, e
    necessario estrategias diferentes para encontrar o meio da lista – a partir do qual se  ́
    determina as metades da direita e da esquerda a serem ordenadas – e para mesclar
    listas previamente ordenadas.
*/
 
#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int chave;
    struct no *prox;
} Tno;
typedef Tno *Pno;
 
Pno criar_no(int chave);
Pno inserir_no(Pno l, int chave);
void merge_sort(Pno *l);
void fast_slow_strategy(Pno l, Pno *esq, Pno *dir);
Pno sorted_merge(Pno a, Pno b);
void imprimir(Pno l);
Pno liberar(Pno l);
 
Pno criar_no(int chave)
{
    Pno p;
    p = (Pno)malloc(sizeof(Tno));
    if (p == NULL)
        return NULL;
 
    p->chave = chave;
    p->prox = NULL;
 
    return p;
}
 
Pno inserir_no(Pno l, int chave)
{
    if (l == NULL)
        return criar_no(chave);
 
    l->prox = inserir_no(l->prox, chave);
 
    return l;
}
 
void merge_sort(Pno *l)
{
    Pno a, b; // NULL, 
 
    if ((*l) == NULL || (*l)->prox == NULL)
        return;
 
    // divide a lista em questao em duas sublistas a e b usando a estrategia de ponteiros Fast/Slow
    fast_slow_strategy(*l, &a, &b);
 
    merge_sort(&a); // metade esquerda
    merge_sort(&b); // metade direita
 
    *l = sorted_merge(a, b); // combina as duas listas a e b depois de ordenadas em uma lista unica
}
 
void fast_slow_strategy(Pno l, Pno *esq, Pno *dir)
{
    // fast fica dois nos a frente de slow
    Pno slow = l;
    Pno fast = l->prox; // 1 a frente de slow
 
    while (fast != NULL)
    {
        fast = fast->prox; // 2 a frente de slow
        if (fast != NULL)
        {
            slow = slow->prox;
            fast = fast->prox;
        }
    }
 
    // slow está no meio da lista e por conta disso poderemos dividi-la em duas
    *esq = l;
    *dir = slow->prox;
    slow->prox = NULL;
}
 
Pno sorted_merge(Pno a, Pno b)
{
    Pno l = NULL;
 
    if (a == NULL)
        return b;
 
    if (b == NULL)
        return a;
 
    // basicamente a ideia eh ir reapontando os nos de a e b de maneira que l fique ordenada
    if (a->chave <= b->chave)
    {
        l = a;
        l->prox = sorted_merge(a->prox, b);
    }
 
    if (a->chave > b->chave)
    {
        l = b;
        l->prox = sorted_merge(a, b->prox);
    }
 
    return l;
}
 
void imprimir(Pno l)
{
    if (l != NULL)
    {
        printf("%d ", l->chave);
        imprimir(l->prox);
    }
}
 
Pno liberar(Pno l)
{
    if (l != NULL)
    {
        l->prox = liberar(l->prox);
        free(l);
    }
    return NULL;
}
 
int main()
{
    int chave, n, i;
    Pno l = NULL;
 
    scanf("%d", &n);
 
    for (i = 0; i < n; i++)
    {
        scanf("%d", &chave);
        l = inserir_no(l, chave);
    }

    merge_sort(&l);
 
    imprimir(l);
 
    l = liberar(l);

    return 0;
}
/*
5
1 5 3 4 2
6
3 5 2 1 4 6
*/