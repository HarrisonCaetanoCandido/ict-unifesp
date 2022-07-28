#include <stdio.h>
#include <stdlib.h>

/*
    Escreva algoritmos para resolver os seguintes problemas e, se
    possível, determine a complexidade do algoritmo desenvolvido:

    Verificar se uma dada matriz de entrada é matriz identidade, triangular
    superior (todos os elementos abaixo da diagonal principal são nulos e
    os demais não podem ser todos nulos) ou triangular inferior.
*/

int main()
{
    int i, j, l, c, identidade, naoidentidade;

    printf("Digite quantas linhas tera a matriz: ");
    scanf("%d", &l);

    printf("Digite quantas colunas tera a matriz: ");
    scanf("%d", &c);

    int matriz[l][c];

    for (i = 0; i < l; i++)
    { // O(N)
        for (j = 0; j < c; j++)
        { // O(N)
            printf("Digite o elemento da posicao [%d][%d] na matriz: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    for (i = 0; i < l; i++)
    { // O(N)
        for (j = 0; j < c; j++)
        { // O(N)
            if (i == j)
            { // verifica diagonal
                if (matriz[i][j] != 1 || l != c)
                {
                    // printf("Matriz nao eh identidade\n");
                    identidade = 0;
                }
                else
                {
                    identidade = 1; // eh identidade
                }
            }
            else
            { // verifica o resto menos a diagonal
                if (matriz[i][j] != 0)
                {
                    identidade = 0; // nao eh identidade
                }
                else
                {
                    if (identidade == 1) // se for identidade
                        identidade = 1;
                }
            }
        }
    } // 2O(N^2)
      // matriz triangular superior/inferior
    /*ex: matriz 3 x 3

        | i0j0 i0j1 i0j2 |
        | i1j0 i1j1 i1j2 |
        | i2j0 i2j1 i2j2 |

    */
    int naotriangular_superior = 0, naotriangular_inferior = 0;
    for (i = 0; i < l; i++)
    { // O(N)
        for (j = 0; j < c; j++)
        { // O(N)
            if (i > j)
            {
                if (matriz[i][j] != 0)
                    naotriangular_superior = 1; // nao eh triangular inferior
            }
        }
    }
    for (i = 0; i < l; i++)
    { // O(N)
        for (j = 0; j < c; j++)
        { // O(N)
            if (i < j)
            {
                if (matriz[i][j] != 0)
                {
                    naotriangular_inferior = 1;
                }
            }
        }
    }
    for (i = 0; i < l; i++)
    { // O(N)
        printf("|  ");
        for (j = 0; j < c; j++)
        { // O(N)
            printf("%d ", matriz[i][j]);
        }
        printf(" |");
        printf("\n");
    }
    if (identidade == 1)
    {
        printf("A Matriz eh identidade\n");
        return 0;
    }
    if (naotriangular_inferior == 0)
    {
        printf("A matriz eh triangular inferior\n");
        return 0;
    }
    if (naotriangular_superior == 0)
    {
        printf("A matriz eh triangular superior\n");
        return 0;
    }
    if (identidade == 0)
    {
        printf("A Matriz nao eh identidade\n");
    }
    if (naotriangular_inferior == 1)
    {
        printf("A matriz nao eh triangular inferior\n");
    }
    if (naotriangular_superior == 1)
    {
        printf("A Matriz nao eh triangular superior\n");
    }

    return 0;
}

// 5O(N^2), complexidade O(N^2)