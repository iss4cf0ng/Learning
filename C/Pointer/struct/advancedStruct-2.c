#include <stdio.h>

int main()
{
    struct student
    {
        char name[20];
        int score;
    };

    struct student st = {"John", 97};
    struct student *ptr = &st;

    printf("ptr->name = %s\n", ptr->name);
    printf("*(ptr->name) = %c\n", *(ptr->name));
    printf("++*(ptr->name) = %c\n", ++*(ptr->name));
    printf("ptr->name = %s\n", ptr->name);
    printf("ptr->score = %d\n", ptr->score);
    printf("(ptr->score)++ = %d\n", (ptr->score)++);
    printf("ptr->score = %d\n", ptr->score);

    return 0;
}