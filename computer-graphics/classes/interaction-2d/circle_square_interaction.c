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
float ray = 0.25;
float x_offset_circle = 0, y_offset_circle = 0;

void clear_window();
void draw();
void square(float x_offset, float y_offset);
void circle();
void special_keys(int key, int x, int y);

void clear_window()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void circle()
{
    int i;

    glBegin(GL_POLYGON);
    for (i = 0; i < n; i++)
    {
        glVertex2f(ray * cos(ang) + x_offset_circle, ray * sin(ang) + y_offset_circle);
        ang = ang + (2 * M_PI) / n;
    }
    glEnd();
}

void square(float x_offset, float y_offset)
{
    glBegin(GL_QUADS);
    glVertex2f(-0.25 + x_offset, 0.25 + y_offset);
    glVertex2f(0.25 + x_offset, 0.25 + y_offset);
    glVertex2f(0.25 + x_offset, -0.25 + y_offset);
    glVertex2f(-0.25 + x_offset, -0.25 + y_offset);
    glEnd();
}

void draw()
{
    clear_window();

    glColor3f(1.0, 1.0, 1.0);
    circle();

    glColor3f(1.0, 0.0, 0.0);
    square(-0.5, 0.5);

    glColor3f(0.0, 1.0, 0.0);
    square(0.5, 0.5);

    glColor3f(0.0, 0.0, 1.0);
    square(0.5, -0.5);

    glColor3f(1.0, 1.0, 0.0);
    square(-0.5, -0.5);

    glFlush();
}

void special_keys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        x_offset_circle += 0.1;
        break;
    case GLUT_KEY_UP:
        y_offset_circle += 0.1;
        break;
    case GLUT_KEY_LEFT:
        x_offset_circle -= 0.1;
        break;
    case GLUT_KEY_DOWN:
        y_offset_circle -= 0.1;
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0, 0);

    glutInitWindowSize(600, 600);

    glutCreateWindow("circle square interaction");

    glutDisplayFunc(draw);

    glutSpecialFunc(special_keys);

    glutMainLoop();

    return 0;
}