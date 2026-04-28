#include <iostream>
#include <string>
using namespace std;

typedef struct {
    int weight;
    string label;
} Box;

int main()
{
    Box b1;
    b1.weight = 50;
    b1.label = "Fragile";
    cout << "label: " << b1.label << endl;
    cout << "weight: " << b1.weight << endl;
    return 0;
}