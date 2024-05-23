/*
 * Nome: Harrison Caetano Candido. RA: 156264
 * Turma: Integral
 */

#include <stdio.h>
#include <unistd.h> // biblioteca para criar, manipular e gerenciar processos
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

/*
Criação de Processos e Gerenciamento (30%)

Descrição:

Nesta atividade, você implementará um programa que utiliza a função fork() para criar e gerenciar processos.
O programa deve permitir que você especifique, por meio de um parâmetro de linha de comando, quantos processos filhos
devem ser criados. Cada processo filho será responsável por calcular uma parte de uma somatória de uma lista de números
inteiros. O intervalo dos números a ser calculado por cada processo filho também deverá ser passado como parâmetro.
Você deve dividir a lista de números de forma equitativa entre os processos filhos, de modo que cada um calcule a soma
de um subconjunto específico.
Após o cálculo, os processos filhos devem se comunicar com o processo pai para enviar os resultados parciais.
O processo pai receberá os resultados parciais dos processos filhos e calculará a soma total combinando os valores
recebidos.
Certifique-se de encerrar os processos filhos corretamente, garantindo que todos sejam eliminados ao final da execução
do programa ou quando uma condição de saída especificada for alcançada.

Objetivo: O objetivo desta atividade é fornecer experiência prática na criação e gerenciamento de processos.
*/

// O no representa um item do somatorio
typedef struct node
{
    int value;
    struct node *prox;
} Tnode;
typedef Tnode *Pnode;

int process(int sons, int interval, int *list, int n);
Pnode create_node(int i);
int sum_nodes(Pnode p);
Pnode free_list(Pnode p);

Pnode create_node(int i)
{
    Pnode p;
    p = (Pnode)malloc(sizeof(Tnode));
    if (p == NULL)
        return NULL;

    p->value = i;
    p->prox = NULL;
    return p;
}

Pnode list_concatenate(Pnode l, Pnode n)
{
    // n se torna a cabeça se ele for o primeiro no
    if (l == NULL)
        return n;

    n->prox = l;

    return n;
}

// Faz a soma dos subconjuntos
int sum_nodes(Pnode p)
{
    int i;
    i = 0;
    while (p != NULL)
    {
        i = i + p->value;
        p = p->prox;
    }
    return i;
}

int process(int sons, int interval, int *list, int n)
{
    __pid_t pid;
    Pnode *pList;
    int total, i, new, j, s, f, status;

    s = total = 0;

    pList = (Pnode *)malloc(sizeof(Tnode) * sons);
    if (pList == NULL)
        return -1;

    for (i = 0; i < sons; i++)
        pList[i] = NULL;

    // O pid inicialmente eh 1, pois permite identificar o pai nas repetições do laco que cria os processos filhos
    pid = 1;

    // Vamos descobrir o tamanho da lista e comecar a separar a lista de traz para frente usando o tamanho de new
    new = n;
    new -= 1;

    // O(n)
    // Se new for menor do que zero, nos ja separamos todos os subconjuntos do somatorio em algum processo filho
    for (i = 0; new >= 0; i++)
    {
        // Reinicio o contador de filhos
        if (s == sons)
            s = 0;

        // Jogo cada item no vetor. Gracas a propriedade comutativa da soma, nao faz diferenca colocar invertido
        for (j = 0; j < interval && new - j >= 0; j++)
            pList[s] = list_concatenate(pList[s], create_node(list[new - j])); // Agora vou criar um no pra cada iteracao aqui, vou linkando esse no na lista desse filho

        // Vou para outra particao do tamanho do intervalo que o usuario quer
        new = new - interval;

        // Como ja iterei naquele intervalo, vou para o proximo filho
        s++;
    }

    printf("getpid() dad: %d\n", getpid());

    for (i = 0; i < sons & pid != 0; i++)
    {
        // Salvo o indice da posicao dessa lista no vetor de ponteiros para o filho utilizar
        f = i;

        pid = fork();
        // printf("Son\n");
        printf("pid: %d\n", pid);
        printf("getpid(): %d\n", getpid());
    }

    if (pid == 0)
    {
        printf("f: %d pid son: %d sum_nodes(): %d\n", f, getpid(), sum_nodes(pList[f]));
        exit(sum_nodes(pList[f]));
    }
    else
    {
        // Vamos esperar por qualquer processo filho que retornar
        while ((pid = waitpid(-1, &status, 0)) > 0)
            if (WIFEXITED(status))
            {
                printf("Processo filho %d terminou com status %d\n", pid, WEXITSTATUS(status));

                // Aqui somo os subconjuntos da soma retornados de cada processo filho
                total += WEXITSTATUS(status);
            }
    }

    // Apenas desaloco memoria aqui
    for (i = 0; i < s; i++)
        pList[i] = free_list(pList[i]);

    free(pList);

    printf("ultimo processo a finalizar | getpid(): %d\n", getpid());

    return total;
}

// Funcao que libera a lista dinamica
Pnode free_list(Pnode p)
{
    Pnode q;

    while (p != NULL)
    {
        q = p;
        p = p->prox;
        free(q);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int sons, interval, i, n;

    if (argc == 1)
    {
        printf("./ex01 <filhos> <intervalo> <semente>\n");
        return 0;
    }

    // Uso uma semente geradora de sequencia numerica para o rand
    srand(atoi(argv[3]));

    sons = atoi(argv[1]);

    interval = atoi(argv[2]);

    // Gero um tamanho aleatorio de lista
    n = rand() % 20;
    n += 1;

    printf("N: %d\n", n);

    int list[n];

    for (i = 0; i < n; i++)
    {
        // Gera um numero aleatorio entre 0 e 99
        list[i] = rand() % 100;
        printf("Lista [%d]: %d\n", i, list[i]);
    }

    // Se retornar -1, temos problema de alocacao de memoria
    printf("resultado: %d\n", process(sons, interval, list, n));

    return 0;
}