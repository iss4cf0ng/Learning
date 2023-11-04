#include <stdio.h>

int main()
{
    int i[5] = {10, 20, 30, 40, 50};
    int *ptr[] = {i, i+1, i+2, i+3, i+4};
    int **p2 = ptr;
    int k;

    printf("ptr = %p\n", ptr);
    for (k=0; k<5; k++)
        printf("*ptr[%d] = %d, ptr[%d] = %p\n", k, *ptr[k], k, ptr[k]);
    printf("\n");
    
    for (k=0; k<5; k++)
        printf("**(p2+%d) = %d, *(p2+%d) = %p, (p2+%d) = %p\n", k, **(p2+k), k, *(p2+k), k, p2+k);

    return 0;
}