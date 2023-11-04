#include <stdio.h>

int main()
{
    int *pt;
    int (*pa)[3];
    int **p2;
    int arr1[2][3] = {0, 1, 2, 3, 4, 5};
    int arr2[3][2] = {10, 20, 30, 40, 50, 60};

    printf("&arr1[0][0] = %p\n", &arr1[0][0]);
    printf("&arr2[0][0] = %p\n", &arr2[0][0]);

    pt = &arr1[0][0];
    printf("pt = %p, &arr1[0][0] = %p\n", pt, &arr1[0][0]);
    pt = arr1[0];
    printf("*pt = %d\n", *pt);

    pa = arr1;
    printf("**pa = %d\n", **pa);
    p2 = &pt;
    printf("**p2 = %d\n", **p2);
    *p2 = arr2[0];
    printf("*p2 = %p, arr2[0] = %p\n", *p2, arr2[0]);
    printf("**p2 = %d\n", **p2);

    return 0;
}