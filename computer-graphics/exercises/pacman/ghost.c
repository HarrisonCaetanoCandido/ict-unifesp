/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
  g++ -o example example.cpp -lglut -lGLU -lGL -lm
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void lightning();
void ghost_head();
void ghost_eyes();
void semi_sphere();
void ghost_body();
void ghost_skirt();
void movement(int key, int x, int y);

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;

void lightning()
{
    GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat light1_pos[] = {-2.0f, 0.0f, 0.0f, 1.0f};
    GLfloat direction[] = {1.0f, 0.0f, 0.0f}; // direcao de alguma fonte de luz
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    // primeira fonte de luz pontual
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    // segunda fonte de Luz pontual
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);

    // direcao da segunda fonte de luz
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction); // luz como um vetor direcao, como um holofote
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);         // espalhamento angular
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.1f);        // atenuacao angular

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

// inicializacao do programa
void init(void)
{
    // glEnable(GL_COLOR_MATERIAL);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // define a cor de fundo

    // habilita o teste de profundidade
    // para determinar se objeto recem renderizado deve substituir valor no buffer
    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH); // sombreamento suave

    glEnable(GL_NORMALIZE); // normalizamos os vetores (util para reflexao especular)

    glMatrixMode(GL_MODELVIEW); // define que a matrix é a model (transformacoes3d na cena) view (transformacoes da camera)
    glLoadIdentity();           // carrega a matrix de identidade (matriz limpa)
    gluLookAt(0.0, 2.0, 5.0,    // posição da camera
              0.0, 0.0, 0.0,    // para onde a camera aponta
              0.0, 1.0, 0.0);   // vetor view-up

    glMatrixMode(GL_PROJECTION); // define que a matrix é a de projeção
    glLoadIdentity();            // carrega a matrix de identidade

    gluPerspective(45.0, 1.0, 2.0, 8.0); // define uma projeção perspectiva

    // define dimensoes da area de renderizacao da viewport. x, y, width, height
    glViewport(0, 0, 500, 500);
    lightning();
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // limpa o buffer

    glMatrixMode(GL_MODELVIEW); // define que a matrix é a de model (transformacoes na cena3d) view (transformacoes da camera)

    glPushMatrix(); // empurramos (salvamos) a matriz atual em uma pilha, fazemos transformacoes no contexto atual e depois damos pop na matriz para restaurar o contexto interrompido
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    //ghost_head();
    //ghost_eyes();
    //ghost_body();
    ghost_skirt();
    glPopMatrix(); // devolvo o contexto anterior as transformacoes atuais

    glFlush(); // força o desenho das primitivas
}

// ref: https://www.songho.ca/opengl/gl_sphere.html
void ghost_head()
{
    int i, j, slices, stacks;
    float theta1, theta2, radius, phi, x1, y1, z1, x2, y2, z2;

    radius = 0.49f;
    slices = 10;
    stacks = 10;

    for (i = 0; i < stacks; i++)
    {
        theta1 = (M_PI * i) / stacks;
        theta2 = (M_PI * (i + 1)) / stacks;

        glBegin(GL_QUAD_STRIP);

        for (j = 0; j <= slices; j++)
        {
            phi = (2.0 * M_PI * j) / slices;

            x1 = radius * sin(theta1) * cos(phi);
            y1 = radius * sin(theta1) * sin(phi);
            z1 = radius * cos(theta1);

            x2 = radius * sin(theta2) * cos(phi);
            y2 = radius * sin(theta2) * sin(phi);
            z2 = radius * cos(theta2);

            glNormal3f(x1, y1, z1);
            glVertex3f(x1, y1, z1);

            glNormal3f(x2, y2, z2);
            glVertex3f(x2, y2, z2);
        }

        glEnd();
    }
}

void ghost_eyes()
{
    glTranslatef(-0.2f, 0.2f, 0.3f);
    semi_sphere();

    glTranslatef(0.4f, 0.0f, 0.0f);
    semi_sphere();

    glTranslatef(-0.2f, -0.2f, -0.3f);
}

void semi_sphere()
{
    int i, j, slices, stacks;
    float theta1, theta2, radius, phi, x1, y1, z1, x2, y2, z2;

    radius = 0.1f;
    slices = 10;
    stacks = 10;

    for (i = 0; i < stacks; i++)
    {
        theta1 = (M_PI * i) / stacks;
        theta2 = (M_PI * (i + 1)) / stacks;

        glBegin(GL_QUAD_STRIP);

        for (j = 0; j <= slices; j++)
        {
            phi = (2.0 * M_PI * j) / slices;

            x1 = radius * sin(theta1) * cos(phi);
            y1 = radius * sin(theta1) * sin(phi);
            z1 = radius * cos(theta1);

            x2 = radius * sin(theta2) * cos(phi);
            y2 = radius * sin(theta2) * sin(phi);
            z2 = radius * cos(theta2);

            glNormal3f(x1, y1, z1);
            glVertex3f(x1, y1, z1);

            glNormal3f(x2, y2, z2);
            glVertex3f(x2, y2, z2);
        }

        glEnd();
    }
}

// ref: https://www.songho.ca/opengl/gl_sphere.html
void ghost_body()
{
    int i, segments;
    float ang, x, z, radius, height;

    radius = 0.5f;
    height = 0.5f;
    segments = 10;

    // lados do cilindro
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= segments; i++)
    {
        ang = (2.0f * M_PI * i) / segments; // angulo
        x = radius * cos(ang);              // cos = cat. adjacente/ hipotenusa
        z = radius * sin(ang);              // sen = cat. oposto/ hipotenusa
        glNormal3f(x, 0.0f, z);
        glVertex3f(x, 0.0f, z);
        glNormal3f(x, height, z);
        glVertex3f(x, height, z);
    }
    glEnd();
}

void ghost_skirt()
{
    int i, segments;
    float ang, x, z, radius, height;

    radius = 0.5f;
    height = 0.5f;
    segments = 10;

    // lados do cilindro
    glBegin(GL_TRIANGLES);
    for (i = 0; i <= segments; i++)
    {
        ang = (2.0f * M_PI * i) / segments; // angulo
        x = radius * cos(ang);              // cos = cat. adjacente/ hipotenusa
        z = radius * sin(ang);              // sen = cat. oposto/ hipotenusa
        //glNormal3f(x, 0.0f, z);
        //glVertex3f(x, 0.0f, z);
        glNormal3f(x, height, z);
        glVertex3f(x, height, z);
    }
    glEnd();
}

void movement(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        angleX -= 2; // rotacao horaria
        break;

    case GLUT_KEY_DOWN:
        angleX += 2; // rotacao anti horaria
        break;

    case GLUT_KEY_LEFT:
        angleY += 2; // rotacao anti horaria
        break;

    case GLUT_KEY_RIGHT:
        angleY -= 2; // rotacao horaria
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Fantasma");
    glutDisplayFunc(draw);
    glutSpecialFunc(movement);
    init();
    glutMainLoop();
    return 0;
}