#include <stdio.h>

int main()
{
    int a = 100, b = 200;

    const int *p = &a;
    int *const q = &b;
    printf("a = %d, *p = %d\n", a, *p);
    printf("b = %d, *q = %d\n", b, *q);

    /*
        Cannot alter a value as *p
        *p = b;
    */
   //But we can do this.
   p = &b;
   printf("*p = %d\n", *p);

   /*--------------------------------------*/
   /*Cannot alter q pointer to another address of variable.
    q = &a;
   */
    //But we can change b value as q pointer.
    *q = 888;
    printf("*q = %d\n", *q);

    /*-------------------------------------*/
    const int *const r = &a;
    a = 150;
    printf("*r = %d, &r = %p\n", *r, &r);

    return 0;
}