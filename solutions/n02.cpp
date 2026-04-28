#include <iostream>
using namespace std;

int main()
{
    int x = 100;
    int* ptr = &x;
    *ptr = 999;
    cout << "Now x is: " << x << endl;

    return 0;
}