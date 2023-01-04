/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Noturno
*/
/*
  Considere a existencia de uma lista A[n] ordenada contendo n numeros inteiros e
  um dado inteiro x que nao esta presente na lista. O problema consiste em determinar
  entre qual par de itens na lista esta o item x, isto e, encontrar A[i] e A[i+ 1] de tal forma
  que A[i] < x < A[i + 1], para 1 ≤ i < n, ou informar que nao eh possivel encontrar
  este par de elementos, ou seja, caso x < A[0] ou x > A[n].

  Usando o algoritmo de Busca Binaria, crie um algoritmo para resolver este problema.
  Para isso, considere as seguintes condicoes:

  1. Seu algoritmo deve ser recursivo;
  2. Use alocacao dinamica. Memoria alocada dinamicamente deve ser desalocada;
  3. Nenhuma variavel global deve ser utilizada;
  4. O codigo-fonte  ́ deve ser escrito em C;
*/

#include <stdio.h>
#include <stdlib.h>

int binary_search(int *vet, int x, int n);

int binary_search(int *vet, int x, int n)
{
  int meio, calibre;

  if (n <= 0)
    return -1;

  // impar 7 / 2 = (0 + 7) 2, pois 0,1,2,3,4,5,6 | par 6 / 2 = (0 + 5)/2 = 3, pois 0,1,2,3,4,5
  meio = ((n - 1) / 2); // em c um numero continuo eh truncado para baixo para inteiro, entao no segundo exemplo o meio seria 2

  if (vet[meio - 1] == (x - 1) && vet[meio] == (x + 1))
    return meio;

  if (vet[meio] > x)
    return binary_search(vet, x, meio); // passa meio como tamanho de n, busca apenas a esquerda do meio inicial

  if (vet[meio] < x)
  {
    calibre = binary_search(&vet[meio + 1], x, (n - 1 - meio)); // manda o endereço de um subvetor

    if (calibre != -1)
      return calibre + 1 + meio;
    return -1;
  }

  if (vet[meio] != x)
    return meio;
  else
    return -1;
}

int main()
{
  int x, n, i, meio, *vet, indice;

  scanf("%d %d", &x, &n); // valor do item x, numero (n) de elementos na lista

  vet = (int *)malloc(n * sizeof(int));
  if (vet == NULL)
    return 0;

  for (i = 0; i < n; i++)
    scanf("%d", &vet[i]);

  indice = binary_search(vet, x, n);

  indice == -1 ? printf("nao ha intervalo valido") : printf("%d %d", vet[indice - 1], vet[indice]);

  free(vet);

  return 0;
}