/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
*/
/*
  3) Crie um programa com duas funcoes: a de imprimir uma
  linha entre dois pontos quaisquer e a de alterar a cor da
  linha. Uma linha inicial entre os pontos (0,0) e (0,0) azul
  deve ser tracada. A linha muda de posicao de acordo com
  as coordenadas dadas por um clique inicial e um clique
  final com o botao esquerdo do mouse. As cores sao
  selecionadas da mesma maneira que no exercicio 2.
*/

#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/gl.h>

float gXE = 0.0, gYE = 0.0, gXD = 0.0, gYD = 0.0, gR = 0.5, gG = 0.5, gB = 1.0;
char vertexTurn[11] = {"vertice 1\0"};

void clearWindow();
void object();
void draw();
void mouse(int botao, int estado, int x, int y);

void clearWindow()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void object()
{
    // Redefine em pixels o tamanho dos pontos na janela
    glLineWidth(5.0);

    // Defino a forma do objeto
    glBegin(GL_LINES);
    // Defino a posicao dos vertices do objeto
    glVertex2f(gXE, gYE);
    glVertex2f(gXD, gYD);
    glEnd();
}

void draw()
{
    clearWindow();

    // Defino a cor do objeto
    glColor3f(gR, gG, gB);

    // Chamo a funcao construtora do formato e estrutura do objeto
    object();

    // Forco a execucao de todos os comandos do OpenGL enviados a fila de processos
    glFlush();
}

void mouse(int botao, int estado, int x, int y)
{
    switch (botao)
    {
    case GLUT_LEFT_BUTTON:
        if (estado == GLUT_DOWN && strcmp(vertexTurn, "vertice 1") == 0)
        {
            // ---------------------------------------------------------------------------------------
            // Normalizacao das coordenadas x e y capturadas pela funcao para o intervalo de -1 a 1:

            // normalizedValue = (newValue - minNew) / (maxNew - minNew) * (maxOriginal - minOriginal) + minOriginal
            gXE = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;

            // normalizedValue = 2 * (originalValue - minOriginal) / (maxOriginal - minOriginal) - 1
            gYE = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);
            // ---------------------------------------------------------------------------------------

            printf("vertice 1: x = %f, y = %f\n", gXE, gYE);

            // Passo a string que trava para o tratamento da interacao com o segundo vertice
            strcpy(vertexTurn, "vertice 2");

            break;
        }
        if (estado == GLUT_DOWN && strcmp(vertexTurn, "vertice 2") == 0)
        {
            // ---------------------------------------------------------------------------------------
            // Normalizacao das coordenadas x e y capturadas pela funcao para o intervalo de -1 a 1:

            // normalizedValue = (newValue - minNew) / (maxNew - minNew) * (maxOriginal - minOriginal) + minOriginal
            gXD = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;

            // normalizedValue = 2 * (originalValue - minOriginal) / (maxOriginal - minOriginal) - 1
            gYD = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);
            // ---------------------------------------------------------------------------------------

            printf("vertice 2: x = %f, y = %f\n", gXD, gYD);

            // Passo a string que trava para o tratamento da interacao com o primeiro vertice
            strcpy(vertexTurn, "vertice 1");
        }
        break;
    default:
        break;
    }
    // Essa funcao cria uma solicitacao no fluxo de eventos do OpenGL que faz com que a atualizacao da janela esteja agendada
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '0':
        // Vermelho: (1.0, 0.0, 0.0)
        gR = 1.0;
        gG = 0.0;
        gB = 0.0;
        break;
    case '1':
        // Verde: (0.0, 1.0, 0.0)
        gR = 0.0;
        gG = 1.0;
        gB = 0.0;
        break;
    case '2':
        // Azul: (0.0, 0.0, 1.0)
        gR = 0.0;
        gG = 0.0;
        gB = 1.0;
        break;
    case '3':
        // Amarelo: (1.0, 1.0, 0.0)
        gR = 1.0;
        gG = 1.0;
        gB = 0.0;
        break;
    case '4':
        // Ciano: (0.0, 1.0, 1.0)
        gR = 0.0;
        gG = 1.0;
        gB = 1.0;
        break;
    case '5':
        // Magenta: (1.0, 0.0, 1.0)
        gR = 1.0;
        gG = 0.0;
        gB = 1.0;
        break;
    case '6':
        // Laranja: (1.0, 0.5, 0.0)
        gR = 1.0;
        gG = 0.5;
        gB = 0.0;
        break;
    case '7':
        // Rosa: (1.0, 0.75, 0.8)
        gR = 1.0;
        gG = 0.75;
        gB = 0.8;
        break;
    case '8':
        // Verde-água: (0.5, 1.0, 0.83)
        gR = 0.5;
        gG = 1.0;
        gB = 0.83;
        break;
    case '9':
        // Roxo: (0.5, 0.0, 0.5)
        gR = 0.5;
        gG = 0.0;
        gB = 0.5;
        break;

    default:
        break;
    }
    // Essa funcao cria uma solicitacao no fluxo de eventos do OpenGL que faz com que a atualizacao da janela esteja agendada
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    // Configura a quantidade de buffers e qual o sistema de cores (RGBA ou INDEXADO)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Configura a posicao da janela na tela
    glutInitWindowPosition(750, 100);

    // Configura o tamanho da janela
    glutInitWindowSize(600, 600);

    // Inicia o programa com comandos passados pelo terminal se necessario
    glutInit(&argc, argv);

    // Da um nome e cria a janela
    glutCreateWindow("Exercicio 3");

    // Chama a funcao que vai construir o objeto na tela
    glutDisplayFunc(draw);

    // Chama a funcao de escuta do mouse para o vertice 1
    glutMouseFunc(mouse);

    // Chama a funcao de escuta do mouse para o vertice 2
    glutMouseFunc(mouse);

    // Chama a funcao de escuta do teclado
    glutKeyboardFunc(keyboard);

    // Mantem a main como um processo iterativo, semelhante ao busy wait, mas sem ocupar ineficientemente a cpu
    glutMainLoop();

    return 0;
}
