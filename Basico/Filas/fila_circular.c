#include <stdio.h>
#include <stdlib.h>
# define max_fila 10

typedef struct{
    int itens[max_fila];
    int n; // indice para a quantidade de elementos na fila
    int ini; // indice para o inicio da fila
}Tfila;

Tfila *cria_fila();
int insere(Tfila *p,int val);
int retira(Tfila *p);
int incr_indice(int i);
void imprimir(Tfila* p);

int main(){
    Tfila *p;
    
    p=cria_fila();

    if(p==NULL){
        printf("Nao foi possivel alocar memoria!\n");
        return 0;
    }

    int val,op,inser,retir;
    do{
        printf("1 | Inserir\n");
        printf("2 | Retirar\n");
        printf("3 | Imprimir\n");
        printf("4 | Sair\n");
        printf("Selecione: ");
        scanf("%d",&op);
        switch (op)
        {
        case 1: // insere
        printf("Digite um valor: ");
        scanf("%d",&val);
        inser=insere(p,val);
        if(inser==0){printf("Tudo certo na insercao!\n");}
            break;
        case 2: // retira
        retir=retira(p);
        if(retir==0){printf("O primeiro elemento foi removido com sucesso!\n");}
            break;
        case 3: // ler
        imprimir(p);
            break;
        case 4: // sair
        printf("Programa encerrado!\n");
            break;
        default:
            break;
        }
    }while(op!=4);

    free(p);
    return 0;
}

Tfila *cria_fila(){
    Tfila *p;
    p=(Tfila*)malloc(sizeof(Tfila));
    p->ini=0;
    p->n=0;
    return p;
}

int insere(Tfila *p,int val){
    int fim,soma;
    if(p->n==max_fila){
        printf("Fila cheia!\n");
        return -1;
    }
    printf("p->ini: %d\n",p->ini);
    printf("p->n: %d\n\n",p->n);
    soma=p->ini+p->n;
    fim=(soma)%max_fila; // pega o incio + tamanho e pega o resto dessa soma, que sera igual a futura posicao na lista. Observe que sempre que o divisor for maior que o dividendo, o resto sera igual ao dividendo
    p->itens[fim]=val; // insere no fim da fila
    p->n++; // incrementa o tamanho
    printf("fim: %d\n",fim);
    printf("p->ini(fim): %d\n",p->ini);
    printf("p->n++: %d\n",p->n);
    return 0;
} // 0,1,2,3,4,5,6,7,8,9
  // |,|,|,i,#,#,#,#,f,| => Perceba que f nao tem valor, serve apenas como referencia para a proxima posicao de insercao no vetor

int retira(Tfila *p){ // 3, 4, 5 ,9 | , 4, 5, 9 => ,4, 5, 3 | 1/4= 1
    if(p->n==0){
        printf("Fila vazia!\n");
        return -1;
    }
    p->ini=incr_indice(p->ini);
    --(p->n);

    if(p->n==0){
        p->ini=0;
    }

    printf("p->ini: %d\n",p->ini);
    printf("p->n: %d\n",p->n);
    
    return 0;
}

int incr_indice(int i){ // de uso em filas circulares
    if(i==max_fila-1){
        return 0;
    }else{
        return i+1;
    }
}

void imprimir(Tfila* p){
    int i,fim;
    fim=p->ini+p->n;
    if(p->ini>0 && p->n==max_fila){
    for(i=0;i<p->ini;i++){
        printf("vet[%d]: %d\n",i,p->itens[i]);
    }
    for(i=p->ini;i<fim-1;i++){
        printf("vet[%d]: %d\n",i,p->itens[i]);
    }
    }else{
        for(i=p->ini;i<fim;i++){
        printf("vet[%d]: %d\n",i,p->itens[i]);
    }
    }
}