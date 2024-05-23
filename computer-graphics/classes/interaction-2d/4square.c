/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
*/

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int n = 10;
float ang = 0;

void clear_window();
void draw();
void square(float offset_x, float offset_y);

void clear_window()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void square(float offset_x, float offset_y)
{
    // Daremos a possibilidade de transladar os quadrados
    glBegin(GL_QUADS);
    glVertex2f(-0.25 + offset_x, 0.25 + offset_y);
    glVertex2f(0.25 + offset_x, 0.25 + offset_y);
    glVertex2f(0.25 + offset_x, -0.25 + offset_y);
    glVertex2f(-0.25 + offset_x, -0.25 + offset_y);
    glEnd();
}

void draw()
{
    clear_window();

    glColor3f(1.0,0.0,0.0);
    square(-0.5, 0.5);

    glColor3f(0.0,1.0,0.0);
    square(0.5, 0.5);

    glColor3f(0.0,0.0,1.0);
    square(0.5, -0.5);

    glColor3f(1.0,1.0,0.0);
    square(-0.5, -0.5);

    glFlush();
}

int main(int argc, char *argv[])
{
    // Inicializa a glut (sistema de gerenciamento de janelas) com argumentos
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0, 0);

    glutInitWindowSize(600, 600);

    glutCreateWindow("4 squares");

    glutDisplayFunc(draw);

    glutMainLoop();

    return 0;
}