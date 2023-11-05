#include <stdio.h>

int main()
{
    char *str = "Apple iPhone";
    int i;
    printf("String str : ");
    for (i=0; *str!='\n'; i++) 
    {
        printf("%c", *str);
        str++;
    }

    getchar();
    return 0;
}