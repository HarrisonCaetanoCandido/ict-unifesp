/*
    Nome: Harrison Caetano Candido
    RA: 156264
    Turma: Integral
*/
/*
    Uma Wishlist (Lista de desejos) não é difícil de se ver em aplicativos de compras 
    e nos ajudam a lembrar e a planejar para comprar os produtos que são considerados 
    importantes. Você decide abrir sua loja de departamentos, mas acaba percebendo que 
    suas vendas não estão indo muito bem. Assim, você decide criar um aplicativo para a 
    sua loja que tenha funcionalidades interessantes.
    Para ajudar os seus clientes a planejar as suas compras você pensou em uma 
    ideia que lembra os clientes da ordem em que deve ser feita a compra dos seus 
    produtos. Cada produto deve ser inserido na lista seguido de um número que indicará a 
    sua prioridade de compra (quanto menor o número, maior a prioridade). Seu objetivo é 
    inserir em uma lista encadeada simples os produtos, mas mantendo uma ordem 
    decrescente em relação ao parâmetro de importância de compra. Caso o parâmetro de 
    importância seja repetido, você deve seguir a ordem de inserção, o seja, o que foi 
    inserido primeiro aparecerá primeiro na lista.
    Imprevistos podem acontecer e o cliente pode decidir retirar da lista algum 
    produto. Desta forma, você deve ser capaz de excluir um elemento da lista dado o seu 
    nome. Antes de cada chamada para excluir, o usuário irá colocar a senha que é sempre 
    “UNIFESPSJC”. É a colocação desta senha que indicará que o usuário deseja excluir 
    algum item.
    A entrada -1 indica o fim da entrada. Você não deve inserir itens repetidos!
    Cuidado ao tentar retirar itens que não existem da lista!

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct lista
{
    char produto[20];
    int id;
    struct lista *prox; // ponteiro que aponta para outros tipos struct lista
} Tlista;
 
typedef Tlista *Plista; // renomeia o tipo lista como um ponteiro do tipo lista
 
// ------------------------------- FUNCOES ---------------------------------
Plista inicia_lista();
Plista insere(Plista lista, char prod[], int ident);
Plista remover(Plista lista, char prod[]);
void imprime(Plista lista);
Plista liberar(Plista lista);
//--------------------------------------------------------------------------
 
int main()
{
    Plista lista, p;
 
    lista = inicia_lista();
 
    char nome_prod[20];
    int ident, entrada=0;
 
    while (entrada != -1)
    {
        scanf("%s", &nome_prod); // digitar o nome do produto
 
        if (strcmp(nome_prod, "-1") == 0)
        {
            entrada = -1;
        }
        else
        {
            if (strcmp(nome_prod, "UNIFESPSJC") == 0)
            {
                scanf("%s", &nome_prod);
                lista = remover(lista, nome_prod);
            }
            else
            {
                scanf("%d", &ident); // digitar o id
                lista = insere(lista, nome_prod, ident);
            }
        }
    }
 
    imprime(lista);
 
    liberar(lista);
 
    return 0;
}
 
Plista inicia_lista()
{
    return NULL;
}
 
Plista insere(Plista lista, char prod[], int ident)
{
    Plista novo, atual = NULL, p;
    novo = (Plista)malloc(sizeof(Tlista));
 
    strcpy(novo->produto, prod);
    novo->id = ident;
 
    for (p = lista; p != NULL; p = p->prox)
    {
        if (strcmp(p->produto, novo->produto) == 0)
        {
            return lista;
        }
    }
 
    if (lista == NULL) // se a lista eh vazia
    {
        novo->prox = lista;
        return novo;
    }
    else
    {
 
        if (novo->id < lista->id) // se o primeiro valor eh menor do que o atual
        {
            novo->prox = lista;
            return novo;
        }
        else
        {
            atual = lista;
            while (atual->prox && novo->id > atual->prox->id) // le-se: enquanto existir proximo e novo->id for maior que o proximo id
            {
                atual = atual->prox;
            }
            novo->prox = atual->prox;
            atual->prox = novo;
            return lista;
        }
    }
}
 
Plista remover(Plista lista, char prod[])
{
    Plista p, ant = NULL;
 
    for (p = lista; p != NULL && (strcmp(p->produto, prod) != 0); p = p->prox)
    {
        ant = p;
    }
 
    if (p == NULL)
    {
        return lista;
    }
 
    if (ant != NULL)
    {
        ant->prox = p->prox;
        free(p);
    }
 
    if (ant == NULL)
    {
        lista = p->prox;
    }
    return lista;
}
 
void imprime(Plista lista)
{
    Plista p;
 
    for (p = lista; p != NULL; p = p->prox)
    {
        printf("%s\n", p->produto);
    }
}
 
Plista liberar(Plista lista)
{
    if (lista != NULL)
    {
        liberar(lista->prox);
        free(lista);
    }
}