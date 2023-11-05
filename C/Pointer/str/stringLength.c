#include <stdio.h>
#include <string.h>

int stringLength(char *);

int main()
{
    int length = 0;
    char *str = "Apple iPod";
    printf("The length of \"%s\" is %d\n\n", str, strlen(str));
    printf("%s\n", str);

    length = stringLength(str);
    printf("%s\n", str);
    printf("The length of \"%s\" is %d\n\n", str, length);
}

int stringLength(char *p)
{
    int t = 0;
    while (*p != '\0')
    {
        t++;
        p++;
    }
    return t;
}