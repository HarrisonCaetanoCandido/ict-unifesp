/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
*/

#include <math.h>
// rotinas para executar tarefas como ajustar matrizes para orientações e projeções
// com pontos de vista específicos e geração de superfícies
#include <GL/glut.h>

int n = 10;
float ang = 0;

void clear_window()
{
  // limpo a tela
  glClearColor(0, 0, 0, 0); // preto
  glClear(GL_COLOR_BUFFER_BIT);
}

void draw()
{
  int i;

  clear_window();

  glColor3f(1.0, 1.0, 1.0);

  glBegin(GL_LINE_LOOP);
  for (i = 0; i < n; i++)
  {
    // sendo 0.5 o raio
    glVertex2f(0.5 * cos(ang), 0.5 * sin(ang));
    ang = ang + (2 * M_PI) / n;
  }
  glEnd();

  // força o inicio da execucao de todos os comandos OpenGL enviados
  glFlush();
}

int main(int argc, char *argv[])
{
  // inicializa a glut com parametros de entrada do programa
  glutInit(&argc, argv);

  // especifica se utilizaremos o sinal RGBA ou indexado e se vamos usar GLUT_SINGLE ou GLUT_DOUBLE buffers para geração de imagens
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  // especifica a largura e altura da janela de sistema
  glutInitWindowSize(600, 600);

  // especifica a posição da janela de sistema na tela
  glutInitWindowPosition(0, 0);

  // cria a janela de sistema com um nome
  glutCreateWindow("Conversao matricial - circulo");

  // chama a função que será executada para criar a cena 2d
  glutDisplayFunc(draw);

  // todas as janelas criadas são exibidas na tela, com o processamento de eventos iniciado e as imagens construídas na tela
  glutMainLoop();

  return 0;
}