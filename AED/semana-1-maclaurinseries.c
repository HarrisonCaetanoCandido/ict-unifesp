#include <stdio.h>
#include <math.h>

/*
    Escreva algoritmos para resolver os seguintes problemas e, se
    possível, determine a complexidade do algoritmo desenvolvido:

    ✓ Calcule o valor de e^x, sendo x um valor de entrada e 'e' calculado da
    seguinte forma (calcular até que a fração seja < 0.001)

    -------------------------------------------------------------------------------------------------

    Sabendo que ao multiplicar um numero fatorial pelo seu proximo nós obtemos o 
    fatorial desse proximo como demonstrado na logica 1.1(a) abaixo:

    1!*2 = 2!, 2!*3 = 3!, ...

    ...e tendo em mente que a serie de maclauren para e^x eh da seguinte forma:

    e^x = 1 + x/1! + x^2/2! + x^3/3! + x^4/4!... 

    ...tomaremos a variavel fat=fat*i como denominador, usaremos pow(x,y) para o numerador das funcoes
    e usaremos uma variavel 'funcao' = 1 em que iremos somar as fracoes dentro de um laco      


         O(1)  =  O(yeah) - constante
    O(log n)   =  O(nice) - logarítmica
         O(n)  =    O(k)  - linear
    O(n log n) = O(k-ish) - logarítmica linear
        O(n^2) =   O(my)  - quadrática
        O(2^n) =   O(no)  - subexponencial
        O(n^n) = O(fuck)  - exponencial
         O(n!) = O(mg!)   - fatorial
*/

int main(){
    int precisao;
    float entrada;
    float funcao=1;
    float fat=1;

    printf("Digite um valor 'x' de entrada: ");
    scanf("%f",&entrada); // O(1)

    printf("Digite a precisao que deseja alcancar(numero de fracoes, recomendo 100): ");
    scanf("%d",&precisao); // O(1)

    for(int i=1;i<=precisao;i++){       //funcao = 1 + (2^1)/1*1 + (2^2)/1*2 + (2^3)/2*3 + (2^4)/6*4 ...
        fat*=i;                        // Transcrevendo temos 1!*1+1=2!, ou melhor k=j, k!*k+1 = k+1!
        funcao+=(pow(entrada,i))/fat; //funcao=funcao+(pow(entrada,i))/fat;
    }                                // O(N)*(O(N!)+(O(N^N)/O(N!)) = O(N!)

    printf("\nf(x) = e^%.2f = %f",entrada,funcao); 

    return 0;
}

// Nosso algoritmo parece ser de complexidade O(N!)