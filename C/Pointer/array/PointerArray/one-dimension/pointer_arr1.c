#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[] = {100, 101, 102};
    int *ptr = arr;
    int i, size = 0;
    size = (sizeof arr / sizeof(arr[0]));
    printf("sizeof(arr) : %d\n", sizeof(arr));
    printf("sizeof(arr[0]) : %d\n", sizeof(arr[0]));
    printf("size = %d\n", size);
    printf("arr = %p\n", arr);
    printf("ptr = %p\n", ptr);
    printf("&arr = %p\n", arr);
    printf("&ptr = %p\n", ptr);

    printf("-----------Using arr-----------\n");
    for (i = 0; i < size; i++)
        printf("&arr[%d] = %x\n", i, &arr[i]);
    printf("\n");

    for (i = 0; i < size; i++)
        printf("arr+%d = %x\n", i, arr + i);
    printf("\n");

    for (i = 0; i < size; i++)
        printf("arr[%d] = %d\n", i, arr[i]);
    printf("\n");

    for (i = 0; i < size; i++)
        printf("*(arr+%d) = %d\n", i, *(arr+i));
    printf("\n");

    printf("-----------Using ptr-----------\n");
    for (i = 0; i < size; i++)
        printf("ptr+%d = %x\n", i, ptr + i);
    printf("\n");

    for (i = 0; i < size; i++)
        printf("*(ptr+%d) = %d\n", i, *(ptr + i));

    return 0;
}