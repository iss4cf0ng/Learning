#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int gval = 10; //Global value

int main(int argc, char *argv[])
{
    pid_t pid;
    int lval = 20; //Local value
    gval++;
    lval++;

    pid = fork();
    if (pid == 0) //If child process
    {
        gval += 2;
        lval += 2;
    }
    else
    {
        gval -= 2;
        lval -= 2;
    }

    if (pid == 0)
        printf("Child proc: [%d, %d]\n", gval, lval);
    else
        printf("Parent proc: [%d, %d]\n", gval, lval);

    return 0;
}