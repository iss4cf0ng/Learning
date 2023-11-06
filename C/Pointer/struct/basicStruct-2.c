#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct student
    {
        char name[20];
        int score;
    };
    struct student st1, *st2;
    st2 = (struct student *)malloc(sizeof(struct student));
    printf("Enter name : ");
    scanf("%s", st1.name); //scanf(str, &x), the second parameter is the address of x.
    printf("C language score : ");
    scanf("%d", &st1.score);

    printf("\nAnother name : ");
    scanf("%s", st2->name);
    printf("C language score : ");
    scanf("%d", &st2->score);

    printf("%s C language score : %d\n", st1.name, st1.score);
    printf("%s C language score : %d\n", st2->name, st2->score);
    free(st2);

    return 0;
}