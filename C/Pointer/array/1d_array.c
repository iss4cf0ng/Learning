#include <stdio.h>

int main()
{
    int x[5];
    int i;

    for (i = 0; i < 5; i++)
    {
        printf("Enter x[%d] integer value : ", i);
        scanf("%d", &x[i]);
    }
    for (i = 0; i < 5; i++)
    {
        printf("x[%d] = %3d, Addr : %p\n", i, x[i], &x[i]);
    }
}