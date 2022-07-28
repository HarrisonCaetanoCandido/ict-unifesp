/*
    Nome: Harrison Caetano Candido
    RA: 156264
    Turma: Integral
*/
/*
    Você está em uma empresa que segue uma regra para definir o seu presidente a 
    cada quatro anos. A empresa realiza uma hierarquia onde o parâmetro para decidir quem 
    está mais alto nela é o tempo nesta empresa e também quem foi o funcionário que o 
    contratou, um funcionário pode contratar outros e podemos expressar as contratações 
    como uma árvore. 
    João é o primeiro funcionário, portanto ele será o presidente da empresa durante o 
    primeiro mandato. Na hierarquia, o próximo presidente será Ana e de forma não muito 
    intuitiva Gabriel será o próximo. A mecânica para determinar o próximo presidente sempre 
    escolhe qual será o com mais tempo na empresa primeiramente, ou seja, o funcionário mais 
    à esquerda da árvore e um detalhe a ser considerado é que para o segundo funcionário 
    contratado do presidente ser eleito presidente, todos os funcionários indicados pelo seu 
    primeiro funcionário e seus sucessores devem ter feito seu mandato para isso ocorrer. Ou 
    seja, o funcionário mais à esquerda e seus sucessores possuem mais prioridade que o 
    segundo funcionário contratado pelo presidente. Exemplificando, no caso do diagrama 
    acima a ordem será: João, Ana, Gabriel, Matheus e Bob.
    Como qualquer outra empresa, funcionários podem ser contratados a qualquer 
    momento e demitidos, então da árvore a ser montada, deverá ser possível inserir e deletar 
    nós a qualquer momento. Caso um funcionário seja demitido, todos os funcionários que ele 
    indicou e seus sucessores também devem ser removidos da árvore
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvgen
{
    char *nome;
    int dia, mes, ano;
    struct arvgen *prim, *prox;
} Tarvgen;

typedef Tarvgen *Parvgen;

// ---------------- Funcoes ----------------

Parvgen inserir(Parvgen a);
Parvgen cria_folha(char nome[]);
int nome_repetido(Parvgen a, char nome[]);
Parvgen busca(Parvgen a, char nome[]);
Parvgen remover(Parvgen a, char nome[]);
void presidentes(Parvgen a);
Parvgen liberar(Parvgen a);

// -----------------------------------------

Parvgen cria_folha(char nome[])
{
    int i;
    Parvgen a;

    a = (Parvgen)malloc(sizeof(Tarvgen));

    if (a == NULL)
        return NULL;

    a->prim = a->prox = NULL;

    a->nome = (char *)malloc(strlen(nome) * sizeof(char));

    for (i = 0; i < strlen(nome); i++)
        a->nome[i] = nome[i];

    a->nome[i] = '\0';

    // data de contratacao(inteiros indicando dia, mes, ano)
    scanf("%d", &a->dia);
    scanf("%d", &a->mes);
    scanf("%d", &a->ano);

    return a;
}

/*  Operacao 1:

    nome (nao incluir nomes repetidos - percorrer toda a arvore e ver se o nome ja existe)
    data de contratacao(inteiros indicando dia, mes, ano)
    nome do funcionario que o indicou (quando for o no raiz principal o nome que o indicou devera ser "fundador")

    Obs:
    - Caso seja feita a tentativa de incluir alguem sem que tenha sido criado o fundador (no raiz) ou com o
    nome de indicado que ainda nao foi incluido, o no nao sera incluido na arvore;

    - Caso haja mais de um funcionario indicado pela mesma pessoa na mesma data, a ordem de insercao sera a ordem de chegada
    (o primeiro nome que aparecer estara na frente) <= Operacao na lista prim do no
*/

Parvgen inserir(Parvgen a)
{
    int i;
    Parvgen novo, p, q;
    char nome[50], indicou[50], compara[] = "fundador";

    scanf("%s", &nome);

    novo = cria_folha(nome);

    scanf("%s", &indicou); // nome do funcionario que o indicou (quando for o no raiz principal o nome que o indicou devera ser "fundador")

    if (a == NULL) // verifica se o indicou eh a string "fundador"
    {
        for (i = 0; i < strlen(compara); i++)
            if (indicou[i] != compara[i])
            {
                free(novo);
                return NULL;
            }

        return novo;
    }

    if (nome_repetido(a, nome) == 1) // nome (nao incluir nomes repetidos - percorrer toda a arvore e ver se o nome ja existe)
    {
        free(novo);
        return a;
    }

    if (a != NULL) // vai buscar e inserir conforme a regra de indicacao e data de contratacao/ indicacao
    {
        p = busca(a, indicou);

        if (p == NULL)
        {
            free(novo);
            return a;
        }

        if (p->prim == NULL)
            p->prim = novo;
        else
        {
            for (q = p->prim; q != NULL; q = q->prox)
            {
                if (novo->dia == q->dia && novo->mes == q->mes && novo->ano == q->ano) // insere por ordem de chegada caso as datas sejam iguais
                {
                    if (q->prox != NULL && (novo->ano < q->prox->ano || novo->ano <= q->prox->ano && novo->mes < q->prox->mes ||
                        novo->ano <= q->prox->ano && novo->mes <= q->prox->mes && novo->dia < q->prox->dia)) 
                        // caso o nó da frente nao tenha uma data exatamente igual ao do novo nó, se tiver, precisaremos percorrer mais um nó                   
                    {    
                        novo->prox = q->prox;
                        q->prox = novo;
                        return a;
                    }

                    if(q->prox == NULL)
                    {
                        q->prox = novo;
                        return a;
                    }
                }

                if (q == p->prim && q->ano >= novo->ano && q->mes > novo->mes ||
                    q->ano >= novo->ano && q->mes == novo->mes && q->dia >= novo->dia) // inserir no inicio
                {
                    novo->prox = p->prim;
                    p->prim = novo;
                    return a;
                }

                if (q->ano < novo->ano || q->ano <= novo->ano && q->mes < novo->mes ||
                    q->ano <= novo->ano && q->mes == novo->mes && q->dia < novo->dia) // inserir no meio/fim
                {
                    if (q->prox == NULL) // inserir no fim
                    {
                        q->prox = novo;
                        return a;
                    }

                    if (q->prox->ano > novo->ano || q->prox->ano >= novo->ano && q->prox->mes > novo->mes ||
                        q->prox->ano >= novo->ano && q->prox->mes == novo->mes && q->prox->dia > novo->dia) // inserir no meio, data da frente menor, data posterior maior
                    {
                        novo->prox = q->prox;
                        q->prox = novo;
                        return a;
                    }
                }
            }
        }
        return a;
    }
}

int nome_repetido(Parvgen a, char nome[])
{
    int i;
    if (a != NULL)
    {
        for (i = 0; i < strlen(nome); i++)
            if (a->nome[i] != nome[i])
                return nome_repetido(a->prim, nome) + nome_repetido(a->prox, nome);

        return 1;
    }
    return 0;
}

Parvgen busca(Parvgen a, char nome[])
{
    Parvgen b;
    int i = 0;

    if (a == NULL)
        return NULL;

    for (i = 0; i < strlen(nome); i++)
        if (a->nome[i] != nome[i])
        {
            b = busca(a->prim, nome);

            if (b == NULL)
                b = busca(a->prox, nome);

            return b;
        }

    return a;
}

/*
    Operacao 2:

    nome (implica na remocao de todos os seus sucessores tambem, IRMAO de um no NAO eh seu sucessor)
*/

Parvgen remover(Parvgen a, char nome[])
{
    Parvgen p;
    int i = 0;

    if (a == NULL)
        return NULL;

    for (i = 0; i < strlen(nome); i++)
        if (a->nome[i] != nome[i])
        {
            a->prim = remover(a->prim, nome);
            a->prox = remover(a->prox, nome);
            return a;
        }

    if (a->prox == NULL) // fim da lista
    {
        a->prim = liberar(a->prim);
        free(a);
        return NULL;
    }

    // esta no inicio/ meio da lista
    p = a->prox;
    a->prim = liberar(a->prim);
    free(a);
    return p;
}

/*
    Operacao 3:

    Imprime a ordem que deve ser seguida para a nomeacao dos presidentes da empresa (Ordem Pre-fixa)
*/

void presidentes(Parvgen a) // impressao na ordem pre-fixa (raiz, esq, dir)
{
    if (a != NULL)
    {
        printf("%s\n", a->nome);
        presidentes(a->prim);
        presidentes(a->prox);
    }
}

Parvgen liberar(Parvgen a)
{
    if (a != NULL)
    {
        a->prim = liberar(a->prim);
        a->prox = liberar(a->prox);
        free(a);
    }
    return NULL;
}

int main()
{
    Parvgen a = NULL;
    char nome[50];
    int op;

    do
    {
        /*
            Operacoes:

            1 | Contratacao
            2 | Demissao
            3 | Impressao da ordem de presidentes (apenas imprimir na pre-fixa)
            4 | Sair
            5 ou mais | "Erro"
        */
        scanf("%d", &op);

        switch (op)
        {
        case 1: // inserir
            a = inserir(a);
            break;

        case 2: // remover
            scanf("%s", &nome);
            a = remover(a, nome);
            break;

        case 3: // imprimir a ordem de presidentes (pre-fixa)
            presidentes(a);
            break;

        default: // erro
            break;
        }
    } while (op != 4);

    /*
        Operacao 4:

        A entrada deverá ser finalizada apenas quando o usuário digitar a opção 4 (em
        opções diferentes de 1, 2, 3 ou 4 o programa ficará esperando nova entrada).
    */

    a = liberar(a);

    return 0;
}