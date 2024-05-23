/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
*/
/*
  1) Escreva um programa que imprima um ponto azul de
  tamanho 5.0 na posicao em que houver um clique de
  botao esquerdo do mouse.

  Inicialmente, o ponto deve ficar nas coordenadas (0,0).

  Este exercicio sera fundamental para aprender:
  (a) a ajustar as coordenadas do mouse e da janela;
  (b) a desenhar o ponto na funcao correta;
  (c) a guardar as coordenadas lidas.
*/

#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

float gx = 0.0, gy = 0.0;

void clearWindow();
void object();
void draw();
void mouse(int botao, int estado, int x, int y);

// Limpa a janela
void clearWindow()
{
    // Seto a cor no buffer de cores
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    // Limpo a janela de acordo com a cor especificada no buffer de cores da janela (setado anteriormente)
    glClear(GL_COLOR_BUFFER_BIT);
}

// A descricao dos objetos geometricos eh feita por vertices. O conjunto de arestas formado desenha nosso objeto
void object()
{
    // Redefine o tamanho em pixels dos pontos
    glPointSize(5.0);

    glBegin(GL_POINTS);
    // Coordenadas x e y do plano 2D
    glVertex2f(gx, gy);
    glEnd();
}

void draw()
{
    clearWindow();

    // Defino uma cor independentemente da descricao do formato do objeto
    glColor3f(0.5, 0.5, 1.0); // RED, GREEN, BLUE

    // Chamo o objeto
    object();

    // Forca a execucao de todos os comandos enviados para a fila de processos, garantindo que sejam terminados em tempo finito
    glFlush();
}

void mouse(int botao, int estado, int x, int y)
{
    switch (botao)
    {
    case GLUT_LEFT_BUTTON:
        if (estado == GLUT_DOWN)
        {
            // -----------------------------------------------------------------------
            // Normalizar as coordenadas para o intervalo de -1 a 1:

            // normalizedValue = (newValue - minNew) / (maxNew - minNew) * (maxOriginal - minOriginal) + minOriginal
            gx = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;

            // normalizedValue = 2 * (originalValue - minOriginal) / (maxOriginal - minOriginal) - 1
            gy = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);
            // -----------------------------------------------------------------------

            printf("x = %f, y = %f\n", gx, gy);
        }
        break;

    default:
        break;
    }
    glutPostRedisplay(); // Faz uma solicitacao de redesenho na janela na proxima iteracao da main
}

int main(int argc, char *argv[])
{
    // Especifica qual o sistema de cores (RGBA ou INDEXADO) e quantidade de buffers (GLUT_SINGLE ou GLUT_DOUBLE) para geracao de imagens
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Especifica as coordenadas da janela na tela
    glutInitWindowPosition(50, 100);

    // Especifica largura e altura em pixels da janela
    glutInitWindowSize(600, 600);

    // Inicializa o programa com comandos especificados pelo terminal se necessario
    glutInit(&argc, argv);

    // Cria a janela com nome igual ao da string passada
    glutCreateWindow("Exercicio 1");

    // Chama o procedimento que sera executado para criar e mostrar o objeto na janela
    glutDisplayFunc(draw);

    // Chama a funcao que ira definir a interacao com o mouse
    glutMouseFunc(mouse);

    // Depois de chamada todas as janelas configuradas e criadas sao mostradas na tela
    glutMainLoop();

    return 0;
}
