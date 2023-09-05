#include <stdio.h>
#include <stdlib.h>

typedef struct Lista_Circular
{
    int info;
    struct Lista_Circular *prox;
} Tlista_circ;

typedef Tlista_circ *Plista;

Plista cria_lista();
Plista inserir(Plista ultimo, int v);
void imprime(Plista ultimo);
Plista buscar(Plista ultimo, int v);
Plista remover(Plista ultimo, int v);
void libera(Plista ultimo);

int main()
{
    Plista ultimo, busca;
    int v, qtd, i, continuar = 1;

    ultimo = cria_lista();

    printf("Digite a quantidade de valores que deseja inserir: ");
    scanf("%d", &qtd);

    i = 0;
    while (i < qtd)
    {
        printf("Digite o %d valor: ", i + 1);
        scanf("%d", &v);

        ultimo = inserir(ultimo, v);
        i++;
    }
    imprime(ultimo);
    // ---------------------------------------------------
    while (continuar == 1)
    {
        printf("Digite o valor que deseja buscar: ");
        scanf("%d", &v);

        busca = buscar(ultimo, v);

        if (busca != NULL)
        {
            printf("Valor encontrado %d\n\n", busca->info);
            continuar = 0;
        }
        else
        {
            printf("Valor nao encontrado. Deseja continuar? (sim: 1 | nao: 0): ");
            scanf("%d", &continuar);
        }
    }

    // ---------------------------------------------------
    printf("Digite o valor que deseja remover: ");
    scanf("%d", &v);

    ultimo = remover(ultimo, v);
    
    if (ultimo != NULL) // para nao dar segmentation fault no replit
    { 

        imprime(ultimo);

        libera(ultimo);
    }

    // ---------------------------------------------------

    return 0;
}

Plista cria_lista()
{
    return NULL;
}

Plista inserir(Plista ultimo, int v)
{
    Plista novo;
    novo = (Plista)malloc(sizeof(Tlista_circ));
    novo->info = v;

    if (novo == NULL)
    {
        return; // erro de alocacao de memoria
    }

    if (ultimo == NULL) // se a fila esta vazia,
    {
        novo->prox = novo; // proximo do ultimo no, que eh 'novo' recebe o endereco dele mesmo, ja que eh o unico elemento
        return novo;
    }

    novo->prox = ultimo->prox; // insere no final da lista
    ultimo->prox = novo;

    return ultimo;
}

void imprime(Plista ultimo)
{
    Plista p;

    if (ultimo == NULL)
    {
        return;
    }

    p = ultimo->prox; // p igual ao primeiro

    do
    {
        printf("%d\n", p->info);
        p = p->prox;
    } while (p != ultimo->prox);
}

Plista buscar(Plista ultimo, int v)
{
    Plista p = ultimo->prox;

    if (ultimo == NULL)
    {
        return NULL;
    }

    do
    {
        if (p->info != v)
        {
            p = p->prox;
        }
    } while (p != ultimo->prox && p->info != v);

    if (p->info == v)
    {
        return p;
    }
    else
    {
        return NULL;
    }
}

Plista remover(Plista ultimo, int v)
{
    Plista p, ant;

    ant = p = ultimo->prox;

    if (ultimo == NULL)
        return NULL;

    do
    {
        if (p->info != v)
        {
            ant = p; // ant sempre recebe o endereco anterior de p; exemplo: if(p->info != v),p = end1, ant = end1, p = p->prox(end2)
            p = p->prox;
        }
    } while (p != ultimo->prox && p->info != v);

    if (p->info == v)
    {
        if (ultimo == ultimo->prox) // se so tiver um no na lista
        {
            printf("Valor removido com sucesso!\n\n");

            free(p);
            return NULL;
        }

        if (p == ultimo->prox)
        { // ou ele for o primeiro
            printf("Valor removido com sucesso!\n\n");

            ultimo->prox = p->prox;
            free(p);

            return ultimo;
        }

        printf("Valor removido com sucesso!\n\n");

        ant->prox = p->prox;

        if (p == ultimo) // se o valor estiver no ultimo 'no'
        {
            free(p);
            return ant;
        }

        free(p);
    }
    else
    {
        printf("Valor nao foi encontrado!\n\n");
    }
    return ultimo;
}

void libera(Plista ultimo)
{
    Plista p = ultimo->prox;

    if (ultimo == NULL)
        return;

    if (ultimo->prox == ultimo)
    {
        free(ultimo);
        return;
    }

    ultimo->prox = p->prox;
    free(p);
    libera(ultimo);
}