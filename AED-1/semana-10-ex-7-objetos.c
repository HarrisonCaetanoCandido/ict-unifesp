/*
    Nome: Harrison Caetano Candido
    RA: 156264
    Turma: Integral
*/
/*
    Considere que exista uma sequência de descrições de objetos geométricos (círculos, 
    retângulos e triângulos). Faça um programa que armazene estas figuras em uma Árvore 
    Binária de Busca (ABB) usando como chave a área de cada figura. Desta forma, cada nó 
    conterá a letra que identificará o objeto (‘C’ou ‘c’ para círculo, ’R’,ou ‘r’ para retângulo, e ’T’ 
    ou ’t’ para triângulo) e o valor da área do objeto, além dos ponteiros necessários para 
    montar a árvore. Considere que nenhum objeto terá área igual a outro para que seja 
    possível montar a árvore. Desta forma, se algum objeto tiver área igual a outro que já tenha 
    sido inserido na árvore, ele não deverá ser inserido
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct arvBB
{
    char objeto; // (‘C’ou ‘c’ para círculo, ’R’,ou ‘r’ para retângulo, e ’T’ ou ’t’ para triângulo)
    float area;
    struct arvBB *esq, *dir;
} TarvBB;

typedef TarvBB *ParvBB;

// ---------------- Funcoes ----------------

ParvBB cria_folha(float X, char caractere);
ParvBB inserir(ParvBB a, float X, char caractere);
void imprimir(ParvBB a, char caractere);
int buscar_objetos(ParvBB a, char caractere);
ParvBB remover(ParvBB a, float X, char caractere);
ParvBB remover_esq(ParvBB a);
ParvBB maior_esq(ParvBB a);
ParvBB liberar(ParvBB a);

// -----------------------------------------

ParvBB cria_folha(float X, char caractere)
{
    ParvBB a;

    a = (ParvBB)malloc(sizeof(TarvBB));

    if (a == NULL)
        return NULL;

    a->area = X;
    a->objeto = caractere;
    a->esq = a->dir = NULL;

    return a;
}

ParvBB inserir(ParvBB a, float X, char caractere)
{
    if (a == NULL)
        return cria_folha(X, caractere);

    if (a->area > X)
        a->esq = inserir(a->esq, X, caractere);

    if (a->area < X)
        a->dir = inserir(a->dir, X, caractere);

    return a; // se ja inseriu a funcao retorna, se for igual apenas retorna e nao aloca memoria e nem insere
}

void imprimir(ParvBB a, char caractere)
{
    if (a != NULL)
    {
        imprimir(a->esq, caractere);

        if (a->objeto == caractere)
            printf("%.1f ", a->area);

        imprimir(a->dir, caractere);
    }
}

int buscar_objetos(ParvBB a, char caractere) // funcao que vai buscar tipos de objetos e ajudar na impressao
{
    if (a == NULL)
        return 0;

    if (a->objeto == caractere) 
        return 1;

    if (buscar_objetos(a->esq, caractere) == 0)
        return buscar_objetos(a->dir, caractere);

    return 1;
}

ParvBB remover(ParvBB a, float X, char caractere) // remocao ordenada
{
    ParvBB p;

    if (a == NULL)
        return NULL;

    if (a->area < X)
    {
        a->esq = remover(a->esq, X, caractere); // se o no atual for menor do que a area X, segue para a esquerda
        a->dir = remover(a->dir, X, caractere); // depois segue para a direita para cobrir casos em que alguns dos nos a direita ainda sao menores do que X, mas maiores do que o no atual
    }
    else
        a->esq = remover(a->esq, X, caractere); // caso o no atual seja maior do que X, segue para a esquerda, como os nos nunca terao valores iguais por conta da funcao de inserir, nao eh preciso um if para essa condicao especifica

    if (a->objeto == caractere && a->area < X)
    {
        if (a->esq == NULL && a->dir == NULL)
        {
            free(a);
            return NULL;
        }

        if (a->esq != NULL && a->dir == NULL)
        {
            p = a->esq;
            free(a);
            return p;
        }

        if (a->esq == NULL && a->dir != NULL)
        {
            p = a->dir;
            free(a);
            return p;
        }

        if (a->esq != NULL && a->dir != NULL)
        {
            p = maior_esq(a->esq); // busca o maior a esquerda
            a->area = p->area;
            a->objeto = p->objeto;

            a->esq = remover_esq(a->esq);
        }
    }

    return a;
}

ParvBB maior_esq(ParvBB a) // busca o maior a esquerda
{
    if (a->dir != NULL)
        a = maior_esq(a->dir);

    return a;
}

ParvBB remover_esq(ParvBB a)
{
    ParvBB p;

    if (a->dir != NULL)
        a->dir = remover_esq(a->dir);
    else
    {
        if(a->esq == NULL) // caso seja um no folha
        {
            free(a);
            return NULL;
        }
        
        if(a->esq != NULL) // caso nao seja um no folha, mas sim o maior a esquerda
        {
            p = a->esq;
            free(a);
            return p;
        }
    }
    return a;
}

ParvBB liberar(ParvBB a) // pos-fixa
{
    if (a != NULL)
    {
        a->esq = liberar(a->esq);
        a->dir = liberar(a->dir);
        free(a);
    }
    return NULL;
}

int main()
{
    ParvBB a;
    float X, raio, base, altura;
    char caractere;

    a = NULL;

    do // Em cada linha você receberá uma letra (‘C’, ‘c’, ‘R’, ‘r’, ’T’ ou ’t’) que indica um círculo, retângulo ou triângulo
    {
        caractere = getchar();

        if (caractere == 'T' || caractere == 't')
            caractere = 'T'; // padronizar para facilitar a impressao

        if (caractere == 'R' || caractere == 'r')
            caractere = 'R'; // padronizar para facilitar a impressao

        if (caractere == 'C' || caractere == 'c')
            caractere = 'C'; // padronizar para facilitar a impressao

        if (caractere == 'I' || caractere == 'i')
            caractere = 'I'; // padronizar para facilitar a selecao

        if (caractere == 'E' || caractere == 'e')
            caractere = 'E'; // padronizar para facilitar a selecao

        switch (caractere)
        {
        case 'R': // se for retangulo

            scanf("%f %f", &base, &altura);

            X = base * altura;

            a = inserir(a, X, caractere);

            break;

        case 'T': // se for triangulo

            scanf("%f %f", &base, &altura);

            X = (base * altura) / 2.0; // para qualquer triangulo

            a = inserir(a, X, caractere);

            break;

        case 'C': // se for circulo

            scanf("%f", &raio);

            X = M_PI * raio * raio;

            a = inserir(a, X, caractere);

            break;

        case 'I': // imprimir objetos em ordem crescente

            if (buscar_objetos(a, 'C') == 1) // se existir circulos na arvore, ele imprime apenas os circulos
            {
                printf("circulo\n");
                imprimir(a, 'C'); // imprime apenas os nos com o caractere selecionado
                printf("\n");
            }

            if (buscar_objetos(a, 'R') == 1) // se existir retangulos na arvore, ele imprime apenas os retangulos
            {
                printf("retangulo\n");
                imprimir(a, 'R'); // imprime apenas os nos com o caractere selecionado
                printf("\n");
            }

            if (buscar_objetos(a, 'T') == 1) // se existir triangulos na arvore, ele imprime apenas os triangulos
            {
                printf("triangulo\n");
                imprimir(a, 'T'); // imprime apenas os nos com o caractere selecionado
                printf("\n");
            }

            break;

        case 'E': // se quiser remover

            scanf(" %c", &caractere); // digitar o objeto

            if (caractere == 'T' || caractere == 't' || caractere == 'R' || caractere == 'r' || caractere == 'C' || caractere == 'c')
            {
                scanf("%f", &X); // digitar a area

                if (caractere == 'T' || caractere == 't')
                    caractere = 'T'; // padronizar para facilitar a impressao

                if (caractere == 'R' || caractere == 'r')
                    caractere = 'R'; // padronizar para facilitar a impressao

                if (caractere == 'C' || caractere == 'c')
                    caractere = 'C'; // padronizar para facilitar a impressao

                a = remover(a, X, caractere);
            }

            caractere = 'L'; // caractere aleatorio para nao sair do laço caso seja inserido o caractere 'F' ou 'i' na remocao

            break;

        default: // caractere aleatorio/erro
            break;
        }

    } while (caractere != 'F' && caractere != 'f');

    a = liberar(a);

    return 0;
}