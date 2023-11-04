#include <stdio.h>

int main()
{
    int i[][3] = {10, 20, 30, 40, 50, 60};
    int (*ptr)[3];
    int a, b, total = 0;

    for (a=0; a<2; a++)
        for (b=0; b<3; b++)
            printf("&i[%d][%d] = %x\n", a, b, &i[a][b]);
    printf("\n");

    for (a=0; a<2; a++)
        for (b=0; b<3; b++)
            printf("i[%d][%d] = %d\n", a, b, i[a][b]);
    printf("\n");
}