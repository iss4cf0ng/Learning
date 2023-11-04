#include <stdio.h>

double calAverage(double, double);
int main()
{
    double x, y, aver;
    printf("Enter x, y: ");
    scanf("%lf %lf", &x, &y);
    aver = calAverage(x, y);
    printf("Average of x, y : %d", aver);

    return 0;
}

double calAverage(double a, double b)
{
    double aver;
    aver = (a + b)/2;
    return aver;
}