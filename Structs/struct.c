#include <stdio.h>
#include <conio.h> // mostrar enderecos de memoria

struct horario{
    int horas; // 4
    int minutos; // 4
    int segundos; // 4
    double teste; // 8
    char letra; // 1
};

int main(){
    struct horario agora; // cria uma variavel do tipo 'struct horario'. essa variavel possui um endereco de memoria proprio para aquele tipo de dado 'struct horario'

    agora.horas=15;
    agora.minutos=17;
    agora.segundos=30;
    agora.teste=45.6/123.4;
    agora.letra='e';

    struct horario depois; // cria uma variavel do tipo 'struct horario'. essa variavel possui um endereco de memoria proprio para aquele tipo de dado 'struct horario'
    depois.horas=agora.horas+10;
    depois.minutos=agora.minutos;
    depois.segundos=agora.segundos*4;
    depois.teste=50.55/123;
    depois.letra='a';

    system("clear||cls");
    printf("Endereco de memoria de agora: %d\n",&agora);
    printf("Endereco de memoria de 'agora.horas': %d\n",&agora.horas);
    printf("Endereco de memoria de 'agora.minutos': %d\n",&agora.minutos);
    printf("Endereco de memoria de 'agora.segundos': %d\n",&agora.segundos);
    printf("Endereco de memoria de 'agora.teste': %d\n",&agora.teste);
    printf("Endereco de memoria de 'agora.letra': %d\n",&agora.letra);
    printf("sizeof(agora): %d bytes\n",sizeof(agora));
    printf("sizeof(agora.horas): %d bytes\n",sizeof(agora.horas));
    printf("sizeof(agora.minutos): %d bytes\n",sizeof(agora.minutos));
    printf("sizeof(agora.segundos): %d bytes\n",sizeof(agora.segundos));
    printf("sizeof(agora.teste): %d bytes\n",sizeof(agora.teste));
    printf("sizeof(agora.letra): %d bytes\n",sizeof(agora.letra));
    printf("\n");
    printf("Endereco de memoria de depois: %d\n",&depois);
    printf("Endereco de memoria de 'depois.horas': %d\n",&depois.horas);
    printf("Endereco de memoria de 'depois.minutos': %d\n",&depois.minutos);
    printf("Endereco de memoria de 'depois.segundos': %d\n",&depois.segundos);
    printf("Endereco de memoria de 'depois.teste': %d\n",&depois.teste);
    printf("Endereco de memoria de 'depois.letra': %d\n",&depois.letra);
    printf("sizeof(depois): %d bytes\n",sizeof(depois));
    printf("sizeof(depois.horas): %d bytes\n",sizeof(depois.horas));
    printf("sizeof(depois.minutos): %d bytes\n",sizeof(depois.minutos));
    printf("sizeof(depois.segundos): %d bytes\n",sizeof(depois.segundos));
    printf("sizeof(depois.teste): %d bytes\n",sizeof(depois.teste));
    printf("sizeof(depois.letra): %d bytes\n",sizeof(depois.letra));
    printf("\n");
    printf("Pressione qualquer tecla para continuar...");getch();system("clear||cls");
    printf("Valores nos campos das structs\n");
    printf("agora.horas: %d\n",agora.horas);
    printf("agora.minutos: %d\n",agora.minutos);
    printf("agora.segundos: %d\n",agora.segundos);
    printf("agora.teste: %f\n",agora.teste);
    printf("agora.letra: %c\n",agora.letra);
    printf("\n");
    printf("depois.horas: %d\n",depois.horas);
    printf("depois.minutos: %d\n",depois.minutos);
    printf("depois.segundos: %d\n",depois.segundos);
    printf("depois.teste: %f\n",depois.teste);
    printf("depois.letra: %c",depois.letra);

    return 0;
}
