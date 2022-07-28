#include <stdio.h>
#include <stdlib.h>

int digitos(int n){
    int cont = 1; // Se tiver 1 digito retornara 1

    if(n>=10){ // Se for maior que dez, entao tem mais de 1 digito
        n=n/10; // Joga em inteiros a quantidade de vezes que n eh maior que 10
        printf("\n%d\n",n);
        cont = cont + digitos(n); /* Aqui cont ja eh 1, entao seria cont=1+digitos(1), cont=2, cont=cont(1)+digitos(2), cont=3, cont=cont(2)+digitos(3), cont=4*/
        printf("\nteste: %d\n",n);
    }
    return cont;
}

int main(){
    int n,cont;

    printf("\nDigite um numero: ");
    scanf("%d",&n);

    cont=digitos(n);

    printf("\nDigitos: %d",cont);

    return 0;
}