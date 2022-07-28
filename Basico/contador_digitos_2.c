#include <stdio.h>
int contador_digitos(int digito);
/*
100/10=10/10=1/10=0 = 2+1
1000/10=100/10=10/10 = 3+1
10000/10=1000/10=100/10=10 =  4+1
*/

int contador_digitos(int digito){
    int soma=1;
    while(digito>=10){
        digito=digito/10; //100/10=10/10=
        soma+=1;// 1+1=2,2+1=3,3+1=4
        printf("digito(while): %d\n",digito);
    }
    return soma;
}

int main(){
    int tam,digito;
    //long long digito; // mesmo usando long long parece que ta dando overflow

    printf("Digito: ");
    scanf("%d",&digito);

    tam=contador_digitos(digito);

    printf("Soma: %d",tam);

    return 0;
}