#include <stdio.h>

int main()
{
    int i[] = {100, 200, 300, 400, 500};
    int *pi = i;
    printf("...%d\n", *pi++);
    printf("*pi = %d\n", *pi);
    printf("...%d\n", *++pi);
    printf("*pi = %d\n", *pi);
    printf("...%d\n", ++*pi);
    printf("*pi = %d\n", *pi);

    return 0;
}