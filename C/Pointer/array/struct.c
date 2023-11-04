#include <stdio.h>

int main()
{
    struct employee
    {
        char id[7];
        char name[20];
        int salary;
    };
    
    struct employee manager = {"D123456", "Peter", 35000};
    
    printf("&manager = %p\n", &manager);
    printf("manager.id = %p\n", manager.id);
    printf("&manager.id = %p\n", &manager.id);
    printf("manager.name = %p\n", manager.name);
    printf("&manager.name = %p\n", &manager.name);
    printf("manager.salary = %p\n", manager.salary);
    printf("&manager.salary = %p\n", &manager.salary);
}