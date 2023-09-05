#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char string[10], istring[10];
    int cont, incrementa = 0, i, j;

    printf("Digite uma palavra: ");
    scanf("%s", &string);

    strcpy(istring, string);

    strrev(istring);

    if (strcmp(string, istring) == 0)
    {
        printf("\nTemos um palindromo!");
    }
    return 0;
}