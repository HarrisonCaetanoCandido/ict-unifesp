/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turma Integral
*/
/*
    Você e seus amigos combinaram de se reunirem no fim de semana para jogar alguns jogos, 
    incluindo jogos de baralho, no qual você se sai muito bem, pois sempre tem sorte nas 
    cartas recebidas. O jogo que você mais se destaca é o pife.
    O jogo de cartas pife consiste em, cada jogador recebe 9 cartas de baralho inicialmente e a 
    cada rodada cada jogador compra uma carta e descarta outra. O objetivo é formar 3 trios 
    em que, dentro do trio, sejam cartas sequenciais ou todas iguais.
    A sequência das cartas é: 
    A 2 3 4 5 6 7 8 9 J Q K 
    A sequência das cartas é circular, ou seja, o trio Q, K e A, por exemplo, é válido.
    Um exemplo de uma mão de cartas iniciais é: exemplo: A, 2, 4, 5, 6, 9, 9, 9 e K. Nesse 
    exemplo 4, 5 e 6; 9, 9 e 9; K, A e 2; são trios válidos.
    Você tem que criar um programa que leia a sequência de 9 cartas e insira ordenadamente 
    em uma lista circular. Depois calcule quantas possibilidades de trios dá para montar com 
    essas cartas.
*/

#include <stdio.h>
#include <stdlib.h>
#define nCARTAS 9

typedef struct lista_circular
{
    char Carta;
    int prioridade;
    struct lista_circular *prox;
} Tlista;

typedef Tlista *Plista;

// --------------------------------- FUNCOES
void liberar(Plista ultimo);
Plista inserir_ord(Plista ultimo, char carta);
void imprimir(Plista ultimo);
int formacao_trios(Plista ultimo);
// -----------------------------------------

int main()
{
    /*
    Você tem que criar um programa que leia a sequência de 9 cartas e insira ordenadamente
    em uma lista circular. Depois calcule quantas possibilidades de trios dá para montar com
    essas cartas
    */
    Plista ultimo;
    int i, trios;
    char carta[nCARTAS];

    ultimo = NULL; // cria a lista

    scanf("%s", carta); // recebe a string

    i = 0;
    while (i < nCARTAS) // fazer a insercao ordenada
    {

        if (carta[i] == 'A' || carta[i] == '2' || carta[i] == '3' || carta[i] == '4' || carta[i] == '5' ||
            carta[i] == '6' || carta[i] == '7' || carta[i] == '8' || carta[i] == '9' || carta[i] == 'J' || carta[i] == 'Q' || carta[i] == 'K')
        {

            ultimo = inserir_ord(ultimo, carta[i]); // manda todos os indices menos o do caracter nulo
        }
        i++;
    }

    trios = formacao_trios(ultimo);

    imprimir(ultimo);

    printf("\n%d", trios);

    liberar(ultimo);

    return 0;
}

Plista inserir_ord(Plista ultimo, char carta)
{
    Plista novo, p, ant;
    int passou = 0;

    novo = (Plista)malloc(sizeof(Tlista));

    if (novo == NULL)
        return NULL; // erro de alocacao de memoria

    //                         A sequência das cartas é:
    //                          A 2 3 4 5 6 7 8 9 J Q K
    /*  se for:
            prioridade
        A =     1
        2 =     2
        3 =     3
        4 =     4
        5 =     5
        6 =     6
        7 =     7
        8 =     8
        9 =     9
        J =     10
        Q =     11
        K =     12
    */
    // ------------------------- TABELA DE PRIORIDADES --------------------------
    // Fazer atribuicoes de acordo com o char que vier:

    if(carta == 'A') novo->prioridade = 1; 
    if(carta == '2') novo->prioridade = 2; 
    if(carta == '3') novo->prioridade = 3; 
    if(carta == '4') novo->prioridade = 4; 
    if(carta == '5') novo->prioridade = 5; 
    if(carta == '6') novo->prioridade = 6; 
    if(carta == '7') novo->prioridade = 7; 
    if(carta == '8') novo->prioridade = 8; 
    if(carta == '9') novo->prioridade = 9; 
    if(carta == 'J') novo->prioridade = 10;
    if(carta == 'Q') novo->prioridade = 11;
    if(carta == 'K') novo->prioridade = 12;

    novo->Carta = carta; // guarda a carta

    // -------------------------------------------------------------------------

    // Caso em que nao tem nenhum no alocado na lista:
    if (ultimo == NULL)
    {
        novo->prox = novo;
        return novo;
    }

    // Trabalhar em n iteracoes utilizando as prioridades para ir posicionando na nossa lista

    ant = p = ultimo->prox;

    do
    {
        if (p->prioridade < novo->prioridade)
        {
            passou = 1;
            ant = p;
            p = p->prox; // 4 < 6 , 5 < 6, 7 < 6 (para nesse ultimo e fecha o laco com o endereco de p)
        }
    } while (p != ultimo->prox && p->prioridade < novo->prioridade);

    if (passou == 0) // se for colocar na primeira posicao da lista
    {
        novo->prox = p;
        ultimo->prox = novo;
        return ultimo;
    }

    // 9[0], ant = 0, p = 0, ultimo->prox = novo(2); novo(2)->prox = p(9);
    // 2[0] , 9[1], ant = 0, p = 1, aqui p(9) > novo(3), ant(2[0])->prox = novo(3); novo(3)->prox = p;
    // 2[0] , 3[1], 9[2], ant = 2, p = 0, aqui ele ja percorreu tudo, novo(K)->prox = ultimo->prox; ultimo->prox = novo(K);
    // 2[0] , 3[1], 9[2], K[3]

    if (p == ultimo->prox)
    {
        novo->prox = ultimo->prox;
        ultimo->prox = novo;
        return novo; // retorna novo como ultimo, pois ele estara na ultima posicao
    }

    // Se for inserir no meio:
    ant->prox = novo;
    novo->prox = p;

    return ultimo;
}

int formacao_trios(Plista ultimo)
{

    //                         A sequência das cartas é:
    /*                          A 2 3 4 5 6 7 8 9 J Q K
       --------------------------------------------------------------------------
        Exemplo:

         ENTRADA  |    SAIDA    | SEQUENCIAS ENCONTRADAS
        923K9A946 |  A2346999K  |   A23
                  |             |   234
                  |             |   999
                  |             |   KA2
        Agora perceba, ele pega o primeiro no, compara com os proximos 2, pega o segundo compara com os proximos 2, e assim por diante,
        até que o ultimo no esteja comparando considerando que a lista eh circular
    */

    Plista p, percorrendo, f;
    int i, contagem, soma = 0;

    if (ultimo == NULL)
        return 0;

    percorrendo = ultimo->prox;

    do
    {
        p = percorrendo;
        f = p->prox->prox; // 1,  ,2
        contagem = 0;

        if (p->prioridade == p->prox->prioridade && p->prox->prioridade == f->prioridade) // 1, 1, 1
        {                                                                                 // AAAAAAAAA
            contagem = 2;
        }

        if (p->prioridade + 1 == p->prox->prioridade && p->prox->prioridade == f->prioridade) // aqui eh como se fosse: AAA{,A,.2.;2;}234
        {
            do
            {
                if (p->prox->prioridade == f->prioridade) // Se: AAA|A{2}[2]|234 {2} == [2]
                {
                    p = p->prox; // AAA{A,2,.2.};2;34 => AAA{A2,2,}.2.;3;4
                    f = f->prox;
                    contagem = 1;
                }
                else
                {
                    if (p->prox->prioridade + 1 == f->prioridade)
                    {
                        contagem = 2;
                    }
                    else
                    {
                        contagem = 0;
                    }
                }
            } while (contagem != 2 && contagem != 0);
        }

        p = percorrendo;
        f = p->prox->prox;

        if (p->prioridade + 1 == p->prox->prioridade && p->prox->prioridade + 1 == f->prioridade) // 1, 2 , 3
        {                                                                                         // A23456789
            contagem = 2;
        }

        // Se 'percorrendo' estiver no penultimo no:
        if (percorrendo->prox == ultimo &&
            (percorrendo->prioridade == 11 || percorrendo->prioridade == 12) &&
            ((p->prioridade + 1 == p->prox->prioridade && f->prioridade == 1) ||
             (p->prioridade == 12 && p->prioridade == p->prox->prioridade && f->prioridade == 1)))
        { // Semi-finais com: AAAAAAAQK | AAAAAAAKK
            contagem = 2;
        }

        // Se 'percorrendo' estiver no ultimo no:
        if (percorrendo->prox == ultimo->prox && percorrendo->prioridade == 12 &&
            (p->prox->prioridade == 1 || p->prox->prioridade == 12) &&
            (p->prox->prioridade == f->prioridade || p->prox->prioridade + 1 == f->prioridade))
        { // Finais com: AAAAAAAQK | AAAAAAAKK
            if (p->prox->prioridade == f->prioridade)
            {
                contagem = 0;
                do
                {
                    if (p->prox->prioridade == f->prioridade)
                    {
                        p = p->prox;
                        f = f->prox;
                        contagem = 1;
                    }
                    else
                    {
                        if (p->prox->prioridade + 1 == f->prioridade)
                        {
                            contagem = 2;
                        }
                        else
                        {
                            contagem = 0;
                        }
                    }
                } while (contagem != 0 && contagem != 2);
            }
            else
            {
                contagem = 2;
            }
        }

        if (contagem == 2)
        {
            soma = soma + 1;
        }

        percorrendo = percorrendo->prox; // passa para o proximo no, vamos comparar dois a dois 2 vezes, mas no proximo no da lista

    } while (percorrendo != ultimo->prox);

    return soma;
}

void imprimir(Plista ultimo)
{
    Plista p;

    if (ultimo == NULL)
        return;

    p = ultimo->prox;

    do
    {
        printf("%c", p->Carta);
        p = p->prox;
    } while (p != ultimo->prox);
}

void liberar(Plista ultimo)
{
    Plista p;

    if (ultimo == NULL) // esta vazio
        return;

    if (ultimo->prox == ultimo) // se so tem um no na lista
    {
        free(ultimo);
        return;
    }

    p = ultimo->prox;

    ultimo->prox = p->prox;
    free(p);
    liberar(ultimo);
}