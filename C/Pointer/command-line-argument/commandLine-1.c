#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    printf("argc = %d\n", argc);
    for (i=0; i < argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);
    printf("*(argv[2]+2) = %c\n", *(argv[2]+2));
    printf("*(*(argv+2)+2) = %c\n", *(*(argv+2)+2));
}