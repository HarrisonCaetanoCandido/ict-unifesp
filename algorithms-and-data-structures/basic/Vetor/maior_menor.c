#include <stdio.h>
#include <stdlib.h>

int main()
{
    int vetor[] = {10, 20, 15, 25};
    int temp;

    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            if (vetor[i] > vetor[j])
            {
                temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", vetor[i]);
    }
    return 0;
}