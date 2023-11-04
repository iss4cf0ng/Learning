#include <stdio.h>

int sum(int [][2], int, int);
int main()
{
    int i, j, row, column, total = 0;
    int arr2[][2] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int elements = sizeof(arr2)/sizeof(arr2[0][0]);
    row = elements / 2;
    column = 2;
    total = sum(arr2, row, column);

    printf("Sum : %d\n", total);
}

int sum(int p2[][2], int n, int m)
{
    int i, j, t = 0;
    for (i=0; i<n; i++)
        for (j=0; j<m; j++)
            t += *(*(p2 + i) + j);
    return t;
}