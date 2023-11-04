#include <stdio.h>

int main()
{
    int x = 100, y = 200;
    int *ptr = &x;
    printf("Variable x address : %p, value : %d\n", &x, x);
    printf("Variable y address : %p, value : %d\n", &y, y);
    printf("ptr address : %p\n\n", &ptr);

    printf("ptr value : %p\n", ptr);
    printf("x = %d, *ptr = %d\n\n", x, *ptr);

    ptr = &y;
    printf("ptr value : %p\n", ptr);
    printf("y = %d, *ptr = %p\n", y, *ptr);

    getchar();
    return 0;
}