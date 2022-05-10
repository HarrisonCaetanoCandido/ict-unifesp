/*
Você, que é dono de uma editora, ficou sabendo que haverá uma feira de livros na
sua região, então levou seus livros para vender lá. A expectativa é que vendam muitos
livros para muitos clientes, então, para agilizar nas vendas, você precisa criar um
programa que calcula automaticamente o número de livros que o cliente consegue
comprar e o troco de você tem que devolver.
Você atenderá um número N de clientes e deverá alocar dinamicamente um vetor
de registro de tamanho N, em que em cada registro deve conter um valor D, que é o
dinheiro que o cliente possui, Q que indica a quantidade de livros que o cliente tem
interesse, e P, que é um vetor com o preço de cada livro que ele deseja comprar, por
ordem de preferência. Você deve calcular quantos livros ele consegue comprar e o troco
que restará da compra. Faça as verificações de erros! É obrigatório que o programa tenha
duas função, sendo uma para a leitura dos dados de cada cliente e a outra para o cálculo
da saída.
*/

// Problema: Programa que calcula automaticamente o numero de livros que o cliente consegue comprar e o troco que devo devolver

#include <stdio.h>
#include <stdlib.h>

typedef struct CLIENTE{
    float D; // dinheiro do cliente
    int Q; // quantidade de livros que o cliente tem interesse
    float P[]; // preco de cada livro que o cliente deseja comprar, por ordem de preferencia
}Cliente;

void entrada(Cliente *vet,int nclientes);
void saida(Cliente *vet[],int nclientes);

int main(){
    int nclientes,i;

    scanf("%d",&nclientes); // Numero de clientes:

    while(nclientes<1 || nclientes >100){
        scanf("%d",&nclientes); // Digite a quantidade de clientes novamente: 
    }

    Cliente *vet[nclientes];

    for(i=0;i<nclientes;i++){
        vet[i]=(Cliente*)malloc(sizeof(Cliente));

        if(vet==NULL){
            return 0;
        }
        
        entrada(vet[i],nclientes);
    }
    saida(vet,nclientes);

    for(i=0;i<nclientes;i++){
        free(vet[i]);
    }

    return 0;
}

void entrada(Cliente *vet, int nclientes){
    int j;
        // D>=0, dinheiro do cliente
        scanf("%f",&vet->D); // Digite a quantidade de dinheiro que o cliente possui:

        while(vet->D<0){
            scanf("%f",&vet->D);
        }

        // Q>=0, qtd de livros de interesse do cliente
        scanf("%d",&vet->Q); // Digite a quantidade de livros de interesse do cliente:

        while(vet->Q<0 || vet->Q>100){
            scanf("%d",&vet->Q); // Digite a quantidade de livros de interesse do cliente novamente:
        }

        // P>=0, de cada livro que o cliente deseja comprar
        j=0;
        while(j<vet->Q){
            scanf("%f",&vet->P[j]); //Digite o preco do produto %d:

            while(vet->P[j]<0){
                scanf("%f",&vet->P[j]); // Digite o preco do produto %d novamente: 
            }
            j++;
        }
}

void saida(Cliente *vet[],int nclientes){ // n de livros comprados | Troco
    float din,troco,soma,*p,*fim;
    int i,j,cont=0;

    for(i=0;i<nclientes;i++){
        din=0.00;soma=0.00;troco=0.00;cont=0;
        din=vet[i]->D;
        
        fim=vet[i]->P+vet[i]->Q;
        for(p=vet[i]->P;p<fim;p++){
            soma=soma+*p;
        }
    
        troco=din-soma;
        
            for(j=0;j<vet[i]->Q;j++){
                din=din-vet[i]->P[j];
                if(din>=0){
                    cont++;
                }
            }
            if(troco>=0){
                printf("%d %.2f\n",cont,troco);
            }else{
                if(troco<0){
                    printf("%d %.2f\n",cont,vet[i]->D);
                }
            }
    }
    
}