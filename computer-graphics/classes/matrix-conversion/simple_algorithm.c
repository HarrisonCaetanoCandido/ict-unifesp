#include <GL/glut.h>
#include <GL/gl.h>



int main(int argc, char *argv[])
{
    // Especifica qual o sistema de cores (RGBA ou INDEXADO) e quantidade de buffers (GLUT_SINGLE ou GLUT_DOUBLE) para geracao de imagens
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Especifica as coordenadas da janela na tela
    glutInitWindowPosition(50, 100);

    // Especifica largura e altura em pixels da janela
    glutInitWindowSize(600, 600);

    // Inicializa o programa com comandos especificados pelo terminal se necessario
    glutInit(&argc, argv);

    // Cria a janela com nome igual ao da string passada
    glutCreateWindow("Exercicio simples");

    // Chama o procedimento que sera executado para criar e mostrar o objeto na janela
    glutDisplayFunc(draw);

    // Chama a funcao que ira definir a interacao com o mouse
    glutMouseFunc(mouse);

    // Depois de chamada todas as janelas configuradas e criadas sao mostradas na tela
    glutMainLoop();

    return 0;
}
