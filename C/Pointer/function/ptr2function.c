#include <stdio.h>

int add(int, int);
int substract(int, int);
int multiply(int, int);
int divide(int, int);
int (*operation)(int, int); //Pointer point to function

int main()
{
    int x, y, output;
    printf("Enter x, y : ");
    scanf("%d %d", &x, &y);
    operation = add;
    output = (*operation)(x, y);
    printf("%d + %d = %d\n", x, y, output);

    operation = substract;
    output = (*operation)(x, y);
    printf("%d - %d = %d\n", x, y, output);

    operation = multiply;
    output = (*operation)(x, y);
    printf("%d * %d = %d\n", x, y, output);

    operation = divide;
    output = (*operation)(x, y);
    printf("%d / %d = %d\n", x, y, output);
}

int add(int x, int y)
{
    return x+y;
}

int substract(int x, int y)
{
    return x-y;
}

int multiply(int x, int y)
{
    return x*y;
}

int divide(int x, int y)
{
    return x/y;
}