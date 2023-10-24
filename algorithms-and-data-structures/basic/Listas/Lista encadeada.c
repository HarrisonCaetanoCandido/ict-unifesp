#include <stdio.h> //INPUT OUTPUT
#include <stdlib.h> //ALOCACAO DE MEMORIA, CONTROLE DE PROCESSOS, CONVERSOES
#include <locale.h> //NECESSÁRIA PARA USAR setlocale(LC_ALL, "") NA MAIN

/*
    LISTA ENCADEADA - TEORIA

    - Quando criamos um vetor de 5 posi��es, separamos regi�es de mem�ria para guardar valores da seguinte forma:
     
        |25|24|73|82|56| -> vet[0]|vet[1]|vet[2]|vet[3]|vet[4]

        Pela aritm�tica de ponteiros, temos que:

        *(vet+1) = 24 -> O computador entende que é um endereço de memória

    A principal caracteristica desse vetor é que ele possui tamanho ESTÁTICO 5
____________________________________________________________________________________

    - Toda Lista Encadeada possui um Nó, uma struct do tipo Nó, onde temos um 'valor'
    e um ponteiro 'proximo', que é um ponteiro para o tipo 'valor', esboçando temos:

    |Nó
    |Valor   | ? |
    |*proximo| ? |

    Sabemos que como são Nó's precisamos ir encadeando, fazendo uma sequência de Nó's, teremos então
    uma segunda struct chamada 'Lista', com um ponteiro para o tipo Nó e um tamanho,
    sendo esboçada pelo seguinte:

    |Lista  |
    |*inicio|   ?  | -> APONTA PARA O ENDEREÇO DE ALGUM NÓ
    |tam    |   ?  | -> INCREMENTA O TAMANHO

    Ao criarmos nosso primeiro N�, ele estar� em uma regi�o de mem�ria, por exemplo 'A0', logo:

        A0
    |N�
    |Valor   |  50  |
    |*proximo| NULL |

    Se queremos inseri-lo na lista, ent�o nosso *inicio ir� ser NULL e apontar� para o 
    endere�o de mem�ria do N� 'A0', logo n�s teremos:

    |Lista  |
    |*inicio|   NULL  | -> LISTA VAZIA NUM PRIMEIRO MOMENTO
    |tam    |   0     | -> INCREMENTA O TAMANHO

        A0
    |N�
    |Valor   |  50  | -> PRIMEIRO NÓ COM UM VALOR INSERIDO
    |*proximo| NULL |

    |Lista  |
    |*inicio|   A0    | -> LISTA RECEBE O VALOR DO N� 'A0'
    |tam    |   0+1   | -> INCREMENTA O TAMANHO

       B3
    |N�
    |Valor   |  74  | -> SEGUNDO N� COM UM VALOR INSERIDO, POSSO INSERI-LO NO IN�CIO
    |*proximo| NULL |    OU NO FINAL

    Suponhamos que iremos inserir 'B3' no IN�CIO da Lista, teremos ent�o que o pr�ximo
    de 'B3' apontar� para 'A0', ap�s isso, diremos para a Lista que o *inicio apontar�
    para 'B3' e n�o mais para 'A0', sendo assim:

       B3
    |N�
    |Valor   |  74  | -> SEGUNDO N� COM UM VALOR INSERIDO NO IN�CIO DA LISTA
    |*proximo|  A0  |    

    |Lista  |
    |*inicio|    B3     | -> LISTA RECEBE O VALOR DO N� 'B3'
    |tam    |   0+1+1   | -> INCREMENTA O TAMANHO

    Suponhamos agora que iremos inserir um novo N� 'A2' no FINAL da Lista, teremos ent�o
    que o ponteiro 'pr�ximo' de 'A0', at� ent�o o �ltimo N� da Lista, apontar� agora n�o
    mais para 'NULL' e sim para 'A2', logo:

       B3
    |N�
    |Valor   |  74  | -> SEGUNDO N� COM UM VALOR INSERIDO NO IN�CIO DA LISTA
    |*proximo|  A0  | 

        A0
    |N�
    |Valor   |  50  | -> PRIMEIRO N� COM UM VALOR INSERIDO
    |*proximo| NULL |

    |Lista  |
    |*inicio|    B3     | -> LISTA RECEBE O VALOR DO N� 'B3' COMO IN�CIO
    |tam    |   0+1+1   | -> INCREMENTA O TAMANHO

        A2
    |N�
    |Valor   |  11  | -> TERCEIRO N� COM UM VALOR INSERIDO, MAS AGORA NO FINAL!
    |*proximo| NULL |    PARA ISSO, 'A0' APONTAR� PARA 'A2'

        A0
    |N�
    |Valor   |  50  | -> PRIMEIRO N� COM UM VALOR INSERIDO AGORA APONTANDO
    |*proximo|  A2  |    PARA 'A2'

    |Lista  |
    |*inicio|    B3       | -> LISTA RECEBE O VALOR DO N� 'B3' COMO IN�CIO E 'A2' NO FINAL
    |tam    |   0+1+1+1   | -> INCREMENTA O TAMANHO

    Ou seja encadeamos!
*/

typedef struct No{ //ELEMENTOS
    int valor;
    struct no *proximo; // PONTEIRO PARA A STRUCT 'no'
}No; //APELIDO QUE VAMOS USAR NO MAIN, PODEM SER IGUAIS INCLUSIVE

typedef struct Lista{ //LISTA QUE APONTA PARA OS ENDERE�OSS DE N�
    No *inicio; //PONTEIRO PARA UM TIPO N�
    int tam; // OPCIONAL
}Lista;

void inserirINICIO(Lista *lista, int valor){//N�o recebe um objeto lista, mas sim um ponteiro, e um valor que ser� inserido na lista
    
    /*Para que o valor n�o desapare�a, criaremos um ponteiro, ou seja, n�o � uma vari�vel local e, para isso criaremos 
    tamb�m uma aloca��o din�mica de mem�ria, e para isso passaremos um tamanho para o tipo No

    Como queremos alocar mem�ria o suficiente para um tipo No, passaremos para malloc() o tamanho da mem�ria para um tipo N�,
    logo teremos que utilizar malloc(sizeof(No)) -> Tamanho de um N� na mem�ria
    No *novo= malloc(sizeof(No))

    Por�m precisamos dizer para 'No *novo= malloc(sizeof(No))' que seu retorno � do tipo ponteiro, logo:

    No *novo =(No*)malloc(sizeof(No)) -> Voc� est� alocando espa�o de mem�ria para o tipo N�, por�m � um ponteiro
    
    Feito isso, temos ent�o uma regi�o de mem�ria, um ponteiro para o tipo No criado

    Poderemos ent�o alterar e guardar esse nosso valor l� dentro*/
    No *novo =(No*)malloc(sizeof(No));
  //nome_da_variavel->campo_que_queremos_alterar=nome_do_valor_que_queremos_inserir

    novo->valor = valor; //NOVO N� RECEBE O VALOR INSERIDO

  /*Teremos que dizer que o pr�ximo endere�o do N� criado � NULL
    novo->proximo == NULL;*/

    //Ou tamb�m poderemos fazer com que ele aponte para o inicio da lista

    novo->proximo = lista->inicio; //O PR�XIMO DO NOVO N� APONTA PARA O ENDERE�O DE IN�CIO QUE A LISTA APONTA
    
    //E o nosso inicio da lista receba o novo N�

    lista->inicio = novo; //AGORA O IN�CIO DA LISTA APONTA PARA O NOVO ENDERE�O DO NOVO N� INSERIDO NO IN�CIO

    //Para incrementar, teremos:
    lista->tam++;
}

void inserirFINAL(Lista *lista, int valor){
    No *no, *novo = (No*)malloc(sizeof(No)); //TEREMOS QUE CRIAR DUAS VARIAVEIS DO TIPO N�

    novo->valor = valor; //NOVO NÓ RECEBE O VALOR INSERIDO
    novo->proximo=NULL; //O PRÓXIMO DO NOVO NÓ APONTA PARA NULL PQ É O ULTIMO NÓ

    if(lista->inicio==NULL){//CASO A LISTA ESTEJA VAZIA, TEREMOS QUE:
    lista->inicio=novo;// O INICIO DA LISTA APONTA PARA O NOVO NÓ
    }
    else{ //CASO NÃO TENHAMOS UMA LISTA VAZIA, TEREMOS QUE:
        
        no = lista->inicio; //NOSSA NOVA LISTA RECEBERÁ O ENDEREÇO APONTADO PELO INÍCIO DA LISTA
       
        while(no->proximo!=NULL){ /*O PRÓXIMO DESSE PRIMEIRO NÓ QUE ESTÁ SENDO APONTADO PELA LISTA APONTA PARA NULL?
                                    SE NÃO ENTÃO CONTINUA PARA O PRÓXIMO NÓ ATÉ ACHAR NULL*/
            no=no->proximo; //PULA PARA A PRÓXIMA POSIÇÃO
        }
        no->proximo=novo; //Quando o 'while' terminar estaremos no ultimo Nó da lista, e "no->proximo" será NULL, logo 'novo' recebe o novo Nó
    }
    lista->tam++;
}

void imprimir(Lista *lista){
    /*Sabemos que a lista tem uma sequ�ncia de N�'s, ent�o criaremos um tipo No chamado de *inicio
    que receber� o inicio da nossa lista, sendo assim iremos percorre-la*/
    No *inicio = lista->inicio;

    printf("Tamanho da Lista: %d\n", lista->tam);

    while(inicio!=NULL){ //Forma intuitiva
        printf("%d | ", inicio->valor);
        inicio=inicio->proximo; //PARA N�O FICARMOS EM LOOP
    }
    printf("\n\n");
}

int main(){
    setlocale(LC_ALL, "");
    Lista lista;

    lista.inicio=NULL;
    lista.tam=0;

    int valor,escolha;

    do{
        system("clear||cls");
        printf("1|Inserir no In�cio\n");
        printf("2|Inserir no Final\n");
        printf("3|Imprimir\n");
        printf("5|Sair\n");
        scanf("%d", &escolha);

        switch(escolha){
            case 1: //INSERIR NO IN�CIO
                system("clear||cls");
                printf("Insira um Valor no In�cio: ");
                scanf("%d", &valor);
                inserirINICIO(&lista, valor); //Manda o endere�o da lista e o valor
            break;
            case 2: //INSERIR NO FINAL
                system("clear||cls");
                printf("Insira um Valor no Final: ");
                scanf("%d", &valor);
                inserirFINAL(&lista, valor);
            break;
            case 3: //IMPRIMIR
                system("clear||cls");
                imprimir(&lista); //Precisamos passar o endere�o da nossa Lista
                getch();
            break;
            case 4:
            break;
            case 5: //SA�DA
                system("clear||cls");
                printf("Obrigado pela Visita!\n");
            break;
            default:
            printf("Op��o Inv�lida!\n");
        }
    }while(escolha!=5);
return 0;
}