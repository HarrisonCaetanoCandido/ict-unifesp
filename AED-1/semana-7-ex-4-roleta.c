/*
    Nome: Harrison Caetano Candido
    RA: 156264
    Turma: Integral
*/
/*
    Um cassino decide colocar em sua lista de jogos uma modalidade nova de jogo
    baseado no jogo da roleta. Para jogar você precisa possuir uma quantia de dinheiro
    inicial D. Caso suas perdas sejam maiores que a sua quantia inicial não se preocupe,
    pois você poderá pagar ao cassino na saída. Desta forma, seu valor D poderá admitir
    valores negativos à medida que você joga.
    A mecânica deste no jogo funciona da seguinte forma: você possui uma roleta
    em que cada número representa um prêmio para o jogador ou um valor que o jogador
    precisa pagar ao cassino. Para deixar mais claro, caso a bola caia em um número
    par, o jogador deverá pagar ao casino um valor X; caso a bola caia em um número
    ímpar, o jogador ganha um valor X em dinheiro. Você deverá implementar uma lista
    circular duplamente encadeada que representará a roleta e, para montá-la, um
    número N será dado que representa a quantidade de posições na roleta. Seguido
    deste número você encontrará N linhas em que cada um conterá um número R que
    será uma casa da roleta e um outro número V que será o valor do prêmio ou o valor
    a ser pago pelo jogador. Desta forma, cada posição do registro armazenará os valores
    R e V.
    Um novo valor M será dado, que representará a quantidade de casas
    sorteadas, seguido dos números das casas sorteadas.
    Alguns detalhes devem ser considerados. Quando um número é sorteado, ele
    deve ser retirado da lista e também um movimento de rotação deve ser aplicado. O
    movimento de rotação consiste em deslocar os valores V uma casa no sentido horário
    ou anti-horário. A regra para definir o sentido é de acordo com o número sorteado, ou
    seja, se for ímpar a rotação será anti-horário, e se for par, sentido horário.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct lista_circ
{
    int R; // casa da roleta (provavelmente impar ou par)
    int V; // valor do premio ou valor a ser pago pelo jogador
    struct lista_circ *prox;
    struct lista_circ *ant;
} Tlista2;

typedef Tlista2 *Plista2;

// ----------------- FUNCOES ------------------
Plista2 inserir(Plista2 l, int R, int V);
void imprimir(Plista2 l);
Plista2 remover(Plista2 l, int R, int *D);
Plista2 rotacionar_ahorario(Plista2 l);
Plista2 rotacionar_horario(Plista2 l);
Plista2 liberar(Plista2 l);


Plista2 inserir(Plista2 l, int R, int V) // Aqui l eh como se fosse o ultimo em uma lista simplesmente encadeada circular
{
    Plista2 novo;

    novo = (Plista2)malloc(sizeof(Tlista2));

    if (novo == NULL)
        return NULL;

    novo->R = R;
    novo->V = V;

    if (l == NULL)
    {
        novo->prox = novo->ant = novo;
    }
    else
    {
        novo->prox = l->prox;
        novo->ant = l;
        l->prox->ant = novo;
        l->prox = novo;
    }
    return novo;
}

void imprimir(Plista2 l)
{
    Plista2 p;

    p = l->prox;

    do
    {
        printf("%d %d\n", p->R, p->V);
        p = p->prox;
    } while (p != l->prox);
}

Plista2 remover(Plista2 l, int R, int *D)
{
    Plista2 p;

    if(l == NULL) return NULL;

    p = l->prox;

    do
    {
        if (p->R != R)
        {
            p = p->prox;
        }
    } while (p != l->prox && p->R != R);

    if (p->R != R)
    {
        *D = 0;
        return l;
    }

    if(l == l->prox) // se so tem um no
    {
        *D = l->V;
        free(l);
        return NULL;
    }

    if (p == l->prox) // se for o primeiro no
    {
        p->prox->ant = l;
        l->prox = p->prox;
        *D = p->V;
        free(p);
        return l;
    }

    if (p == l) // se for o ultimo no
    {
        l->ant->prox = l->prox;
        l->prox->ant = l->ant;
        *D = l->V;
        l = l->ant;
        free(p);
        return l;
    }

    p->prox->ant = p->ant;
    p->ant->prox = p->prox;
    *D = p->V;
    free(p);
    return l;
}

Plista2 rotacionar_ahorario(Plista2 l) // impar
{
    Plista2 p, g, a;

    if(l == NULL) return NULL;

    p = l;    // inicio/fim da lista circular, nesse caso vai ler ao contrario, entao sera do fim para o comeco considerando que l seja o ultimo no
    a = p->V; // guarda o valor do atual

    do
    {
        g = p->ant->V; // guarda o valor do no anterior // 14
        p = p->ant;    // anda pra tras uma vez // esta em l
        p->V = a;      // novo atual recebe o antigo valor do no anterior // igual ao valor do primeiro, ou seja 14
        a = g;         // recebe o antigo valor do no atual // a recebe 14
    } while (p != l);

    return l;
}

Plista2 rotacionar_horario(Plista2 l) // par
{
    Plista2 p, a, g;

    if(l == NULL) return NULL;

    p = l->prox; // p eh igual ao inicio
    a = p->V;    // valor atual

    do
    {
        g = p->prox->V; // guarda o valor da frente
        p = p->prox;    // vai pra frente
        p->V = a;       // no atual recebe o valor do no anterior, valor antigo do no atual ja esta guardado em g
        a = g;          // a, que eh a variavel que guarda os valores trocados recebe o antigo valor do no atual guardado anteriormente por g
    } while (p != l->prox);

    return l;
}

Plista2 liberar(Plista2 l)
{
    Plista2 p;

    if (l == NULL)
        return NULL;

    if (l->prox == l)
    {
        free(l);
        return NULL;
    }

    p = l->prox;
    l->prox = p->prox;
    free(p);
    liberar(l);
}

int main()
{
    Plista2 l;
    int D, Dd, N, i, R, V, M, num;

    l = NULL;

    scanf("%d", &D); // valor inicial de dinheiro D // 100

    Dd = D;

    scanf("%d", &N); // quantidade N de casas da roleta // 5

    i = 0;
    while (i < N) // n linhas
    {
        scanf("%d %d", &R, &V); // R = Casa | V = Valor do premio (par ou impar)
                                // R   V   R  V   R  V  R  V   R V
        l = inserir(l, R, V);   // pedidos os valores R e V de cada casa // 28 100, 30 10, 12 0, 13 90, 7 7
        i++;
    }

    scanf("%d", &M); // quantidade M de rodadas jogadas, nas M linhas seguintes, serão informados os valores dos números sorteados // 2

    i = 0;
    while (i < M) // os numeros R das casas sorteadas precisam ser passados
    {
        scanf("%d", &R);

        num = R % 2;

        if (num == 1) // impar - ganha (+)
        { 
            l = remover(l, R, &Dd);
            D = D + Dd;
            l = rotacionar_ahorario(l);
        }

        if (num == 0) // par - perde (-)
        { 
            l = remover(l, R, &Dd);
            D = D + (-Dd); 
            l = rotacionar_horario(l);
        }

        i++;
    }

    // A saída deverá conter a soma que representa o saldo do jogador após o fim das rodadas e, nas linhas seguintes, imprima a lista resultante.
    
    printf("%d\n", D);

    if (l == NULL)
    {
        printf("Lista Vazia!");
    }
    else
    {
        imprimir(l);
    }

    l = liberar(l);

    return 0;
}