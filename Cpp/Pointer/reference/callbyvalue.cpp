#include <iostream>
void callByValue(int);
using namespace std;

int main()
{
    int k = 100;
    cout << "The address of k is " << &k << endl;
    cout << "k=" << k << endl;
    cout << "callByValue()...\n";
    callByValue(k);
    cout << "k=" << k << endl;

    getchar();
    return 0;
}

void callByValue(int x)
{
    cout << "The address of x is " << &x << endl;
    x += 1000;
}