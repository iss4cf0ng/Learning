#include <iostream>
void callByRef(int &);
using namespace std;

int main()
{
    int k = 100;
    cout << "The address of k is " << &k << endl;
    cout << "k=" << k << endl;
    callByRef(k);
    cout << "callByRef()...\n";
    cout << "k=" << k << endl;

    getchar();
    return 0;
}

void callByRef(int &x)
{
    cout << "The address of x is " << &x << endl;
    x +=1000;
}