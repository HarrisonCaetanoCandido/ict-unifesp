/*
 * Nome: Felipe Martins de Paula RA:140777
 * Nome: Harrison Caetano Candido RA:156264
 * Nome: Pedro Figueiredo Dias RA:156333
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PAG_SIZE 4096
#define TRUE 1
#define FALSE 0

/*
 * Um algoritmo de substituicao de paginas eh utilizado pelo SO quando ha uma falta
 * de pagina, em que ele escolhe uma pagina a ser removida da memoria a fim de liberar
 * espaco para uma nova pagina a ser trazida para a memoria. Se a pagina removida tiver
 * sido modificada enquanto esteve na memoria, ela devera ser reescrita no swap com o
 * proposito de atualizar a copia virtual la existente. Se, contudo, a pagina nao
 * tiver sido modificada (por ex: uma pagina de codigo), a copia em swap ja estara atualizada e,
 * assim nao sera necesario reescreve-la. A pagina a ser trazida para a memoria simplesmente sobrepoe
 * a pagina que esta sendo destituida
 */

/*
 * Uma pagina pode ser modelada adequadamente atraves de um registro (struct), por tanto, para
 * representar as memórias MR, MV e MS, um conjunto de páginas agrupadas e acessadas a partir de
 * vetores, matrizes ou estruturas de dados.
 */

// Esse cara abaixo constitui a tabela de paginas para fazer o Mapeamento. Eh a memoria virtual
typedef struct Ptp
{
    unsigned char referenciada : 1; // Campo de 1 bit que indica se a pagina foi referenciada recentemente. Esse bit eh usado por algoritmos de substituicao de pagina para identificar paginas que não foram acessadas por um longo periodo de tempo
    unsigned char modificada : 1;   // Campo de 1 bit que indica se a pagina foi modificada desde a ultima vez que foi carregada na memoria. Esse bit eh usado para identificar paginas que foram alteradas e precisam ser gravadas de volta no armazenamento secundario
    unsigned char pres_aus : 1;     // bit de presente ou ausente (1 e 0 respectivamente) na memoria real
    unsigned char pad : 5;          // Eh um campo de 5 bits reservado para preenchimento e alinhamento da estrutura
    unsigned short moldura_pag;     // Eh o local fisico onde a pagina na virtual esta armazenada na memoria. Nesse caso um indice
    unsigned short end_swap;        // Eh o endereco de memoria em swap
} Pagina_tab_pag;
typedef Pagina_tab_pag *Ptp;

// Essa struct representa tanto uma pagina virtual quanto uma moldura de pagina
typedef struct Pagina
{
    unsigned short endereco;    // Endereco seja da mem real ou virtual
    unsigned short entrada_tab; // Entrada na tabela de paginas
    char dados[5];              // Guarda dados aleatorios
} Tpagina;
typedef Tpagina *Ppagina;

typedef struct No_fila
{
    Ppagina no;           // Aponta para uma pagina
    struct No_fila *prox; // Aponta para um outro no do mesmo tipo que guarda uma pagina
} Tno_fila;
typedef Tno_fila *Pno_fila;

// A fila precisa guardar paginas
typedef struct fila
{
    Pno_fila inicio;
    Pno_fila fim;
    int n;
} Tfila;
typedef Tfila *Pfila;

// tam. memoria virtual, tam. memoria real, tam. memoria swap, semente e qtd de interacoes
int MV_SIZE, MR_SIZE, MS_SIZE, SEED, ITER;

// Uso geral
void iniciar_tp(Ptp tp);
int posicao_memoria(char tipo[], int endereco);
void atualizar_bits_status(Ptp tp, int qtd_mv_pages);

// Algoritmos FIFO e SC
Pfila iniciar_fifo(Pfila fila);
void percorre_fila(Pfila fila);

// Algoritmo First In, First Out
void push(Pfila fila, Ppagina pv);
Ppagina pop(Pfila fila);
void fifo(char algoritmo[], int *cont_page_miss);
void libera_fifo(Pfila fila);

// Algoritmo NUR
void nur(int *cont_page_miss);

// Algoritmo Second Chance
void push_sc(Pfila fila, Ppagina pv);
Ppagina pop_sc(Pfila fila, Ptp tp);
void libera_sc(Pfila fila);

// --------------------------------------- Geral ---------------------------------------
void iniciar_tp(Ptp tp)
{
    int qtd_mv_pages, i;

    // -------------------------- Inicializacao da TP --------------------------
    qtd_mv_pages = MV_SIZE / PAG_SIZE;
    for (i = 0; i < qtd_mv_pages; i++)
    {
        // Inicializo a tabela de paginas
        tp[i].referenciada = FALSE;
        tp[i].modificada = FALSE;
        tp[i].pres_aus = FALSE;
        tp[i].end_swap = PAG_SIZE * (1 + i); // Endereco virtual
        tp[i].moldura_pag = -1;              // So estamos inicializando a tabela de paginas
    }
}

void atualizar_bits_status(Ptp tp, int qtd_mv_pages)
{
    int i;

    // Define aleatoriamente os bits de status das paginas virtuais antes de simular
    for (i = 0; i < qtd_mv_pages; i++)
    {
        tp[i].referenciada = rand() % 2;
        tp[i].modificada = rand() % 2;
    }
}

// Funcao que faz a conversao do endereco virtual ou fisico para o indice dos vetores (memorias)
int posicao_memoria(char tipo[], int endereco)
{
    int i, pagina, qtd_paginas, M_SIZE;

    M_SIZE = 0;

    if (strcmp(tipo, "memoria_virtual") == 0)
        M_SIZE = MV_SIZE;

    if (strcmp(tipo, "memoria_real") == 0)
        M_SIZE = MR_SIZE;

    if (strcmp(tipo, "memoria_swap") == 0)
        M_SIZE = MS_SIZE;

    if (M_SIZE == 0)
        return -1;

    // Descubro a quantidade de paginas na memori, ou seja, a quantidade de iteracoes
    qtd_paginas = M_SIZE / PAG_SIZE;

    for (i = 0; i < qtd_paginas; i++)
    {
        // Faco a conversao para saber qual a quantidade de bytes limite dessa pagina
        pagina = PAG_SIZE * (1 + i);

        // Verifico se a pagina convertida tem a quantidade de bytes necessaria para encaixar a pagina a ser carregada
        if (endereco <= pagina)
            // Perceba que com essa logica o i eh exatamente a posicao do vetor que corresponde a faixa de bytes necessaria
            return i;
    }
    return -1;
}
// -------------------------------------------------------------------------------------

// ------------------------------------- FIFO e SC -------------------------------------
Pfila iniciar_fifo(Pfila fila)
{
    fila = (Pfila)malloc(sizeof(Tfila));
    if (fila == NULL)
        return NULL;

    fila->inicio = fila->fim = NULL;
    fila->n = 0;

    return fila;
}

void percorre_fila(Pfila fila)
{
    Pno_fila p, q;
    p = fila->inicio;
    q = fila->fim;

    if (p == NULL)
        return;

    do
    {
        printf("\tendereco: %d | entrada_tab: %d | dados: %s\n", p->no->endereco, p->no->entrada_tab, p->no->dados);
        p = p->prox;
    } while (p != NULL && p != q->prox);
}
// -------------------------------------------------------------------------------------

// ---------------------------------------- FIFO ---------------------------------------
void push(Pfila fila, Ppagina pv)
{
    Pno_fila no;

    no = (Pno_fila)malloc(sizeof(Tno_fila));
    if (no == NULL)
        return;

    no->no = pv;

    if (fila->n == 0)
    {
        fila->inicio = fila->fim = no;
        no->prox = NULL;
        fila->n += 1;
    }
    else
    {
        fila->fim->prox = no;
        fila->fim = no;
        no->prox = NULL;
        fila->n += 1;
    }
}

Ppagina pop(Pfila fila)
{
    Ppagina inicio = NULL;
    Pno_fila p;

    if (fila->inicio != NULL)
    {
        p = fila->inicio;
        inicio = p->no;
        fila->inicio = fila->inicio->prox;
        --(fila->n);
        free(p);
    }
    return inicio;
}

void libera_fifo(Pfila fila)
{
    Pno_fila p, q;
    p = fila->inicio;

    while (p != NULL)
    {
        q = p;
        p = p->prox;
        free(q);
    }
}

void fifo(char algoritmo[], int *cont_page_miss)
{
    int i, aux, j, qtd_mv_pages, qtd_mr_pages, qtd_ms_pages, unid_ender, s_end;
    char prefixo[3] = {"Ax\0"};
    Pfila fila;
    Ppagina mr, ms, p, paux, pv;
    Ptp tp;
    time_t tempo_inicial, tempo_atual;

    qtd_mv_pages = MV_SIZE / PAG_SIZE;
    qtd_mr_pages = MR_SIZE / PAG_SIZE;
    qtd_ms_pages = MS_SIZE / PAG_SIZE;

    mr = (Ppagina)malloc(sizeof(Tpagina) * qtd_mr_pages);
    if (mr == NULL)
        return;

    ms = (Ppagina)malloc(sizeof(Tpagina) * qtd_ms_pages);
    if (ms == NULL)
        return;

    tp = (Ptp)malloc(sizeof(Pagina_tab_pag) * qtd_mv_pages);
    if (tp == NULL)
        return;

    paux = (Ppagina)malloc(sizeof(Tpagina));
    if (paux == NULL)
        return;

    iniciar_tp(tp);

    fila = iniciar_fifo(fila);

    /* -------------------------- Preencher a Memoria Real Totalmente --------------------------
     *
     *  Quando a CPU referencia um endereco virtual, ele eh tratado pela MMU.
     *  Se o endereco virtual em questao estiver indicado na tabela de paginas como ausente em memoria
     *  temos entao page-miss, essa pagina virtual deve entao ser carregada na memoria real.
     *  Caso a memoria real esteja cheia e tenha ocorrido page-miss, temos entao que utilizar algum
     *  algoritmo de substituicao de pagina para liberar espaco na memoria real.
     *  Observe que para paginas que forem removidas da mr por conta de page-miss terao que ser salvas
     *  temporariamente em swap e, quando forem referenciadas, deverao retornar a memoria real, podendo
     *  ocorrer novamente page-miss levando a um tratamento por substituicao de paginas mais uma vez.
     */

    aux = i = j = 0;
    for (i; i < qtd_mv_pages || aux < qtd_mr_pages; i++)
    {
        // A CPU comeca a referenciar enderecos virtuais aleatorios a MMU
        unid_ender = rand() % qtd_mv_pages;

        printf("Endereco virtual: %d. unid_ender virtual: %d Bytes\n", unid_ender, unid_ender * PAG_SIZE);

        if (tp[unid_ender].referenciada == FALSE) // Se a pagina nao foi referenciada ainda, vamos tentar carrega-la na RAM
        {
            tp[unid_ender].referenciada = TRUE; // Agora que verificamos eh TRUE
            tp[unid_ender].moldura_pag = -1;    // 65535 quando nao mapeada na mr

            printf("Iteracao %d | Pagina virtual [%d] foi referenciada agora pela primeira vez pela CPU.\n", i, unid_ender);

            if (aux < qtd_mr_pages)
            {
                // ------ Preencho a Memoria Real a Partir de 0 ------
                sprintf(mr[i].dados, "%s%d", prefixo, rand() % qtd_mv_pages); // Aqui gera strings aleatorias e salva como dado
                mr[i].endereco = PAG_SIZE * (1 + i);                          // Guardo o endereco em bytes
                mr[i].entrada_tab = unid_ender;

                // Push na fila de memoria real
                if (strcmp(algoritmo, "fifo\0") == 0)
                    push(fila, &mr[i]);

                if (strcmp(algoritmo, "sc\0") == 0)
                    push_sc(fila, &mr[i]);

                tp[unid_ender].pres_aus = TRUE; // Digo que a pagina virtual esta presente numa moldura de pagina na memoria real
                tp[unid_ender].moldura_pag = i; // Moldura de pagina na memoria real salva na pagina virtual em questao
                tp[unid_ender].end_swap = -1;   // Nao esta na swap mais
                ++(aux);
            }
            else
            {
                // Digo que a pagina virtual nao esta presente numa moldura de pagina na memoria real
                tp[unid_ender].pres_aus = FALSE;
                tp[unid_ender].end_swap = PAG_SIZE * (1 + j);

                // Preencho a memoria swap com paginas que nao podem ser carregadas na RAM
                sprintf(ms[j].dados, "%s%d", prefixo, rand() % qtd_mv_pages); // Aqui gera strings aleatorias e salva como dado
                ms[j].endereco = PAG_SIZE * (1 + j);
                ms[j].entrada_tab = unid_ender;
                ++(j);
            }
        }
        else if (tp[unid_ender].referenciada == TRUE) // Se a pagina ja foi referenciada, entao eu continuo nessa iteracao ate encontrar outro endereco valido
        {
            printf("Iteracao %d | Pagina virtual [%d] ja foi referenciada alguma vez pela CPU.\n", i, unid_ender);
            --(i); // Decrementa para a CPU continuar buscando por enderecos aleatorios que nao referenciou
            continue;
        }
    }

    printf("\nAo percorrer toda a memoria real temos:\n");
    for (i = 0; i < qtd_mr_pages; i++)
        printf("\tmr[%d].dados = %s | mr[%d].endereco = %d | mr[%d].entrada_tab = %d\n", i, mr[i].dados, i, mr[i].endereco, i, mr[i].entrada_tab);

    printf("\nAo percorrer toda a tabela de paginas temos (Enxergue 65553 como X):\n");
    for (i = 0; i < qtd_mv_pages; i++)
        printf("\ttp[%d].pres_aus = %d | tp[%d].moldura_pag = %d | tp[%d].end_swap = %d\n", i, tp[i].pres_aus, i, tp[i].moldura_pag, i, tp[i].end_swap);

    printf("\nAo percorrer toda a memoria swap temos:\n");
    for (i = 0; i < qtd_ms_pages; i++)
        printf("\tms[%d].endereco: %d | ms[%d].entrada_tab: %d | ms[%d].dados: %s\n", i, ms[i].endereco, i, ms[i].entrada_tab, i, ms[i].dados);

    printf("\nAo percorrer toda a fila da MR temos:\n");
    percorre_fila(fila);

    /*
     * Entre uma interrupcao de tempo e outra, um subconjunto aleatorio de paginas H,
     * sendo H um subconjunto de MV, eh referenciado em memoria e,
     * eventualmente, uma das paginas precisa ser substituida.
     *
     * O laco while abaixo busca por Page Miss ou Hit ao gerar aleatoriamente enderecos de memoria
     */

    printf("\n-------------------------- Memoria real cheia --------------------------\n\n");

    // Gera inicialmente os bits de status de cada pagina virtual
    atualizar_bits_status(tp, qtd_mv_pages);

    printf("-------------------------- CPU Referencia PV --------------------------\n\n");
    i = aux = s_end = 0;
    while (i < ITER) // Iteramos pelo tamanho maximo da memoria swap apenas para teste
    {
        tempo_inicial = time(NULL); // Recebe o tempo inicial da maquina

        printf("-------------------------- Iteracao %d --------------------------\n\n", i);
        // 1. CPU Referencia Aleatoriamente uma PV => No caso a funcao rand gera enderecos aleatorios para referenciar uma pagina virtual
        unid_ender = rand() % qtd_mv_pages;

        printf("endereco virtual: %d. unid_ender virtual: %d Bytes\n", unid_ender, unid_ender * PAG_SIZE);

        // 2. Identifica Page Miss pela Tabela de Pagina => No caso a PV eh dita como inexistente na MR pelo campo pres_aus da struct
        if (tp[unid_ender].pres_aus == FALSE)
        {
            printf("Houve Page Miss na pagina virtual de endereco virtual: %d. Endereco na swap: %d\n", unid_ender, tp[unid_ender].end_swap);
            ++(*cont_page_miss);

            // ----------------------------- Verificacao no swap -----------------------------

            // 3. Verifica se a PV Esta no swap => Caso a PV nao esteja na memoria real, vamos busca-la no swap e carrega-la
            s_end = posicao_memoria("memoria_swap", tp[unid_ender].end_swap);

            printf("s_end: %d\n", s_end);

            if (s_end == -1) // Ou seja, nao esta no swap
                return;

            if (fila->n != qtd_mr_pages) // Ou seja, a MR nao esta cheia
            {
                strcpy(pv->dados, ms[s_end].dados);
                pv->endereco = ms[s_end].endereco;
                pv->entrada_tab = ms[s_end].entrada_tab;

                strcpy(mr[tp[unid_ender].moldura_pag].dados, ms[s_end].dados);
                mr[tp[unid_ender].moldura_pag].entrada_tab = ms[s_end].entrada_tab;

                tp[unid_ender].pres_aus = TRUE;
                tp[unid_ender].moldura_pag = (fila->n - 1);

                // Push na fila de memoria real
                if (strcmp(algoritmo, "fifo\0") == 0)
                    push(fila, pv);

                if (strcmp(algoritmo, "sc\0") == 0)
                    push_sc(fila, pv);

                continue;
            }

            // ------------------------------------------------------------------------------------

            // -------------------------- Algoritmo de Substituicao FIFO --------------------------
            // 4. Usa Algoritmo de Substituicao de Pagina => Vamos dar um Pop na Moldura de Pagina que está a mais tempo na MR
            if (strcmp(algoritmo, "fifo\0") == 0)
                pv = pop(fila);

            if (strcmp(algoritmo, "sc\0") == 0)
                pv = pop_sc(fila, tp);

            if (fila->n != 0)
                printf("Moldura de pagina desalocada: %d\n\n", tp[pv->entrada_tab].moldura_pag);

            // Salvo o que esta na memoria real num no auxiliar
            strcpy(paux->dados, mr[tp[pv->entrada_tab].moldura_pag].dados);
            paux->endereco = mr[tp[pv->entrada_tab].moldura_pag].endereco; // Isso aqui acho que ta errado, pq n sei onde exatamente vou coloca-lo na MS
            paux->entrada_tab = mr[tp[pv->entrada_tab].moldura_pag].entrada_tab;

            p = &mr[tp[paux->entrada_tab].moldura_pag];

            // Salvo o que esta no swap na memoria real
            strcpy(mr[tp[pv->entrada_tab].moldura_pag].dados, ms[s_end].dados);

            if (strcmp(algoritmo, "fifo\0") == 0)
                push(fila, &mr[tp[pv->entrada_tab].moldura_pag]);

            if (strcmp(algoritmo, "sc\0") == 0)
                push_sc(fila, &mr[tp[pv->entrada_tab].moldura_pag]);

            // Aponto a moldura de pagina do swap para a entrada da tabela de pagina da antiga MP
            ms[s_end].entrada_tab = pv->entrada_tab;

            // Nova pagina virtual esta na memoria ram
            tp[unid_ender].pres_aus = TRUE;
            tp[unid_ender].moldura_pag = tp[pv->entrada_tab].moldura_pag;
            tp[unid_ender].end_swap = -1;

            // Antiga moldura de pagina removida esta no swap
            tp[pv->entrada_tab].pres_aus = FALSE;
            tp[pv->entrada_tab].moldura_pag = -1;
            tp[pv->entrada_tab].end_swap = ms[s_end].endereco;
            p->entrada_tab = unid_ender;

            // Salvo o que estava na memoria real no swap
            strcpy(ms[s_end].dados, paux->dados);
            ms[s_end].entrada_tab = paux->entrada_tab;
        }
        else
            printf("Houve Page Hit na pagina virtual de endereco: %d\n\n", unid_ender);
        ++(aux);
        ++(i);

        tempo_atual = time(NULL);
        // Atualiza os bits de status a cada 2 segundos aproximadamente, eh a nosssa interrupcao de relogio
        if (tempo_atual - tempo_inicial >= 2)
            atualizar_bits_status(tp, qtd_mv_pages); // Aguarde a proxima interrupcao do relogio

        printf("\nAo percorrer toda a memoria real temos:\n");
        for (j = 0; j < qtd_mr_pages; j++)
            printf("\tmr[%d].dados = %s | mr[%d].endereco = %d | mr[%d].entrada_tab = %d\n", j, mr[j].dados, j, mr[j].endereco, j, mr[j].entrada_tab);

        printf("\nAo percorrer toda a tabela de paginas temos (Enxergue 65553 como X):\n");
        for (j = 0; j < qtd_mv_pages; j++)
            printf("\ttp[%d].pres_aus = %d | tp[%d].moldura_pag = %d | tp[%d].end_swap = %d\n", j, tp[j].pres_aus, j, tp[j].moldura_pag, j, tp[j].end_swap);

        printf("\nAo percorrer toda a memoria swap temos:\n");
        for (j = 0; j < qtd_ms_pages; j++)
            printf("\tms[%d].endereco: %d | ms[%d].entrada_tab: %d | ms[%d].dados: %s\n", j, ms[j].endereco, j, ms[j].entrada_tab, j, ms[j].dados);

        printf("\nAo percorrer toda a fila da MR temos:\n");
        percorre_fila(fila);
        printf("\n-----------------------------------------------------------------\n\n");
    }

    free(mr);
    free(ms);
    free(tp);
    free(paux);

    if (strcmp(algoritmo, "fifo\0") == 0)
        libera_fifo(fila);

    if (strcmp(algoritmo, "sc\0") == 0)
        libera_sc(fila);

    free(fila);
}
// -------------------------------------------------------------------------------------

// ----------------------------------------- NUR ---------------------------------------
void nur(int *cont_page_miss)
{
    int i, aux, j, qtd_mv_pages, qtd_mr_pages, qtd_ms_pages, unid_ender, s_end;
    time_t tempo_atual, tempo_inicial;
    char prefixo[3] = {"Ax\0"};
    Ppagina mr, ms, paux, p;
    Ptp tp;

    qtd_mv_pages = MV_SIZE / PAG_SIZE;
    qtd_mr_pages = MR_SIZE / PAG_SIZE;
    qtd_ms_pages = MS_SIZE / PAG_SIZE;

    mr = (Ppagina)malloc(sizeof(Tpagina) * qtd_mr_pages);
    if (mr == NULL)
        return;

    ms = (Ppagina)malloc(sizeof(Tpagina) * qtd_ms_pages);
    if (ms == NULL)
        return;

    tp = (Ptp)malloc(sizeof(Pagina_tab_pag) * qtd_mv_pages);
    if (tp == NULL)
        return;

    paux = (Ppagina)malloc(sizeof(Tpagina));
    if (paux == NULL)
        return;

    iniciar_tp(tp);

    /* -------------------------- Preencher a Memoria Real Totalmente --------------------------
     *
     *  Quando a CPU referencia um endereco virtual, ele eh tratado pela MMU.
     *  Se o endereco virtual em questao estiver indicado na tabela de paginas como ausente em memoria
     *  temos entao page-miss, essa pagina virtual deve entao ser carregada na memoria real.
     *  Caso a memoria real esteja cheia e tenha ocorrido page-miss, temos entao que utilizar algum
     *  algoritmo de substituicao de pagina para liberar espaco na memoria real.
     *  Observe que para paginas que forem removidas da mr por conta de page-miss terao que ser salvas
     *  temporariamente em swap e, quando forem referenciadas, deverao retornar a memoria real, podendo
     *  ocorrer novamente page-miss levando a um tratamento por substituicao de paginas mais uma vez.
     */

    aux = i = j = 0;
    for (i; i < qtd_mv_pages || aux < qtd_mr_pages; i++)
    {
        // A CPU comeca a referenciar enderecos virtuais aleatorios a MMU
        unid_ender = rand() % qtd_mv_pages;

        printf("Endereco virtual: %d. unid_ender virtual: %d Bytes\n", unid_ender, unid_ender * PAG_SIZE);

        if (tp[unid_ender].referenciada == FALSE) // Se a pagina nao foi referenciada ainda, vamos tentar carrega-la na RAM
        {
            tp[unid_ender].referenciada = TRUE; // Agora que verificamos eh TRUE
            tp[unid_ender].moldura_pag = -1;    // 65535 quando nao mapeada na mr

            printf("Iteracao %d | Pagina virtual [%d] foi referenciada agora pela primeira vez pela CPU.\n", i, unid_ender);

            if (aux < qtd_mr_pages)
            {
                // ------ Preencho a Memoria Real a Partir de 0 ------
                sprintf(mr[i].dados, "%s%d", prefixo, rand() % qtd_mv_pages); // Aqui gera strings aleatorias e salva como dado
                mr[i].endereco = PAG_SIZE * (1 + i);                          // Guardo o endereco em bytes
                mr[i].entrada_tab = unid_ender;

                tp[unid_ender].pres_aus = TRUE; // Digo que a pagina virtual esta presente numa moldura de pagina na memoria real
                tp[unid_ender].moldura_pag = i; // Moldura de pagina na memoria real salva na pagina virtual em questao
                tp[unid_ender].end_swap = -1;   // Nao esta na swap mais
                ++(aux);
            }
            else
            {
                // Digo que a pagina virtual nao esta presente numa moldura de pagina na memoria real
                tp[unid_ender].pres_aus = FALSE;
                tp[unid_ender].end_swap = PAG_SIZE * (1 + j);

                // Preencho a memoria swap com paginas que nao podem ser carregadas na RAM
                sprintf(ms[j].dados, "%s%d", prefixo, rand() % qtd_mv_pages); // Aqui gera strings aleatorias e salva como dado
                ms[j].endereco = PAG_SIZE * (1 + j);
                ms[j].entrada_tab = unid_ender;
                ++(j);
            }
        }
        else if (tp[unid_ender].referenciada == TRUE) // Se a pagina ja foi referenciada, entao eu continuo nessa iteracao ate encontrar outro endereco valido
        {
            printf("Iteracao %d | Pagina virtual [%d] ja foi referenciada alguma vez pela CPU.\n", i, unid_ender);
            --(i); // Decrementa para a CPU continuar buscando por enderecos aleatorios que nao referenciou
            continue;
        }
    }

    printf("\nAo percorrer toda a memoria real temos:\n");
    for (i = 0; i < qtd_mr_pages; i++)
        printf("\tmr[%d].dados = %s | mr[%d].endereco = %d | mr[%d].entrada_tab = %d\n", i, mr[i].dados, i, mr[i].endereco, i, mr[i].entrada_tab);

    printf("\nAo percorrer toda a tabela de paginas temos (Enxergue 65553 como X):\n");
    for (i = 0; i < qtd_mv_pages; i++)
        printf("\ttp[%d].referenciada = %d | tp[%d].modificada = %d | tp[%d].pres_aus = %d | tp[%d].moldura_pag = %d | tp[%d].end_swap = %d\n", i, tp[i].referenciada, i, tp[i].modificada, i, tp[i].pres_aus, i, tp[i].moldura_pag, i, tp[i].end_swap);

    printf("\nAo percorrer toda a memoria swap temos:\n");
    for (i = 0; i < qtd_ms_pages; i++)
        printf("\tms[%d].endereco: %d | ms[%d].entrada_tab: %d | ms[%d].dados: %s\n", i, ms[i].endereco, i, ms[i].entrada_tab, i, ms[i].dados);
    printf("\n");

    printf("\n-------------------------- Memoria real cheia --------------------------\n\n");

    // Gera inicialmente os bits de status de cada pagina virtual
    atualizar_bits_status(tp, qtd_mv_pages);

    printf("-------------------------- CPU Referencia PV --------------------------\n\n");
    i = aux = s_end = 0;
    while (i < ITER) // Iteramos pelo tamanho maximo da memoria swap apenas para teste
    {
        tempo_inicial = time(NULL); // Recebe o tempo inicial da maquina

        printf("-------------------------- Iteracao %d --------------------------\n\n", i);
        // 2. CPU Referencia Aleatoriamente uma PV => No caso a funcao rand gera enderecos aleatorios para referenciar uma pagina virtual
        unid_ender = rand() % qtd_mv_pages;

        printf("endereco virtual: %d. unid_ender virtual: %d Bytes\n", unid_ender, unid_ender * PAG_SIZE);

        // 3. Identifica Page Miss pela Tabela de Pagina => No caso a PV eh dita como inexistente na MR pelo campo pres_aus da struct
        if (tp[unid_ender].pres_aus == FALSE)
        {
            printf("Houve Page Miss na pagina virtual de endereco virtual: %d. Endereco na swap: %d\n", unid_ender, tp[unid_ender].end_swap);
            ++(*cont_page_miss);

            // 4. Inspeciona todas as molduras de paginas e as separo
            //    em quatro categorias com base nos bits Referenciada e Modificada.
            //    Procuro qual pagina posso retirar com base na prioridade de classes.
            //    Classe 0 < Classe 1 < Classe 2 < Classe 3
            // Lembre-se de contar mais operacoes de escrita para classes com bit MODIFICADA = TRUE

            // ---------------- Classe 0: NAO REFERENCIADA && NAO MODIFICADA ----------------
            j = 0;
            while (j < qtd_mr_pages)
            {
                if (tp[mr[j].entrada_tab].referenciada == FALSE && tp[mr[j].entrada_tab].modificada == FALSE)
                {
                    printf("Pagina [%d] nao foi referenciada e nao foi modificada.\n", mr[j].entrada_tab);

                    // ----------------------------- Verificacao no swap -----------------------------
                    // 5. Verifica se a PV Esta no swap => Caso a PV nao esteja na memoria real, vamos busca-la no swap e carrega-la
                    s_end = posicao_memoria("memoria_swap", tp[unid_ender].end_swap);

                    printf("s_end: %d\n", s_end);

                    if (s_end == -1) // Ou seja, nao esta no swap
                        return;

                    // Salva o que esta na memoria real num no auxiliar
                    strcpy(paux->dados, mr[j].dados);
                    paux->endereco = mr[j].endereco;
                    paux->entrada_tab = mr[j].entrada_tab;

                    // Salva o que esta no swap na memoria real
                    strcpy(mr[j].dados, ms[s_end].dados);

                    // Aponta a pagina do swap para a entrada da tabela da moldura de pagina
                    ms[s_end].entrada_tab = mr[j].entrada_tab;

                    // Antiga pagina virtual esta na memoria RAM
                    tp[unid_ender].pres_aus = TRUE;
                    tp[unid_ender].moldura_pag = tp[mr[j].entrada_tab].moldura_pag;
                    tp[unid_ender].end_swap = -1;

                    // Antiga moldura de pagina removida esta no swap
                    tp[mr[j].entrada_tab].pres_aus = FALSE;
                    tp[mr[j].entrada_tab].moldura_pag = -1;
                    tp[mr[j].entrada_tab].end_swap = ms[s_end].endereco;
                    mr[j].entrada_tab = unid_ender;

                    // Salva o que estava na memoria real na swap
                    strcpy(ms[s_end].dados, paux->dados);
                    ms[s_end].entrada_tab = paux->entrada_tab;

                    break;
                }
                ++(j);
            }

            // Se nao achou paginas daquela classe, continua buscando
            if (j == qtd_mr_pages)
            {
                // ------ Volto a percorrer as molduras de pagina da MR procurando qual pagina posso retirar ------
                // ---------------- Classe 1: NAO REFERENCIADA && MODIFICADA ----------------
                j = 0;
                while (j < qtd_mr_pages)
                {
                    if (tp[mr[j].entrada_tab].referenciada == FALSE && tp[mr[j].entrada_tab].modificada == TRUE)
                    {
                        printf("Pagina [%d] nao foi referenciada e foi modificada.\n", mr[j].entrada_tab);

                        // ----------------------------- Verificacao no swap -----------------------------
                        // 5. Verifica se a PV Esta no swap => Caso a PV nao esteja na memoria real, vamos busca-la no swap e carrega-la
                        s_end = posicao_memoria("memoria_swap", tp[unid_ender].end_swap);

                        printf("s_end: %d\n", s_end);

                        if (s_end == -1) // Ou seja, nao esta no swap
                            return;

                        // Salva o que esta na memoria real num no auxiliar
                        strcpy(paux->dados, mr[j].dados);
                        paux->endereco = mr[j].endereco;
                        paux->entrada_tab = mr[j].entrada_tab;

                        // Salva o que esta no swap na memoria real
                        strcpy(mr[j].dados, ms[s_end].dados);

                        // Aponta a pagina do swap para a entrada da tabela da moldura de pagina
                        ms[s_end].entrada_tab = mr[j].entrada_tab;

                        // Antiga pagina virtual esta na memoria RAM
                        tp[unid_ender].pres_aus = TRUE;
                        tp[unid_ender].moldura_pag = tp[mr[j].entrada_tab].moldura_pag;
                        tp[unid_ender].end_swap = -1;
                        tp[unid_ender].referenciada = TRUE;
                        tp[unid_ender].modificada = FALSE;

                        // Antiga moldura de pagina removida esta no swap
                        tp[mr[j].entrada_tab].pres_aus = FALSE;
                        tp[mr[j].entrada_tab].moldura_pag = -1;
                        tp[mr[j].entrada_tab].end_swap = ms[s_end].endereco;
                        tp[mr[j].entrada_tab].referenciada = FALSE;
                        tp[mr[j].entrada_tab].modificada = TRUE;
                        mr[j].entrada_tab = unid_ender;

                        // Salva o que estava na memoria real na swap
                        strcpy(ms[s_end].dados, paux->dados);
                        ms[s_end].entrada_tab = paux->entrada_tab;

                        break;
                    }
                    ++(j);
                }

                // Se nao achou paginas daquela classe, continua buscando
                if (j == qtd_mr_pages)
                {
                    // ------ Volto a percorrer as molduras de pagina da MR procurando qual pagina posso retirar ------
                    // ---------------- Classe 2: REFERENCIADA && NAO MODIFICADA ----------------
                    j = 0;
                    while (j < qtd_mr_pages)
                    {
                        if (tp[mr[j].entrada_tab].referenciada == TRUE && tp[mr[j].entrada_tab].modificada == FALSE)
                        {
                            // ------ Essa pagina foi referenciada e nao foi modificada ------

                            printf("Pagina [%d] foi referenciada e nao foi modificada.\n", mr[j].entrada_tab);

                            // ----------------------------- Verificacao no swap -----------------------------
                            // 5. Verifica se a PV Esta no swap => Caso a PV nao esteja na memoria real, vamos busca-la no swap e carrega-la
                            s_end = posicao_memoria("memoria_swap", tp[unid_ender].end_swap);

                            printf("s_end: %d\n", s_end);

                            if (s_end == -1) // Ou seja, nao esta no swap
                                return;

                            // Salva o que esta na memoria real num no auxiliar
                            strcpy(paux->dados, mr[j].dados);
                            paux->endereco = mr[j].endereco;
                            paux->entrada_tab = mr[j].entrada_tab;

                            // Salva o que esta no swap na memoria real
                            strcpy(mr[j].dados, ms[s_end].dados);

                            // Aponta a pagina do swap para a entrada da tabela da moldura de pagina
                            ms[s_end].entrada_tab = mr[j].entrada_tab;

                            // Antiga pagina virtual esta na memoria RAM
                            tp[unid_ender].pres_aus = TRUE;
                            tp[unid_ender].moldura_pag = tp[mr[j].entrada_tab].moldura_pag;
                            tp[unid_ender].end_swap = -1;
                            tp[unid_ender].referenciada = TRUE;
                            tp[unid_ender].modificada = FALSE;

                            // Antiga moldura de pagina removida esta no swap
                            tp[mr[j].entrada_tab].pres_aus = FALSE;
                            tp[mr[j].entrada_tab].moldura_pag = -1;
                            tp[mr[j].entrada_tab].end_swap = ms[s_end].endereco;
                            tp[mr[j].entrada_tab].referenciada = FALSE;
                            tp[mr[j].entrada_tab].modificada = FALSE;
                            mr[j].entrada_tab = unid_ender;

                            // Salva o que estava na memoria real na swap
                            strcpy(ms[s_end].dados, paux->dados);
                            ms[s_end].entrada_tab = paux->entrada_tab;

                            break;
                        }
                        ++(j);
                    }

                    // Se nao achou paginas daquela classe, continua buscando
                    if (j == qtd_mr_pages)
                    {
                        // ------ Volto a percorrer as molduras de pagina da MR procurando qual pagina posso retirar ------
                        // ---------------- Classe 3: REFERENCIADA && MODIFICADA ----------------
                        j = 0;
                        while (j < qtd_mr_pages)
                        {
                            if (tp[mr[j].entrada_tab].referenciada == TRUE && tp[mr[j].entrada_tab].modificada == TRUE)
                            {
                                // ------- Essa pagina foi referenciada e foi modificada -------

                                printf("Pagina [%d] foi referenciada e foi modificada.\n", mr[j].entrada_tab);

                                // ----------------------------- Verificacao no swap -----------------------------
                                // 5. Verifica se a PV Esta no swap => Caso a PV nao esteja na memoria real, vamos busca-la no swap e carrega-la
                                s_end = posicao_memoria("memoria_swap", tp[unid_ender].end_swap);

                                printf("s_end: %d\n", s_end);

                                if (s_end == -1) // Ou seja, nao esta no swap
                                    return;

                                // Salva o que esta na memoria real num no auxiliar
                                strcpy(paux->dados, mr[j].dados);
                                paux->endereco = mr[j].endereco;
                                paux->entrada_tab = mr[j].entrada_tab;

                                // Salva o que esta no swap na memoria real
                                strcpy(mr[j].dados, ms[s_end].dados);

                                // Aponta a pagina do swap para a entrada da tabela da moldura de pagina
                                ms[s_end].entrada_tab = mr[j].entrada_tab;

                                // Antiga pagina virtual esta na memoria RAM
                                tp[unid_ender].pres_aus = TRUE;
                                tp[unid_ender].moldura_pag = tp[mr[j].entrada_tab].moldura_pag;
                                tp[unid_ender].end_swap = -1;
                                tp[unid_ender].referenciada = TRUE;
                                tp[unid_ender].modificada = FALSE;

                                // Antiga moldura de pagina removida esta no swap
                                tp[mr[j].entrada_tab].pres_aus = FALSE;
                                tp[mr[j].entrada_tab].moldura_pag = -1;
                                tp[mr[j].entrada_tab].end_swap = ms[s_end].endereco;
                                tp[mr[j].entrada_tab].referenciada = FALSE;
                                tp[mr[j].entrada_tab].modificada = TRUE;
                                mr[j].entrada_tab = unid_ender;

                                // Salva o que estava na memoria real na swap
                                strcpy(ms[s_end].dados, paux->dados);
                                ms[s_end].entrada_tab = paux->entrada_tab;

                                break;
                            }
                            ++(j);
                        }
                    }
                }
            }
        }
        else
            printf("Houve Page Hit na pagina virtual de endereco: %d\n\n", unid_ender);
        ++(i);

        tempo_atual = time(NULL);
        // Atualiza os bits de status a cada 2 segundo aproximadamente, eh a nosssa interrupcao de relogio
        if (tempo_atual - tempo_inicial >= 2)
            atualizar_bits_status(tp, qtd_mv_pages); // Aguarde a proxima interrupcao do relogio

        // ------ Resultado Final ------
        printf("\nAo percorrer toda a memoria real temos:\n");
        for (j = 0; j < qtd_mr_pages; j++)
            printf("\tmr[%d].dados = %s | mr[%d].endereco = %d | mr[%d].entrada_tab = %d\n", j, mr[j].dados, j, mr[j].endereco, j, mr[j].entrada_tab);

        printf("\nAo percorrer toda a tabela de paginas temos (Enxergue 65553 como X):\n");
        for (j = 0; j < qtd_mv_pages; j++)
            printf("\ttp[%d].referenciada = %d | tp[%d].modificada = %d | tp[%d].pres_aus = %d | tp[%d].moldura_pag = %d | tp[%d].end_swap = %d\n", j, tp[j].referenciada, j, tp[j].modificada, j, tp[j].pres_aus, j, tp[j].moldura_pag, j, tp[j].end_swap);

        printf("\nAo percorrer toda a memoria swap temos:\n");
        for (j = 0; j < qtd_ms_pages; j++)
            printf("\tms[%d].endereco: %d | ms[%d].entrada_tab: %d | ms[%d].dados: %s\n", j, ms[j].endereco, j, ms[j].entrada_tab, j, ms[j].dados);
        printf("\n");
    }

    free(tp);
    free(mr);
    free(ms);
    free(paux);
}

// -------------------------------------------------------------------------------------

// ---------------------------------------- SC -----------------------------------------
void push_sc(Pfila fila, Ppagina pv)
{
    Pno_fila no;

    no = (Pno_fila)malloc(sizeof(Tno_fila));
    if (no == NULL)
        return;

    no->no = pv;

    if (fila->n == 0)
    {

        fila->inicio = fila->fim = no;
        no->prox = no; // O ultimo elemento aponta para o primeiro, formando um ciclo
    }
    else
    {
        fila->fim->prox = no;
        fila->fim = no;
        no->prox = fila->inicio; // O ultimo elemento aponta para o primeiro, formando um ciclo
    }
    fila->n += 1;
}

Ppagina pop_sc(Pfila fila, Ptp tp)
{
    Ppagina inicio = NULL;
    Pno_fila p, ant;

    p = fila->inicio;
    ant = fila->fim;

    if (fila->inicio != NULL)
    {
        while (1)
        {
            if (tp[p->no->entrada_tab].referenciada == FALSE)
            {
                inicio = p->no;
                ant->prox = p->prox;
                fila->inicio = p->prox;
                fila->fim = ant;
                break;
            }
            else
            {
                tp[p->no->entrada_tab].referenciada = FALSE;
                ant = p;
                p = p->prox;
            }
        }
        --(fila->n);
        free(p);
    }

    return inicio;
}

void libera_sc(Pfila fila)
{
    Pno_fila p, q, r;
    p = fila->inicio;
    r = fila->fim;

    while (p != NULL)
    {
        q = p;
        p = p->prox;

        if (p->prox == r)
        {
            free(p);
            p = NULL;
        }
        free(q);
    }
}
// -------------------------------------------------------------------------------------

/*
 * O SO mantem uma lista de todas as paginas atuais na memoria, com a pagina mais antiga na cabeca
 * e a pagina que chegou mais recentemente situada no final da fila. Na ocorrencia de page-miss a primeira
 * pagina eh removida e a nova pagina eh inserida.
 */
int main(int argc, char **argv)
{
    if (argc < 6)
    {
        printf("Algoritmos: fifo, nur, sc.\n\nOs tamanhos de memoria sao em Bytes.\n");
        printf("Para facilitar, pode digitar em Kilobytes para cada tamanho de memoria que sera feita a conversao automaticamente\n\n");
        printf("--------------------------------------------------------------------------------\n\n");
        printf("Nosso programa utiliza geracao aleatoria de sequencias numericas que representam enderecos ");
        printf("para melhorar a distribuicao uniforme da amostra.\nAlém de nao verificar paginas virtuais ja referenciadas, ");
        printf("eh necessario dar como entrada sementes para a inicializacao da sequencia de enderecos\n\n");
        printf("--------------------------------------------------------------------------------");
        printf("\n\nUso: %s <MV_SIZE> <MR_SIZE> <MS_SIZE> <SEED> <ITER>\n\n", argv[0]);
        return 0;
    }

    clock_t start, end;
    double cpu_time_used[3];
    int cont_page_miss[3];

    MV_SIZE = atoi(argv[1]) * 1024; // Conversao para Bytes
    MR_SIZE = atoi(argv[2]) * 1024; // Conversao para Bytes
    MS_SIZE = atoi(argv[3]) * 1024; // Conversao para Bytes
    SEED = atoi(argv[4]);
    ITER = atoi(argv[5]);

    printf("MV_SIZE: %d Bytes| MR_SIZE: %d Bytes | MS_SIZE: %d Bytes | PAG_SIZE: %d Bytes\n", MV_SIZE, MR_SIZE, MS_SIZE, PAG_SIZE);
    printf("Pressione qualquer tecla para continuar...\n");
    getchar();

    if (MV_SIZE <= MR_SIZE)
    {
        printf("\n--------------------------------------------------------------------------------\n\n");
        printf("Memoria virtual nao pode ser menor ou igual a real\n\n");
        printf("--------------------------------------------------------------------------------\n");
        return 0;
    }

    if (MS_SIZE < (MV_SIZE - MR_SIZE))
    {
        printf("\n--------------------------------------------------------------------------------\n\n");
        printf("A memoria swap nao pode ser menor do que a diferenca entre o tamanho da memoria virtual e real\n\n");
        printf("--------------------------------------------------------------------------------\n");
        return 0;
    }

    if (MV_SIZE < PAG_SIZE)
    {
        printf("\n--------------------------------------------------------------------------------\n\n");
        printf("A memoria virtual nao pode ser menor do que o tamanho da pagina virtual\n\n");
        printf("--------------------------------------------------------------------------------\n");
        return 0;
    }

    if (MR_SIZE < PAG_SIZE)
    {
        printf("\n--------------------------------------------------------------------------------\n\n");
        printf("A memoria real nao pode ser menor do que o tamanho da moldura de pagina\n\n");
        printf("--------------------------------------------------------------------------------\n");
        return 0;
    }

    if (MS_SIZE < PAG_SIZE)
    {
        printf("\n--------------------------------------------------------------------------------\n\n");
        printf("A memoria swap nao pode ser menor do que o tamanho da moldura de pagina\n\n");
        printf("--------------------------------------------------------------------------------\n");
        return 0;
    }

    /*
     * Precisamos que exista distribuicao uniforme na sequencia de enderecos aleatorios na busca por paginas virtuais.
     *
     * Pseudoaleatoriedade: Sendo assim, eh necessario que nossa sequencia seja aleatoria, para tal,
     * vamos sempre alterar o valor da semente dessa sequencia para que, a cada semente,
     * tenhamos diferentes sequencias, ou seja, a pseudoaleatoriedade ja que a sequencia depende de um valor inicial.
     * A funcao rand() retorna a cada chamada o proximo numero gerado na sequencia de numeros aleatorios a partir da seed.
     *
     * Altera a semente da sequencia, eh com base nela que faremos os testes aleatorios melhorando um pouco a distribuicao uniforme
     */
    srand(SEED);

    // -------------------- Algoritmo de Substituicao --------------------

    cont_page_miss[0] = 0;

    start = clock(); // Marca o início do tempo de execução
    fifo("fifo\0", &cont_page_miss[0]);
    end = clock();                                               // Marca o fim do tempo de execução
    cpu_time_used[0] = ((double)(end - start)) / CLOCKS_PER_SEC; // Calcula o tempo em segundos
    printf("Fifo finalizado. Pressione qualquer tecla para continuar...\n");
    getchar();

    cont_page_miss[1] = 0;

    start = clock();
    nur(&cont_page_miss[1]);
    end = clock();
    cpu_time_used[1] = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("NUR finalizado. Pressione qualquer tecla para continuar...\n");
    getchar();

    cont_page_miss[2] = 0;

    start = clock();
    fifo("sc\0", &cont_page_miss[2]);
    end = clock();
    cpu_time_used[2] = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("SC finalizado. Pressione qualquer tecla para continuar...\n");
    getchar();

    printf("FIFO | Quantidade de page miss: %d\n", cont_page_miss[0]);
    printf("FIFO | Tempo de execucao: %f segundos\n\n", cpu_time_used[0]);
    printf("NUR | Quantidade de page miss: %d\n", cont_page_miss[1]);
    printf("NUR | Tempo de execucao %f segundos\n\n", cpu_time_used[1]);
    printf("SC | Quantidade de page miss: %d\n", cont_page_miss[2]);
    printf("SC | Tempo de execucao %f segundos\n", cpu_time_used[2]);

    return 0;
}
