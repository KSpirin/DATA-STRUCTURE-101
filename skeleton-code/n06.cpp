#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

// Function for printing
void printList(Node *n)
{
    while (n != nullptr)
    {
        cout << n->data << " > ";
        n = n->next;
    }
    cout << "NULL" << endl;
}

// Focus on this function: Insert node at the front
void insertAtFront(Node **head_ref, int new_data)
{
    // 1. Create a new Node using new
    // ...

    // 2. Put new_data into ->data
    // ...

    // 3. Set ->next of the new node to point to the old head (which is *head_ref)
    // ...

    // 4. Update the old head to point to the new node (update *head_ref)
    // ...
}

int main()
{
    Node *head = nullptr; // Start with an empty list

    // Try inserting data repeatedly (always insert at the front)
    insertAtFront(&head, 30); // Now the list is: 30 > NULL
    insertAtFront(&head, 20); // Now the list is: 20 > 30 > NULL
    insertAtFront(&head, 10); // Now the list is: 10 > 20 > 30 > NULL

    // Print the result
    printList(head);
    // Expected output: 10 > 20 > 30 > NULL

    return 0;
}