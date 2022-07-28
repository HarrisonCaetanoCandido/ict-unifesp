#include <stdio.h>  //entrada e saida
#include <stdlib.h> //alocacao dinamica etc

int main()
{
    int *p; // ponteiro para int, se transformará no meu vetor
    int i, qtd_elementos;

    /*
    Alocacao dinamica nada mais eh do que acolcar memoria enquanto
    o programa ja esta rodando. Aqui a variavel ou vetor tera um tamanho definido enquanto o programa roda

    Estatica eh alocar memoria antes do programa rodar, sera imutavel. O vetor ou variavel tera um tamanho predefinido
    */

    printf("Digite a quantidade de elementos do vetor: ");
    scanf("%d", &qtd_elementos);

    // Alocar espaco na memoria para armazenar os elementos digitados
    // qtd_elementos * sizeof(int) => Seriam quantos bytes ocupam a quantidade de elementos inteiros na memória
    // malloc('quantidade de bytes que os elementos ocupam') - o Malloc faz a requisição/reserva na memória da quantidade de bytes que aqueles elementos necessitariam
    // (int *) - Visto que Malloc() retorna *void (sem tipo), converteremos *void para um vetor de inteiros
    // atribui ao vetor 'p' que terá o espaço de memória necessário para n elementos inteiros

    p = (int *)(malloc(qtd_elementos * sizeof(int)));

    if (p == NULL)
    {
        printf("\nErro na Alocacao de memoria!\n");
    }
    else
    {
        for (i = 0; i < qtd_elementos; i++)
        {
            printf("\nDigite o numero para o indice [%d]: ", i + 1);
            scanf("%d", &p[i]);
        }
        printf("\n");
        for (i = 0; i < qtd_elementos; i++)
        {
            printf("[%d] Elemento: %d\n", i + 1, p[i]);
        }
        free(p); // Diz para o programa que eu nao quero mais o espaco de memoria alocado
    }

    return 0;
}