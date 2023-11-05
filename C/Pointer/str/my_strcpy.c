#include <stdio.h>
#include <string.h>

void myStringCopy(char *, char *);

int main()
{
    int length = 0;
    char str2[80];
    char *str1 = "Apple iPhone";

    printf("str2 = %s\n\n", str2);
    myStringCopy(str2, str1);
    printf("str2 = %s\n\n", str2);

    return 0;
}

void myStringCopy(char *dest, char *source)
{
    while ((*dest = *source) != '\0')
    {
        source++;
        dest++;
    }
}