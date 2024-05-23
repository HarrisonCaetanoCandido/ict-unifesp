/*
  Nome: Harrison Caetano Cândido
  RA: 156264
  Turno: Integral
*/
/*
- Crie um robo parecido com um humanoide
- Fazer uma animacao do robo se movimentando.
- Os bracos devem possuir braco e antebraco e as pernas as duas partes unidas pelo joelho.
- Essas partes devem se movimentar de forma coerente a medida que o robo caminha.
- Com uma visao de cima, um pouco inclinada (para uma melhor visualização) o robô começar parado e, ao pressionar as setas, ele deve começar a se movimentar utilizando a animacao.
- Ao parar de pressionar as teclas, ele deve ficar parado novamente.
- Além disso, ao pressionar as setas, o robô deve rotacionar em torno de seu eixo para caminhar naquela direção.
- Cuidar da iluminação e da textura.
- Utilizar projeção perspectiva
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
void sphere(float radius, float slices, float stacks);
void cabeca();
void peito();
void antebraco();
void cotovelos();
void braco();
void pernas();
void joelhos();
void pes();
void movimento(int key, int x, int y);

GLUquadricObj *obj;

GLfloat aBracoThetaEsq = 90.0f; // progrido +10 ate 180 (de 90 ate 180)
GLfloat aBracoThetaDir = 90.0f;
GLfloat aBracoTxEsq = -0.7f;
GLfloat aBracoTxDir = 0.7f;
GLfloat aBracoTZ = 0.0f;
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLfloat tY = -1.3;
GLfloat oX = 0.0;
GLfloat tZ = 0.0;
GLfloat tpY = -2.0;
int left = 0, right = 0;

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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // define a cor de fundo
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
    glViewport(0, 0, 500, 500);          // define dimensoes da area de renderizacao da viewport. x, y, width, height

    lightning();
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // limpa o buffer

    glMatrixMode(GL_MODELVIEW); // define que a matrix é a de model (transformacoes na cena3d) view (transformacoes da camera)

    glPushMatrix(); // empurramos (salvamos) a matriz atual em uma pilha, fazemos transformacoes no contexto atual e depois damos pop na matriz para restaurar o contexto interrompido
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    cabeca();
    peito();
    braco();
    antebraco();
    cotovelos();
    pernas();
    joelhos();
    pes();
    glPopMatrix(); // devolvo o contexto anterior as transformacoes atuais

    glFlush(); // força o desenho das primitivas
}

void cylinder(float radius, float height, int segments, int guidance)
{
    int i;
    float ang, x, y, z;

    // lados do cilindro
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= segments; i++)
    {
        ang = (2.0f * M_PI * i) / segments; // angulo
        x = radius * cos(ang);              // cos = cat. adjacente/ hipotenusa

        if (guidance == 0)
        {
            z = radius * sin(ang); // sen = cat. oposto/ hipotenusa
            glNormal3f(x, 0.0f, z);
            glVertex3f(x, 0.0f, z);
            glNormal3f(x, height, z);
            glVertex3f(x, height, z);
        }
        else
        {
            y = radius * sin(ang);
            glNormal3f(x, y, 0.0f);
            glVertex3f(x, y, 0.0f);
            glNormal3f(x, y, height);
            glVertex3f(x, y, height);
        }
    }
    glEnd();
}

void sphere(float radius, float slices, float stacks)
{
    int i, j;
    float theta1, theta2, phi, x1, y1, z1, x2, y2, z2;

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

void cabeca()
{
    glPushMatrix();
    sphere(0.2, 10, 10);
    glPopMatrix();
}

void peito()
{
    glPushMatrix();
    glTranslatef(0.0, -0.8, 0.0);
    /// radius, height, segments, guidance
    cylinder(0.1f, 0.6f, 10, 0);
    glPopMatrix();
}

void pernas()
{
    // Desenhe as pernas
    if (left == right)
    {
        glPushMatrix();
        glTranslatef(-0.1, tY, 0.0);
        glRotatef(90.0, oX, 0.0, 0.0);
        cylinder(0.08f, 0.5f, 10, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.1, tY, 0.0); // Posiciona perna direita
        glRotatef(90.0, oX, 0.0, 0.0);
        cylinder(0.08f, 0.5f, 10, 0);
        glPopMatrix();
    }

    if (left == 1 && right == 0)
    {
        glPushMatrix();
        glTranslatef(-0.1, tY, 0.0);
        glRotatef(90.0, oX, 0.0, 0.0);
        cylinder(0.08f, 0.5f, 10, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.1, -1.3, 0.0); // Posiciona perna direita
        glRotatef(90.0, 0.0, 0.0, 0.0);
        cylinder(0.08f, 0.5f, 10, 0);
        glPopMatrix();
    }

    if (left == 0 && right == 1)
    {
        glPushMatrix();
        glTranslatef(0.1, -1.3, 0.0); // Posiciona perna direita
        glRotatef(90.0, 0.0, 0.0, 0.0);
        cylinder(0.08f, 0.5f, 10, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.1, tY, 0.0);
        glRotatef(90.0, oX, 0.0, 0.0);
        cylinder(0.08f, 0.5f, 10, 0);
        glPopMatrix();
    }
}

void joelhos()
{
    if (left == right)
    {
        glPushMatrix();
        glTranslatef(-0.1, tY, tZ);
        sphere(-0.1, 10, 10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.1, tY, tZ);
        sphere(0.1, 10, 10);
        glPopMatrix();
    }

    if (left == 1 && right == 0)
    {
        glPushMatrix();
        glTranslatef(-0.1, tY, tZ);
        sphere(-0.1, 10, 10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.1, -1.4, 0.0);
        sphere(0.1, 10, 10);
        glPopMatrix();
    }

    if (left == 0 && right == 1)
    {
        glPushMatrix();
        glTranslatef(0.1, tY, tZ);
        sphere(0.1, 10, 10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.1, -1.4, 0.0);
        sphere(-0.1, 10, 10);
        glPopMatrix();
    }
}

void braco()
{
    glPushMatrix();
    glTranslatef(0.1, -0.3, 0.0);   // Posiciona o braço direito na horizontal
    glRotatef(90.0, 0.0, 1.0, 0.0); // Gira o braço direito para ficar na horizontal
    cylinder(0.08f, 0.3f, 10, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4, -0.3, 0.0);  // Posiciona o braço esquerdo na horizontal
    glRotatef(90.0, 0.0, 1.0, 0.0); // Gira o braço esquerdo para ficar na horizontal
    cylinder(0.08f, 0.3f, 10, 1);
    glPopMatrix();
}

void cotovelos()
{
    glPushMatrix();
    glTranslatef(-0.5, -0.3, 0.0);
    sphere(-0.1, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, -0.3, 0.0);
    sphere(0.1, 10, 10);
    glPopMatrix();
}

void antebraco()
{
    glPushMatrix();
    glTranslatef(-1.1, -0.3, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0); // Gira o braço direito para ficar na horizontal
    cylinder(0.08f, 0.5f, 10, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6, -0.3, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0); // Gira o braço esquerdo para ficar na horizontal
    cylinder(0.08f, 0.5f, 10, 1);
    glPopMatrix();
}

void pes()
{
    glPushMatrix();
    glTranslatef(-0.1, tpY, tZ); // Posiciona o pé da esquerda
    cylinder(0.08f, 0.5f, 10, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1, tpY, tZ); // Posiciona o pé da direita
    cylinder(0.08f, 0.5f, 10, 0);
    glPopMatrix();
}

void movimento(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (left == 1)
        {
            left = 0;
            right = 1;
        }
        else
        {
            left = 1;
            right = 0;
        }

        tY = -0.9;
        oX = 1.0;
        tZ = 0.6;

        break;
    case GLUT_KEY_DOWN:
        if (left == 1)
        {
            left = 0;
            right = 1;
        }
        else
        {
            left = 1;
            right = 0;
        }
        tY = -0.9;
        oX = 1.0;
        tZ = 0.6;

        break;
    case GLUT_KEY_LEFT:
        if (left == 1)
        {
            left = 0;
            right = 1;
        }
        else
        {
            left = 1;
            right = 0;
        }
        tY = -0.9;
        oX = 1.0;
        tZ = 0.6;

        break;
    case GLUT_KEY_RIGHT:
        if (left == 1)
        {
            left = 0;
            right = 1;
        }
        else
        {
            left = 1;
            right = 0;
        }
        tY = -0.9;
        oX = 1.0;
        tZ = 0.6;

        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // esquerda
    case 'a':
        angleY -= 10;
        break;

    // direita
    case 'd':
        angleY += 10;
        break;

    // cima
    case 'w':
        angleX -= 10;
        break;

    // baixo
    case 's':
        angleX += 10;
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
    glutDisplayFunc(draw);
    glutSpecialFunc(movimento);
    glutKeyboardFunc(keyboard);
    init();
    initTexture();
    glutMainLoop();
    return 0;
}