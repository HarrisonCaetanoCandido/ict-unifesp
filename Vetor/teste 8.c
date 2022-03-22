#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 10
#define TAM_MAX 100
#define TAM_TEL 11

typedef struct
{
    char nome[TAM_NOME];
    char tel[TAM_TEL];
    int indice;
} Meuscontatos;

//_________________________________________________________________________________
//                                    FUNÇÕES
void sobrescrever();
void pause (float);
//_________________________________________________________________________________
//                              PURAMENTE ESTETICO

/** procedimento de compilacao normal
  * uso: pause(valor)
  *
  * valor eh um numero maior que zero podendo ser uma fracao.
  * eh o tempo em segundos de pausa no programa.
**/

void pause (float delay1)
{

    if (delay1<0.001) return; // pode ser ajustado e/ou evita-se valores negativos.

    float inst1=0, inst2=0;

    inst1 = (float)clock()/(float)CLOCKS_PER_SEC;

    while (inst2-inst1<delay1) inst2 = (float)clock()/(float)CLOCKS_PER_SEC;

    return;

}

int main()
{
    Meuscontatos Agenda[TAM_MAX]; //Declara a variavel Agenda para a struct com os 100 possiveis contatos
    
    //Case 1 (Registrar contato)
    int index=0;//Vai contar quantos contatos registramos
    int i=0,j=0;
    int indice_int;
    char auxiliartel1[TAM_TEL];
    int Aindice;
    int auxiliar_da_tel1;
    //int k,l,sobrescrever; //Case 1 - sobrescrever


    //Case 2 (Listar todos os contatos)
    int escolha;
    int telefone[TAM_TEL];

    //Case 3 (Buscar contato)
    int indice_contato;
    int Telefone;
    int confirmacao=0; //PRA NAO FICAR DANDO LOOP CASO O INDICE NAO SEJA O CORRESPONDENTE DO VETOR

    //Case 4 (Apagar contato pelo indice)
    int indice_apagarctt=0;
    int desejapagar;
    char auxiliar_indice[3];
    char auxiliar_indice_2[3];

    //Case 5 (Apagar contato pelo nome)
    char apagar_ctt[TAM_NOME];

    do
    {
        printf("\n1 | Registrar contato\n");
        printf("2 | Listar contatos\n");
        printf("3 | Buscar contato\n");
        printf("4 | Apagar contato\n");
        printf("5 | Apagar contatos pelo nome\n");
        printf("6 | Sair\n");
        printf("Selecione: ");
        scanf("%d",&escolha);
        switch(escolha)
        {
//____________________________________________________________
        case 1:
        system("clean||cls");
        printf("\n\n___Registrar contato___\n\n");


            printf("\nDigite um indice de 1 a 100: ");
            scanf("%d", &Agenda[index].indice);

            Aindice=Agenda[index].indice;
            while(Aindice<1||Aindice>100)
            {
                printf("\nIndice digitado nao existe [1,100]!\n");
                printf("\nDigite um indice novamente [1,100]: ");
                scanf("%d", &Agenda[index].indice);
                Aindice=Agenda[index].indice;
            }

            printf("\nDigite o nome do contato[%d]: ",Agenda[index].indice);
            scanf("%s", &Agenda[index].nome);

            printf("Digite o telefone do contato[%d]: ",Agenda[index].indice);
            scanf("%s", &Agenda[index].tel);

            while(strlen(Agenda[index].tel)<10||strlen(Agenda[index].tel)>11)
            {
                system("clear||cls");
                printf("\nErro!\n");
                printf("\nPor favor, digite um numero de telefone entre 10 a 11 caracteres: ");
                scanf("%s", &Agenda[index].tel);
            }

            index++; //Pra gente saber quantos contatos tem na agenda

//__________________________VAI SOBRESCREVER O QUE JA FOI INSERIDO_______________________________
/*
            for(k=0; k<index; k++){
                for(l=1;l<index;l++){
                    if(Agenda[k].indice==Agenda[l].indice)
                    {
                        strcpy(Agenda[k].nome,Agenda[l].nome); // Pega o da frente e sobrescreve no de tras
                        strcpy(Agenda[k].tel,Agenda[l].tel); // Pega o da frente e sobrescreve no de tras
                        Agenda[k].indice=Agenda[l].indice; // Faz o de tras receber o valor do contato da frente
                        printf("\nDeu problema! O novo contato sera sobrecrito no antigo de mesmo indice\n");
                        index--;
                        confirmacao++;
                    }
                }
            }

            if(confirmacao==0)
            {
                printf("\nTudo certo! Nenhum contato foi sobrescrito.\n");
            }
            */
//________________________________________________________________________________________________

            printf("\n\nPressione qualquer tecla para continuar...");
            getch();
            system("clear||cls");

        break;

//__________________________________________________________________________________________________________________
        case 2:
            system("clear||cls"); //Serve para limpar o terminal, mas pode apagar tambem, eh so enfeite
            printf("\n____Listando todos os contatos____\n\n");


            if(index==0)
            {
                printf("Agenda Vazia!\n");
                printf("Retornando para o Menu...\n");
                pause(5.5);
            }
            else
            {
                printf("\nindice: %d\n",index);
                for(i=0; i<index; i++)
                {
                    printf("______\nContato[%d]\n Nome: %s\n Numero: %s\n______",Agenda[i].indice, Agenda[i].nome, Agenda[i].tel);
                }
            }

            printf("\n\nPressione qualquer tecla para continuar...");
            getch();
            system("clear||cls");
            break;
//__________________________________________________________
        case 3:
            system("clear||cls");
            printf("\n____Mostrar um contato pelo indice____\n\n");

                
                if(index==0)
                {
                    printf("Agenda Vazia!\n");
                    printf("Voltando para o menu...");
                    pause(5.5);
                }
                else
                {
                    printf("Digite o indice do contato que quer achar: ");
                    scanf("%d", &indice_contato);

                    for(i=0; i<index; i++)
                    {
                        if(indice_contato==Agenda[i].indice)
                        {
                            printf("\nContato[%d]\n",Agenda[i].indice);
                            printf("Nome: %s\n", Agenda[i].nome);
                            printf("Telefone: %s", Agenda[i].tel);
                            confirmacao++;
                        }
                    }
                    if(confirmacao==0)
                    {
                        printf("\n\nIndice nao encontrado!\n"); 
                    }
                }
            printf("\n\nPressione qualquer tecla para continuar...");
            getch();
            system("clear||cls");
            break;
//__________________________________________________________
        case 4:
            system("clear||cls");
            printf("\n\n____Apagar contatos pelo indice____\n\n");


            if(index==0)
            {
                printf("Agenda Vazia!\n");
                printf("Retornando para o Menu...\n");
                pause(5.5);
            }
            else
            {
                printf("Digite o indice do contato que quer apagar: ");
                scanf("%d",&indice_apagarctt);
                for(j=0; j<index; j++)
                {
                    if(indice_apagarctt==Agenda[j].indice)
                    {
                        printf("\nOs dados escolhidos sao: \n");
                        printf("Nome: %s", Agenda[j].nome);
                        printf("\nTelefone: %s", Agenda[j].tel);

                        confirmacao++;

                        printf("\n\nDeseja mesmo apagar?(Digite 1 para sim e 2 para nao)\n\n");// <--- AQUI VC PODE PENSAR EM COLOCAR ESSA PERGUNTINHA E UM SWITCH OU USAR IF, EH SO PRA DEIXAR BONITO MESMO, MAS AI DEU PREGUICA DE CONTINUAR KSKS
                        scanf("%d",&desejapagar);

                        switch(desejapagar)
                        {
                        case 1:
                            strcpy(Agenda[j].nome,Agenda[j+1].nome);//Vai copiar o nome do contato que tiver na frente do vetor Agendapara o endereco desse contato que vc quer apagar
                            strcpy(Agenda[j].tel,Agenda[j+1].tel);//Vai copiar o telefone do contato que tiver na frente do vetor Agenda para o endereco desse contato que vc quer apagar
                            Agenda[j].indice=Agenda[j+1].indice; //Vai copiar o indice do contato que tiver na frente do vetor Agenda para o endereco desse contato que vc quer apagar
                            index--; //QUANDO FOR IGUAL ELE USA INDEX
                            printf("Contato removido com sucesso!\n");

                            for(i=0;i<index;i++){
                                printf("Contato[%i]\nNome: %s\nTel: %s",Agenda[i].indice,Agenda[i].nome,Agenda[i].tel);
                            }
                        
                            break;
                        case 2:
                            printf("Retornando para o Menu...\n");
                            pause(5.5);
                            break;
                        }
                    }
                }
                if(confirmacao==0)
                    {
                        printf("\nNenhum contato foi encontrado!\n");
                    }
            }

            printf("\n\nPressione qualquer tecla para continuar...");
            getch();
            break;
//___________________________________________________________
        case 5:
            system("clear||cls");
            printf("\n\n____Apagar contatos pelo nome____\n\n");


            if(index==0)
            {
                printf("\nAgenda esta vazia!\n");
            }
            else
            {
                printf("Digite o nome do contato que deseja apagar: ");
                scanf("%s",&apagar_ctt);

                for(i=0; i<index; i++)
                {
                    if(strcmp(apagar_ctt, Agenda[i].nome)==0)
                    {
                        strcpy(Agenda[i].nome,Agenda[i+1].nome);
                        strcpy(Agenda[i].tel,Agenda[i+1].tel);
                        Agenda[i].indice=Agenda[i+1].indice;
                        index--;
                        confirmacao++;
    
                        for(i=0;i<index;i++){
                            printf("Contato[%i]\nNome: %s\nTel: %s\n",Agenda[i].indice,Agenda[i].nome,Agenda[i].tel);
                        }
                    }
                }
                if(confirmacao==0)
                {
                    printf("\nNome nao encontrado!\n");
                }
            }
        
            printf("\n\nPressione qualquer tecla para continuar...");
            getch();
            break;
//___________________________________________________________
        case 6:
            system("clear||cls");
            printf("\nObrigado pela visita!\n");
            break;
//____________________________________________________________
        default:
            printf("\nErro!\n\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
            system("clear||cls");

        }
    }
    while(escolha!=6);
    return 0;
}
