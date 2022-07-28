#include <stdio.h>
#include <stdbool.h> // lidar com variaveis booleanas
#define tam 10

typedef struct{
    char palavra[20]; // 19 letras
    char definicao[50]; // 49 letras
}dicionario;

dicionario inserir(dicionario dcn[],int n_palavras);
bool comparar_strings(char string1[],char string2[]);
int buscar_string(dicionario dcn[],char buscar[],int n_palavras);

int main(){
    dicionario dcn[tam];
    char palavra[20];
    int resultado_busca,selecione,n_palavras=0;

    do{
        system("clear||cls");
        fflush(stdin);
        printf("1 | Inserir palavra\n");
        printf("2 | Buscar palavra\n");
        printf("3 | Listar palavras\n");
        printf("4 | Sair\n");
        printf("Selecione: ");
        scanf("%d",&selecione);
        switch(selecione){
            case 1: // inserir palavra
                system("clear||cls");
                inserir(dcn,n_palavras);
                n_palavras++;
            break;
            case 2: // buscar palavra
                system("clear||cls");
                printf("Digite a palavra que deseja encontrar: ");
                scanf("%s",&palavra);

                resultado_busca=buscar_string(dcn,palavra,n_palavras);
                if(resultado_busca!=-1){
                    printf("Palavra numero %d\n\n",resultado_busca);
                    printf("Palavra: %s\n",dcn[resultado_busca].palavra);
                    printf("Definicao: %s\n\n",dcn[resultado_busca].definicao);
                    printf("Quantidade total de palavras: %d\n\n",n_palavras);
                }else{
                    printf("\nPalavra nao encontrada!\n");
                }
                printf("Pressione qualquer tecla para continuar...");
                getch();
            break;
            case 3: // listar palavras
                system("clear||cls");
                printf("Quantidade total de palavras: %d\n\n",n_palavras);
                for(int i=0;i<n_palavras;i++){
                    printf("Palavra: %s\n",dcn[i].palavra);
                    printf("Definicao: %s\n\n",dcn[i].definicao);
                }
                printf("Pressione qualquer tecla para continuar...");
                getch();
            break;
            case 4: // sair
                system("clear||cls");
                printf("Exit(1)");
            break;
            default:
                system("clear||cls");
                printf("Erro, selecione uma opcao novamente!\n");
            break;
        }
    }while(selecione!=4);

    return 0;
}

dicionario inserir(dicionario dcn[],int n_palavras){
    char caractere;int i=0;

    fflush(stdin);
    printf("Digite uma palavra: ");
    do{
        caractere=getchar();
        dcn[n_palavras].palavra[i]=caractere;
        i++;
    }while(caractere!='\n');
    dcn[n_palavras].palavra[i-1]='\0';
    i=0;

    fflush(stdin);
    printf("Digite a definicao da palavra: ");
    do{
        caractere=getchar();
        dcn[n_palavras].definicao[i]=caractere;
        i++;
    }while(caractere!='\n');
    dcn[n_palavras].definicao[i-1]='\0';
    printf("\nDados registrados com sucesso!\n");
}

bool comparar_strings(char string1[],char string2[]){
    int i=0;
    while(string1[i]==string2[i] && string1[i]!='\0' && string2[i]!='\0'){
        i++;
    }
    if(string1[i]=='\0' && string2[i]=='\0'){
        return true;}else{return false;}
}

int buscar_string(dicionario dcn[],char buscar[],int n_palavras){
    int i=0;
    while(i<n_palavras){
        if(comparar_strings(buscar,dcn[i].palavra)){
            return i; // retorna a posicao no vetor do tipo 'dicionario'
        }else{
            i++;
        }
    }
    return -1;
}