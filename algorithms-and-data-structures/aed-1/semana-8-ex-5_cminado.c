/*
    Nome: Harrison Caetano Candido
    RA: 156264
    Turma: Integral
*/
/*
    O jogo campo minado consiste em marcar todas as bombas do jogo sem apertar em 
    nenhuma, e há uma técnica para descobrir onde elas estão.Inicialmente você se arrisca 
    apertando em um local aleatório. Caso não seja uma bomba, aparecerá um valor que indica 
    quantas bombas tem ao seu redor numa distância de 1 espaço, como no exemplo:

                                    X 1 0 0 0 0 0
                                    3 2 2 0 0 0 0
                                    X X 1 0 0 0 0
                                    1 1 1 0 0 0 0
                                    0 0 0 0 0 0 0
                                    0 0 0 0 0 0 0
                                    0 0 0 0 0 1 1
                                    0 0 0 0 0 1 X

                                  (X indica a bomba)

    Você deverá construir um campo minado utilizando matrizes esparsas. Você receberá 
    as dimensões máximas do campo minado, o número de bombas e suas coordenadas no 
    campo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_COL 100

typedef struct no *pme;

struct no
{
    int col;   // coluna
    int valor; // indica se eh ou nao uma bomba, se for -1 eh bomba, se nao, indica quantas bombas tem ao redor na distancia de 1 espaco
    pme prox, ant;
};

typedef pme *matriz;

void inicializar(matriz m, int lin);
void inserir_ord(matriz m, int lin, int col, int L, int C);
pme incrementa(matriz m, int lin, int col, int L, int C);
void imprimir(matriz m, int lin, int col);
void liberar(matriz m, int lin);

void inicializar(matriz m, int lin)
{
    int i;

    for (i = 0; i < lin; i++)
    {
        m[i] = NULL;
    }
}

void inserir_ord(matriz m, int lin, int col, int L, int C) // usuario digita qual coluna e linha ele quer
{
    pme bomba, atras, frente, p, ant;

    // ----------------------------------------------- APENAS ALOCAR MEMORIA -----------------------------------------------

    bomba = (pme)malloc(sizeof(struct no));

    if (bomba == NULL)
        return;

    bomba->col = col; // vai servir para a ordenacao
    bomba->valor = -1;
    bomba->prox = bomba->ant = NULL;

    atras = (pme)malloc(sizeof(struct no));

    if (atras == NULL)
        return;

    atras->col = col - 1;
    atras->valor = 1;
    atras->prox = atras->ant = NULL;

    frente = (pme)malloc(sizeof(struct no));

    if (frente == NULL)
        return;

    frente->col = col + 1;
    frente->valor = 1;
    frente->prox = frente->ant = NULL;

    // ----------------------------------------------------------------------------------------------------------------------

    // ----------------------------- LEMBRANDO QUE AQUI ESTAMOS APENAS INICIANDO UMA LINHA VAZIA ----------------------------

    if (m[lin] == NULL)
    {
        if (col - 1 >= 0) // saber se nao vaza pra tras na linha
        {
            atras->prox = bomba;
            bomba->ant = atras;
            m[lin] = atras;
        }
        else
        {
            free(atras); // libera atras caso vaze pra esquerda

            m[lin] = bomba;
        }

        if (col + 1 < C) // saber se nao vaza pra frente na linha
        {
            bomba->prox = frente;
            frente->ant = bomba;
        }
        else
            free(frente);

        if (lin - 1 >= 0)                                        // saber se a linha nao vaza pra cima da matriz
            m[lin - 1] = incrementa(m[lin - 1], lin, col, L, C); // COLOCA UNS NAS LINHAS DE CIMA

        if (lin + 1 < L)
            m[lin + 1] = incrementa(m[lin + 1], lin, col, L, C); // COLOCA UNS NAS LINHAS DE BAIXO

        return;
    }

    // ----------------------------------------------------------------------------------------------------------------------

    // ------------------------------------- CASO EM QUE A LINHA NAO EH VAZIA ------------------------------------------------

    for (p = m[lin]; p != NULL && p->col < col; p = p->prox)
    {
        if (p->prox != NULL && (p->col == col && p->valor == -1 || p->prox->col == col && p->prox->valor == -1)) // se a coluna selecionada possuir uma bomba
            return;                                                                                              // pq sao iguais

        ant = p; // salva o ultimo no quando p percorre toda a lista
    }

    if (p != NULL && p->col == col) // se a coluna selecionada ja existe
    {
        p->valor = -1; // o no da coluna selecionada possui agora uma bomba

        if (p->ant != NULL) // se o no selecionado nao eh o primeiro
        {
            if (p->ant->col != col - 1) // se a tupla anterior a selecionada for diferente da coordenada anterior a da coluna da nova bomba, criamos um no de coordenada anterior
            {
                atras->prox = p;
                p->ant->prox = atras;

                atras->ant = p->ant;
                p->ant = atras;
            }
            else
            {
                free(atras); // free em atras pois a coordenada anterior a tupla escolhida ja existe

                if (p->ant->valor != -1)
                    p->ant->valor += 1;
            }
        }
        else // se o no selecionado for o primeiro, criamos um no de coordenada anterior ao da tupla selecionada
        {
            if (col - 1 >= 0) // se nao vazar pra esquerda
            {
                atras->prox = p;
                p->ant = atras;

                m[lin] = atras;
            }
        }

        if (p->prox != NULL) // impedir erro de memoria
        {
            if (col + 1 < C && p->prox->col != col + 1)
            {
                frente->prox = p->prox;
                p->prox->ant = frente;

                frente->ant = p;
                p->prox = frente;
            }
            else
            {
                free(frente);

                if (p->prox->valor != -1)
                    p->prox->valor += 1;
            }
        }
        else // caso a coordenada posterior a tupla selecionada ainda nao exista e ele nao vaze para direita da matriz
        {
            if (col + 1 < C)
            {
                frente->ant = p;
                p->prox = frente;
            }
            else
                free(frente);
        }

        if (lin - 1 >= 0)                                        // saber se a linha nao vaza pra cima da matriz
            m[lin - 1] = incrementa(m[lin - 1], lin, col, L, C); // COLOCA UNS NAS LINHAS DE CIMA

        if (lin + 1 < L)                                         // saber se a linha nao vaza pra baixo da matriz
            m[lin + 1] = incrementa(m[lin + 1], lin, col, L, C); // COLOCA UNS NAS LINHAS DE BAIXO

        return;
    }

    if (p == NULL) // nao achou ninguem menor
    {
        if (ant->col == col - 1) // se a coluna do ultimo no FOR igual a coluna anterior a do no da bomba
        {
            free(atras); // da free em atras pq ja encontramos a coluna anterior a do no da bomba

            ant->prox = bomba;

            bomba->ant = ant;

            if (ant->valor != -1) // se o valor do ultimo no for diferente de uma bomba vai incrementar 1
                ant->valor += 1;

            if (col + 1 < C)
            {
                bomba->prox = frente;
                frente->ant = bomba;
            }
            else
                free(frente);
        }
        else // se a colunao do ultimo no NAO for igual a coluna anterior a do no da bomba
        {

            ant->prox = atras;
            atras->ant = ant;

            atras->prox = bomba;
            bomba->ant = atras;

            if (col + 1 < C)
            {
                bomba->prox = frente;
                frente->ant = bomba;
            }
            else
                free(frente);
        }

        if (lin - 1 >= 0)                                        // saber se a linha nao vaza pra cima da matriz
            m[lin - 1] = incrementa(m[lin - 1], lin, col, L, C); // COLOCA UNS NAS LINHAS DE CIMA

        if (lin + 1 < L)
            m[lin + 1] = incrementa(m[lin + 1], lin, col, L, C); // COLOCA UNS NAS LINHAS DE BAIXO

        return;
    }

    if (p == m[lin]) // se p estiver no primeiro no, ou seja eh a menor coluna
    {

        if (p->col != col + 1) // cria frente caso o no da frente nao corresponda ao da bomba
        {
            frente->prox = p;
            p->ant = frente;

            bomba->prox = frente;
            frente->ant = bomba;
        }
        else // caso o no da frente corresponda ao da frente da bomba
        {
            free(frente);

            bomba->prox = p;
            p->ant = bomba;

            if (p->valor != -1)
                p->valor += 1;
        }

        m[lin] = bomba;

        if (col - 1 >= 0) // nao vaza pra esquerda
        {
            atras->prox = bomba;
            bomba->ant = atras;

            m[lin] = atras;
        }
        else             // vaza pra esquerda
            free(atras); // free atras pq se nao vaza pra esquerda

        if (lin - 1 >= 0)                                        // saber se a linha nao vaza pra cima da matriz
            m[lin - 1] = incrementa(m[lin - 1], lin, col, L, C); // COLOCA UNS NAS LINHAS DE CIMA

        if (lin + 1 < L)
            m[lin + 1] = incrementa(m[lin + 1], lin, col, L, C); // COLOCA UNS NAS LINHAS DE BAIXO

        return;
    }

    if (p->ant->col != col - 1) // se a coluna do no anterior for diferente da coluna do no da bomba
    {
        p->ant->prox = atras;
        atras->ant = p->ant;

        atras->prox = bomba;
        bomba->ant = atras;

        if (p->col != col + 1)
        {
            bomba->prox = frente;
            frente->ant = bomba;

            frente->prox = p;
            p->ant = frente;
        }
        else
        {
            free(frente);

            bomba->prox = p;
            p->ant = bomba;

            if (p->valor != -1)
                p->valor += 1;
        }
    }
    else // se a coluna do no anterior for igual a da coluna anterior a do no da bomba
    {

        free(atras);

        if (p->ant->valor != -1)
            p->ant->valor += 1;

        if (p->col == col)
        {
            if (p->valor == -1)
            {
                p->ant->prox = bomba;
                bomba->ant = p->ant;

                if (p->ant->valor != -1)
                    p->ant->valor += 1;

                if (p->col != col + 1)
                {
                    bomba->prox = frente;
                    frente->ant = bomba;

                    frente->prox = p;
                    p->ant = frente;
                }
                else
                {
                    free(frente);

                    bomba->prox = p;
                    p->ant = bomba;
                }
            }
            else
            {
                p->valor = -1;

                if (p->ant->valor != -1)
                    p->ant->valor += 1;

                if (p->prox != NULL && p->prox->valor != -1)
                    p->prox->valor += 1;

                if (p->prox == NULL)
                {
                    p->prox = frente;
                    frente->ant = p;
                }
            }
        }
        else
        {
            if (p->col != col + 1)
            {
                bomba->prox = frente;
                bomba->ant = p->ant;

                frente->prox = p;
                frente->ant = bomba;

                p->ant->prox = bomba;
                p->ant = frente;
            }
            else
            {
                free(frente);

                if (p->valor != -1)
                    p->valor += 1;

                bomba->prox = p;
                bomba->ant = p->ant;

                p->ant->prox = bomba;
                p->ant = bomba;
            }
        }
    }

    if (lin - 1 >= 0)                                        // saber se a linha nao vaza pra cima da matriz
        m[lin - 1] = incrementa(m[lin - 1], lin, col, L, C); // COLOCA UNS NAS LINHAS DE CIMA

    if (lin + 1 < L)
        m[lin + 1] = incrementa(m[lin + 1], lin, col, L, C); // COLOCA UNS NAS LINHAS DE BAIXO
}

pme incrementa(matriz m, int lin, int col, int L, int C)
{
    pme atras, meio, frente, p, ant;

    // ----------------------- PARA CIMA/BAIXO ----------------------------

    meio = (pme)malloc(sizeof(struct no));

    if (meio == NULL)
        return NULL;

    meio->col = col;
    meio->prox = meio->ant = NULL;

    atras = (pme)malloc(sizeof(struct no));

    if (atras == NULL)
        return NULL;

    atras->col = col - 1;
    atras->prox = atras->ant = NULL;

    frente = (pme)malloc(sizeof(struct no));

    if (frente == NULL)
        return NULL;

    frente->col = col + 1;
    frente->prox = frente->ant = NULL;

    meio->valor = atras->valor = frente->valor = 1;

    if (m == NULL) // criar nos que correspondam aos nos da linha da bomba
    {
        if (col - 1 >= 0) // se nao vaza pra tras
        {
            atras->prox = meio;
            meio->ant = atras;

            m = atras;

            if (col + 1 < C)
            {
                meio->prox = frente;
                frente->ant = meio;
            }
        }
        else // se vazar pra tras
        {
            free(atras);

            if (col + 1 < C)
            {
                meio->prox = frente;
                frente->ant = meio;
            }

            m = meio;
        }
    }
    else // se a linha nao for vazia
    {
        for (p = m; p != NULL && p->col < col; p = p->prox)
            ant = p; // salva o ultimo no quando p percorre toda a lista

        if (p != NULL && p->col == col) // se a coluna selecionada ja existe
        {
            if (col - 1 >= 0) // se a coluna nao vaza pra esquerda
            {
                if (p->ant != NULL) // se o no selecionado nao eh o primeiro
                {
                    if (p->ant->col != col - 1) // se a tupla anterior a selecionada for diferente da coordenada anterior a da coluna da nova bomba, criamos um no de coordenada anterior
                    {
                        atras->prox = p;
                        atras->ant = p->ant;

                        p->ant->prox = atras;
                        p->ant = atras;
                    }
                    else // se a tupla anterior a selecionada tiver coordenada correspondente a coordenada anterior teorica
                    {
                        free(atras);

                        if (p->ant->valor != -1)
                            p->ant->valor += 1;
                    }
                }
                else // cria o no anterior caso o no de coordenada anterior nao exista
                {
                    atras->prox = p;
                    p->ant = atras;

                    m = atras;
                }
            }

            if (p->valor != -1)
                p->valor += 1;

            if (col + 1 < C) // caso nao vaze pra direita
            {
                if (p->prox != NULL && p->prox->col != col + 1) // se a coluna da frente nao corresponder as coordenadas da coluna posterior a do no selecionado
                {
                    frente->prox = p->prox;
                    p->prox->ant = frente;

                    frente->ant = p;
                    p->prox = frente;
                }
                else
                {
                    if (p->prox != NULL && p->prox->col == col + 1) // se a coluna da frente corresponder as coordenadas da coluna posterior a do no selecionado
                    {
                        free(frente); // nesse caso nao sera preciso encadear um no de coordenada posterior, pois ele ja existe

                        if (p->prox->valor != -1)
                            p->prox->valor += 1;
                    }
                }

                if (p->prox == NULL) // cria o no de coordenada posterior caso seja necessario
                {
                    p->prox = frente;
                    frente->ant = p;
                }
            }
            return m;
        }

        if (p == m) // se p esta no inicio
        {
            meio->prox = p;
            p->ant = meio;

            m = meio;

            if (p->col != col + 1) // se a coordenada posterior a do no de referencia nao existe, entao vamos criar
            {
                frente->prox = p;
                p->ant = frente;

                meio->prox = frente;
                frente->ant = meio;
            }
            else
            {
                free(frente);
                if (p->valor != -1)
                    p->valor += 1;
            }

            if (col - 1 >= 0) // se nao vaza pra esquerda
            {
                atras->prox = meio;
                meio->ant = atras;

                m = atras;
            }
            else
                free(atras); // se vazar pra esquerda vamos desalocar o no atras, pois nao sera utilizado

            return m;
        }

        if (p == NULL) // se percorreu toda a lista / linha e nao foi possivel encontrar uma coluna menor existente
        {
            if (ant->col != col - 1) // se a coluna do no anterior nao corresponde teoricamente a coordenada do no anterior da tupla selecionada
            {
                atras->prox = meio;
                meio->ant = atras;

                ant->prox = atras;
                atras->ant = ant;

                if (col + 1 < C) // se nao vaza pra direita
                {
                    meio->prox = frente;
                    frente->ant = meio;
                }
                else
                    free(frente); // se vaza pra direita desalocaremos o no da frente
            }
            else // se a coluna do no anterior corresponde teoricamente a coordenada do no anterior da tupla selecionada
            {
                free(atras); // desaloca o no atras pois nao iremos utilizar, ja que a coordenada correspondente a coordenada do no anterior a tupla selecionada ja existe

                if (ant->valor != -1)
                    ant->valor += 1;

                ant->prox = meio;
                meio->ant = ant;

                if (col + 1 < C) // se nao vaza pra direita
                {
                    meio->prox = frente;
                    frente->ant = meio;
                }
                else
                    free(frente); // desaloca o no da frente caso seu encadeamento cause um vazamento pra direita
            }
            return m;
        }

        // --------------- CASO p ESTEJA NO MEIO DA LISTA --------------

        if (p->ant->col != col - 1) // caso o no anterior nao seja de coordenada anterior a da bomba
        {
            atras->prox = meio;
            meio->ant = atras;

            atras->ant = p->ant;
            p->ant->prox = atras;

            p->ant = meio;
            meio->prox = p;
        }
        else
        {
            free(atras); // desaloca atras pois nao iremos utilizar

            if (p->ant->valor != -1)
                p->ant->valor += 1;

            p->ant->prox = meio;
            meio->ant = p->ant;

            meio->prox = p; // provisoriamente
            p->ant = meio;
        }

        if (p->col != col + 1) // caso o no posterior nao seja da coordenada posterior a da bomba
        {
            frente->prox = p;
            frente->ant = p->ant;

            p->ant->prox = frente;
            p->ant = frente;
        }
        else
        {
            free(frente); // desaloca frente pois nao iremos utilizar

            if (p->valor != -1)
                p->valor += 1;
        }
    }
    return m;
}

void imprimir(matriz m, int lin, int col)
{
    int i, j;
    pme p;

    for (i = 0; i < lin; i++) // linhas
    {
        p = m[i]; // p == linha
        for (j = 0; j < col; j++)
        {
            if (p != NULL && p->col == j) // colunas
            {
                if (p->valor != -1)
                {
                    printf("%d ", p->valor);
                }
                else
                {
                    printf("X ");
                }
                p = p->prox;
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void liberar(matriz m, int lin)
{
    pme p, q;
    int i;

    for (i = 0; i < lin; i++)
    {
        p = m[i];
        while (p != NULL)
        {
            q = p;
            p = p->prox;
            free(q);
        }
    }
}

int main()
{
    matriz m;
    int L, C, B, i, j, k; // L e C (0 <= L, C <= 100)

    do
    {
        scanf("%d", &L); // Digite a quantidade de linhas da matriz
    } while (L < 0);

    do
    {
        scanf("%d", &C); // Digite a quantidade de colunas da matriz
    } while (C < 0 && C > MAX_COL);

    do
    {
        scanf("%d", &B); // Digite o numero de bombas na matriz
    } while (B < 0 && B > 50);

    m = (pme)malloc(L * sizeof(struct no));

    if (m == NULL)
        return 0;

    inicializar(m, L); // inicializa a matriz

    k = 0;
    while (k < B)
    {
        scanf("%d", &i); // coordenada da linha

        scanf("%d", &j); // coordenada da coluna

        if ((i >= 0 && i < L) && (j >= 0 && j < C))
        {
            inserir_ord(m, i, j, L, C);
        }
        k++;
    }

    imprimir(m, L, C);

    liberar(m, L);

    return 0;
}