#include <stdio.h>

struct horario{ // define um tipo struct
    int horas; // 4
    int minutos; // 4
    int segundos; // 4
};

struct horario teste(struct horario x); // eh uma funcao do tipo 'struct horario' que recebe uma variavel x do tipo 'struct horario' 

int main(){
    struct horario agora;

    agora.horas=10;
    agora.minutos=42;
    agora.segundos=58;
    printf("Endereco de memoria de 'agora'(variavel original): %d\n",&agora);

    struct horario proxima;
    printf("Endereco de memoria de 'proxima'(recebe os dados da variavel copia): %d\n",&proxima);
    proxima=teste(agora); // retorna valors alterados para aquela variavel

    printf("\nDepois de alterar(variavel 'proxima' que recebe dados de 'x'):\n"); // eh quase uma copia da variavel x que eh uma copia da variavel agora
    printf("Horas: %d\n",proxima.horas);
    printf("Minutos: %d\n",proxima.minutos);
    printf("Segundos: %d",proxima.segundos);
    
    return 0;
}

struct horario teste(struct horario x){ // cria uma copia da variavel

    printf("Endereco de memoria de x(variavel copia de agora): %d\n\n",&x);
    printf("Antes de alterar(variavel original):\n");
    printf("Horas: %d\n",x.horas);
    printf("Minutos: %d\n",x.minutos);
    printf("Segundos: %d\n",x.segundos);

    x.horas=105;
    x.minutos=120;
    x.segundos=130;

    return x; // retorna uma struct, ou seja retorna todos os campos do tipo de struct que a funcao foi declarada
}