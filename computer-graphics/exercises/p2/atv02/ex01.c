/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Point {
  float x;
  float y;
  float z;
};

int n = 10;
float t = 0.0;
float tstep = 1.0/10.0;
struct Point P0;
struct Point P1;
struct Point P2;
struct Point P3;
struct Point P;

struct Point a;
struct Point b;
struct Point c;
struct Point d;
struct Point e;

GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLfloat angleZ = 0.0f;

float p0X = -1.0;
float p0Y = 2.0;
float p0Z = 5.0;
float p1X = -2.0;
float p1Y = -2.0;
float p1Z = -5.0;
float p2X = 1.0;
float p2Y = 2.0;
float p2Z = 0.0;
float p3X = 3.0;
float p3Y = -2.0;
float p3Z = 1.0;

void lightning(){
    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

  //Fonte de Luz Direcional - Efeito de Holofote
  GLfloat light1_pos[] = {-2.0, -2.0, -2.0f, 1.0f};
  glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
  glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
  glLightfv(GL_LIGHT1,GL_SPECULAR, white);
  GLfloat direction[] = {2.0f, 2.0f, 2.0f};
  glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);       //vetor direção
  glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,30.0f);               //espalhamento angular
  glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.5f);    

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
}

void init(){
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 1.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, 0.0, 8.0);
    glViewport(0, 0, 500, 500);
    glShadeModel(GL_SMOOTH);
    lightning();

    P0.x = -1.0;
    P0.y = 2.0;
    P0.z = 5.0;
    P1.x = -2.0;
    P1.y = -2.0;
    P1.z = -5.0;
    P2.x = 1.0;
    P2.y = 2.0;
    P2.z = 0.0;
    P3.x = 3.0;
    P3.y = -2.0;
    P3.z = 1.0;
}

void pista(){
  GLfloat shininess;
  GLfloat diffuse[4];
  GLfloat specular[4];
  float count;
  int i;

  shininess = 65.0;
  diffuse[0] = 0.65;
  diffuse[1] = 0.65;
  diffuse[2] = 0.65;
  diffuse[3] = 1.0;
  specular[0] = 1.0;
  specular[1] = 1.0;
  specular[2] = 1.0;
  specular[3] = 1.0;
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
  glMaterialf(GL_FRONT,GL_SHININESS,shininess);

  // topo
  glBegin(GL_TRIANGLE_STRIP);
  t = count = 0.0;

  P0.x = p0X;
  P0.y = p0Y;
  P0.z = p0Z;
  P1.x = p1X;
  P1.y = p1Y;
  P1.z = p1Z;
  P2.x = p2X;
  P2.y = p2Y;
  P2.z = p2Z;
  P3.x = p3X;
  P3.y = p3Y;
  P3.z = p3Z;
  

  for(int i=0;i<n;i++){
    a.x = (1.0-t)*P0.x+t*P1.x;
    a.y = (1.0-t)*P0.y+t*P1.y;
    a.z = (1.0-t)*P0.z+t*P1.z;
    b.x = (1.0-t)*P1.x+t*P2.x;
    b.y = (1.0-t)*P1.y+t*P2.y;
    b.z = (1.0-t)*P1.z+t*P2.z;
    c.x = (1.0-t)*P2.x+t*P3.x;
    c.y = (1.0-t)*P2.y+t*P3.y;
    c.z = (1.0-t)*P2.z+t*P3.z;
    d.x = (1.0-t)*a.x+t*b.x;
    d.y = (1.0-t)*a.y+t*b.y;
    d.z = (1.0-t)*a.z+t*b.z;
    e.x = (1.0-t)*b.x+t*c.x;
    e.y = (1.0-t)*b.y+t*c.y;
    e.z = (1.0-t)*b.z+t*c.z;

    P.x = (1.0-t)*d.x+t*e.x;
    P.y = (1.0-t)*d.y+t*e.y;
    P.z = (1.0-t)*d.z+t*e.z;
    glNormal3f(0.0,P.y,0.0);
    glVertex3f(P.x,P.y,P.z-0.2);
    glNormal3f(P.x,P.y,P.z+0.2);
    glVertex3f(P.x,P.y,P.z+0.2);
    t+=tstep;
  }
  glEnd();

  // chao
  for(i = 0; i < 100; i++)
  {
    count += 0.01;
    glBegin(GL_TRIANGLE_STRIP);
    t = 0.0;
  
    P0.x = p0X;
    P0.y = p0Y;
    P0.z = p0Z;
    P1.x = p1X;
    P1.y = p1Y;
    P1.z = p1Z;
    P2.x = p2X;
    P2.y = p2Y;
    P2.z = p2Z;
    P3.x = p3X;
    P3.y = p3Y;
    P3.z = p3Z;
  
    for(int i=0;i<n;i++){
      a.x = (1.0-t)*P0.x+t*P1.x;
      a.y = (1.0-t)*P0.y+t*P1.y;
      a.z = (1.0-t)*P0.z+t*P1.z;
      b.x = (1.0-t)*P1.x+t*P2.x;
      b.y = (1.0-t)*P1.y+t*P2.y;
      b.z = (1.0-t)*P1.z+t*P2.z;
      c.x = (1.0-t)*P2.x+t*P3.x;
      c.y = (1.0-t)*P2.y+t*P3.y;
      c.z = (1.0-t)*P2.z+t*P3.z;
      d.x = (1.0-t)*a.x+t*b.x;
      d.y = (1.0-t)*a.y+t*b.y;
      d.z = (1.0-t)*a.z+t*b.z;
      e.x = (1.0-t)*b.x+t*c.x;
      e.y = (1.0-t)*b.y+t*c.y;
      e.z = (1.0-t)*b.z+t*c.z;
  
      P.x = (1.0-t)*d.x+t*e.x;
      P.y = (1.0-t)*d.y+t*e.y - count;
      P.z = (1.0-t)*d.z+t*e.z;
      glNormal3f(0.0,P.y,0.0);
      glVertex3f(P.x,P.y,P.z-0.2);
      glNormal3f(P.x,P.y,P.z+0.2);
      glVertex3f(P.x,P.y,P.z+0.2);
      t+=tstep;
    }
    glEnd();
  }
}

void displayFunc() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glRotatef(angleX,1.0,0.0,0.0);
  glRotatef(angleY,0.0,1.0,0.0);
  glRotatef(angleZ,0.0,0.0,1.0);
  pista();
  glPopMatrix();
  lightning();
  glFlush();
}


void keyboard (unsigned char key, int x, int y){
    switch(key){
       case 'x':
       case 'X':
            angleX+=5.0f;
          break;
       case 'y':
       case 'Y':
            angleY+=5.0f;
          break;
      case 'z':
      case 'Z':
            angleZ+=5.0f;
          break;
      case '1':
        p0X = -1.0;
        p0Y = 2.0;
        p0Z = 5.0;
        p1X = -2.0;
        p1Y = -2.0;
        p1Z = -5.0;
        p2X = 1.0;
        p2Y = 2.0;
        p2Z = 0.0;
        p3X = 3.0;
        p3Y = -2.0;
        p3Z = 1.0;
        break;
      case '2':
        p0X = -5.0;
        p0Y = -1.0;
        p0Z = 0.0;
        p1X = -2.0;
        p1Y = 0.0;
        p1Z = 0.0;
        p2X = 1.0;
        p2Y = 0.0;
        p2Z = 5.0;
        p3X = 2.0;
        p3Y = -1.0;
        p3Z = 0.0;
        break;
      case '3':
        p0X = -2.0;
        p0Y = 3.0;
        p0Z = 0.0;
        p1X = -1.0;
        p1Y = -5.0;
        p1Z = 2.0;
        p2X = 1.0;
        p2Y = 1.0;
        p2Z = -1.0;
        p3X = 1.5;
        p3Y = 3.0;
        p3Z = 0.0;
        break;
      default:
          break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Pista");
    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}