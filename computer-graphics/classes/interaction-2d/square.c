/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
*/

#include <stdio.h>

// Rotinas para ajustar orientações e projeções de matrizes com pontos de vistas específicos
// e geração de superfícies
#include <GL/glut.h>

void clear_window();
void draw();

void clear_window()
{
    glClearColor(0, 0, 0, 0); // seto o GL_COLOR_BUFFER_BIT
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw()
{
    clear_window();

    glBegin(GL_QUAD_STRIP);
    glVertex2f(0.0, 0.3);
    glVertex2f(0.0, 0.6);
    glVertex2f(0.3, 0.3);
    glVertex2f(0.3, 0.6);
    glEnd();

    // Força a inicialização de todos os comandos OpenGL
    glFlush();
}

int main(int argc, char *argv[])
{
    // Inicializo a glut (sistema de gerenciamento de janelas) com argumentos
    glutInit(&argc, argv);

    // Modo de inicialização do display. Quantidade de buffer | Sistema de cores
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Posição da Janela de sistema na tela
    glutInitWindowPosition(0, 0);

    // Inicializo a janela de sistema com um tamanho
    glutInitWindowSize(400, 400);

    // Dou um nome para a janela de sistema
    glutCreateWindow("square");

    // Crio a janela usando esta viewport
    glutDisplayFunc(draw);

    // Carrego todas as viewports
    glutMainLoop();

    return 0;
}