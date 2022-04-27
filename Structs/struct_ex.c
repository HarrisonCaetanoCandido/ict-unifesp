/*
Crie um programa que possui uma função que recebe como argumento um vetor de tamanho 5 de tipo estrutura 
sendo que essa estrutura deve armaenar um determinado horario no formato hh:mm:ss, peça que o usuario 
digite 5 horarios diversos que deverao ser armazenados no argumento recebido. 

Crie uma segunda funcao que recebera este mesmo vetir estrutura mas dessa vez a funcao devera apenas ler 
os valors armazenados no vetor estrutura mostrando uma mensagem apropriada*/
#include <stdio.h>
typedef struct{
    int hora,minutos,segundos;
}tipo_horario;

tipo_horario horario(tipo_horario x[]);
tipo_horario ler_registros(tipo_horario ler[]);

int main(){
    int n=5;
    tipo_horario vetor_h[n];

    horario(vetor_h); // como eh um vetor, vamos escrever no endereco de memoria do vetor que entra como argumento da funcao
    ler_registros(vetor_h);

    return 0;
}

tipo_horario horario(tipo_horario x[]){ 
    for(int i=0;i<5;i++){
        printf("\nRegistro %d | Digite o horario(hh:mm:ss): ",i);
        scanf("%d:%d:%d",&x[i].hora,&x[i].minutos,&x[i].segundos);
    }
}

tipo_horario ler_registros(tipo_horario ler[]){
    for(int i=0;i<5;i++){
        printf("%d:%d:%d\n",ler[i].hora,ler[i].minutos,ler[i].segundos);
    }
}