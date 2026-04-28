#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

int main()
{
    Node *myNode = new Node();
    myNode->data = 99;
    myNode->next = nullptr;
    cout << "data: " << myNode->data << endl;
    delete myNode;
    return 0;
}