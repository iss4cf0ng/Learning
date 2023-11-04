#include <stdio.h>

int main()
{
    int x[][3] = {10, 20, 30, 40, 50, 60};
    int i, j;

    printf("&x = %p, &x[0][0] = %p, &x[0] = %p\n", &x, &x[0][0], &x[0]);
    printf("x = %p, x[0][0] = %p, x[0] = %p\n", x, x[0][0], x[0]);

    for (i = 0; i < 2; i++)
        printf("x[%d] = %p\n", i, x[i]);
    printf("\n");

    for (j = 0; j < 6; j++)
        printf("x[0]+%d = %p\n", j, x[0] + j);
    printf("\n");
    
    for (j = 0; j < 3; j++)
        printf("x[1]+%d = %p\n", j, x[1] + j);
    printf("\n");

    for (i = 0; i < 2; i++)
        printf("x+%d = %p\n", i, x + i);
}