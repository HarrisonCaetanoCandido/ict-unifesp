/*
 * Nome: Harrison Caetano Candido. RA: 156264
 * Turma: Integral
 */

#include <stdio.h>
#include <stdlib.h>

/*
Descrição: Desenvolva um programa que simule os seguintes algoritmos de escalonamento de processos: First-Come,
First-Served (FCFS); Round Robin (RR) e; Shortest Job First (SJF).

Implemente cada um desses algoritmos de forma a poder compará-los facilmente.

Seu programa deve aceitar uma lista de processos, cada um com um tempo de chegada
e uma duração específica.

First-Come, First-Served (FCFS): Neste algoritmo, os processos são atendidos na ordem em que chegam, ou seja, o
primeiro a chegar é o primeiro a ser processado.

Round Robin (RR): Neste algoritmo, cada processo é atribuído um quantum de tempo fixo. Os processos são atendidos
em uma ordem circular, com cada processo sendo interrompido após o término de seu quantum para dar lugar ao próximo
na fila, retornando ao final da fila se necessário.

Shortest Job First (SJF): Neste algoritmo, os processos com as menores durações de execução são atendidos primeiro,
priorizando aqueles que podem ser concluídos mais rapidamente. Considere a possibilidade de ativar o modo preemptivo,
passando por parâmetro.

Ao simular esses algoritmos, analise o desempenho do sistema em relação a métricas como tempo de espera (quanto
tempo os processos ficam aguardando antes de serem processados), tempo de resposta (tempo entre a submissão do
processo e a primeira resposta), tempo de processamento (tempo total necessário para concluir o processo) e o tempo de
turnaround (tempo transcorrido desde o momento em que o processo entra e o instante em que termina sua execução).
Objetivo: O objetivo desta atividade é ajudá-lo a entender como diferentes algoritmos de escalonamento funcionam e como
eles influenciam o desempenho do sistema operacional.
*/

typedef struct process
{
    int pid;
    int turnaround;   // quantidade de tempo para executar o processo
    int arrival_time; // tempo de chegada do processo
} Tprocess;

typedef Tprocess *Pprocess;

void fcfs(Pprocess p, int n);
void round_robin(Pprocess p, int quantum, int n);
int compare(const void *p, const void *q);
void sjf(Pprocess p, int preemptive, int n);

void fcfs(Pprocess p, int n)
{
    int i, waiting_time, actual_time, answer_time, total_waiting_time, total_turnaround;
    float average_waiting_time, average_answer_time;

    actual_time = total_turnaround = answer_time = waiting_time = total_waiting_time = 0;

    // Vamos percorrer toda a lista de processos na execucao
    for (i = 0; i < n; i++)
    {
        printf("---- Process %d ----\n", p[i].pid);

        // Iniciamos com o calculo do tempo de espera do processo
        waiting_time = actual_time - p[i].arrival_time;

        if (waiting_time < 0)
            waiting_time = 0;

        printf("waiting time: %d\n", waiting_time);
        printf("actual time: %d\n", actual_time);
        printf("answer time: %d\n", answer_time);

        // Aqui calculamos o tempo de resposta do processo
        answer_time = waiting_time + p[i].turnaround;

        total_waiting_time += waiting_time;
        total_turnaround += answer_time;

        actual_time += p[i].turnaround;
        printf("turnaround: %d\n", answer_time);

        printf("total turnaround: %d\n", total_turnaround);
    }

    average_answer_time = (float)total_turnaround / n;
    average_waiting_time = (float)total_waiting_time / n;

    printf("Tempo medio de espera: %.2f\n", average_waiting_time);
    printf("Tempo medio de turnaround %.2f\n", average_answer_time);
}

void round_robin(Pprocess p, int quantum, int n)
{
    int i, waiting_time, actual_time, answer_time, total_waiting_time, total_turnaround, *time_left, remaining_processes;
    float average_answer_time;

    actual_time = total_turnaround = answer_time = waiting_time = total_waiting_time = 0;
    remaining_processes = n;

    // Esse vetor mantem o tempo restante de cada processo
    time_left = (int *)malloc(n * sizeof(int));
    if (time_left == NULL)
        return;

    // O time left eh importante, pois numa fila de round robin mesmo os processos sendo executados
    // no tempo de um quantum, ainda podem existir instrucoes a serem executadas para que o processo
    // seja realmente concluido. Portanto, vamos salvar os turnarounds para fazer as interrupcoes
    for (i = 0; i < n; i++)
        time_left[i] = p[i].turnaround;

    // Vamos fazer a computacao enquanto existirem processos com tempo de execucao maior que 0
    while (remaining_processes > 0)
        for (i = 0; i < n; i++)
            if (time_left[i] > 0)
            {
                printf("---- Process %d ----\n", p[i].pid);

                waiting_time = actual_time - p[i].arrival_time;

                if (waiting_time < 0)
                    waiting_time = 0;

                printf("waiting time: %d\n", waiting_time);
                printf("actual time: %d\n", actual_time);
                printf("answer time: %d\n", answer_time);

                answer_time = waiting_time + (quantum < time_left[i] ? quantum : time_left[i]);

                // Se o tempo restante de processamento eh maior que o quantum, o processo
                // sera interrompido antes de concluir seu tempo de execucao total dentro de um quantum
                // Se o tempo restante for menor ou igual ao quantum atual, significa que o
                // processo sera concluido dentro do quantum
                // Dessa forma garantimos que time_left nunca seja negativo
                time_left[i] -= quantum < time_left[i] ? quantum : time_left[i];
                actual_time += quantum;

                // Se o processo foi concluido, entao decrementamos da quantidade de processos para conclusao
                if (time_left[i] <= 0)
                    remaining_processes--;

                total_turnaround += answer_time;

                printf("turnaround: %d\n", answer_time);
                printf("total turnaround: %d\n", total_turnaround);
            }

    average_answer_time = (float)total_turnaround / n;

    printf("Tempo medio de turnaround %.2f\n", average_answer_time);

    free(time_left);
}

// Compare eh utilizada para determinar qual eh a chave de comparacao do quicksort
int compare(const void *p, const void *q)
{
    Pprocess p1 = (Pprocess)p;
    Pprocess p2 = (Pprocess)q;

    return p1->turnaround - p2->turnaround;
}

void sjf(Pprocess p, int preemptive, int n)
{
    int i, waiting_time, actual_time, answer_time, total_waiting_time, total_turnaround;
    float average_waiting_time, average_answer_time;

    actual_time = total_turnaround = answer_time = waiting_time = total_waiting_time = 0;

    // Se preemptive for 1, usamos o SJF preemptivo
    if (preemptive == 1)
        // Ordena os processos com base no tempo de turnaround
        qsort(p, n, sizeof(Tprocess), compare);

    for (i = 0; i < n; i++)
    {
        printf("---- Process %d ----\n", p[i].pid);

        // Inicia o cálculo do tempo de espera do processo
        waiting_time = actual_time - p[i].arrival_time;

        if (waiting_time < 0)
            waiting_time = 0;

        printf("waiting time: %d\n", waiting_time);
        printf("actual time: %d\n", actual_time);
        printf("answer time: %d\n", answer_time);

        // Calcula o tempo de resposta do processo
        answer_time = waiting_time + p[i].turnaround;

        // Calculo o tempo atual com base no turnaround atual e de processos anteriores
        actual_time += p[i].turnaround;

        total_waiting_time += waiting_time;
        total_turnaround += answer_time;

        printf("turnaround: %d\n", answer_time);
        printf("total turnaround: %d\n", total_turnaround);
    }

    average_answer_time = (float)total_turnaround / n;
    average_waiting_time = (float)total_waiting_time / n;

    printf("Tempo medio de espera: %.2f\n", average_waiting_time);
    printf("Tempo medio de turnaround %.2f\n", average_answer_time);
}

int main(int argc, char *argv[])
{
    Pprocess p;
    int i, n, quantum;

    if (argc == 1)
    {
        printf("./main <numero de processos>\n");
        return 0;
    }

    // determino o tamanho da lista
    n = atoi(argv[1]);

    // Crio minha lista de processos
    p = (Pprocess)malloc(sizeof(Tprocess) * n);
    if (p == NULL)
        return 0;

    for (i = 0; i < n; i++)
    {
        // salvo o pid aqui
        p->pid = i;

        printf("Digite o tempo de chegada do processo %d: ", i);
        scanf("%d", &p[i].arrival_time);

        printf("Digite o tempo de processamento do processo %d: ", i);
        scanf("%d", &p[i].turnaround);

        printf("%d %d\n", p[i].arrival_time, p[i].turnaround);
    }

    // Simula o algoritmo FCFS
    printf("---- First-Come, First-Served (FCFS) ----\n");
    fcfs(p, n);

    printf("---- Round Robin ----\n");

    printf("Digite o quantum: ");
    scanf("%d", &quantum);

    round_robin(p, quantum, n);

    printf("---- Shortest Job First (SJF) Não Preemptivo ----\n");
    sjf(p, 0, n);

    printf("---- Shortest Job First (SJF) Preemptivo ----\n");
    sjf(p, 1, n);

    free(p);

    return 0;
}

/*
0 10
2 5
4 8

0 10
10 11
11 13
13 14
14 19
*/