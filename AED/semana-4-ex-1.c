/*
Hoje é a inauguração de um grande supermercado em sua cidade, e todos estão muito
excitados com os baixos preços prometidos.

Este supermercado tem N funcionários que trabalham no caixa, identificados por números
de 1 a N, em que cada funcionário leva um determinado tempo vi para processar um item
de um cliente. Ou seja, se um cliente tem cj itens em sua cesta, um determinado funcionário
levará vi*cj segundos para processar todos os itens deste cliente.
Quando um cliente entra na fila para ser atendido ele espera até que um funcionário esteja
livre para o atendê-lo. Se mais de um funcionário estiver livre ao mesmo tempo, o cliente
será atendido pelo funcionário de menor número de identificação. Tal funcionário só estará
livre novamente após processar todos os itens deste cliente.
Há M clientes na fila para serem atendidos, cada um com um determinado número de itens
na sua cesta. Dadas as informações sobre os funcionários nos caixas e os clientes, o
gerente pediu sua ajuda para descobrir quanto tempo levará para que todos os clientes
sejam atendidos.
Este exercício deverá ser implementado utilizando a estrutura de dados do tipo Fila
Sequencial!!! Vocês deverão alocar a estrutura do tipo Fila e utilizar funções para a sua
manipulação, assim com uma função para calcular a saída (que deverá receber como
parâmetro as duas filas criadas). Cada cliente atendido deverá sair da fila!
*/

// Supermercado com N funcionarios que trabalham no caixa, identificados de 1 a N;
// Cada funcionario leva um tempo vi para processar um item de um cliente;
// Se um cliente tem cj itens na sua cesta, um determinado funcionario levara vi*cj segundos para processar;
// Cliente entra na fila para ser atendido, espera ate que um funcionario esteja livre para atende-lo;
// Se mais de um funcionario estiver livre ao mesmo tempo, o cliente sera atendido pelo funcionario de menor n identificacao, tal funcionario so estara livre apos ler todos os itens deste cliente;
// Há M clientes na fila para serem atendidos, cada um com determinado numero de itens na sua cesta;
// Aparentemente sao duas filas;

// Quanto tempo levara para que todos os clientes sejam atendidos?

#include <stdio.h>
#include <stdlib.h>

// --------------------------------------- FUNCIONARIO
typedef struct vet_FUNCIONARIO
{
    int vi;
    int tempo;
} Func;

typedef struct fila_FUNCIONARIO
{
    Func *f; // aloca um bloco de memoria para que ele se torne um vetor de ponteiros do tipo Func
    int n;
    int ini;
} Funcionario; // FILA

// ---------------------------------------- CLIENTE
typedef struct fila_CLIENTE
{
    int *cj;
    int n;
    int ini;
} Cliente; // FILA

//---------------------------------------  FUNCOES
Funcionario *Fcria_fila();
Cliente *Ccria_fila();
void inserir(Funcionario *fun, int N,Cliente *cli, int M);
void saida(Funcionario *fun, int N, Cliente *cli, int M, int *soma);
int comparar(Funcionario *fun, int N);
void diminuivet(Funcionario *fun, int *menor, int indice_menor, int N);
int remover(Cliente *cli, int M);

Funcionario *Fcria_fila()
{
    Funcionario *p = (Funcionario *)malloc(sizeof(Funcionario));
    p->n = 0;
    p->ini = 0;
    return p;
}

Cliente *Ccria_fila()
{
    Cliente *p = (Cliente *)malloc(sizeof(Cliente));
    p->n = 0;
    p->ini = 0;
    return p;
}

int main()
{
    int N, M, i, soma = 0;

    scanf("%d", &N); // Quantidade de funcionarios

    while (N < 1 || N > 10000)
    {
        scanf("%d", &N); // Quantidade de funcionarios novamente
    }

    scanf("%d", &M); // Quantidade de clientes

    while (M < 1 || M > 10000)
    {
        scanf("%d", &M); // Quantidade de clientes novamente
    }

    Funcionario *fun;
    Cliente *cli;

    fun = Fcria_fila();
    cli = Ccria_fila();

    if (fun == NULL || cli == NULL)
    {
        return 0;
    }

    inserir(fun, N,cli, M);

    saida(fun, N, cli, M, &soma);

    printf("%d", soma);

    free(fun->f);
    free(cli->cj);
    free(fun);
    free(cli);

    return 0;
}

void inserir(Funcionario *fun, int N,Cliente *cli, int M) // Aqui digitamos apenas o tamanho das filas
{
    int fim;

    fun->f = (Func *)malloc(N * sizeof(Func)); // aloca memoria para uma struct que tem o campo vi

    while ((fun->ini + fun->n) != N) // Pode ser que nao seja pra usar laco e sim 'fim'
    {
        fim = (fun->ini + fun->n) % N;

        scanf("%d", &fun->f[fim].vi); // escaneia o tempo de execucao do primeiro funcionario

        while ((fun->f[fim].vi) < 1 || (fun->f[fim].vi) > 100)
        {
            scanf("%d", &fun->f[fim].vi); // escaneia o tempo de execucao do primeiro funcionario novamente
        }

        fun->n++;
    }

    cli->cj = (int *)malloc(M * sizeof(int));

    while ((cli->ini + cli->n) != M) 
    {
        fim = (cli->ini + cli->n) % M;

        scanf("%d", &cli->cj[fim]); // escaneia a quantidade de itens do cliente i

        while ((cli->cj[fim]) < 1 || (cli->cj[fim]) > 100)
        {
            scanf("%d", &cli->cj[fim]); // escaneia a quantidade de itens do cliente i novamente
        }

        cli->n++;
    }
}

void saida(Funcionario *fun, int N, Cliente *cli, int M, int *soma)
{
    int i, r_cliente, cont = 0, *menor, j = 0, indice_menor, indice_m_foi = N;

    i = 0;

    if (N > M) // caso a fila fun seja maior que cli
    {
        while (i < M) // significa que nao percorremos toda a fila funcionario
        {

            r_cliente = remover(cli, M);

            fun->f[i].tempo = fun->f[i].vi * r_cliente; // vetor do produto

            *soma = *soma + fun->f[i].vi * r_cliente;

            i++; // 1, 2, 3, 4 | 4
            cont++;
        }
    }
    if (N < M) // caso a fila cli seja maior que fun
    {
        while (i < N) // significa que nao percorremos toda a fila funcionario
        {

            r_cliente = remover(cli, M);

            fun->f[i].tempo = fun->f[i].vi * r_cliente; // vetor do produto

            *soma = *soma + fun->f[i].vi * r_cliente;

            i++; 
            cont++;
        }
    }

    while (cont != M)
    {
        indice_menor = 0;
        menor = &fun->f[0].tempo;

        for (j = 0; j < N; j++)
        {
            if (*menor > fun->f[j].tempo) // ate ele descobrir um menor
            {
                menor = &fun->f[j].tempo;
                indice_menor = j; // indice do menor
                indice_m_foi++;
            }
        }

        if (indice_m_foi == N) // significa que nao achou nenhum valor na struct menor do que *menor
        {
            indice_menor = comparar(fun, N);
        }

        diminuivet(fun, menor, indice_menor, N);

        r_cliente = remover(cli, M);

        fun->f[indice_menor].tempo = fun->f[indice_menor].vi * r_cliente; // vetor do produto

        *soma = *soma + fun->f[indice_menor].vi * r_cliente;

        cont++;
    }
}

int remover(Cliente *p, int M)
{
    int inicio;
    inicio = p->ini;
    p->ini = ((p->ini) + 1) % M; // proximo ini
    --(p->n);
    return p->cj[inicio];
}

int comparar(Funcionario *fun, int N)
{
    int k, j;
    for (k = 0; k < N; k++)
    {
        for (j = 1; j < N; j++)
        {
            if (fun->f[k].tempo == fun->f[j].tempo && k != j && k < j)
            {
                return k;
            }
        }
    }
    return 0;
}

void diminuivet(Funcionario *fun, int *menor, int indice_menor, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (indice_menor != i) // indice_menor que eh a posicao do menor valor
        {
            fun->f[i].tempo = (fun->f[i].tempo) - (*menor);
        }
    }
}