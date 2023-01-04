/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turno: Noturno
*/
/*
    Como vimos em aula, a complexidade do algoritmo quick_sort e na media O(n log n),
    o que faz dele um algoritmo de ordenacao eficiente. No entanto, essa eficiencia e atingida
    quando o tamanho n do problema e maior que 25, ou seja n > 25. Para valores
    menores que 25, outros algoritmos, como o insertion_sort, sao mais eficientes, pois
    realizam menos trocas que o quick_sort.
    Uma maneira de contornar esse problema do quick_sort e implementando um algoritmo
    que combine o quick_sort e insertion_sort. Nesse algoritmo, sempre que um
    subproblema tiver um tamanho m menor que um limiar t, previamente definido,
    invocamos o insertion_sort para resolver esse subproblema. Caso contrario, invocamos
    o quick_sort.
    Seguindo a descricao acima, implemente um algoritmo para ordenacao de pontos
    cartesianos (x, y) que combine o quick_sort e o Insertion sort. A ordenacao deve ser
    feita usando como comparacao a coordenada x dos pontos cartesianos.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct coordenada
{
    int x;
    int y;
} Tposvet;
typedef Tposvet *Pposvet;

int binary_search(Pposvet vet, int p, int x, int r);
void insertion_sort(Pposvet vet, int p, int n);
int partition(Pposvet vet, int p, int r);
void quick_sort(Pposvet vet, int t, int p, int r);

int binary_search(Pposvet vet, int p, int x, int r)
{
    int ini, meio, fim;
    ini = p;
    fim = r;

    while (ini <= fim)
    {
        meio = (ini + fim) / 2;

        if (x >= vet[meio].x) // direita, se x for maior do que o valor do meio ele anda pra direita pra buscar mais valores até estourar o while: isto é até quando ver que o vetor até a ultima posicao de fim esta ordenado ou até quando achar uma posição que x < vet[meio]
            ini = meio + 1;

        if (x < vet[meio].x) // esquerda, entao tem que colocar na posicao em que x é menor do que meio
            fim = meio - 1;
    }
    return ini; // O(log n)
}

void insertion_sort(Pposvet vet, int p, int n)
{
    int i, j, pos, auxx, auxy;

    for (j = p + 1; j < n; j++)
    {
        i = j - 1;
        auxx = vet[j].x;
        auxy = vet[j].y;

        pos = binary_search(vet, p, auxx, i); // O(log n)

        i = j;
        while (i > pos)
        {
            vet[i].x = vet[i - 1].x;
            vet[i].y = vet[i - 1].y;
            i = i - 1;
        }

        vet[pos].x = auxx;
        vet[pos].y = auxy;
    }
}
/*
    A ideia é basicamente chamar o insertion_sort para subvetores < t, logo e necessario chamar
    a verificacao para cada subvetor/subproblema
*/
void quick_sort(Pposvet vet, int t, int p, int r) // abordagem hibrida do quick_sort que deve ser chamada ate que todo o vetor seja ordenado
{
    int q;

    if (p < r)
    {
        if ((r - p + 1) < t)
            insertion_sort(vet, p, r + 1); // faz a ordenacao de todo o vetor caso seja adequado
        else
        {
            /* ordena a particao em questao de forma que os elementos a esquerda do pivo sejam
           menores do que ele enquanto que os a direita sejam maiores */
            q = partition(vet, p, r);

            quick_sort(vet, t, p, q - 1);
            p = q + 1; // essa parte ja esta ordenada teoricamente, faremos uma aproximacao cada vez mais para a direita a fim de encerrar a recursao

            quick_sort(vet, t, q + 1, r);
            r = q - 1; // essa parte ja esta ordenada teoricamente, faremos uma aproximacao cada vez mais para a esquerda a fim de encerrar a recursao

            quick_sort(vet, t, p, r); // vai julgar pelo tamanho novamente
        }
    }
}

int partition(Pposvet vet, int p, int r)
{
    int x, i, j, auxx, auxy;
    x = vet[r].x; // obtem o pivo x
    i = p - 1;

    for (j = p; j < r; j++)
        if (vet[j].x <= x)
        {
            i = i + 1;
            auxx = vet[i].x;
            auxy = vet[i].y;
            vet[i].x = vet[j].x;
            vet[i].y = vet[j].y;
            vet[j].x = auxx;
            vet[j].y = auxy;
        }

    auxx = vet[i + 1].x;
    auxy = vet[i + 1].y;
    vet[i + 1].x = vet[r].x;
    vet[i + 1].y = vet[r].y;
    vet[r].x = auxx;
    vet[r].y = auxy;

    return (i + 1);
}

/*
Nesse algoritmo, sempre que um subproblema tiver um tamanho m menor que um limiar t, previamente definido,
invocamos o insertion_sort para resolver esse subproblema. Caso contrario, invocamos o quick_sort.
*/

int main()
{
    int n, i, t;
    Pposvet vet;

    scanf("%d", &t); // A primeira linha contem o valor de um inteiro t. n < t que representa o limiar que determina se o insertion_sort sera invocado ou nao.

    scanf("%d", &n); // A segunda linha contem o valor de um inteiro positivo n que representa a quantidade de pontos cartesianos.

    vet = (Pposvet)malloc(n * sizeof(Tposvet));
    if (vet == NULL)
        return 0;

    // A terceira linha contem uma lista de inteiros que representa as coordenadas x de todos os n pontos cartesianos. Os numeros estao separados por um espaco em branco.
    for (i = 0; i < n; i++)
        scanf("%d", &vet[i].x);

    // A quarta linha contem uma lista de inteiros que representa as coordenadas y de todos os n pontos cartesianos. Os numeros estao separados por um espaco em branco.
    for (i = 0; i < n; i++)
        scanf("%d", &vet[i].y);

    quick_sort(vet, t, 0, n - 1);

    for (i = 0; i < n; i++)
        printf("(%d,%d) ", vet[i].x, vet[i].y);

    free(vet);

    return 0;
}
/*
2
5
1 4 2 4 5
2 5 3 3 2

5
10
6 3 4 6 2 4 4 6 1 2
0 5 9 1 8 2 3 4 7 6
*/