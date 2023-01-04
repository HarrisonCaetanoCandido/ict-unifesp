/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turno: Noturno
*/
/*
Implemente as operacoes basicas insercao e pesquisa para manipulacao
de dados em arvores B. Cada procedimento deve ser implementado separadamente.
*/

#include <stdio.h>
#include <stdlib.h>
#define M 2
#define MM (2 * M)

typedef struct SNo
{
    int item[MM];               // posicoes da pagina em questao
    struct SNo *pagina[MM + 1]; // vetor de ponteiros para as 2m + 1 paginas descendentes
    int n;                      // conta a quantidade de itens na pagina em questao
    struct SNo *pai;            // guarda o no pai do no atual
} Tno;

typedef Tno *PArvoreB;

// essa struct serve para quando for necessario fazer operacoes no pai do pai do no folha, seja ele NULL ou nao
typedef struct VerificaNoPai
{
    int indice;        // preciso do indice pra saber onde inserir o valor em questao, na metade esquerda ou direita do pai
    int valor;         // valor pode ser o maior da esquerda ou o menor da direita
    PArvoreB esq, dir; // vetor da metade esquerda e direita respectivamente
} TVerif;

typedef TVerif *PVerificaPai;

PArvoreB criar_no(int item_a, int item_b, int item_c, int item_d);
int binary_search(int *item, int x, int n);
PArvoreB inserir(PArvoreB A, PVerificaPai verif, int x);
PArvoreB pesquisar(PArvoreB A, int x);
PArvoreB liberar(PArvoreB A);

PArvoreB criar_no(int item_a, int item_b, int item_c, int item_d)
{
    PArvoreB p;

    p = (PArvoreB)malloc(sizeof(Tno));
    if (p == NULL)
        return NULL;

    p->item[0] = item_a;
    p->item[1] = item_b;
    p->item[2] = item_c;
    p->item[3] = item_d;

    p->pai = NULL;

    p->pagina[0] = NULL;
    p->pagina[1] = NULL;
    p->pagina[2] = NULL;
    p->pagina[3] = NULL;
    p->pagina[4] = NULL;
    p->n = 0;

    return p;
}

int binary_search(int *item, int x, int n)
{
    int meio, calibre;

    if (n < 1)
        return -1;

    meio = ((n - 1) / 2);

    // para cobrir a operacao de pesquisa
    if (item[meio] == x)
        return meio;

    // para acessar a pagina[4] quando necessario
    if (item[meio + 1] == NULL && item[meio] < x && n == 1)
        return meio + 1;

    if (item[meio] == -1 || item[meio - 1] != NULL && item[meio - 1] < x && item[meio] >= x || item[meio] >= x && n <= 2)
        return meio;

    if (item[meio] > x)
        return binary_search(item, x, meio);

    if (item[meio] < x)
    {
        calibre = binary_search(&item[meio + 1], x, (n - 1 - meio));

        if (calibre != -1)
            return calibre + 1 + meio;

        return -1;
    }
}

PArvoreB inserir(PArvoreB A, PVerificaPai verif, int x)
{
    int indice, i;
    PArvoreB p;

    if (A == NULL)
    {
        // inicializo a maioria dos itens com -1 para facilitar as operacoes do algoritmo de busca binaria (-1 eh posicao vazia)
        p = criar_no(x, -1, -1, -1);
        ++(p->n);

        return p;
    }

    if (A->n < MM)
        ++(A->n);

    indice = binary_search(A->item, x, A->n);

    // se nao existe no descendente, faremos a operacao neste no em questao
    if (A->pagina[indice] == NULL)
    {
        // verifica se o vetor esta cheio
        if (A->item[3] == -1)
        {
            // -1 significa que a posicao esta vazia
            if (A->item[indice] == -1)
                A->item[indice] = x;
            else
            {
                // se chegou ate essa linha, eh pq precisamos deslocar os itens da posicao atual para mais a direita do vetor
                for (i = A->n - 1; i > indice; i--)
                    A->item[i] = A->item[i - 1];

                A->item[indice] = x;
            }
        }
        // como o vetor esta cheio, precisaremos dividi-lo em dois
        else
        {
            p = criar_no(A->item[2], A->item[3], -1, -1);
            A->item[2] = -1;
            A->item[3] = -1;
            A->n = 2;
            p->n = 2;

            /*
            como eh necessario saber em qual dos dois vetores que o item sera inserido, usaremos a seguinte logica:
                - Se o indice for da metade esquerda do vetor, entao o item deve ser inserido no vetor a esquerda, que no caso eh A
                - Se o indice for da metade direita do vetor, entao o item deve ser inserido no vetor a direita, que no caso eh p
                *Lembrando que o tamanho do vetor eh MM = 2*M = 2*2 = 4 nesse caso
            */

            // metade esquerda
            if (indice <= (MM - 1) / 2) // TALVEZ SEJA MELHOR RODAR A BUSCA BINARIA MAIS UMA VEZ, SE CASO ESSA LOGICA AQUI FALHAR EM ALGUM CASO
            {
                ++(A->n);
                for (i = A->n - 1; i > indice; i--)
                    A->item[i] = A->item[i - 1];

                A->item[indice] = x;

                if (A->pai == NULL)
                {
                    A->pai = criar_no(A->item[A->n - 1], -1, -1, -1);
                    A->item[A->n - 1] = -1;
                    A->pai->pagina[0] = A;
                    A->pai->pagina[1] = p;
                    ++(A->pai->n);
                    --(A->n);

                    p->pai = A->pai;
                    return A->pai;
                }
                else
                {
                    // verifica se o pai esta cheio
                    if (A->pai->item[3] == -1)
                    {
                        // eh feita entao a atualizacao do no A-> pegando o maior do vetor a esquerda apos a divisao
                        ++(A->pai->n);
                        indice = binary_search(A->pai->item, A->item[A->n - 1], A->pai->n);

                        for (i = A->pai->n - 1; i > indice; i--)
                        {
                            A->pai->item[i] = A->pai->item[i - 1];

                            /* lembrando que a pagina na posicao atual representa os elementos menores que o valor em questao,
                            enquanto que os da posicao i + 1 representam valores maiores que o atual */
                            A->pai->pagina[i + 1] = A->pai->pagina[i];
                        }

                        A->pai->item[indice] = A->item[A->n - 1];
                        A->item[A->n - 1] = -1;
                        --(A->n);

                        A->pai->pagina[indice] = A;
                        A->pai->pagina[indice + 1] = p; // ISSO AQUI A PRIORI FUNCIONA, PRECISAMOS VER PARA MAIS CASOS ALEM DO PRIMEIRO

                        p->pai = A->pai;
                    }
                    else // se o pai estiver cheio, vamos retornar o valor a ser inserido com return e tratar no bloco de chamadas recursivas
                    {
                        /*
                        simplesmente retornar uma chave identificadora para saber se devemos dividir o no pai ou nao,
                        bem como saber em qual indice deve ser inserido, talvez retornar uma struct ou usar uma como parametro para
                        guardar o valor a ser inserido (maior da esquerda ou menor da direita e o indice)
                        */
                        verif = (PVerificaPai)malloc(sizeof(TVerif));
                        if (verif == NULL)
                            return A;

                        verif->esq = A;
                        verif->dir = p;
                        verif->indice = indice;
                        verif->valor = A->item[A->n - 1];
                        A->item[A->n - 1] = -1;

                        --(A->n);

                        return A->pai;
                    }
                }
            }
            // metade direita
            else
            {
                ++(p->n);

                // indice - 2 para fazer a correcao do indice que o novo item deve ser inserido, apenas quando for a direita
                for (i = p->n - 1; i > indice - 2; i--)
                    p->item[i] = p->item[i - 1];

                p->item[indice] = x;

                if (p->pai == NULL)
                {
                    p->pai = criar_no(p->item[0], -1, -1, -1);
                    p->pai->pagina[0] = A;
                    p->pai->pagina[1] = p;
                    ++(p->pai->n);

                    // rearranjar o vetor apos a remocao do menor valor
                    for (i = 0; i < p->n; i++)
                        p->item[i] = p->item[i + 1];

                    --(p->n);

                    A->pai = p->pai;

                    return p->pai;
                }
                else // se o pai existe...
                {
                    // verifica o valor do ultimo item pq verificar por tamanho nao funcionaria em todos os casos, ja que o pai pode ou nao estar em seu limite de descendentes MM + 1
                    if (p->pai->item[3] == -1)
                    {
                        ++(p->pai->n);
                        indice = binary_search(p->pai->item, p->item[0], p->pai->n);

                        for (i = p->pai->n - 1; i > indice; i--)
                        {
                            p->pai->item[i] = p->pai->item[i - 1];
                            p->pai->pagina[i + 1] = p->pai->pagina[i];
                        }

                        p->pai->item[indice] = p->item[0];
                        p->pai->pagina[indice] = A;
                        p->pai->pagina[indice + 1] = p;

                        // rearranjar o vetor apos a remocao do menor valor
                        for (i = 0; i < p->n; i++)
                            p->item[i] = p->item[i + 1];

                        A->pai = p->pai;

                        --(p->n);
                    }
                    else // se o pai estiver cheio, vamos dividi-lo
                    {
                        /*
                        simplesmente retornar uma chave identificadora para saber se devemos dividir o no pai ou nao,
                        bem como saber em qual indice deve ser inserido, talvez retornar uma struct ou usar uma como parametro para
                        guardar o valor a ser inserido (maior da esquerda ou menor da direita e o indice)
                        */
                        verif = (PVerificaPai)malloc(sizeof(TVerif));
                        if (verif == NULL)
                            return A;

                        verif->esq = A;
                        verif->dir = p;
                        verif->indice = indice;
                        verif->valor = p->item[0];

                        // rearranjar o vetor apos a remocao do menor valor
                        for (i = 0; i < p->n; i++)
                            p->item[i] = p->item[i + 1];

                        --(p->n);

                        A->pai = p->pai;

                        return p->pai; // sera que isso vai dar certo??? pq esse cara sempre eh parametro, mas a ideia entao eh fazer as operacoes nele
                    }
                }
            }
        }
    }
    else
    {
        --(A->n);
        A = inserir(A->pagina[indice], verif, x);

        // se verif nao for nulo, significa que precisamos fazer alguma operacao no no em questao, que eh agora o pai dos nos guardados em verif
        if (verif == NULL)
            return A;

        indice = binary_search(A->pai->item, A->item[A->n - 1], A->pai->n);

        // como ja verifiquei que o no atual esta cheio, ja sabemos que precisamos dividir o pai
        p = criar_no(A->item[2], A->item[3], -1, -1);
        A->item[2] = -1;
        A->item[3] = -1;

        /*
        A->pagina[2] deve aguardar analise de em qual metade do no atual o verif->valor deve ser
        inserido, sendo apontado no momento pelos ponteiros A->pagina[2] e p->pagina[0]
        */
        A->pagina[3] = NULL;
        A->pagina[4] = NULL;
        A->n = 2;

        p->pagina[0] = A->pagina[2];
        p->pagina[1] = A->pagina[3];
        p->pagina[2] = A->pagina[4];
        p->n = 2;

        // lembrando que esse indice eh referente a que posicao o item do vetor A deveria estar no vetor pai
        if (verif->indice <= (MM - 1) / 2)
        {
            ++(A->n);
            for (i = A->n - 1; i > verif->indice; i--)
            {
                A->item[i] = A->item[i - 1];
                A->pagina[i + 1] = A->pagina[i];
            }

            A->item[verif->indice] = verif->valor;
            A->pagina[verif->indice] = verif->esq;
            A->pagina[verif->indice + 1] = verif->dir;

            A->pagina[A->n] = NULL; // decisao do que fazer com o A->pagina[2]

            if (A->pai == NULL)
            {
                A->pai = criar_no(A->item[A->n - 1], -1, -1, -1);
                A->pai->pagina[0] = A;
                A->pai->pagina[1] = p;
                A->pai->n = 1;

                A->item[A->n - 1] = -1; // PONTO DE ATENCAO AQUI AO MANIPULAR OS PONTEIROS PARA AS PAGINAS

                p->pai = A->pai;

                return A->pai;
            }
            else
            {
                // verifica se o pai esta cheio
                if (A->pai->item[3] == -1)
                {
                    // eh feita entao a atualizacao do no A-> pegando o maior do vetor a esquerda apos a divisao
                    ++(A->pai->n);
                    indice = binary_search(A->pai->item, A->item[A->n - 1], A->pai->n);

                    for (i = A->pai->n - 1; i > indice; i--)
                    {
                        A->pai->item[i] = A->pai->item[i - 1];

                        /* lembrando que a pagina na posicao atual representa os elementos menores que o valor em questao,
                        enquanto que os da posicao i + 1 representam valores maiores que o atual */
                        A->pai->pagina[i + 1] = A->pai->pagina[i];
                    }

                    A->pai->item[indice] = A->item[A->n - 1];
                    A->item[A->n - 1] = -1;
                    --(A->n);

                    A->pai->pagina[indice] = A;
                    A->pai->pagina[indice + 1] = p; // ISSO AQUI A PRIORI FUNCIONA, PRECISAMOS VER PARA MAIS CASOS ALEM DO PRIMEIRO

                    p->pai = A->pai;
                }
                else // se o pai do pai estiver cheio, vamos retornar o valor a ser inserido com return e tratar no bloco de chamadas recursivas
                {
                    /*
                    simplesmente retornar uma chave identificadora para saber se devemos dividir o no pai ou nao,
                    bem como saber em qual indice deve ser inserido, talvez retornar uma struct ou usar uma como parametro para
                    guardar o valor a ser inserido (maior da esquerda ou menor da direita e o indice)
                    */
                    verif = (PVerificaPai)malloc(sizeof(TVerif));
                    if (verif == NULL)
                        return A;

                    verif->esq = A;
                    verif->dir = p;
                    verif->indice = indice;
                    verif->valor = A->item[A->n - 1];
                    A->item[A->n - 1] = -1;

                    --(A->n);

                    return A->pai;
                }
            }
        }
        else
        {
            ++(p->n);
            for (i = p->n - 1; i > indice - 2; i--)
            {
                p->item[i] = p->item[i - 1];
                p->pagina[i + 1] = p->pagina[i];
            }

            p->item[indice] = verif->valor;
            p->pagina[indice] = verif->esq;
            p->pagina[indice + 1] = verif->dir;

            // pois nao existe ninguem menor do que ele no vetor em questao
            if (indice - 2 == 0)
                p->pagina[0] = NULL;

            if (p->pai == NULL)
            {
                p->pai = criar_no(p->item[0], -1, -1, -1);
                p->pai->pagina[0] = A;
                p->pai->pagina[1] = p;
                p->pai->n = 1;

                p->pai = A->pai;
            }
            else
            {
                // verifica o valor do ultimo item pq verificar por tamanho nao funcionaria em todos os casos, ja que o pai pode ou nao estar em seu limite de descendentes MM + 1
                if (p->pai->item[3] == -1)
                {
                    ++(p->pai->n);
                    indice = binary_search(p->pai->item, p->item[0], p->pai->n);

                    for (i = p->pai->n - 1; i > indice; i--)
                    {
                        p->pai->item[i] = p->pai->item[i - 1];
                        p->pai->pagina[i + 1] = p->pai->pagina[i];
                    }

                    p->pai->item[indice] = p->item[0];
                    p->pai->pagina[indice] = A;
                    p->pai->pagina[indice + 1] = p;

                    // pois nao existe ninguem menor do que ele no vetor em questao
                    if (indice - 2 == 0)
                        p->pagina[0] = NULL;

                    for (i = 0; i < p->n; i++)
                    {
                        p->item[i] = p->item[i + 1];
                        p->pagina[i] = p->pagina[i + 1];
                    }

                    --(p->n);

                    A->pai = p->pai;
                }
                else
                {
                    /*
                    simplesmente retornar uma chave identificadora para saber se devemos dividir o no pai ou nao,
                    bem como saber em qual indice deve ser inserido, talvez retornar uma struct ou usar uma como parametro para
                    guardar o valor a ser inserido (maior da esquerda ou menor da direita e o indice)
                    */
                    verif = (PVerificaPai)malloc(sizeof(TVerif));
                    if (verif == NULL)
                        return A;

                    verif->esq = A;
                    verif->dir = p;
                    verif->indice = indice;
                    verif->valor = p->item[0];

                    // rearranjar o vetor apos a remocao do menor valor
                    for (i = 0; i < p->n; i++)
                        p->item[i] = p->item[i + 1];

                    --(p->n);

                    A->pai = p->pai;

                    return p->pai; // sera que isso vai dar certo??? pq esse cara sempre eh parametro, mas a ideia entao eh fazer as operacoes nele
                }
            }
            return p->pai;
        }
    }
    return A;
}

PArvoreB pesquisar(PArvoreB A, int x)
{
    int indice;

    if (A == NULL)
        return NULL;

    indice = binary_search(A->item, x, A->n);

    if (indice == -1)
        return NULL;

    if (A->item[indice] == x)
        return A;

    return pesquisar(A->pagina[indice], x);
}

PArvoreB liberar(PArvoreB A)
{
    if (A != NULL)
    {
        A->pagina[0] = liberar(A->pagina[0]);
        A->pagina[1] = liberar(A->pagina[1]);
        A->pagina[2] = liberar(A->pagina[2]);
        A->pagina[3] = liberar(A->pagina[3]);
        A->pagina[4] = liberar(A->pagina[4]);
        free(A);
    }
    return NULL;
}

int main()
{
    PArvoreB A, p;
    int x;

    A = NULL;
    x = 0;

    /*
    A primeira linha da entrada para criacao da arvore, consiste de uma lista de numeros
    inteiros positivos separados por espacos. Essa lista consiste de valores a serem inseridos na arvore B.
    A lista termina quando for digitado um numero inteiro negativo
    */
    do
    {
        scanf("%d", &x);
        if (x > -1)
            A = inserir(A, NULL, x);

    } while (x > -1);

    /*
    A segunda linha representa um unico valor inteiro positivo a ser pesquisado na
    arvore. Note que esse valor pode ou nao estar contido na arvore
    */
    scanf("%d", &x);
    p = pesquisar(A, x);

    // A primeira linha da saida refere-se a quantidade de elementos da pagina raiz.
    printf("%d\n", A->n);

    /*
    Na segunda linha deve ser impresso a quantidade de elementos da pagina que se
    encontra o elemento pesquisado. Caso esse valor pesquisado nao seja encontrado,
    deve ser exibido "Valor nao encontrado"
    */
    if (p == NULL)
        printf("Valor nao encontrado");
    else
        printf("%d", p->n);

    A = liberar(A);

    if (A == NULL)
        printf("Arvore liberada");
    else
        printf("Arvore nao liberada");

    return 0;
}