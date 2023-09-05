/*
    Nome: Harrison Caetano Cândido
    RA: 156264
    Turno: Noturno
*/
/*
    Implemente uma versao recursiva do algoritmo de ordenacao em memoria interna
    Insertion Sort usando uma versao iterativa da busca binaria para localizar a
    posicao exata onde a chave deve ser posicionada. A busca binaria permite otimizar
    a localizacao da posicao correta da chave de O(n) para O(log n).
*/

#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *vet, int i, int n);
int binary_search(int *vet, int x, int n);

int binary_search(int *vet, int x, int n)
{
    int ini, fim, meio;
    ini = 0;
    fim = n;

    while (ini <= fim)
    {
        meio = (ini + fim) / 2;
        
        if (x >= vet[meio]) // direita, se x for maior do que o valor do meio ele anda pra direita pra buscar mais valores até estourar o while: isto é até quando ver que o vetor até a ultima posicao de fim esta ordenado ou até quando achar uma posição que x < vet[meio] 
            ini = meio + 1;

        if(x < vet[meio]) // esquerda, entao tem que colocar na posicao em que x é menor do que meio
            fim = meio - 1;
    }
    return ini;
}

void insertion_sort(int *vet, int i, int n)
{
    int j, pos, chave;
    j = i;
    i = j - 1;
    chave = vet[j];

    pos = binary_search(vet, chave, i); // busca a posicao para colocar a chave

    while (j > pos) // enquanto o while nao atingir a posicao que a chave deve ser colocada vamos ordenar a esquerda do vetor
    {
        vet[j] = vet[j - 1]; 
        j = j - 1;
    }

    vet[pos] = chave;
    j = i + 1;

    printf("%d %d %d\n", (n - i - 1), chave, pos); // O nivel de recursao, o valor da chave e a localizacao do elemento chave no vetor, conforme determinado pela busca binaria

    if (j < n - 1)
        insertion_sort(vet, (++j), n);
}

int main()
{
    int *vet, n, i;

    scanf("%d", &n); // Na primeira linha, deve-se ler o tamanho n da sequencia de numeros a ser digitada

    vet = (int *)malloc(n * sizeof(int));
    if (vet == NULL)
        return 0;

    for (i = 0; i < n; i++)
        scanf("%d", &vet[i]); // Na segunda linha, deve-se ler a lista de n inteiros distintos a ser ordenada. Os elementos da lista sao separados por um espaco em branco

    insertion_sort(vet, 1, n);

    for (i = 0; i < n; i++)
        printf("%d ", vet[i]);

    free(vet);

    return 0;
}