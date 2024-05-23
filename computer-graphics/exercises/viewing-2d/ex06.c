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

void clear_window()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw()
{
    clear_window();

    
}

int main(int argc, char *argv)
{
    glutInit(argc, &argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);

    glutInitWindowSize(400, 400);

    glutCreateWindow('Cohen-Sutherland');

    glutDisplayFunc(draw);

    glutMainLoop();

    return 0;
}