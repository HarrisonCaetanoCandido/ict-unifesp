/*
1) Faça um programa que peça para o usuário entrar com os seguintes itens n vezes:
nome do produto
quantidade vendida
mês da venda
quem comprou
Estes dados devem ser armazenados em um vetor de estruturas (vetor de struct). A seguir,
apresente o seguinte Menu de opções para o usuário:
• Total de vendas num dado mês (de todos os produtos)
• Total de vendas de um determinado produto num dado mês para um determinado
cliente (qual produto, para quem e em que mês)
• Total de vendas de cada produto (em todos os meses)
• Total vendido para cada cliente
• 5) Fim
Para cada opção que o usuário escolher, faça os cálculos necessários. Os cálculos devem ser
repetidos até que o usuário escolha a opção 5. Não esqueça de verificar que o usuário digitou
uma opção válida.0/
*/
#include <stdio.h>
#include <stdlib.h>
#define str 30

typedef struct{
    char nproduto[str],ncliente[str];
    int qvendida,mes;
}Itens;

int main(){
    int op;

    do{
        switch(op){/*
            • Total de vendas num dado mês (de todos os produtos)
            • Total de vendas de um determinado produto num dado mês para um determinado
            cliente (qual produto, para quem e em que mês)
            • Total de vendas de cada produto (em todos os meses)
            • Total vendido para cada cliente
            • 5) Fim*/
        }
    }while(op!=5);
    return 0;
}
