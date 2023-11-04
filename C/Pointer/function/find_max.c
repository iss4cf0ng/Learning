#include <stdio.h>

int findmax(int [], int);
int findmax_ptr(int *, int);
int main()
{
    int i;
    int arr[] = {20, 10, 100, 40, 60, 80, 90};
    int elements = sizeof(arr)/sizeof(arr[0]);
    int max_number = findmax(arr, elements);

    printf("Max(");
    for (i=0; i<elements; i++)
        printf("%d ", arr[i]);
    printf(") is %d\n\n", max_number);

    max_number = findmax_ptr(arr, elements);
    printf("Max(");
    for (i=0; i<elements; i++)
        printf("%d ", arr[i]);
    printf(") is %d\n", max_number);

    return 0;
}

int findmax(int x[], int n)
{
    int j;
    int max = x[0];
    for (j=1; j<n; j++)
        if (x[j] > max)
            max = x[j];
    return max;
}

int findmax_ptr(int *x, int n)
{
    int j;
    int max = *x;
    for (j=0; j<n; j++)
        if (*(x+j) > max)
            max = *(x+j);
    return max;
}