/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turno: Noturno
*/
/*
    Implemente as operacoes basicas de um algoritmo de pesquisa para
    arvores do tipo AVL.

    Seu programa deve conter os seguintes procedimentos: (1) inicializacao,
    (2) pesquisa, (3) insercao, (4) remocao e (5) calcular altura do no.

    Para isso, considere:
        • Na operacao de remocao, quando necessario, de a preferencia para a promocao
        da menor chave da subarvore a direita, ou seja, o sucessor;
        • A altura de um no x em uma AVL e a mesma ja utilizada na atividade anterior,
        sobre ABB. Isto e, a distancia entre x e o seu descendente mais afastado, ou seja,
        a altura de x e o numero de passos no mais longo caminho que leva de x ate um no folha.

    Lembre-se que, cada insercao em uma arvore AVL requer que se verifique o fator de
    balanceamento e, se necessario, uma rotacao e realizada. As remocoes tambem podem
    demandar rotacoes para manter a arvore balanceada
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct SNo
{
    int item;
    int fb; // fator de balanceamento: -1, 0, +1
    int h;  // cada no vai guardar a altura de si ao no folha descendente mais afastado de si
    int he; // cada no vai guardar a altura do no descendente a esquerda
    int hd; // cada no vai guardar a altura do no descendente a direita
    struct SNo *esq, *dir;
} Tno;

typedef Tno *PArvBin;

PArvBin inicializacao();
PArvBin criar_no(int item);
PArvBin inserir(PArvBin A, int item);
int calc_altura_no(PArvBin A);
PArvBin rotacao_ll(PArvBin A);
PArvBin rotacao_lr(PArvBin A);
PArvBin rotacao_rr(PArvBin A);
PArvBin rotacao_rl(PArvBin A);
PArvBin pesquisa(PArvBin A, int item);
PArvBin remover(PArvBin A, int item);
PArvBin busca_sucessor(PArvBin A, int *aux);
PArvBin liberar(PArvBin A);

PArvBin inicializacao()
{
    return NULL;
}

PArvBin criar_no(int item)
{
    PArvBin p;

    p = (PArvBin)malloc(sizeof(Tno));
    if (p == NULL)
        return NULL;

    p->esq = p->dir = NULL;
    p->item = item;
    p->fb = 0;

    return p;
}

PArvBin inserir(PArvBin A, int item)
{
    PArvBin p;

    if (A == NULL)
        return criar_no(item);

    // vai a esquerda
    if (A->item > item)
    {
        A->esq = inserir(A->esq, item);

        calc_altura_no(A);

        if (A->fb > 1)
        {
            //  Eh entao verificado se existe um item menor do que o item a esquerda do no atual, se sim, isso indica que foi feita uma insercao a esquerda e por isso a rotacao eh LL. Caso contrario, eh feita uma verificacao seguindo a mesma logica, mas no lado direito, verificando ser RL
            if (item < A->esq->item)
                // Rotacao do tipo LL
                A = rotacao_ll(A);
            else
                // Rotacao do tipo LR
                A = rotacao_lr(A);
        }
        return A;
    }

    // vai a direita
    if (A->item < item)
    {
        A->dir = inserir(A->dir, item);

        calc_altura_no(A);

        if (A->fb < -1)
        {
            if (item > A->dir->item)
                // Rotacao do tipo RR
                A = rotacao_rr(A);
            else
                // Rotacao do tipo RL
                A = rotacao_rl(A);
        }
    }
    return A;
}

// Essa funcao alem de calcular a altura do no tambem calcula o fator de balanceamento dos nos da arvore
int calc_altura_no(PArvBin A)
{
    int esq, dir;

    if (A == NULL)
        return 0;

    esq = calc_altura_no(A->esq) + 1;
    dir = calc_altura_no(A->dir) + 1;

    A->fb = (esq - dir);

    A->he = esq - 1;
    A->hd = dir - 1;

    if (esq > dir)
    {
        A->h = esq - 1;
        return esq;
    }
    else
    {
        A->h = dir - 1;
        return dir;
    }
}

PArvBin rotacao_ll(PArvBin A)
{
    PArvBin pa, pb;

    pa = A;
    pb = pa->esq;
    pa->esq = pb->dir;
    pb->dir = pa;
    return pb;
}

PArvBin rotacao_lr(PArvBin A)
{
    PArvBin pa, pb, pc;

    pa = A;
    pb = pa->esq;
    pc = pb->dir;
    pb->dir = pc->esq;
    pc->esq = pb;
    pa->esq = pc->dir;
    pc->dir = pa;
    return pc;
}

PArvBin rotacao_rr(PArvBin A)
{
    PArvBin pa, pb;

    pa = A;
    pb = pa->dir;
    pa->dir = pb->esq;
    pb->esq = pa;
    return pb;
}

PArvBin rotacao_rl(PArvBin A)
{
    PArvBin pa, pb, pc;

    pa = A;
    pb = pa->dir;
    pc = pb->esq;
    pb->esq = pc->dir;
    pc->dir = pb;
    pa->dir = pc->esq;
    pc->esq = pa;
    return pc;
}

/*
No caso de uma pesquisa sem sucesso, ou seja, o numero nao esta na arvore,
o numero pesquisado devera ser inserido na arvore.
Se a pesquisa for bem sucedida, ou seja, o numero esta na arvore, o numero devera ser
removido.
*/
PArvBin pesquisa(PArvBin A, int item)
{
    if (A == NULL)
        return NULL;

    if (A->item > item)
        return pesquisa(A->esq, item);

    if (A->item < item)
        return pesquisa(A->dir, item);

    if (A->item == item)
        return A;
}

PArvBin remover(PArvBin A, int item)
{
    PArvBin p;
    int aux;

    if (A == NULL)
        return NULL;

    if (A->item > item)
    {
        A->esq = remover(A->esq, item);

        // faz o balanceamento da arvore a partir do no atual
        calc_altura_no(A);

        if (A->fb > 1)
        {
            if (A->esq->dir == NULL && A->esq->esq != NULL || A->esq->dir != NULL && A->esq->esq != NULL && A->esq->dir->h <= A->esq->esq->h)
                // Rotacao do tipo LL
                A = rotacao_ll(A);

            if (A->esq->dir != NULL && A->esq->esq == NULL || A->esq->dir != NULL && A->esq->esq != NULL && A->esq->dir->h > A->esq->esq->h)
                // Rotacao do tipo LR
                A = rotacao_lr(A);

            return A;
        }

        if (A->fb < -1)
        {
            if (A->dir->esq == NULL && A->dir->dir != NULL || A->dir->esq != NULL && A->dir->dir != NULL && A->dir->esq->h <= A->dir->dir->h)
                // Rotacao do tipo RR
                A = rotacao_rr(A);

            if (A->dir->esq != NULL && A->dir->dir == NULL || A->dir->esq != NULL && A->dir->dir != NULL && A->dir->esq->h > A->dir->dir->h)
                // Rotacao do tipo RL
                A = rotacao_rl(A);
        }
        return A;
    }

    if (A->item < item)
    {
        A->dir = remover(A->dir, item);

        // faz o balanceamento da arvore a partir do no atual
        calc_altura_no(A);

        if (A->fb > 1)
        {
            if (A->esq->dir == NULL && A->esq->esq != NULL || A->esq->dir != NULL && A->esq->esq != NULL && A->esq->dir->h <= A->esq->esq->h)
                // Rotacao do tipo LL
                A = rotacao_ll(A);

            if (A->esq->dir != NULL && A->esq->esq == NULL || A->esq->dir != NULL && A->esq->esq != NULL && A->esq->dir->h > A->esq->esq->h)
                // Rotacao do tipo LR
                A = rotacao_lr(A);

            return A;
        }

        if (A->fb < -1)
        {
            if (A->dir->esq == NULL && A->dir->dir != NULL || A->dir->esq != NULL && A->dir->dir != NULL && A->dir->esq->h <= A->dir->dir->h)
                // Rotacao do tipo RR
                A = rotacao_rr(A);

            if (A->dir->esq != NULL && A->dir->dir == NULL || A->dir->esq != NULL && A->dir->dir != NULL && A->dir->esq->h > A->dir->dir->h)
                // Rotacao do tipo RL
                A = rotacao_rl(A);
        }
        return A;
    }

    if (A->item == item)
    {
        if (A->esq == NULL && A->dir == NULL)
        {
            free(A);
            return NULL;
        }

        if (A->esq == NULL && A->dir != NULL)
        {
            p = A->dir;
            free(A);
            return p;
        }

        if (A->esq != NULL && A->dir == NULL)
        {
            p = A->esq;
            free(A);
            return p;
        }

        if (A->esq != NULL && A->dir != NULL)
        {
            A->dir = busca_sucessor(A->dir, &aux);

            A->item = aux;

            calc_altura_no(A);

            if (A->fb > 1)
            {
                if (A->esq->dir == NULL && A->esq->esq != NULL || A->esq->dir != NULL && A->esq->esq != NULL && A->esq->dir->h <= A->esq->esq->h)
                    // Rotacao do tipo LL
                    A = rotacao_ll(A);

                if (A->esq->dir != NULL && A->esq->esq == NULL || A->esq->dir != NULL && A->esq->esq != NULL && A->esq->dir->h > A->esq->esq->h)
                    // Rotacao do tipo LR
                    A = rotacao_lr(A);

                return A;
            }

            if (A->fb < -1)
            {

                if (A->dir->esq == NULL && A->dir->dir != NULL || A->dir->esq != NULL && A->dir->dir != NULL && A->dir->esq->h <= A->dir->dir->h)
                    // Rotacao do tipo RR
                    A = rotacao_rr(A);

                if (A->dir->esq != NULL && A->dir->dir == NULL || A->dir->esq != NULL && A->dir->dir != NULL && A->dir->esq->h > A->dir->dir->h)
                    // Rotacao do tipo RL
                    A = rotacao_rl(A);
            }
            return A;
        }
    }
}

// Busca para o caso do sucessor
PArvBin busca_sucessor(PArvBin A, int *aux)
{
    if (A == NULL)
        // Erro na busca (caso que eh praticamente impossivel de acontecer devido a forma que a funcao foi escrita)
        return NULL;

    if (A->esq == NULL)
    {
        *aux = A->item;
        free(A);
        return NULL;
    }

    A->esq = busca_sucessor(A->esq, aux);

    return A;
}

PArvBin liberar(PArvBin A)
{
    if (A != NULL)
    {
        A->esq = liberar(A->esq);
        A->dir = liberar(A->dir);
        free(A);
    }
    return NULL;
}

int main()
{
    PArvBin A, p;
    int x, h, he, hd;

    A = inicializacao();
    x = 0;

    /*
    A primeira linha da entrada consiste de uma lista de numeros inteiros positivos
    separados por espacos. Esses numeros devem ser inseridos na arvore. A sequencia
    termina com um numero inteiro negativo que nao deve ser inserido
    */
    do
    {
        scanf("%d", &x);
        if (x != -1)
            A = inserir(A, x);
    } while (x != -1);

    h = A->h;
    he = A->he;
    hd = A->hd;

    /*
    A segunda linha contem outra lista de numeros inteiros positivos separados por
    espacos. Assim como na lista da primeira linha, um numero inteiro negativo marca o
    final da lista. Cada um desses numeros, com excecao do numero negativo, deve-se ser
    usado como chave de pesquisada na arvore. No caso de uma pesquisa sem sucesso, ou
    seja, o numero nao esta na arvore, o numero pesquisado devera ser inserido na arvore.
    Se a pesquisa for bem sucedida, ou seja, o numero esta na arvore, o numero devera ser
    removido
    */

    do
    {
        scanf("%d", &x);
        if (x != -1)
        {
            p = pesquisa(A, x);
            if (p == NULL)
                A = inserir(A, x);
            else
                A = remover(A, x);
        }
    } while (x != -1);

    /*
    A terceira linha contem um unico valor inteiro positivo a ser apenas pesquisado na
    arvore. Esse numero pode ou nao estar na arvore
    */
    scanf("%d", &x);

    p = pesquisa(A, x);

    /*
    A primeira linha da saida contem a altura maxima da ABB a partir do seu no raiz
    seguida da altura da sub-arvore da esquerda e da direita do no raiz. Esses valores
    devem ser calculados considerando apenas a arvore construida com os numeros da
    primeira linha da entrada
    */
    printf("%d, %d, %d\n", h, he, hd);

    /*
    Na segunda linha, deve ser impresso o valor da altura do no pesquisado (linha 03
    dos dados de entrada), seguido pela altura da sub-arvore da esquerda e direita. Caso
    esse valor pesquisado nao seja encontrado, deve ser exibido "Valor nao encontrado"
    */
    if (p == NULL)
        printf("Valor nao encontrado");
    else
        printf("%d, %d, %d", p->h, p->he, p->hd);

    A = liberar(A);

    return 0;
}

/*
6 4 3 2 1 -1
4 5 -1
6

6 4 3 2 1 -1
4 5 -1
5

16 12 20 12 11 19 18 15 17 13 -1
14 19 15 20 -1
18

16 12 20 12 11 19 18 15 17 13 -1
14 19 15 20 -1
100
*/