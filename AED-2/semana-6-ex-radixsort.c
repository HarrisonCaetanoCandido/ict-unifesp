/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turno: Noturno
*/
/*
    O grupo de amigos achou divertido brincar com o jogo "Brincando com as palavras
    ordenadas" e resolveu continuar com a brincadeira.
    Mas desta vez, eles acharam que seria mais divertido nao excluir palavras e tambem trata-las como se tivessem o mesmo
    comprimento (medido em numero de caracteres). Por isso, incluiram mais duas regras
    a brincadeira:

        1. se a palavra contiver letras maiusculas, elas devem ser convertidas para minusculas;
        2. espacos em branco devem ser utilizados para deixar todas as palavras com o
        mesmo comprimento da maior palavra. Cada palavra tem no m´aximo 20 caracteres.

    Assim como no outro jogo, cada participante tera um papel no jogo. O jogo comeca
    com um dos participantes sorteando um numero inteiro positivo N que representa a
    quantidade de palavras, depois o segundo participante escreve as N palavras em um
    papel, e assim por diante.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct dados
{
    char palavra[20];
} Tdados;
typedef Tdados *Pdados;

int identificar_indice(Pdados A, int i, int j);
void counting_sort(Pdados A, Pdados B, int n, int j);
void radix_sort(Pdados A, int d, int n);

/*
O vetor C deve ser de tamanho k = 27, sendo a primeira posicao destinada ao caractere
adicional (vazio) e as posicoes restantes referentes as 26 letras minusculas em ordem
crescente (a, b,. . ., z).
*/
int identificar_indice(Pdados A, int i, int j)
{
    if (A[i].palavra[j] == ' ')
        return 0;

    if (A[i].palavra[j] == 'a')
        return 1;

    if (A[i].palavra[j] == 'b')
        return 2;

    if (A[i].palavra[j] == 'c')
        return 3;

    if (A[i].palavra[j] == 'd')
        return 4;

    if (A[i].palavra[j] == 'e')
        return 5;

    if (A[i].palavra[j] == 'f')
        return 6;

    if (A[i].palavra[j] == 'g')
        return 7;

    if (A[i].palavra[j] == 'h')
        return 8;

    if (A[i].palavra[j] == 'i')
        return 9;

    if (A[i].palavra[j] == 'j')
        return 10;

    if (A[i].palavra[j] == 'k')
        return 11;

    if (A[i].palavra[j] == 'l')
        return 12;

    if (A[i].palavra[j] == 'm')
        return 13;

    if (A[i].palavra[j] == 'n')
        return 14;

    if (A[i].palavra[j] == 'o')
        return 15;

    if (A[i].palavra[j] == 'p')
        return 16;

    if (A[i].palavra[j] == 'q')
        return 17;

    if (A[i].palavra[j] == 'r')
        return 18;

    if (A[i].palavra[j] == 's')
        return 19;

    if (A[i].palavra[j] == 't')
        return 20;

    if (A[i].palavra[j] == 'u')
        return 21;

    if (A[i].palavra[j] == 'v')
        return 22;

    if (A[i].palavra[j] == 'w')
        return 23;

    if (A[i].palavra[j] == 'x')
        return 24;

    if (A[i].palavra[j] == 'y')
        return 25;

    if (A[i].palavra[j] == 'z')
        return 26;
}

void radix_sort(Pdados A, int d, int n)
{
    int i, k;
    Pdados B;

    B = (Pdados)malloc(n * sizeof(Tdados)); // tem o tamanho de A
    if (B == NULL)
        return;

    for (i = d - 1; i > -1; i--) // executar d vezes, que no caso eh o tamanho da maior string
    {
        // eh necessario usar um metodo de ordenacao estavel (no caso o counting sort) para que o array A seja ordenado no digito i
        counting_sort(A, B, n, i);
    }

    free(B);
}

// B eh o output, j seria qual "digito" estamos na string
void counting_sort(Pdados A, Pdados B, int n, int j)
{
    int i, id, C[27];

    // inicializa o vetor de contagem
    for (i = 0; i < 27; i++)
        C[i] = 0;

    // Contar quantos elementos tem pra cada chave
    for (i = 0; i < n; i++)
    {
        id = identificar_indice(A, i, j);
        C[id] = C[id] + 1; // num elem. de tam i
    }

    for (i = 1; i < 27; i++)
        C[i] = C[i] + C[i - 1]; // num. elem <= i

    /*
    O sexto jogador ordena o conjunto resultante e exibe o vetor auxiliar C apos a
    execucao da linha 8 do algoritmo Counting sort apresentado pelo monitor
    */

    for (i = 0; i < 27; i++)
        printf("%d ", C[i]);
    printf("\n");

    for (i = n - 1; i > -1; i--)
    {
        id = identificar_indice(A, i, j);
        strcpy(B[C[id] - 1].palavra, A[i].palavra);
        C[id] = C[id] - 1;
    }

    // por ser estavel, se fez necessario copiar o novo vetor para A todas as vezes para que a ordenacao nao saia errada em casos de digitos maiores a direita, o laco nessa posicao mantem a complexidade O(n) do radixsort
    for (i = 0; i < n; i++)
        strcpy(A[i].palavra, B[i].palavra);
}

int main()
{
    int i, j, n, P, M, maior;
    Pdados A;

    // O primeiro jogador especifica 7 como o numero de palavras do conjunto original de entrada
    scanf("%d", &n);

    A = (Pdados)malloc(n * sizeof(Tdados));
    if (A == NULL)
        return 0;

    // O segundo jogador escreve as palavras desse conjunto
    for (i = 0; i < n; i++)
        scanf("%s", A[i].palavra);

    // O terceiro jogador tem a funcao de definir uma sublista do vetor ordenado para ser exibida como resultado da saida
    scanf("%d", &P); // P(1 ≤ P ≤ N) referente ao indice do primeiro nome da lista ordenada a ser impresso

    scanf("%d", &M); // M(1 ≤ M ≤ N − P + 1) referente a quantidade de **nomes**(ou NUMEROS?) a serem exibidos a partir do P-esimo nome da lista ordenada

    // O quarto transforma maiuscula em minuscula
    for (i = 0; i < n; i++)
    {
        j = 0;
        while (A[i].palavra[j] != '\0')
        {
            A[i].palavra[j] = tolower(A[i].palavra[j]);
            (++j);
        }
    }

    for (i = 0; i < n; i++)
        printf("%s.\n", A[i].palavra);

    /*
    O quinto descobre o tamanho da maior palavra e completa todas com espaco em branco
    para todas terem o tamanho maximo de 20 caracteres
    */

    maior = strlen(A[0].palavra);

    for (i = 0; i < n; i++)
    {
        if (maior < strlen(A[i].palavra))
            maior = strlen(A[i].palavra);

        if (strlen(A[i].palavra) < 20)
        {
            for (j = strlen(A[i].palavra); j < 20; j++)
                A[i].palavra[j] = ' ';

            A[i].palavra[j - 1] = '\0'; // nao vai ser um problema pq comecamos a ordenar no radixsort a partir de 'd - 1'
        }
    }

    /*
    O setimo jogador exibe a saida requisitada, mostrando inicialmente o mesmo vetor de entrada com as palavras convertidas para minusculo.
    Depois deve mostrar um numero inteiro d que corresponde ao tamanho da maior palavra.
    Posteriormente, exibe as d linhas do vetor C do Counting sort. Para finalizar, deve mostrar a sublista do vetor ordenado de acordo
    com o especificado pelo terceiro jogador.
    */

    printf("%d\n", maior);

    radix_sort(A, maior, n);

    /*
    Finalizando, nas proximas M linhas, imprima as M palavras presentes a partir da
    P-esima posicao da lista ordenada, uma palavra a cada linha sem os caracteres adicionais
    (Obs: Nesta sub-lista ordenada as palavras nao tem o sinal de ponto final exibido no fim).
    */

    // removendo os caracteres adicionais
    for (i = 0; i < n; i++)
    {
        // indice 19 guarda o caractere nulo, logo eh valido comecar do indice 18 que eh quase certo que guardara um caractere != ' ' ou '\0'
        for (j = 18; A[i].palavra[j] == ' ' && j > -1; j--)
            if (A[i].palavra[j] == ' ')
                A[i].palavra[j] = '\0';

        strcpy(A[i].palavra, A[i].palavra);
    }

    // imprimindo as M palavras
    for (i = P - 1; i < (P + M - 1); i++)
        printf("%s\n", A[i].palavra);

    free(A);

    return 0;
}