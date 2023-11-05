#include <stdio.h>
#include <string.h>

int main()
{
    char *s = "iPhone";
    char t[80] = " ";
    printf("Before strcpy(t, s)\n");
    printf("s = %s\n", s);
    printf("t = %s\n", t);
    printf("After strcpy(t, s)\n");
    strcpy(t, s);
    printf("s = %s\n", s);
    printf("t = %s\n", t);

    return 0;
}