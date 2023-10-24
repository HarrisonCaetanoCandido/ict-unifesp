#include <stdio.h>
#include <stdlib.h>

int main()
{
    int escolha, Vetor[3], i;

    do
    {
        printf("1 | Fazer a soma das posicoes do vetor sem ponteiros\n");
        printf("2 | Fazer a soma das posicoes do vetor com ponteiros\n");
        printf("3 | Sair\n");
        scanf("%d", &escolha); // O(1)
        switch (escolha)
        {
        case 1:
            for (i = 0; i < 3; i++)
            { // O(N)
                printf("\nDigite um inteiro na posicao %d do Vetor: ", i);
                scanf("%d", &Vetor[i]); // O(1)
            }

            printf("\nResultado da soma sem ponteiros: %d\n", somavetor(Vetor)); // O(N)
            break;
        case 2:
            for (i = 0; i < 3; i++)
            { // O(N)
                printf("\nDigite um inteiro na posicao %d do Vetor: ", i);
                scanf("%d", &Vetor[i]); // O(1)
            }

            printf("\nResultado da soma com ponteiros: %d\n", somavetorcomponteiro(Vetor, 3));
            break;
        case 3:
            printf("Obrigado pela visita!\n");
            break;

        default:
            printf("Digite um valor valido!\n");
            break;
        }
    } while (escolha != 3);
    return 0;
}

int somavetor(int Vetor[])
{ // O(N)
    int soma = 0;
    for (int i = 0; i < 3; i++)
    {                           // O(N)
        soma = soma + Vetor[i]; // O(N)
    }
    return soma;
} // Acaba que a complexidade aqui eh de O(N) * O(N) = O(N^2)

int somavetorcomponteiro(int Vetor[], const int n)
{ // O(M)
    int soma = 0;
    int *ponteiro, *const FinaldoVetor = Vetor + n; // Significa que ele vai para o ultimo endereco de memoria dentro do vetor + 1, ou seja o vetor tem agora 4 posicoes
    for (ponteiro = Vetor; ponteiro < FinaldoVetor; ponteiro++)
    {                      // ponteiro=vetor[0]|ponteiro=vetor[1]|ponteiro=vetor[2]|ponteiro!=vetor[3]=FinaldoVetor
        soma += *ponteiro; // O(M)
    }
    return soma; // O(1)
} // Acaba que a complexidade aqui eh de O(N) * O(N) = O(N^2)

// Somando as complexidades nao constantes das duas funcoes, temos O(N^2) + O(M^2) = O(N^2) + O(M^2)

// Ignorando todas as complexidades O(1), temos que a complexidade do nosso algoritmo é O(N^2) + O(M^2)