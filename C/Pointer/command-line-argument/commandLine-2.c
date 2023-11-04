#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        switch (*(argv[1]+1))
        {
            case 'd':
                system("dir/w C:\\");
                break;
            case 't':
                system("type D:\\geek.exe");
                break;
            default:
                break;
        }
    }
}