/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
*/
/*
    Implementar o algoritmo de recorte de linha 2D de
    Cohen-Sutherland.
        - Plotar um quadro semelhante ao exerc ́ıcio anterior;
        - Dados um clique inicial e um clique final com o botao
        esquerdo do mouse, que darao os pontos inicial e final
        da linha, somente devem ser mostradas as partes da
        linha que se encontram dentro do quadro;
        - O recorte deve ser feito seguindo o algoritmo de
        Cohen-Sutherland.
*/

#include <stdio.h>
#include <GL/glut.h>

void clear_window();
void draw();
gluOrtho2D(GLfloat xw_min, GLfloat xw_max, GLfloat yw_min, GLfloat yx_max);

void clear_window()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw()
{
    GLfloat xw_min, xw_max, yw_min, yw_max;

    clear_window();

    /*
    Antes de definir a Janela de Recorte e a Viewport
    nos definimos a matriz de projeção como a matriz em uso
    */
    glMatrixMode(GL_PROJECTION);

    /*
    Nao esqueca que as transformacoes sao cumulativas,
    entao quando necessario carregar a matriz identidade
    */
    glLoadIdentity();

    /*
    A Janela de Recorte eh definida pela funcao abaixo. Observe que se nao houver
    especificacao as coordenadas padrao serao xw_min = yw_min = -1 e xw_max = yx_max = 1.
    Ou seja o processo de recorte ocorre em um quadrado normalizado entre -1 e 1.
    */
    gluOrtho2D(xw_min, xw_max, yw_min, yw_max);



}

int main(int argc, char *argv)
{
    glutInit(argc, &argv);

    // Nao sei pq usar GLUT_DOUBLE e nao GLUT_SINGLE
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowPosition(0, 0);

    glutInitWindowSize(400, 400);

    glutCreateWindow('Viewing-2D');

    glutDisplayFunc(draw);

    // Nao sei pra que esse timer serve
    glutTimerFunc(10,timerFunc,1);
    init();

    glutMainLoop();

    return 0;
}

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

GLfloat k = -100.0f;

GLfloat kstep = 1.0f;

GLfloat z = 0.0f;

GLfloat zstep = 0.5f;

void drawObject(){
     glBegin(GL_TRIANGLES);
        glVertex2i(50,-50);
        glVertex2i(0,50);
        glVertex2i(-50,-50);
     glEnd();
}

void drawOutline(){
     glBegin(GL_LINE_LOOP);
        glVertex2i(-100,100);
        glVertex2i(100,100);
        glVertex2i(100,-100);
        glVertex2i(-100,-100);
     glEnd();
}

void init(){
     glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void timerFunc(int value)
{
     if(k > 100 || k < -300)
        kstep = -kstep;

    k += kstep;

    if(z > 150 || z < 0)
        zstep = -zstep;

    z += zstep;

    glutPostRedisplay();
    glutTimerFunc(10,timerFunc,1);
}

void displayFunc() {
     glClear(GL_COLOR_BUFFER_BIT);

     glMatrixMode(GL_PROJECTION);

     glLoadIdentity();
     gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
     glViewport(0, 300, 300, 300);
     glColor3f(1.0f, 0.0f, 0.0f);
     drawObject();

     glLoadIdentity();
     gluOrtho2D(k, k+200.0f, -100.0f, 100.0f);
     glViewport(300, 300, 300, 300);
     glColor3f(0.0f, 1.0f, 0.0f);
     drawObject();

     glLoadIdentity();
     gluOrtho2D(-100.0f, 100.0f, k, k+200.0f);
     glViewport(0, 0, 300, 300);
     glColor3f(0.0f, 0.0f, 1.0f);
     drawObject();

     glLoadIdentity();
     gluOrtho2D(-z,z,-z,z);
     glViewport(300, 0, 300, 300);
     glColor3f(0.0f, 0.0f, 0.0f);
     drawObject();

/*
     glLoadIdentity();
     gluOrtho2D(-200,200,-200,200);
     glViewport(0, 0, 600, 600);
     // GL_MODELVIEW utilizada para aplicar transformações geométricas às coordenadas dos objetos

     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     glColor3f(0.0f, 0.0f, 0.0f);
     glTranslatef(-100,-100,0);
     drawOutline();

     glLoadIdentity();
     glTranslatef(100,-100,0);
     drawOutline();

     glLoadIdentity();
     glTranslatef(-100,100,0);
     drawOutline();

     glLoadIdentity();
     glTranslatef(100,100,0);
     drawOutline();
*/
  
     glLoadIdentity();

     glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(600,600);
    glutCreateWindow("Viewing 2D");
    glutDisplayFunc(displayFunc);
    glutTimerFunc(10,timerFunc,1);
    init();
    glutMainLoop();
    return 0;
}