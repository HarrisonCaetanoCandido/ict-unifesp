#include <stdio.h>
#include <stdlib.h>
#define Max 10

typedef struct pilha{
    char string[Max];
    int topo;    
}Tpilha;

typedef Tpilha *Ppilha;

Ppilha cria_pilha(){
    Ppilha p;
    p = (Ppilha)malloc(sizeof(Tpilha));
    p->topo = -1;
    return p;
}

Ppilha liberar(Ppilha p){
    free(p);
    return NULL;
}

void push(Ppilha p, char c){
    p->topo++;
    p->string[p->topo] = c;
}

char pop(Ppilha p, int *tanto){
    char caractere;

    tanto++;
    caractere = p->string[p->topo];
    p->topo--;
    
    return caractere;
}

int main(){
    Ppilha pilha;
    pilha = cria_pilha();

    char string[Max],caractere;
    int tanto,i,soma;

    printf("Digite sua string: ");
    fgets(string,Max,stdin);

    i=0, tanto, soma=0;
    while(caractere != 'c'){
        caractere = pop(pilha,&tanto);
        if(caractere == string[i]){
            soma++;
        }
        i++;
    }

    if(soma == tanto){
        printf("Eh da forma WcM");
    }
    else
    {
        printf("Nao eh da forma WcM");
    }

    liberar(pilha);

    return 0;
}