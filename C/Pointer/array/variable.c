#include <stdio.h>

int main()
{
    int x = 100, y = 200, z = 300;
    printf("x variable addr : %p\n", &x);
    printf("y variable addr : %p\n", &y);
    printf("z variable addr : %p\n", &z);

    printf("x value : %d\n", x);
    printf("y value : %d\n", y);
    printf("z value : %d\n", z);

    return 0;
}