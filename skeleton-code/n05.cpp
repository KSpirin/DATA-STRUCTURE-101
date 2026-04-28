#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

// Function for traversing the Linked List
void printList(Node *n)
{
    // 1. Create a while loop with the condition "as long as n is not nullptr"
    // ... {

    // 2. Print n->data (you may add an arrow for style, e.g., cout << n->data << " -> ";)
    // ...

    // 3. Move n to point to the next node (this is the heart of the loop!)
    // Hint: n = ...
    // ...
    // }

    cout << "NULL" << endl; // End of the train
}

int main()
{
    // Create and link the Linked List (10 -> 20 -> 30)
    Node *head = new Node();
    Node *second = new Node();
    Node *third = new Node();

    head->data = 10;
    head->next = second;

    second->data = 20;
    second->next = third;

    third->data = 30;
    third->next = nullptr;

    // Call the function to print the data
    printList(head);

    delete head;
    delete second;
    delete third;
    return 0;
}