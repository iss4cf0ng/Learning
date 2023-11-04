#include <stdio.h>

int main()
{
    char *s[] = {"Stanford", "University", "California", "American"};
    char **sa[] = {s, s+1, s+2, s+3};
    char ***p3 = sa;
    printf("**p3++ = %s\n", **p3++);
    printf("**++p3 = %s\n", **++p3);
    printf("**++*p3 = %c\n", **++*p3);
    printf("*(*--*++p3+3) = %c\n", *(*--*++p3+3));

    return 0;
}