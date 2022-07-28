/*
    Joselito possui um estacionamento em que cobra R$3,00 por hora
(carro estacionado menos de 15 min não paga). Quando algum carro estaciona,
ele anota o numero da vaga (os carros devem ser estacionados na sequencia de vagas)
e os horarios de entrada e saida (ao sair) do veiculo. Construa um programa em c para que
Joselito controle a entrada e saida de veiculos de seu estacionamento e calcule o faturamento
do dia. Peca para o usuario digitar o numero de vagas (use alocacao dinamica).
    O programa devera ler as entradas e saidas de veiculos. Faca um menu de opcoes indicando
o que deve ser feito (leitura de chegada, saida - pedir o numero da vaga que o carro esta estacionado,
faturamento ate o momento, sair do programa).
    A cada retirada de veiculo, os que estao em vagas posteriores ao que foi retirado deverao ser
movidos uma vaga para tras.
    >>> Fazer verificacao de erros! <<<
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Horas
{
    int horas, minutos;
} horas;

typedef struct Estacionamento
{
    horas he, hs;
} Estacionamento;

void entrada(Estacionamento *p, int *tam);
void saida(Estacionamento *p, int *tam, int *fat);
void faturamento(Estacionamento *p, int *tam);

int main()
{
    int selecione, n, tam;
    float fat;
    tam = 0;
    fat = 0;

    printf("Digite a quantidade de vagas do estacionamento:");
    scanf("%d", &n);

    Estacionamento *vet;

    vet = (Estacionamento *)malloc(n * sizeof(Estacionamento)); // eh criado entao um vetor de tamanho n

    if (vet == NULL)
    {
        printf("Erro na alocacao dinamica!\n");
        return 0;
    }

    do
    {
        printf("1 | Entrada de veiculo\n");
        printf("2 | Saida de veiculo\n");
        printf("3 | Faturamento\n");
        printf("4 | Sair\n");
        printf("Selecione: ");
        scanf("%d", &selecione);
        switch (selecione)
        {
        case 1: // entrada
            entrada(vet, &tam);
            break;
        case 2: // saida
            saida(vet, &tam, &fat);
            break;
        case 3: // faturamento
            faturamento(vet, &tam);
            break;
        case 4: // sair
            break;
        default:
            printf("Opcao invalida, selecione novamente!\n");
            break;
        }
    } while (selecione != 4);

    return 0;
}

void entrada(Estacionamento *p, int *tam)
{
    printf("Digite a hora de entrada(hr:mm): ");
    scanf("%d:%d", &p[*tam].he.horas, &p[(*tam)++].he.minutos);
}

void saida(Estacionamento *p, int *tam, int *fat)
{
    int i, vaga = 0, min, hora;

    if (*tam == 0)
    {
        printf("Estacionamento vazio!\n");
        return;
    }

    if (*tam > 1)
    {
        do
        {
            printf("Digite o numero da vaga: ");
            scanf("%d", &vaga);

            if (vaga < 1 || vaga > *tam)
            {
                printf("Vaga nao existe!\n");
            }
        } while (vaga < 1 || vaga > *tam);
        vaga--;

        printf("Digite o horario de saida(hh:mm): ");
        scanf("%d:%d", &p[vaga].hs.horas, &p[vaga].hs.minutos);

        hora = p[vaga].hs.horas - p[vaga].he.horas;
        min = p[vaga].hs.minutos - p[vaga].he.minutos;
        min = min + hora;

        if (min < 0)
        {
            printf("Hora de saida invalida!\n");
        }

        if (min > 15)
        {
            *fat += (min / 60) * 3;

            if (min % 60 > 0)
            {
                *fat += 3;
            }
            if (*tam > 1)
            {
                for (i = vaga; i < *tam - 1; i++)
                {
                    p[i].he.minutos = p[i + 1].he.minutos;
                    p[i].he.horas = p[i].he.horas;
                }
                (*tam)--;
                printf("Faturamento: %.2f", fat);
            }
        }
    }
}

void faturamento(Estacionamento *p, int *tam)
{
    int vaga, hora, minuto, fat = 0;

    if (*tam == 0)
    {
        printf("Estacionamento vazio!\n");
        return;
    }

    if (*tam > 1)
    {

        printf("Digite o numero da vaga: ");
        scanf("%d", &vaga);

        printf("Digite o horario atual(hh:mm): ");
        scanf("%d:%d", &hora, &minuto);

        vaga--;

        hora = p[vaga].he.horas - hora;
        minuto = p[vaga].he.minutos - minuto;
        minuto = minuto + hora;

        if (minuto < 0)
        {
            printf("Hora atual invalida!\n");
        }

        if (minuto > 15)
        {
            fat += (minuto / 60) * 3;

            if (minuto % 60 > 0)
            {
                fat += 3;
            }
            printf("Faturamento: %d", fat);
        }
    }
}