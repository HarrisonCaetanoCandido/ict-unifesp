#include <stdio.h>
#include <stdlib.h>  

#define max_fila_cliente 100
#define MAX_FILA 10000

typedef struct Atend{//i funcionarios
int v;
int tempo;
}Atendimento;

typedef struct sFuncionario{// Define a fila de funcionarios
  Atendimento *Funcionario;
  int n; /*numero de elementos armazenados na fila*/
  int ini; /* indice para o inicio da fila */
} sFuncionario;

typedef sFuncionario *PFuncionario;

PFuncionario cria_funcionario(){ // aloca memoria para a fila de funcionarios
  sFuncionario *fila = (sFuncionario*) malloc (sizeof (sFuncionario));
  fila->n = 0;
  fila->ini = 0;
  return fila;
}

typedef struct sCliente{// define a fila cliente
  int *itens; // cria os nós da fila
  int n; /*numero de elementos armazenados na fila*/
  int ini; /* indice para o inicio da fila */
} sCliente;

typedef sCliente *PCliente;

PCliente cria_cliente(){
  sCliente *fila = (sCliente*) malloc (sizeof (sCliente));
  fila->n = 0;
  fila->ini = 0;
  return fila;
}

void insere_funcionario (PFuncionario funcionario, int n);
void insere_cliente(sCliente *Cliente, int m);
void saida (sFuncionario *funcionario, int n, sCliente *Cliente, int m);
void retira (sCliente *p, int* remover,int M);

int main(void){

  sFuncionario *funcionario;
  sCliente *cliente;

  funcionario = cria_funcionario(); // recebe o enereco da fila
  cliente = cria_cliente(); // recebe o enereco da fila
  
  int n,m;
  scanf("%d",&n);//faz a leitura da variavel n  
  scanf("%d",&m); //faz a leitura da variavel m]

  insere_funcionario(funcionario,n); // endereco da fila funcionario, tamaho da fila
  insere_cliente(cliente,m);
  saida (funcionario, n, cliente, m);


  free(funcionario->Funcionario);
  free(cliente->itens);
  free(funcionario);
  free(cliente);
  
  return 0;    
}

void insere_funcionario (PFuncionario funcionario, int n){
  int i;
  
  funcionario->Funcionario = (Atendimento *)malloc(n * sizeof(Atendimento)); // aloca memoria
  
  for (i=0; i<n; i++){
    
    scanf("%d",&funcionario->Funcionario[i].v); // insere vi no iesimo funcionario
    
    while(funcionario->Funcionario[i].v < 1 || funcionario->Funcionario[i].v > MAX_FILA){
      scanf("%d",&funcionario->Funcionario[i].v); // insere vi no iesimo funcionario caso nao atenda aos requisitos de ser maior igual a 1 ou menor igual a 10000
    }
    funcionario->n++;
  }
  
}

void insere_cliente(sCliente *Cliente, int m){
  int i;
  
  Cliente->itens = (int*)malloc(m * sizeof(int)); // aloca memoria
  
  for (i=0; i<m; i++){
    
    scanf("%d",&Cliente->itens[i]); // insere vi no iesimo funcionario
    
    while(Cliente->itens[i] < 1 || Cliente->itens[i] > MAX_FILA){
      scanf("%d",&Cliente->itens[i]); // insere vi no iesimo caso nao atenda aos requisitos de ser maior igual a 1 ou menor igual a 10000
    }
    Cliente->n++;
  }
}
  
void saida (sFuncionario *funcionario, int n, sCliente *Cliente, int m) {
  int i,j,k,*maior,*menor,indice,*remover, menores = 0,tempo;
  
  for(i = n; i > 0; i--){
    retira(Cliente,remover,m);
    
    menor = &funcionario->Funcionario[i].tempo;
    
    for(j = 0 ; j < n; j++){
      if(*menor > funcionario->Funcionario[i].tempo){
        menor=&funcionario->Funcionario[i].tempo;
        indice = i;
      }
    }

    menores = menores + *menor;

    for(k=0 ;k < m ;k++){
      funcionario->Funcionario[k].tempo = funcionario->Funcionario[k].tempo - *menor; 
    }
    
    funcionario->Funcionario[indice].tempo = funcionario->Funcionario[indice].v * (*remover);
  }

  maior = &funcionario->Funcionario[i].tempo;   

  for(i = 0 ; i < n; i++){
      if(*maior < funcionario->Funcionario[i].tempo){
        maior=&funcionario->Funcionario[i].tempo;
        }
    }
  
  tempo = *maior + menores;
  printf("%d",tempo);
}

void retira (sCliente *p, int *remover,int M){
  *remover = p->itens[p->ini];
  p->ini = ((p->ini) + 1) % M;
  p->n--;
}