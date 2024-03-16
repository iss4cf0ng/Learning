#include <iostream>
using namespace std;

void swap_by_address(int *, int *);
void swap_by_ref(int &, int &);
void swap_by_value(int, int);

int main()
{
    int x = 100, y = 200;

    x = 100; y = 200;
    cout << "Call by value\n";
    cout << "Before swapping...\n";
    cout << "x=" << x << ", y=" << y << endl;
    swap_by_value(x, y);
    cout << "After swapping...\n";
    cout << "x=" << x << ", y=" << y << endl << endl;

    x = 100; y = 200;
    cout << "Call by address\n";
    cout << "Before swapping...\n";
    cout << "x=" << x << ", y=" << y << endl;
    swap_by_address(&x, &y);
    cout << "After swapping...\n";
    cout << "x=" << x << ", y=" << y << endl << endl;

    x = 100; y = 200;
    cout << "Call by reference\n";
    cout << "Before swapping...\n";
    cout << "x=" << x << ", y=" << y << endl;
    swap_by_ref(x, y);
    cout << "After swapping...\n";
    cout << "x=" << x << ", y=" << y << endl << endl;

    getchar();
    return 0;
}

void swap_by_value(int a, int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swap_by_address(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swap_by_ref(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}