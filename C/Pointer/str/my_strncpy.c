#include <stdio.h>
#include <string.h>

void myStrNCpy(char *, char *, int);

int main()
{
    int length = 0;
    char str2[80];
    char *str1 = "Apple iPhone";
    char str3[80];

    strncpy(str2, str1, 5);
    str2[5] = '\0';
    printf("str2 = %s\n", str2);

    myStrNCpy(str3, str1, 5);
    str3[5] = '\0';
    printf("str3 = %s\n", str3);

    return 0;
}

void myStrNCpy(char *dest, char *source, int n)
{
    int i = 1;
    while ((i <= n) && (*dest = *source) != '\0')
    {
        source++;
        dest++;
        i++;
    }
}