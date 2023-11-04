#include <stdio.h>

int main()
{
    char *parr[] = {"Department", "of", "Some", "Thing"};
    printf("*parr[3] = %c\n", *parr[3]);
    printf("**(parr+3) = %c\n", **(parr+3));
    printf("parr[3][0] = %c\n", parr[3][0]);
    printf("parr[2] = %s\n", parr[2]);
    printf("*(parr+2) + %s\n", *(parr+2));
    printf("**(parr+2) + %c\n", **(parr+2));
    printf("%s", parr[0] + 6);
}