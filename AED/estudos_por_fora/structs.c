#include <stdio.h>

typedef struct{
    int horas;
    int minutos;
}Hm;

int main(){
    int minutoss;
    Hm hm;

    printf("Digite quantos minutos são: ");
    scanf("%d",&minutoss);

    hm.horas=minutoss/60;
    hm.minutos=minutoss%60;

    printf("%d:%d",hm.horas,hm.minutos);

    return 0;
}