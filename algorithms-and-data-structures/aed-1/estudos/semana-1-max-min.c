/*
    Definicoes iniciais e Notacao assintotica
*/
#include <stdio.h>
#include <stdlib.h>
#define n 3

int main()
{
    int A[n];

    for (int i = 0; i < n; i++)
    {
        printf("Digite um numero na posicao %d: ", i + 1);
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nNumeros dentro do nosso vetor: %d", A[i]);
    }

    int *Max = A; // Aponta para A[0]
    int *Min = A; // Aponta para A[0]

    MaxMin1(A, Max, Min);
    MaxMin2(A, Max, Min);
    MaxMin3(A, Max, Min, n);

    return 0;
}

void MaxMin1(int A[n], int *Max, int *Min)
{
    for (int i = 1; i < n; i++)
    {
        if (A[i] > *Max)
        {
            Max = &A[i];
        }
        if (A[i] < *Min)
        {
            Min = &A[i];
        }
    }
    printf("\nValor maximo: %d", *Max);
    printf("\nValor minimo: %d", *Min);
    /*A logica aqui eh basicamente a seguinte:

    Sendo *Max = vetor na posicao zero(inicial) e *Min = vetor na posicao zero(inicial),
    iremos comparar se algum valor dentro do vetor é maior do que o valor que Max aponta,
    que é o A[0](inicial), e também iremos comparar se algum valor dentro do vetor é menor
    do que A[0](inicial), ou seja A[0] é nossa posicao, ou melhor, nosso endereco de
    referencia*/
}

void MaxMin2(int A[n], int *Max, int *Min)
{
    for (int i = 1; i < n; i++)
    {
        if (A[i] > *Max)
        {
            Max = &A[i];
        }
        else
        {
            if (A[i] < *Min)
            {
                Min = &A[i];
            }
        }
    }
    printf("\nMax otimizado: %d", *Max);
    printf("\nMin otimizado: %d", *Min);
}

void MaxMin3(int A[n], int *Max, int *Min, int x)
{
    x = n;
    int FimDoAnel, i;
    if ((x % 2) > 0)
    {
        A[n] = A[n - 1];
        FimDoAnel = n;
    }
    else
    {
        FimDoAnel = n - 1;
        if (A[0] > A[1])
        {
            Max = &A[0];
            Min = &A[1];
        }
        else
        {
            Max = &A[1];
            Min = &A[0];
        }
        i = 2;
        while (i < FimDoAnel)
        {
            if (A[i] > A[i + 1])
            {
                if (A[i] > *Max)
                {
                    Max = &A[i];
                }
                if (A[i + 1] < *Min)
                {
                    Min = &A[i + 1];
                }
            }
            else
            {
                if (A[i] < *Min)
                {
                    Min = &A[i];
                }
                if (A[i + 1] > *Max)
                {
                    Max = &A[i + 1];
                    i = i + 2;
                }
            }
        }
        printf("\nMax mais otimizado ainda: %d", *Max);
        printf("\nMin mais otimizado ainda: %d", *Min);
    }
}