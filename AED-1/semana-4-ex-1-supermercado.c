/*
    Nome: Harrison Caetano Candido
    RA: 156264
    Turma: Integral
*/
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

#include <stdio.h>
#include <stdlib.h>

// --------------------------------------- FUNCIONARIO

typedef struct fila_FUNCIONARIO
{
    int vi;
    int tempo;
} Funcionario;

// ---------------------------------------- CLIENTE
typedef struct fila_CLIENTE
{
    int *cj;
    int n;
    int ini;
} Cliente; // FILA

//---------------------------------------  FUNCOES
Funcionario *cria_funcionario(int N);
Cliente *Ccria_fila();
void inserir(Funcionario *fun, int N, Cliente *cli, int M);
void saida(Funcionario *fun, int N, Cliente *cli, int *soma);
void diminuivet(Funcionario *fun, int N, int *menor, int indice_menor);
int remover(Cliente *cli);

Funcionario *cria_funcionario(int N)
{
    Funcionario *p = (Funcionario *)malloc(N * sizeof(Funcionario));
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
    int N, M, soma = 0;

    scanf("%d", &N); // Quantidade de funcionarios

    scanf("%d", &M); // Quantidade de clientes

    Funcionario *fun;
    Cliente *cli;

    fun = cria_funcionario(N);
    cli = Ccria_fila();

    if (fun == NULL || cli == NULL)
    {
        return 0;
    }

    inserir(fun, N, cli, M);

    saida(fun, N, cli, &soma);

    printf("%d", soma);

    free(cli->cj);
    free(fun);
    free(cli);

    return 0;
}

void inserir(Funcionario *fun, int N, Cliente *cli, int M)
{
    int fim;

    for (fim = 0; fim < N; fim++)
    {

        scanf("%d", &fun[fim].vi); // escaneia o tempo de execucao do primeiro funcionario

        fun[fim].tempo = 0;
    }

    cli->cj = (int *)malloc(M * sizeof(int));

    if (cli->cj == NULL)
    {
        return;
    }

    while (cli->n != M)
    {
        fim = (cli->ini + cli->n) % M;

        scanf("%d", &cli->cj[fim]); // escaneia a quantidade de itens do cliente i

        ++(cli->n);
    }
}

void saida(Funcionario *fun, int N, Cliente *cli, int *soma)
{
    int i, r_cliente, *menor, *maior, indice_menor, aux = 0;

    // -------- VAMOS VERIFICAR QUEM TERMINA MAIS RAPIDO E IR DESENFILEIRANDO E SUBSTITUINDO O TEMPO --------

    while (cli->n != 0)
    {
        indice_menor = 0;      // 0
        menor = &fun[0].tempo; // 0

        for (i = 0; i < N; i++) // [0] = 5, [1] = 6 , [2] = 12 | [0] = 10 , [1] = 1 ,[2] = 7
        {
            if (*menor > fun[i].tempo) // ate ele descobrir um menor
            {
                menor = &fun[i].tempo;
                indice_menor = i; // indice do menor
            }
        }

        // ------------------------------------------------- ATE AQUI SO ACHAMOS O *MENOR ---------------------------------------------------

        aux = aux + *menor; // vai guardar nosso menor tempo ,0 + 5 = 5 + 1 = 6

        diminuivet(fun, N, menor, indice_menor); // desconta o tempo decorrido de todas as posicoes de funcionario

        r_cliente = remover(cli); // remove da fila cliente

        fun[indice_menor].tempo = fun[indice_menor].vi * r_cliente; // [0] = 10 , [1] = 1 ,[2] = 7 | [0] = 9 , [1] = 24 ,[2] = 6
    }
    // -------------------------------------------------------------------------------------------------------------------------
    //                                      PEGAR O MAIOR VALOR DE TEMPO E SOMAR EM *SOMA

    maior = &fun[0].tempo;
    for (i = 0; i < N; i++) // [0] = 9 , [1] = 24 ,[2] = 6
    {
        if (fun[i].tempo > *maior)
        {
            maior = &fun[i].tempo;
        }
    }

    // -------------------------------------------------------------------------------------------------------------------------

    *soma = *maior + aux; // aux = 6 + 24 = 30
}

int remover(Cliente *p)
{
    int inicio;
    inicio = p->ini;       // 0
    p->ini = (p->ini) + 1; // proximo ini , 1
    --(p->n);
    return p->cj[inicio];
}

void diminuivet(Funcionario *fun, int N, int *menor, int indice_menor)
{
    int i;
    for (i = 0; i < N; i++) // [0]=5,[1]=6,[2]=12
    {
        if (indice_menor != i) // indice_menor que eh a posicao do menor valor
        {
            fun[i].tempo = (fun[i].tempo) - (*menor); // [0]=5, [1]= 6-5 = 1 ,[2] = 12-5 = 7 | [0] = 10-1 = 9 , [1] = 1 ,[2] = 7-1 = 6
        }
    }
}