#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_MAX 100
#define TAM_NOME 10

typedef struct
{
    int cadastro;
    char nome[TAM_NOME];
} registro[TAM_MAX];

int main()
{
    registro *vetor = (registro *)malloc(100 * sizeof(registro));
    int selecione;
    int i, busca, achou = 0, index = 0;
    char sbusca[TAM_NOME];
    int simnao;

    do
    {
        system("clear||cls");
        printf("__________Menu__________\n\n");
        printf("1 | Inserir registro\n");
        printf("2 | Listar registro\n");
        printf("3 | Buscar registro\n");
        printf("4 | Remover registro pelo numero de cadastro\n");
        printf("5 | Remover registro pelo nome\n");
        printf("6 | Sair\n");
        printf("Selecione: ");
        scanf("%d", &selecione);

        switch (selecione)
        {
        case 1: // Inserir registro
            system("clear||cls");
            printf("__INSERIR REGISTRO__\n\n");
            if (vetor == NULL)
            {
                printf("Erro na Alocacao de Memoria, provavelmente a memoria RAM esta cheia!\n");
                return;
            }
            else
            {
                printf("Registro[%d]\nDigite o numero de cadastro: ", index + 1);
                scanf("%d", &vetor[index]->cadastro);

                while ((vetor[index]->cadastro) > 100 || (vetor[index]->cadastro) < 1)
                {
                    printf("Numero invalido!\nDigite o numero de cadastro novamente [1:10]: ");
                    scanf("%d", &vetor[index]->cadastro);
                }

                printf("\nDigite o nome do registro: ");
                scanf("%s", &vetor[index]->nome);

                while (strlen(vetor[index]->nome) > 10 || strlen(vetor[index]->nome) < 1)
                {
                    printf("Nome invalido!\nDigite o nome do registro novamente [1:10]: ");
                    scanf("%s", &vetor[index]->nome);
                }
                index++;

                for (i = 0; i < index; i++)
                {
                    for (int j = 1; j < index; j++)
                    {
                        if (vetor[i]->cadastro == vetor[j]->cadastro && i != j)
                        {
                            vetor[i]->cadastro = vetor[j]->cadastro;
                            strcpy(vetor[i]->nome, vetor[j]->nome);
                            index--;
                        }
                    }
                }
            }
            printf("Registro feito com sucesso!\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
            break;
        case 2: // Listar registro
            system("clear||cls");
            printf("__LISTAR REGISTRO__\n\n");
            if (index == 0)
            {
                printf("Ainda nao foi feito nenhum registro!\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
            }
            else
            {
                for (i = 0; i < index; i++)
                {
                    printf("Registro[%d]\nNumero de cadastro do registro: %d\n", i + 1, vetor[i]->cadastro);
                    printf("Nome do registro: %s", vetor[i]->nome);
                    printf("\n\n");
                }
                printf("Pressione qualquer tecla para continuar...");
                getch();
            }
            break;
        case 3: // Buscar registro
            system("clear||cls");
            if (index == 0)
            {
                printf("Ainda nao foi feito nenhum registro!\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
            }
            else
            {
                system("clear||cls");
                printf("__BUSCAR REGISTRO__\n\n");
                printf("Digite o numero de cadastro que deseja buscar: ");
                scanf("%d", &busca);

                for (i = 0; i < index; i++)
                {
                    if (busca == vetor[i]->cadastro)
                    {
                        system("clear||cls");
                        printf("Dados encontrados do registro %d: ", i + 1);
                        printf("\nNumero do cadastro: %d", vetor[i]->cadastro);
                        printf("\nNome registrado do cadastro %d: %s", vetor[i]->cadastro, vetor[i]->nome);
                        achou = 1;
                        printf("\nPressione qualquer tecla para continuar...");
                        getch();
                    }
                }
                if (achou == 0)
                {
                    system("clear||cls");
                    printf("\nCadastro nao foi encontrado!\n");
                    printf("Pressione qualquer tecla para voltar ao Menu...");
                    getch();
                }
                achou = 0;
            }
            break;
        case 4: // Remover registro pelo numero de cadastro
            system("clear||cls");
            if (index == 0)
            {
                printf("Ainda nao foi feito nenhum registro!\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
            }
            else
            {
                system("clear||cls");
                busca = 0;
                printf("__REMOVER REGISTRO PELO NUMERO DE CADASTRO__\n\n");
                printf("Digite o numero de cadastro do registro que deseja remover: ");
                scanf("%d", &busca);

                for (i = 0; i < index; i++)
                {
                    if (busca == vetor[i]->cadastro)
                    {
                        system("clear||cls");
                        printf("Dados encontrados: ");
                        printf("\nNumero do cadastro: %d", vetor[i]->cadastro);
                        printf("\nNome registrado do cadastro %d: %s", vetor[i]->cadastro, vetor[i]->nome);
                        achou = 1;

                        printf("\nRealmente deseja apagar os dados registrados? [1:2]: ");
                        scanf("%d", &simnao);

                        if (simnao == 1)
                        {
                            for (i = 0; i < index; i++)
                            {
                                if (busca == vetor[i]->cadastro)
                                {
                                    vetor[i]->cadastro = vetor[i + 1]->cadastro;
                                    strcpy(vetor[i]->nome, vetor[i + 1]->nome);
                                    index--;
                                    printf("\nRegistro removido com sucesso!\n");
                                    printf("Pressione qualquer tecla para voltar ao Menu...");
                                    getch();
                                }
                            }
                        }

                        if (simnao == 2)
                        {
                            system("clear||cls");
                            printf("\nVoltando ao Menu...");
                            getch();
                        }
                    }
                }
                if (achou == 0)
                {
                    system("clear||cls");
                    printf("\nCadastro nao foi encontrado!\n");
                    printf("Pressione qualquer tecla para voltar ao Menu...");
                    getch();
                }
                achou = 0;
            }
            break;
        case 5: // Remover registro pelo nome
            system("clear||cls");
            if (index == 0)
            {
                printf("Ainda nao foi feito nenhum registro!\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
            }
            else
            {
                system("clear||cls");
                busca = 0;
                printf("__REMOVER REGISTRO PELO NOME__\n\n");
                printf("Digite o nome do registro que deseja remover: ");
                scanf("%s", &sbusca);

                for (i = 0; i < index; i++)
                {
                    if (strcmp(sbusca, vetor[i]->nome) == 0)
                    {
                        system("clear||cls");
                        printf("Dados encontrados: ");
                        printf("\nNumero do cadastro: %d", vetor[i]->cadastro);
                        printf("\nNome registrado do cadastro %d: %s", vetor[i]->cadastro, vetor[i]->nome);
                        achou = 1;

                        printf("\nRealmente deseja apagar os dados registrados? [1:2]: ");
                        scanf("%d", &simnao);

                        if (simnao == 1)
                        {
                            for (i = 0; i < index; i++)
                            {
                                if (strcmp(sbusca, vetor[i]->nome) == 0)
                                {
                                    vetor[i]->cadastro = vetor[i + 1]->cadastro;
                                    strcpy(vetor[i]->nome, vetor[i + 1]->nome);
                                    index--;
                                    printf("\nRegistro removido com sucesso!\n");
                                    printf("Pressione qualquer tecla para voltar ao Menu...");
                                    getch();
                                }
                            }
                        }

                        if (simnao == 2)
                        {
                            system("clear||cls");
                            printf("\nVoltando ao Menu...");
                            getch();
                        }
                    }
                }
                if (achou == 0)
                {
                    system("clear||cls");
                    printf("\nCadastro nao foi encontrado!\n");
                    printf("Pressione qualquer tecla para voltar ao Menu...");
                    getch();
                }
                achou = 0;
            }
            break;
        case 6: // Sair
            system("clear||cls");
            printf("Obrigado pela visita!");
            free(vetor);
            break;
        }
    } while (selecione != 6);
    free(vetor);
    return 0;
}
