/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
*/

#include <stdio.h>
#include <GL/glut.h>

void clear_window();
void draw();
void keyboard();
void special_keys();
void mouse();

void clear_window()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw()
{
    clear_window();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 0.8);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.8, -0.8);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(-0.8, -0.8);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
    case 'S':
        // sombreamento 'suave'
        glShadeModel(GL_SMOOTH);
        break;
    case 'f':
    case 'F':
        // sombreamento 'plano'
        glShadeModel(GL_FLAT);
        break;
    default:
        break;
    }
    // Marca a janela de sistema para ser atualizada
    glutPostRedisplay();
}

void special_keys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_LEFT:
        glShadeModel(GL_SMOOTH);
        break;
    case GLUT_KEY_DOWN:
    case GLUT_KEY_RIGHT:
        glShadeModel(GL_FLAT);
        break;
    default:
        break;
    }
    // Marca a janela de sistema para ser atualizada
    glutPostRedisplay();
}

void mouse(int button, int estado, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (estado == GLUT_DOWN)
            glShadeModel(GL_SMOOTH);
        break;
    case GLUT_RIGHT_BUTTON:
        if (estado == GLUT_UP)
            glShadeModel(GL_FLAT);
        break;
    default:
        break;
    }
    // Marco a janela de sistema para ser atualizada
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowPosition(0, 0);

    glutInitWindowSize(600, 600);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow("interaction");

    glutDisplayFunc(draw);

    // Carrega a funcao que configura entrada de comandos pelo teclado
    glutKeyboardFunc(keyboard);

    // Carrega a funcao que configura entrada de comandos por teclas especiais
    glutSpecialFunc(special_keys);

    // Carrega a funcao que configura comandos pelo mouse
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}