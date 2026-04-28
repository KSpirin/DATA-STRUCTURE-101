#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

void printList(Node *n)
{
    while (n != nullptr)
    { // if use n->next != nullptr 30 not found
        cout << n->data << " > ";
        n = n->next;
    }
    cout << "NULL" << endl;
}

int main()
{
    Node *head = new Node();
    Node *second = new Node();
    Node *third = new Node();

    head->data = 10;
    head->next = second;

    second->data = 20;
    second->next = third;

    third->data = 30;
    third->next = nullptr;

    printList(head);

    delete head;
    delete second;
    delete third;
    return 0;
}