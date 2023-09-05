#include <stdio.h>
#include <stdlib.h>

int main()
{
    float i, x, y, p1, p2;
    x = 0;

    printf("Digite as notas dos exercicios (sao 13):\n");
    for (i = 0; i < 13; i++)
    {
        printf("Nota do Exercicio %1.f: ", i + 1);
        scanf("%f", &y);
        x += y;
    }
    x = x / 130 * 0.3;

    p1 = 8.25;
    p2 = 2.75;

    i = (p1 + p2) / 2 * 0.7;

    printf("Media: %f", (i + x));

    getch();
    
    return 0;
}