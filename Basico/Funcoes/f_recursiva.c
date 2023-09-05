#include <stdio.h>

int fatorial(int x);

int fatorial(int x){
    int resultado;
    if(x==0){
        resultado=1;
    }else{
        resultado = x * fatorial(x-1);
        /*          3 * fatorial(3-1) => 
                    2 * fatorial(2-1) => 
                    1 * fatorial(1-1) => resultado=1; |
--------------------------------------------------------------------------------
                    1 * resultado = 1*1 = resultado => 
                    2 * resultado = 2*1 = resultado => 
                    3 * resultado = 3*2 = resultado*/
    }
    return resultado;
}

int main(){
    int x,fat;
    printf("Digite um valor: ");
    scanf("%d",&x);

    fat=fatorial(x);

    printf("Fatorial: %d",fat);
    return 0;
}