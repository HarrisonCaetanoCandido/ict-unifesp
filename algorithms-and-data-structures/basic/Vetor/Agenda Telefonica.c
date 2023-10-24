#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 10
#define TAM_MAX 100
#define TAM_TEL 11

typedef struct
{
    char nome[TAM_NOME];
    int tel;
} Contato;

typedef struct
{
    Contato contato;
    int indice;
} Meuscontatos;

/*
1. Menu
2. Case 1, Registro
3. Case 2, Listar contatos
4. Case 3, Buscar contato
5. Case 4, Apagar contato pelo indice
6. Case 5, Apagar contato pelo nome
*/

int tam_telefone();

int tam_telefone(int telefone)
{
    int c_telefone = 1;

    if (telefone >= 10)
    {
        telefone = telefone / 10;
        c_telefone = c_telefone + tam_telefone(telefone);
    }
    return c_telefone;
}

int main()
{
    Meuscontatos Agenda[TAM_MAX];
    // case 1/geral:
    int selecione, index = 0, i, c_telefone, k;
    int telefone, confirmando;
    char nome[TAM_MAX];

    // case 3/case 4:
    int indice_ctt_buscar;

    // case 5:
    char nome_ctt_buscar[TAM_NOME];

    do
    {
        system("clean||cls");
        printf("___________Menu___________\n\n");
        printf("1 | Inserir contato\n");
        printf("2 | Listar contatos\n");
        printf("3 | Buscar contato\n");
        printf("4 | Apagar contato pelo indice\n");
        printf("5 | Apagar contato pelo nome\n");
        printf("6 | Sair\n");
        printf("\nSelecione: ");
        scanf("%d", &selecione);

        switch (selecione)
        {
        case 1: // Inserir contato
            system("cls||pause");

            //_______________________INDICE_______________________
            printf("\nDigite o Indice do contato: ");
            scanf("%d", &Agenda[index].indice);

            while (Agenda[index].indice < 1 || Agenda[index].indice > 100)
            {
                printf("\n\nDigite o Indice do contato novamente [1:100]: ");
                scanf("%d", &Agenda[index].indice);
            }

            //________________________NOME________________________
            printf("\nDigite o nome do contato: ");
            scanf("%s", &Agenda[index].contato.nome);

            strcpy(nome, Agenda[index].contato.nome);

            while (strlen(nome) < 1 || strlen(nome) > 10)
            {
                printf("Digite o nome do contato novamente: ");
                scanf("%s", &Agenda[index].contato.nome);
                strcpy(nome, Agenda[index].contato.nome);
            }

            //_____________________TELEFONE______________________
            printf("Digite o numero de telefone do contato: ");
            scanf("%d", &Agenda[index].contato.tel);

            telefone = Agenda[index].contato.tel;

            c_telefone = tam_telefone(telefone); // printf("\nDigitos telefone fora do while: %d\n",c_telefone);

            while (c_telefone < 10 || c_telefone > 12)
            {
                printf("\nDigite o numero de telefone do contato novamente: ");
                scanf("%d", &Agenda[index].contato.tel);

                telefone = Agenda[index].contato.tel;

                c_telefone = tam_telefone(telefone); // printf("\nDigitos telefone dentro do while: %d\n",c_telefone);
            }

            index++;
            //_______________________________________Substituir Indice______________________________________________
            for (i = 0; i < index; i++)
            {
                for (int j = 1; j < index; j++)
                {
                    if (Agenda[i].indice == Agenda[j].indice && i != j)
                    {
                        for (k = i; k < index; k++)
                        {
                            strcpy(Agenda[k].contato.nome, Agenda[k + 1].contato.nome);
                            Agenda[k].contato.tel = Agenda[k + 1].contato.tel;
                            Agenda[k].indice = Agenda[k + 1].indice;
                        }
                        index--;
                    }
                }
            }
            //______________________________________________________________________________________________________
            break;
        case 2: // Listar contato
            system("cls||pause");
            printf("__________Listando Contatos__________\n");

            if (index == 0)
            {
                printf("\nA agenda esta vazia!\n");
                printf("\nPressione qualquer tecla para retornar ao menu...");
                getch();
            }
            else
            {
                for (i = 0; i < index; i++)
                {
                    printf("\nContato[%d]\nNome: %s\nTelefone: %d\n", Agenda[i].indice, Agenda[i].contato.nome, Agenda[i].contato.tel);
                }
                printf("\nPressione qualquer tecla para retornar ao menu...");
                getch();
            }
            break;
        case 3: // Buscar contato pelo indice
            system("clean||cls");
            printf("_________Buscar contato pelo Indice_________\n");

            if (index == 0)
            {
                printf("\nA agenda esta vazia!\n");
                printf("\nPressione qualquer tecla para retornar ao menu...");
                getch();
            }
            else
            {
                confirmando = 0;
                printf("\nDigite o indice do contato que quer buscar: ");
                scanf("%d", &indice_ctt_buscar);

                for (i = 0; i < index; i++)
                {
                    if (indice_ctt_buscar == Agenda[i].indice)
                    {
                        printf("\nContato encontrado com sucesso: ");
                        printf("\n\nContato[%d]\nNome: %s\nTelefone: %d\n", Agenda[i].indice, Agenda[i].contato.nome, Agenda[i].contato.tel);
                        printf("\nPressione qualquer tecla para retornar ao menu...");
                        getch();
                        confirmando = 1;
                    }
                }
                if (confirmando == 0)
                {
                    printf("\nO Indice digitado nao corresponde a nenhum contato salvo!\n");
                    printf("\nPressione qualquer tecla para continuar...");
                    getch();
                }
            }
            break;
        case 4: // Apagar contato pelo indice
            printf("__________Apagar contato pelo Indice_________\n");

            if (index == 0)
            {
                printf("\nA agenda esta vazia!\n");
                printf("\nPressione qualquer tecla para retornar ao menu...");
                getch();
            }
            else
            {
                confirmando = 0;
                indice_ctt_buscar = 0;
                printf("\nDigite o Indice do contato que deseja apagar: ");
                scanf("%d", &indice_ctt_buscar);

                for (i = 0; i < index; i++)
                {
                    if (indice_ctt_buscar == Agenda[i].indice)
                    {

                        for (k = i; k < index; k++)
                        {
                            strcpy(Agenda[k].contato.nome, Agenda[k + 1].contato.nome);
                            Agenda[k].contato.tel = Agenda[k + 1].contato.tel;
                            Agenda[k].indice = Agenda[k + 1].indice;
                        }
                        index--;

                        system("clean||cls");
                        if (index == 0)
                        {
                            printf("\nContato apagado com sucesso!!\n");
                            printf("\nA agenda esta vazia\n");
                            printf("Pressione qualquer tecla para retornar ao menu...");
                            getch();
                        }
                        else
                        {
                            printf("\n__________Listando a Agenda__________\n");
                            for (i = 0; i < index; i++)
                            {
                                printf("\nContato[%d]\nNome: %s\nTelefone: %d\n", Agenda[i].indice, Agenda[i].contato.nome, Agenda[i].contato.tel);
                            }
                            printf("\nContato apagado com sucesso!!\n");
                            confirmando = 1;

                            printf("\nPressione qualquer tecla para retornar ao menu...");
                            getch();
                        }
                    }
                }
                if (confirmando == 0)
                {
                    printf("\nO Indice digitado nao corresponde a nenhum contato salvo!\n");
                    printf("\nPressione qualquer tecla para continuar...");
                    getch();
                }
            }
            break;
        case 5: // Apagar contato pelo nome
            system("clean||cls");
            printf("__________Apagar contato pelo nome__________\n");

            if (index == 0)
            {
                printf("\nA agenda esta vazia!\n");
                printf("\nPressione qualquer tecla para retornar ao menu...");
                getch();
            }
            else
            {
                confirmando = 0;
                printf("\nDigite o nome do contato que deseja apagar: ");
                scanf("%s", &nome_ctt_buscar);

                for (i = 0; i < index; i++)
                {
                    if (strcmp(nome_ctt_buscar, Agenda[i].contato.nome) == 0)
                    {
                        for (k = i; k < index - 1; k++)
                        {
                            strcpy(Agenda[k].contato.nome, Agenda[k + 1].contato.nome);
                            Agenda[k].contato.tel = Agenda[k + 1].contato.tel;
                            Agenda[k].indice = Agenda[k + 1].indice;
                        }
                        index--;

                        system("clean||cls");
                        if (index == 0)
                        {
                            printf("\nContato apagado com sucesso!!\n");
                            printf("\nA agenda esta vazia!\n");
                            printf("Pressione qualquer tecla para retornar ao menu...");
                            getch();
                        }
                        else
                        {
                            printf("\n__________Listando a Agenda__________\n");
                            for (i = 0; i < index; i++)
                            {
                                printf("\nContato[%d]\nNome: %s\nTelefone: %d\n", Agenda[i].indice, Agenda[i].contato.nome, Agenda[i].contato.tel);
                            }
                            printf("\nContato apagado com sucesso!!\n");

                            printf("\nPressione qualquer tecla para retornar ao menu...");
                            getch();
                        }
                    }
                }

                if (confirmando == 0)
                {
                    printf("\nO nome digitado nao corresponde ao de nenhum contato salvo!\n");
                    printf("\nPressione qualquer tecla para continuar...\n");
                    getch();
                }
            }
            break;
        case 6:
            printf("\n\nSaindo...");
            break;
        default:
            printf("\nErro! Selecione a opcao novamente\n");
        }
    } while (selecione != 6);
    return 0;
}