#include <iostream>
using namespace std;
struct says {
    char word[20];
    int times;
};

void calls(says *);
int main()
{
    says x = {"Hello, world", 0};
    calls(&x);
    cout << "It's #" << x.times << " called" << endl << endl;

    calls(&x);
    cout << "It's #" << x.times << " called" << endl << endl;

    calls(&x);
    cout << "It's #" << x.times << " called" << endl;

    getchar();
    return 0;
}

void calls(says *p)
{
    cout << p->word << endl;
    p->times++;
}