#include <stdio.h>

int main()
{
    struct employee
    {
        char id[7];
        char name[20];
        int salary;
    };

    struct employee manager = {"D12345", "Peter", 35000};
    struct employee *ptr = &manager;
    
    printf("&ptr = %p\n", &ptr);
    printf("ptr = %p\n", ptr);
    printf("&manager = %p\n", &manager);
    printf("manager.id = %p\n", manager.id);
    printf("manager.name = %p\n", manager.name);
    printf("&manager.salary = %p\n\n", &manager.salary);

    printf("Using . access struct element\n");
    printf("manager.id = %s\n", manager.id);
    printf("manager.name = %s\n", manager.name);
    printf("manager.salary = %d\n\n", manager.salary);

    printf("Using -> access struct element\n");
    printf("ptr->id = %s\n", ptr->id);
    printf("ptr->name = %s\n", ptr->name);
    printf("ptr->salary = %d\n\n", ptr->salary);

    printf("Using (*). access struct element\n");
    printf("(*ptr).id = %s\n", (*ptr).id);
    printf("(*ptr).name = %s\n", (*ptr).name);
    printf("(*ptr).salary = %s\n", (*ptr).salary);

    return 0;
}