#include <stdio.h>

int sum(int *, int);
int main()
{
    int i;
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int elements = sizeof(arr)/sizeof(arr[0]);
    int total = sum(arr, elements);

    printf("Sum is : %d\n", total);

    return 0;
}

int sum(int *x, int n)
{
    int j, t = 0;
    for (j=0; j<n; j++)
        t += *(x+j);
    return t;
}