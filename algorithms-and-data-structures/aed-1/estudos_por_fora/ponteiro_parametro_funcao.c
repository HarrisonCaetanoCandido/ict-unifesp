#include <stdio.h>
#include <stdlib.h>

void testeVariavel(int teste);
void testePonteiro(int *px);

int main()
{

    int teste = 1;

    int *pTeste = &teste;

    // testeVariavel(teste);
    testePonteiro(pTeste); // Bota o endereco de memoria da variavel do tipo ponteiro pTeste

    printf("%d\n", teste);

    return 0;
}

void testeVariavel(int teste)
{            // Aqui nao funciona pq ele ta fazendo uma copia e somando 1
    ++teste; // Adiciona 1 ao valor recebido da variavel x
}

void testePonteiro(int *pX)
{
    ++*pX; // Adiciona 1 ao valor apontado por *pX
}