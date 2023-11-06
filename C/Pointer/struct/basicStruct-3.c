#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct student
    {
        char firstname[20];
        char *lastname;
        int score;
    };

    struct student st1, *st2;

    printf("Enter firstname of first student : ");
    scanf("%s", st1.firstname);
    st1.lastname = "Hello";
    printf("Enter C language score : ");
    scanf("%d", &st1.score);

    st2 = (struct student *)malloc(sizeof(struct student));
    printf("\nEnter firstname of second student : ");
    scanf("%s", st2->firstname);
    st2->lastname = "World";
    printf("Enter C language score : ");
    scanf("%d", &st2->score);

    printf("\n%s%s C language score : %d\n", st1.firstname, st1.lastname, st1.score);
    printf("%s%s C language score : %d\n", st2->firstname, st2->lastname, st2->score);
    free(st2);

    return 0;
}