#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

int main()
{
    // 1. Create 3 nodes
    Node *head = new Node();
    Node *second = new Node();
    Node *third = new Node();

    // 2. Assign data
    head->data = 10;
    // Assign data to second and third...
    // ...

    // 3. Link the train (next)
    head->next = second;
    // Link second to third and third to nullptr...
    // ...

    // 4. Print the data of node 2 and 3 by accessing only through 'head'
    cout << "Node 1: " << head->data << endl;

    // Hint: head->next means jumping to node 2
    // cout << "Node 2: " << ... << endl;

    // Hint: head->next->next means jumping twice to node 3
    // cout << "Node 3: " << ... << endl;

    // 5. Free the memory for all 3 nodes
    // ...

    return 0;
}