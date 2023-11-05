#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *str1 = (char *)malloc(20);
    str1 = "Hello";
    char *str2 = (char *)malloc(20);
    str2 = "Hello";
    char *str3 = (char *)malloc(20);
    str3 = "Hello world";

    printf("Address of str1 : %p\n", str1);
    printf("Address of str2 : %p\n", str2);
    printf("Address of str3 : %p\n", str3);

    if (str1 == str2)
        printf("str1 == str2\n");
    else
        printf("str1 != str2\n");

    if (str1 == str3)
        printf("str1 == str3\n");
    else
        printf("str1 != str3\n");

    return 0;
}