#include <stdio.h>
#include <stdlib.h>

int remove_dup(float v[], int *n);

int main()
{
    int *vet;
    int i, n;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    vet = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        scanf("%d", &vet[i]);
    }
    printf("\n\n");
    if (remove_dup(vet, &n) == 0)
    {
        printf("Nao ha elementos repetidos no vetor.\n");
    }
    else
    {
        printf("tam: %d", n);
        printf("O vetor resultante eh:\n");
        for (i = 0; i < n; i++)
        {
            printf("%d ", vet[i]);
        }
    }
    printf("\n\n");

    free(vet);

    return 0;
}

int remove_dup(float v[], int *n)
{
    int i, j, aux, k;
    i = 0;
    aux = *n;
    while (i < *n)
    {
        j = i + 1;
        while (j < *n)
        {
            if (v[i] == v[j])
            {
                for (k = j; k < (*n) - 1; k++)
                {
                    v[k] = v[k + 1];
                    (*n)--;
                }
                aux++;
            }
            j++;
        }
        i++;
    }
    if (aux == *n)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}