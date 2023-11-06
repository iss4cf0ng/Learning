#include <stdio.h>
struct student
{
    char name[20];
    int score;
    char *passdown;
};
void passOrdown(struct student *);
void output(struct student *);

int main()
{
    struct student stu;
    printf("Enter name : ");
    scanf("%s", stu.name);
    printf("Enter C language score : ");
    scanf("%d", &stu.score);

    passOrdown(&stu);
    output(&stu);

    return 0;
}

void passOrdown(struct student *p)
{
    if (p -> score >= 60)
        p->passdown = (char *)"PASS";
    else
        p->passdown = (char *)"DOWN";
}

void output(struct student *q)
{
    int i;
    printf("\n\n%10s %10s %20s\n", "Name", "Score", "Pass or Down");
    for (i=0; i < 42; i++)
        printf("=");
    printf("\n");
    printf("%10s %10d %20s\n", q->name, q->score, q->passdown);
}