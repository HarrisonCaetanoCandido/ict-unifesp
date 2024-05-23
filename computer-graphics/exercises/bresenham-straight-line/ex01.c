/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
*/
/*
Crie um programa com duas funcoes: a de imprimir uma
linha entre dois pontos quaisquer e a de alterar a cor da
linha. Uma linha inicial entre os pontos (0,0) e (0,0) azul
deve ser tracada. A linha muda de posicao de acordo com
as coordenadas dadas por um clique inicial e um clique
final com o botao esquerdo do mouse. Utilize o algoritmo
de Bresenham para tracar a linha (nao utilizar GL_LINES).
Para mudar a cor, o usuario digitara as teclas de 0 a 9.
Cada tecla devera ter cores indexadas previamente
escolhidas. Escolha as cores que desejar.
*/

#include <stdio.h>
#include <GL/glut.h>
#define SETTED_UP 1
#define SETTED_OFF 0

float red = 0.0, green = 0.0, blue = 1.0, p1_x_offset = 0.0, p2_x_offset = 0.0, p1_y_offset = 0.0, p2_y_offset = 0.0;
int p1_status = SETTED_UP;

void clear_window();
void draw();
void write_pixel(int x, int y);
void bresenham_straight_line(int x0, int y0, int xf, int yf);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int status, int x, int y);

void clear_window()
{
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
}

void draw()
{
  int x0, y0, xf, yf;

  clear_window();

  glColor3f(red, green, blue);

  glLineWidth(2);

  if (p2_x_offset - p1_x_offset == 0)
    // ploto o ponto inicial em (0,0)
    write_pixel(300, 300);

  // SETTED_OFF garante a atualizacao conjunta dos pontos p1 e p2 para nao haver erros no calculo da nova reta
  if (p1_status == SETTED_OFF && (p2_x_offset - p1_x_offset) != 0)
  {
    // sist. coord. do mundo para sist. coord. do dispositivo (float para inteiro)
    x0 = glutGet(GLUT_WINDOW_WIDTH) * (p1_x_offset + 1.0) / 2.0;
    y0 = glutGet(GLUT_WINDOW_HEIGHT) * (1.0 - p1_y_offset) / 2.0;
    xf = glutGet(GLUT_WINDOW_WIDTH) * (p2_x_offset + 1.0) / 2.0;
    yf = glutGet(GLUT_WINDOW_HEIGHT) * (1.0 - p2_y_offset) / 2.0;

    // faco a inversao de pontos caso x0 > xf e y0 > yf ou y0 < yf (pq y aqui cresce pra baixo), para que mantenha o tracado da esquerda para a direita
    if (x0 > xf)
    {
      // sist. coord. do mundo para sist. coord. do dispositivo (float para inteiro)
      xf = glutGet(GLUT_WINDOW_WIDTH) * (p1_x_offset + 1.0) / 2.0;
      yf = glutGet(GLUT_WINDOW_HEIGHT) * (1.0 - p1_y_offset) / 2.0;
      x0 = glutGet(GLUT_WINDOW_WIDTH) * (p2_x_offset + 1.0) / 2.0;
      y0 = glutGet(GLUT_WINDOW_HEIGHT) * (1.0 - p2_y_offset) / 2.0;
    }

    // Projeto as coordenadas da cena 2D para o sistema de coordenadas do mundo
    bresenham_straight_line(x0, y0, xf, yf);
  }

  glFlush();
}

void write_pixel(int x, int y)
{
  float xf, yf;

  printf(">>>> x: %d, y: %d\n", x, y);

  // converto do sist. de coord. do dispositivo para sist. coord. do mundo
  xf = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
  yf = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);

  printf(">>>> P = (x, y) = (%f, %f)\n", xf, yf);

  glPointSize(2);
  glBegin(GL_POINTS);
  glVertex2f(xf, yf);
  glEnd();
}

/*
  Obs: Assumimos que x0 < xend e y0 < yend.
  Portanto o processamento sempre sera da esquerda para a direita.

  Obs 2: As retas decrescentes nao sao bem tracadas por conta de algum problema com a equacao,
  eh necessario adapta-la de alguma forma que ainda nao consegui para que o tracado seja mais 
  perfeito como eh o tracado de retas crescentes (a nocao de crescer e decrescer eh relacionada a y
  no sistema de coordenadas do dispositivo).
*/
void bresenham_straight_line(int x0, int y0, int xf, int yf)
{
  int x, y, k, iterations, p0, pk, y_increment, x_delta, y_delta;

  // calcular delta y e delta x para saber em que eixo o pixel será plotado
  x_delta = xf - x0;
  y_delta = yf - y0;

  printf("----------------- BRESENHAM -----------------\n");
  printf("x0: %d y0: %d xf:%d yf:%d\nx_delta: %d y_delta: %d\n", x0, y0, xf, yf, x_delta, y_delta);

  // decide se a reta (da esquerda para a direita) sera crescente ou decrescente
  if (y0 > yf)
    y_increment = -1;
  else
    y_increment = 1;

  // retas tracadas de cima pra baixo na perspectiva do sist. de coord. do dispositivo. 0.0 < m && m < 1.0
  if (x_delta > y_delta)
  {
    if (y0 > yf)
      p0 = -2 * y_delta + x_delta;
    else
      p0 = 2 * y_delta - x_delta;

    pk = p0;
    x = x0;
    y = y0;

    iterations = x_delta - 1;

    if (iterations < 0.00)
      iterations = iterations * -1;

    for (k = 0; k < iterations; k++)
    {
      if (pk < 0)
      {
        if (y0 > yf)
          pk = pk - 2 * y_delta;
        else
          pk = pk + 2 * y_delta;

        write_pixel(x + 1, y);
        printf("(xk + 1, yk)\n");
        ++(x);
      }
      else if (pk >= 0)
      {
        if (y0 > yf)
          pk = pk - 2 * y_delta + 2 * x_delta;
        else
          pk = pk + 2 * y_delta - 2 * x_delta;

        y += y_increment;
        write_pixel(x + 1, y);
        printf("(xk + 1, yk +/- 1)\n");
        ++(x);
      }

      printf("pk+1: %d\n", pk);
    }
  }

  // retas tracadas de cima pra baixo na perspectiva do sistema de coordenadas do dispositivo. m > 1
  if (y_delta > x_delta)
  {
    if (y0 > yf)
      p0 = -2 * x_delta + y_delta;
    else
      p0 = 2 * x_delta - y_delta;

    pk = p0;
    x = x0;
    y = y0;

    iterations = y_delta - 1;

    if (iterations < 0.00)
      iterations = iterations * -1;

    for (k = 0; k < iterations; k++)
    {
      if (pk < 0)
      {
        if (y0 > yf)
          pk = pk - 2 * x_delta;
        else
          pk = pk + 2 * x_delta;

        y += y_increment;
        write_pixel(x, y);
        printf("(xk, yk +/- 1)\n");
      }
      else if (pk >= 0)
      {
        if (y0 > yf)
          pk = pk - 2 * x_delta + 2 * y_delta;
        else
          pk = pk + 2 * x_delta - 2 * y_delta;
          
        y += y_increment;
        write_pixel(x + 1, y);
        printf("(xk + 1, yk + 1)\n");
        ++(x);
      }

      printf("pk+1: %d\n", pk);
    }
  }
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case '0':
    red = 0.0, green = 0.0, blue = 1.0;
    break;
  case '1':
    red = 0.1, green = 0.0, blue = 1.0;
    break;
  case '2':
    red = 1.0, green = 1.0, blue = 1.0;
    break;
  case '3':
    red = 0.0, green = 1.0, blue = 0.0;
    break;
  case '4':
    red = 1.0, green = 1.0, blue = 0.0;
    break;
  case '5':
    red = 0.1, green = 0.0, blue = 0.5;
    break;
  case '6':
    red = 0.3, green = 0.5, blue = 0.2;
    break;
  case '7':
    red = 0.7, green = 1.0, blue = 0.9;
    break;
  case '8':
    red = 0.5, green = 0.5, blue = 0.5;
    break;
  case '9':
    red = 0.9, green = 0.1, blue = 0.0;
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void mouse(int button, int status, int x, int y)
{
  switch (button)
  {
  case GLUT_LEFT_BUTTON:
    // em ambos os ifs faco a conversao do sist. de coord. do dispositivo para sist. de coord. do mundo
    if (status == GLUT_DOWN && p1_status == SETTED_OFF)
    {
      printf("------------------ NOVA RETA ------------------\n");
      printf("P1 x:%d y:%d\n", x, y);
      p1_x_offset = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
      p1_y_offset = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);
      p1_status = SETTED_UP;
      // printf("P1 = (x1, y1) = (%f, %f)\n", p1_x_offset, p1_y_offset);
    }
    else if (status == GLUT_DOWN && p1_status == SETTED_UP)
    {
      printf("P2 x:%d y:%d\n", x, y);
      p2_x_offset = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
      p2_y_offset = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);
      p1_status = SETTED_OFF;
      // printf("P2 = (x2, y2) = (%f, %f)\n", p2_x_offset, p2_y_offset);
    }
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

  glutCreateWindow("Bresenham: Straight Line");

  glutDisplayFunc(draw);

  glutKeyboardFunc(keyboard);

  glutMouseFunc(mouse);

  glutMainLoop();

  return 0;
}