/*
 * Nome: Felipe Martins de Paula RA:140777
 * Nome: Harrison Caetano Candido RA:156264
 * Nome: Pedro Figueiredo Dias RA:156333
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int simple_cmd(char **cmd, int bckgrd);
int search_for_bckgrd(int argc, char **argv);
int search_conditional_delimiter(char **argv);
int search_pipe(int argc, char **argv);
int pipeline(int argc, char **cmd, int npipes);
int search_pipes(int argc, char **argv);
void conditional_cmd(char **cmd, int del);
int search_archive_delimiter(char **argv, char *c);
int work_archive_one(char **argv);
int work_archive_two(int argc, char **argv);

// interpreta um comando simples
int simple_cmd(char **cmd, int bckgrd)
{
    pid_t pid;

    pid = fork();

    // se o pid eh zero, estamos lidando com o processo filho
    if(pid == 0)
    {
        execvp(cmd[0], cmd);
        
        return 0;
    }
    // se o pid eh diferente de zero, estamos lidando com o processo pai
    else
    {
        int status;

        // se a variavel for zero, o processo deve ser executado em primeiro plano e o shell nao esta livre
        if(bckgrd == 0)
            waitpid(pid, &status, 0);

        return WEXITSTATUS(status);
    }
    return -1;
}

// simplesmente busca pelo caracter "&" em argv, que identifica a execucao do comando em segundo plano
int search_for_bckgrd(int argc, char **argv)
{
    int i = 0;

    while(argv[i] != NULL && i < argc)
    {
        if(strcmp(argv[i], "&") == 0)
        {
            argv[i] = NULL;
            return 1;
        }
        ++(i);
    }
}

// retorna o indice do pipe na linha de comando
int search_pipe(int argc, char **argv)
{
    int i = 0;

    while(argv[i] != NULL && i < argc) // argv[i] != NULL
    {
        if(strcmp(argv[i],"|") == 0)
            return i;
        ++(i);
    }

    return -1;
}

// executa um pipeline, em que a saida de um comando eh a entrada de outro
int pipeline(int argc, char **cmd, int npipes)
{
    int i, pp, fd[2], srfd;
    pid_t pid;

    // save read fd[0] para salvar cada valor salvo em um pipe para o proximo processo filho
    srfd = STDIN_FILENO;

    // pq temos npipes + 1 comandos
    for(i = 0; i < npipes; i++)
    {
        // sao criados exatamente npipes
        if(pipe(fd) == -1)
        {
            perror("pipe()");
            exit(1);
        }

        /*
        para cada iteracao, sera criado um pid para um novo processo filho no codigo inicial (processo pai), 
        ou seja, o teremos um unico processo pai esperando os n processos filhos
        */
        pid = fork();

        pp = search_pipe(argc, cmd);

        if(pp != -1)
            // particiono a matriz de argumentos
            cmd[pp] = NULL;

        // processo filho
        if(pid == 0)
        {
            close(fd[0]);

            // o processo filho precisa receber de outro filho pelo pipe 
            if(dup2(srfd, STDIN_FILENO) == -1)
            {
                perror("dup2()");
                exit(1);
            }

            // so vai escrever se nao for o ultimo
            if(i < npipes)
                // os processos filhos precisam escrever no pipe para outros filhos receberem
                if(dup2(fd[1], STDOUT_FILENO) == -1)
                {
                    perror("dup2()");
                    exit(1);
                }

            execvp(cmd[0], cmd);
        }
        // processo pai
        else if(pid > 0)
        {
            // apenas fecho a entrada desse processo pai, pq ele vai administrar os filhos
            close(fd[1]);

            waitpid(pid, NULL, 0);

            // salvo o valor de entrada do pipe em questao, para a entrada do proximo processo, que tera um novo pipe para escrever
            srfd = fd[0];
        }
        else
            return -1;

        if(pp != -1)
            // atualizo o inicio do ponteiro cmd, ou seja, aponta para o proximo comando
            cmd = &cmd[pp + 1];
    }

    return 0;
}

// conta a quantidade de pipes no array de argumentos argv
int search_pipes(int argc, char **argv)
{
    int i, count;

    i = count = 0;

    while(argv[i] != NULL && i < argc)
    {
        if(strcmp(argv[i], "|") == 0)
            count += 1;
        ++(i);
    }

    return count;
}

// essa funcao busca delimitadores como && e || e retorna o indice
int search_conditional_delimiter(char **argv)
{
    int i = 0;

    while(argv[i])
    {
        if(strcmp(argv[i], "&&") == 0 || strcmp(argv[i], "||") == 0)
            return 1;

        ++(i);
    }
    // retorna 0 caso nao encontre nada
    return -1; 
}

// executa uma linha de comando por partes usando a simple_cmd ao identificar os delimitadores
void conditional_cmd(char **cmd, int del)
{
    int aux, aux2;
    // np = next position no array argv
    char **np;

    aux = -1;

    if(del > 0)
    {
        np = &cmd[del + 1];

        if(strcmp(cmd[del], "&&") == 0)
            aux = 0; // flag para delimitador "e"

        if(strcmp(cmd[del], "||") == 0)
            aux = 1; // flag para delimitador "ou"
    
        cmd[del] = NULL;
    }

    // a ideia aqui eh executar o comando antes do delimitador
    aux2 = simple_cmd(cmd, 0);

    if((aux == 0 && aux2 == 0) || (aux == 1 && aux2 != 0))
    {
        // continuo buscando mais delimitadores ao londo de argv
        del = search_conditional_delimiter(np);

        // pois agora o array de strings tem n-1 elementos
        del -= 1;

        // chamo essa funcao recursivamente a fim de executar a outra parte do codigo
        conditional_cmd(np, del);
    }

    return;
}

int search_archive_delimiter(char **argv, char *c)
{
    int i = 0;

    while(argv[i])
    {
        if(strcmp(argv[i], c) == 0)
            return i;

        ++(i);
    }
    // retorna -1 caso nao encontre nada
    return -1; 
}

/*
pensando em sort < teste.txt > novo_teste.txt, temos
            [1] [2]    [3]  [4]     [5]
*/
int work_archive_one(char **argv) 
{
    /*
    fd[0] - representa aqui nesse caso o descritor do modo de abertura (no caso de leitura)
    fd[1] - representa aqui nesse caso o descritor do modo de abertura (no caso escrita)
    */
    int fd[2], sad;

   /*-------------------------- capturo a E/S do arquivo usando descritores ----------------------------- */

    // busca delimitador de entrada "<"
    sad = search_archive_delimiter(argv, "<");
    
    if(sad == -1)
        // nao encontrou
        exit(1);
    else
        // encontrou alguma entrada, indice do delimitador + 1 da exatamente o nome do arquivo, abre o arquivo de entrada no modo leitura apenas usando a opcao O_RDONLY
        fd[0] = open(argv[sad + 1], O_RDONLY);

    /*
    abre ou cria o arquivo de saida
    
    opcoes:
        O_WRONLY - Abre o arquivo para escrita
        O_CREAT - Cria o arquivo se ele nao existir
        O_TRUNC - Truncando/sobrescrevendo o conteudo do arquivo se ele ja existir
        O_APPEND - Escreve ao fim do conteudo do arquivo se ele ja existir

    permissoes:
        S_IRUSR - 0400 em octal, define a permissao de leitura para o usuario
        S_IWUSR - 0200 em octal, define a permissao de escrita para o usuario 
    */

    // busca delimitador de saida ">"
    sad = search_archive_delimiter(argv, ">");

    if(sad == -1)
        // nao encontrou
        exit(1);
    else
        fd[1] = open(argv[sad + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    // busca delimitador de saida ">>"
    sad = search_archive_delimiter(argv, ">>");

    if(sad == -1)
        // nao encontrou
        exit(1);
    else
        fd[1] = open(argv[sad + 1], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

    /*--------------------------------------------------------------------------------------------------- */

    /*------------------------------ verificacao no retorno dos descritores ----------------------------- */
    if (fd[0] == -1) 
    {
        // abertura do descritor de escrita desse arquivo falhou
        perror("open()");
        exit(1);
    }

    if (fd[1] == -1) 
    {
        // abertura do descritor desse arquivo falhou
        perror("open()");
        exit(1);
    }

    /*--------------------------------------------------------------------------------------------------- */

    /*--------------------------------- redirecionamento de entrada/saida ------------------------------- */

    /*
    sabemos que nosso processo le da entrada e escreve na sua saida padrao. 
    queremos redirecionar a entrada/saida do processo para ler/escrever no arquivo usando os descritores, que como disse identificam o modo de abertura do arquivo
    */
    // redireciona a entrada padrão do PROCESSO (STDIN_FILENO) para o descritor de arquivo do arquivo aberto na opcao de leitura (ele passa a ser a entrada do processo, em vez de ser o terminal por ex)
    if (dup2(fd[0], STDIN_FILENO) == -1) 
    {
        // redirecionamento da entrada padrao desse arquivo falhou
        perror("dup2()");
        exit(1);
    }

    // redireciona a saida padrão do PROCESSO (STDOUT_FILENO) para o descritor de arquivo do arquivo aberto na opcao de escrita (ele passa a ser a saida do processo, em vez de ser o terminal por ex)
    if (dup2(fd[1], STDOUT_FILENO) == -1) 
    {
        // redirecionamento da saida padrao desse arquivo falhou
        perror("dup2()");
        exit(1);
    }

    /*--------------------------------------------------------------------------------------------------- */

    /*------------------------------ execucao da imagem de nucleo do processo --------------------------- */

    // executa o comando "sort" com a entrada e saída padrao redirecionadas
    if (execvp(argv[1], argv + 1) == -1) 
    {
        perror("execvp()");
        exit(1);
    }
    /*--------------------------------------------------------------------------------------------------- */

    return 0;
}

int work_archive_two(int argc, char **argv)
{
    // ponto de atencao aqui: fd[2] eh o vetor que guarda descritores do pipe
    int fd[2], pp, sad, fd_in, fd_out;
    char **cmd1, **cmd2;
    pid_t pid;

    cmd1 = &argv[1];

    /*--------------------------------- redirecionamento de entrada/saida ------------------------------- */
    if(pipe(fd) == -1)
    {
        perror("pipe()");
        exit(1);
    }

    pp = search_pipe(argc, argv);

    if(pp == -1)
        return -1;

    // particiono a matriz argv
    cmd1[pp] = NULL;
    cmd2 = &cmd1[pp + 1];

    pid = fork();

    // processo filho, responsavel por abrir o primeiro arquivo no modo leitura
    if(pid == 0)
    {
        // busca delimitador de entrada "<"
        sad = search_archive_delimiter(argv, "<");
    
        if(sad == -1)
            // nao encontrou
            return 0;
        else
            // encontrou alguma entrada, indice do delimitador + 1 da exatamente o nome do arquivo, abre o arquivo de entrada no modo leitura apenas usando a opcao O_RDONLY
            fd_in = open(argv[sad + 1], O_RDONLY);

        if (fd_in == -1) 
        {
            // abertura do descritor de escrita desse arquivo falhou
            perror("open()");
            exit(1);
        }

        // preciso primeiro fechar a entrada padrao do pipe
        close(fd[0]);
        
        // redireciono a entrada padrao desse processo para o descritor de arquivo do .txt aberto no modo leitura
        if(dup2(fd_in, STDIN_FILENO) == -1)
        {
            perror("dup2()");
            exit(1);
        }

        // redireciono a saida padrao desse processo para o descritor de arquivo de saida do pipe, ou seja, escrevo no pipe
        if(dup2(fd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2()");
            exit(1);
        }

        // execvp envia a saida desse processo pro pipe
        execvp(cmd1[0], cmd1);
    }
    else
    {
        int status;
        /*
        abre ou cria o arquivo de saida
        
        opcoes:
            O_WRONLY - Abre o arquivo para escrita
            O_CREAT - Cria o arquivo se ele nao existir
            O_TRUNC - Truncando/sobrescrevendo o conteudo do arquivo se ele ja existir
            O_APPEND - Escreve ao fim do conteudo do arquivo se ele ja existir

        permissoes:
            S_IRUSR - 0400 em octal, define a permissao de leitura para o usuario
            S_IWUSR - 0200 em octal, define a permissao de escrita para o usuario 
        */

        // busca delimitador de saida ">"
        sad = search_archive_delimiter(argv, ">");

        if(sad == -1)
            // nao encontrou
            exit(1);
        else
            fd_out = open(argv[sad + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

        // busca delimitador de saida ">>"
        sad = search_archive_delimiter(argv, ">>");

        if(sad == -1)
            // nao encontrou
            exit(1);
        else
            fd_out = open(argv[sad + 1], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

        // fecho o descritor de arquivo de saida do pipe
        close(fd[1]);

        // redireciono a saida padrao desse processo para o descritor de arquivo do .txt aberto no modo escrita
        if(dup2(fd_out, STDOUT_FILENO) == -1)
        {
            perror("dup2()");
            exit(1);
        }

        // redireciono a entrada padrao desse processo para o descritor de arquivo de entrada do pipe, ou seja, leio do pipe
        if(dup2(fd[0], STDIN_FILENO) == -1)
        {
            perror("dup2()");
            exit(1);
        }

        // aguardando o filho
        waitpid(pid, &status, 0);

        // execvp processa o proximo comando apos o pipe
        execvp(cmd2[0], cmd2);

        return WEXITSTATUS(status);
    }

    return 0;
}

/*
corpo do interpretador:

argc - int que identifica a quantidade de argumentos passados para o programa na linha de comando
argv - array de ponteiros para caracteres que contém os argumentos passados ao programa, argv[0] é o nome,
	   argv[1], argv[n-1] sao os outros argumentos
*/
int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("Para comandos simples use:\n./main <comando> <parametros>\n");
        printf("Para comandos com operadores use:\n./main <comando> <parametros> <operador> <comando> <parametros> <operador> ...\n");

        return 0;
    }

    int del, npipes, bckgrd;
    char **cmd = &argv[1];

    // busca delimitadores do tipo "<" ou ">" para identificar se estamos trabalhando com arquivos SEM pipe
    if((search_archive_delimiter(argv, "<") != -1 || search_archive_delimiter(argv, ">") != -1) && search_pipe(argc, argv) == -1)
        if(work_archive_one(argv) == 0)
            return 0;

    // busca delimitadores do tipo "<" ou ">" para identificar se estamos trabalhando com arquivos COM pipe
    if((search_archive_delimiter(argv, "<") != -1 || search_archive_delimiter(argv, ">") != -1) && search_pipe(argc, argv) != -1)    
        if(work_archive_two(argc, argv) == 0)
            return 0;

    // nossa segunda operacao do shell consiste em buscar por delimitadores do tipo "&&" e "||", a fim de decidir se a linha de comando sera interpretada como linha de comando condicional ou não
    del = search_conditional_delimiter(argv);

    // pois agora o array de strings tem n-1 elementos
    del -= 1;

    if(del > 0)
    // caso existam delimitadores condicionais
        conditional_cmd(cmd, del);
    else
    // caso nao existam delimitadores condicionais, somente trata linhas de comando com ou sem pipes
    {
        npipes = search_pipes(argc, argv);

        // se tiver algum pipe, executara a linha de comando no modo pipeline
        if(npipes != 0)
            pipeline(argc, cmd, npipes);
        // se nao tiver pipe, ira executar o comando com fork e, de maneira previa, ira tentar entender se o comando deve ser executado em segundo plano
        else
        {
            bckgrd = search_for_bckgrd(argc, argv);

            simple_cmd(cmd, bckgrd);
        }
    }
    
    return 0;
}

/*
gcc shell.c -o shell

1)
./shell ls -la

2)
./shell ls -la | grep "teste.txt"
./shell cat /proc/cpuinfo | grep "model name" | wc -l

3)
./shell cat 12345 || echo "aquivo inexistente"
./shell ping -c1 www.unifesp.br.br && echo "SERVIDOR DISPONIVEL" ||
echo "SERVIDOR INDISPONIVEL"

4)
./shell ping -c5 www.unifesp.br &

5)
./shell sort < teste.txt > novo_teste.txt
./shell sort > teste.txt < novo_teste.txt

6)
./shell sort < teste.txt >> novo_teste.txt

7)
./shell sort < teste.txt | grep "x" > novo_teste.txt
./shell sort < teste.txt | grep "x" >> novo_teste.txt

*/
