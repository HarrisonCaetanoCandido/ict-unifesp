/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Qtd máxima de texturas a serem usadas no programa */
#define MAX_NO_TEXTURES 5

typedef struct BMPImagem
{
    int width;
    int height;
    char *data;
} BMPImage;

const char *filenameArray[MAX_NO_TEXTURES] = {
    "surface1.bmp",
    "surface2.bmp",
    "surface3.bmp",
    "surface4.bmp",
    "surface5.bmp"};

/* vetor com os números das texturas */
GLuint texture_id[MAX_NO_TEXTURES];
void getBitmapImageData(const char *pFileName, BMPImage *pImage);
void CarregaTexturas();
void initTexture(void);
void lightning();
void cabeca();
void peito();
void antebraco();
void braco();
void pernas();
void pes();
void movimento(int key, int x, int y);

GLUquadricObj *obj;

GLfloat aBracoThetaEsq = 90.0f; // progrido +10 ate 180 (de 90 ate 180)
GLfloat aBracoThetaDir = 90.0f;
GLfloat aBracoTxEsq = -0.7f; 
GLfloat aBracoTxDir = 0.7f;   
GLfloat aBracoTZ = 0.0f;

//-----------------------------------------------------------------------------
// Name: getBitmapImageData()
// Desc: Simply image loader for 24 bit BMP files.
//-----------------------------------------------------------------------------
void getBitmapImageData(const char *pFileName, BMPImage *pImage)
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if ((pFile = fopen(pFileName, "rb")) == NULL)
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek(pFile, 18, SEEK_CUR);

    if ((i = fread(&pImage->width, 4, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if ((i = fread(&pImage->height, 4, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if ((fread(&nNumPlanes, 2, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if (nNumPlanes != 1)
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if ((i = fread(&nNumBPP, 2, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if (nNumBPP != 24)
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    // Seek forward to image data
    fseek(pFile, 24, SEEK_CUR);

    // Calculate the image's total size in bytes. Note how we multiply the
    // result of (width * height) by 3. This is becuase a 24 bit color BMP
    // file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char *)malloc(nTotalImagesize);

    if ((i = fread(pImage->data, nTotalImagesize, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    //
    // Finally, rearrange BGR to RGB
    //

    char charTemp;
    for (i = 0; i < nTotalImagesize; i += 3)
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i + 2];
        pImage->data[i + 2] = charTemp;
    }
}

/*Função para Carregar uma imagem .BMP */
void CarregaTexturas()
{
    BMPImage textura;

    /* Define quantas texturas serão usadas no programa  */
    glGenTextures(MAX_NO_TEXTURES, texture_id); /* 1 = uma textura; */
                                                /* texture_id = vetor que guardas os números das texturas */

    int i;
    for (i = 0; i < MAX_NO_TEXTURES; i++)
    {
        getBitmapImageData(filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
}

/* **********************************************************************
  void initTexture(void)
        Define a textura a ser usada

 ********************************************************************** */
void initTexture(void)
{

    /* Habilita o uso de textura bidimensional  */
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    /*Carrega os arquivos de textura */
    //  CarregaTextura("tunnelTexture.bmp");
    // CarregaTextura("tex2.bmp");
    CarregaTexturas();
}

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

void init(void)
{
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // define a cor de fundo
    glEnable(GL_DEPTH_TEST);              // habilita o teste de profundidade

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW); // define que a matrix é a model (transformacoes3d na cena) view (transformacoes da camera)
    glLoadIdentity();           // carrega a matrix de identidade (matriz limpa)
    gluLookAt(4.0, 2.0, 5.0,    // posição da câmera
              0.0, 0.0, 0.0,    // para onde a câmera aponta
              0.0, 1.0, 0.0);   // vetor view-up

    glMatrixMode(GL_PROJECTION); // define que a matrix é a de projeção
    glLoadIdentity();            // carrega a matrix de identidade

    gluPerspective(45.0, 1.0, 2.0, 8.0); // define uma projeção perspectiva
    glViewport(0, 0, 500, 500); // define dimensoes da area de renderizacao da viewport. x, y, width, height

    lightning();
}

void cubo()
{
    float size = 1.0;
    GLfloat n[6][3] =
        {
            {-1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {1.0, 0.0, 0.0},
            {0.0, -1.0, 0.0},
            {0.0, 0.0, 1.0},
            {0.0, 0.0, -1.0}};
    GLint faces[6][4] =
        {
            {0, 1, 2, 3},
            {3, 2, 6, 7},
            {7, 6, 5, 4},
            {4, 5, 1, 0},
            {5, 6, 2, 1},
            {7, 4, 0, 3}};
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--)
    {
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

void cabeca()
{
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.2); // Posiciona a cabeça acima do peito
    glScalef(0.3, 0.3, 0.3);     // Redimensiona a cabeça
    cubo();
    glPopMatrix();
}

void peito()
{
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.2);
    glScalef(0.2, 0.2, -0.6); // Redimension o peito pra baixo
    cubo();
    glPopMatrix();
}

void pernas()
{
    // Desenhe as pernas
    glPushMatrix();
    glTranslatef(-0.1, 0.0, -1.0); // Posiciona perna esquerda
    glScalef(0.15, 0.15, 0.4);     // Redimensione a perna
    cubo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1, 0.0, -1.0); // Posiciona perna direita
    glScalef(0.15, 0.15, 0.4);    // Redimensione a perna
    cubo();
    glPopMatrix();
}

void braco()
{

    glPushMatrix();
    glTranslatef(0.2, 0.0, 0.0);    // Posiciona o braço direito na horizontal
    glRotatef(90.0, 0.0, 1.0, 0.0); // Gira o braço direito para ficar na horizontal
    glScalef(0.15, 0.15, 0.5);      // Redimensione o braço
    cubo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2, 0.0, 0.0);   // Posiciona o braço esquerdo na horizontal
    glRotatef(90.0, 0.0, 1.0, 0.0); // Gira o braço esquerdo para ficar na horizontal
    glScalef(0.15, 0.15, 0.5);      // Redimensione o braço
    cubo();
    glPopMatrix();
}

void antebraco()
{

    glPushMatrix();
    glTranslatef(aBracoTxDir, 0.0, aBracoTZ);   // Posiciona o braço direito na horizontal
    glRotatef(aBracoThetaDir, 0.0, 1.0, 0.0); // Gira o braço direito para ficar na horizontal
    glScalef(0.15, 0.15, 0.5);      // Redimensione o braço
    cubo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(aBracoTxEsq,0.0, aBracoTZ); // Posiciona o braço esquerdo na horizontal
    glRotatef(aBracoThetaEsq, 0.0, 1.0, 0.0);        // Gira o braço esquerdo para ficar na horizontal
    glScalef(0.15, 0.15, 0.5);                  // Redimensione o braço
    cubo();
    glPopMatrix();
}

void pes()
{
    glPushMatrix();
    glTranslatef(-0.1, 0.0, -0.6); // Posiciona o pé da esquerda
    glScalef(0.15, 0.15, 0.4);     // Redimensione a perna
    cubo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1, 0.0, -0.6); // Posiciona o pé da direita
    glScalef(0.15, 0.15, 0.4);    // Redimensione a perna
    cubo();
    glPopMatrix();
}

void displayFunc()
{
    GLfloat angleX = 270.0f;
    GLfloat angleY = 0.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // limpa o buffer

    glMatrixMode(GL_MODELVIEW); // define que a matrix é a de model (transformacoes na cena3d) view (transformacoes da camera)

    glPushMatrix(); // empurramos (salvamos) a matriz atual em uma pilha, fazemos transformacoes no contexto atual e depois damos pop na matriz para restaurar o contexto interrompido
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    cabeca();
    peito();
    antebraco();
    braco();
    pernas();
    pes();
    glPopMatrix(); // devolvo o contexto anterior as transformacoes atuais

    glFlush(); // força o desenho das primitivas
}

void movimento(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (aBracoThetaEsq != 180.0f && aBracoThetaDir != 0.0f)
        {
            printf("up\n");
            aBracoThetaEsq += 10.0f; // progrido +10 ate 180 (de 90 ate 180)
            aBracoThetaDir -= 10.0f; // progrido -10 ate 0 (de 90 ate 0)
            aBracoTxDir -= 0.0333; // progrido +0.0333 ate 0.6
            aBracoTxEsq += 0.0333;
            aBracoTZ += 0.0222;
        }
        break;
    case GLUT_KEY_DOWN:
        if (aBracoThetaEsq != 90.0f && aBracoThetaDir != 90.0f)
        {
            printf("down\n");
            aBracoThetaEsq -= 10.0f; // progrido +10 ate 180 (de 90 ate 180)
            aBracoThetaDir += 10.0f; // progrido -10 ate 0 (de 90 ate 0)
            aBracoTxDir += 0.0333; // progrido +0.0333 ate 0.6
            aBracoTxEsq -= 0.0333;
            aBracoTZ -= 0.0222;
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Robo animado com iluminacao e textura");
    glutDisplayFunc(displayFunc);
    glutSpecialFunc(movimento);
    init();
    initTexture();
    glutMainLoop();
    return 0;
}