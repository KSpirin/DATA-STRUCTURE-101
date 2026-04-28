#include <iostream>
using namespace std;

// 1. Create the structure of the data box (Node)
struct Node
{
    int data;   // Data field
    Node *next; // Pointer to the next node
};

int main()
{
    // 2. Allocate memory for 3 Nodes
    Node *head = new Node();
    Node *second = new Node();
    Node *third = new Node();

    // 3. Assign values and link the pointers together
    head->data = 10;
    head->next = second; // Point to the 2nd node

    second->data = 20;
    second->next = third; // Point to the 3rd node

    third->data = 30;
    third->next = nullptr; // The last node must point to NULL

    // Try printing the values
    cout << "Node 1: " << head->data << endl;
    cout << "Node 2: " << head->next->data << endl; // Access via head's pointer
    cout << "Node 3: " << head->next->next->data<< endl;

    return 0;
}