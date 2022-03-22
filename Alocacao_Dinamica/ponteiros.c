/*
## Teoria - Depende da arquitetura do computador, porém aqui temos um computador de 64 bits

1 bit - Menor tamanho ou espaco de memoria no computador, so pode armazenar 0 ou 1

8 bits = 1 byte

1024 bytes = 1 kilobyte

1024 kilobyte = 1 megabytes

1024 megabytes = 1 gigabyte

## Tipos de Dados

int - 4 bits
float - 4 bits
double - 8 bits

Se quero um endereco de memoria
*/

int main(){
    int x;
    x=10;

    int *ponteiro;
    ponteiro = &x;

    printf("%d",&x); //Acessamos o endereco de memoria da variavel dentro do SO
}


