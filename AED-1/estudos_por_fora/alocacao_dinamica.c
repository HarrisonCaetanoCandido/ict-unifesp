#include <stdio.h>
#include <stdlib.h>

struct x
{
    int a; // 4 bytes
    int b; // 4 bytes
    int c; // 4 bytes
};

int main()
{ 
/*
int x; //Vai na memoria ram do notebook e solicita 4 bytes para a variavel 'x' do tipo inteiro
double y; //Vai na memoria ram do notebook e solicita 8 bytes para a variavel 'y' do tipo double

printf("%d\n",sizeof(x)); // sizeof traz o tamanho da variavel em bytes
printf("%d\n",sizeof(y));
printf("%d\n",sizeof(int)); // Posso colocar um tipo de dado diretamente tambem
printf("%d\n",sizeof(double)); //sizeof pode ler praticamente qualquer tipo de dado

struct x estrutura;

printf("%d\n",sizeof(estrutura));

short x;
x = 10;

int c[10];

short *p = &x; //Aponta para o endereco de memoria da variavel x

/*int *p = malloc(sizeof(int)); /* malloc - memory allocation, pede ao SO o tamanho do bloco de memoria para a variavel ou tipo usado.
                A funcao retorna pra nos o endereco desse bloco de memoria, em que o *p aponta para esse endereco*/

    // int *p = malloc(10 * sizeof(int)); // <-- Se quisessemos trabalhar com um vetor. *apontar-endereco = endereco-bloco-memoria-no-SO(tamanho-memoria)

    int *ponteiro = (int *)malloc(10 * sizeof(int)); /* Visto que malloc() retorna void (generico), temos que dizer qual é o tipo de dado para a variavel *p tipo inteiro
                                                senão da pau. Basicamente antes vc tava fazendo inteiro aponta para void, assim daria erro, logo vamos fazer o casting,
                                                que força o ponteiro tipo void (malloc) a ser do tipo inteiro, que é o mesmo do nosso ponteiro *p do tipo inteiro, logo
                                                teriamos *inteiro = *inteiro(malloc)->bloco-de-memoria. Sendo assim nosso endereco-bloco-memoria está agora disponivel
                                                fisicamente pra gente usar.*/

    *ponteiro = 1000; // Escreve mil no endereco de memoria apontado no SO

    /*printf("%d",*p); /* É importante dizer que, caso a variavel *p nao esteja escrevendo nada no endereco-bloco-memoria, ela provavelmente vai apontar para qualquer
                        endereco dentro do bloco-memoria alocado, ou seja, se tiver lixo la, quando der printf esse lixo ira aparecer pra gente*/

    /*Outro ponto interessante eh que, se por acaso a memoria ram do computador ja estiver cheia, e voce estiver tentando alocar memoria, pode ser que voce nao consiga
      e o valor retornado sera NULL, ou seja ponteiro aponta para lugar nenhum. Sendo assim, podemos escrever: */

    if (ponteiro == NULL)
    {
        printf("A memoria nao foi alocada corretamente!\n");
    }
    else
    {
        printf("%d\n", *ponteiro);

        free(ponteiro); /* Apos a alocacao, quando o programa encerra, ele ira devolver memoria para o SO e apagar o que foi escrito, porém caso quisessemos devolver memoria
                           sem apagar o que foi escrito enquanto o programa roda, teriamos entao que usar o operador free*/

        int *memoria = (int *)malloc(10 * sizeof(int)); /* Criando outro ponteiro e alocando memoria pra ele, temos que, apos dar free no primeiro ponteiro, estando o seu antigo
                                                           endereco de memoria desalocado, poderia ocorrer de a variavel *memoria apontar para esse antigo endereco de memoria e
                                                           quando dessemos o printf, o valor que ficou escrito poderia aparecer pra gente como se fosse lixo de memoria. Ou seja,
                                                           reforca pra gente a importancia de sempre escrever no endereco de memoria apos ser alocado.*/
    }

    return 0;
}