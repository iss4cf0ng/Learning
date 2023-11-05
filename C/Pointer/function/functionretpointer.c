#include <stdio.h>
#define MAX 5
int *pf(int [], int);
int k[MAX];

int main()
{
    int total=0, n;
    int i[MAX] = {10, 20, 30, 40, 50};
    int *ptr;
    ptr = pf(i, MAX);
    printf("ptr = %#x\n\n", ptr);

    printf("Sum of (\n");
    for (n=0; n<MAX; n++)
    {
        printf("k[%d] = %d\n", n, *(ptr+n));
        total += *(ptr+n);
    }
    printf(") is %d\n", total);

    return 0;
}

int *pf(int x[], int n)
{
    int m;
    int j[] = {100, 200, 300, 400, 500};
    for (m=0; m<n; m++)
    {
        k[m] = j[m]+x[m];
        printf("k[%d] = %d\n", m, k[m]);
    }
    printf("k = %#x\n", k);
    return k;
}