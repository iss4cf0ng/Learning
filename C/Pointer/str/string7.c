#include <stdio.h>

int main()
{
    char *str1 = "Apple iPod";
    char str2[10] = "Apple iPod";

    printf("str1 : %p\n", str1);
    printf("str1 : %s\n", str1);
    printf("str2 : %s\n", str2);
}