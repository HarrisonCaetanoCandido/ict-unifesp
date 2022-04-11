#include <stdio.h>
#include <stdlib.h>

int main(){
    int i,Idade[5];
    for(i=0;i<5;i++){ //O(N)
        printf("Digite a idade na posicao %d do vetor: ",i);
        scanf("%d",&Idade[i]);
    }

    int *Maior;
    int *Menor;

    descobrir_idade(Idade,Maior,Menor);

    return 0;
}

void descobrir_idade(int Idade[],int *Maior, int *Menor){
    Maior=&Idade[0];Menor=&Idade[0];
    int i,repeticao_idade_maior=0,repeticao_idade_menor=0;
    for(i=0;i<5;i++){ //O(N)
        if(Idade[i]>*Maior){
            Maior=&Idade[i];
        }else{
            if(Idade[i]<*Menor){
                Menor=&Idade[i];
            }
        }
    }
    for(i=0;i<5;i++){ //O(N)
        if(*Maior==Idade[i]){
            repeticao_idade_maior++; //O(N)
        }
        if(*Menor==Idade[i]){
            repeticao_idade_menor++; //O(N)
        }
    }
    printf("Maior idade: %d | Repeticoes: %d\n",*Maior,repeticao_idade_maior);
    printf("Menor idade: %d | Repeticoes: %d\n",*Menor,repeticao_idade_menor);
}

//Complexidade: O(N) + O(N) + O(N)*(O(N) + O(N)) = 2O(N) + 2O(N^2)

//Nossa funcao de complexidade eh f(n^2), da ordem de no maximo O(N^2)