#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

void printList(Node *n){
    while (n != nullptr){
        cout << n->data << " > ";
        n = n->next;
    }
    cout << "NULL" << endl;
}

void insertAtFront(Node **head_ref, int new_data){
    Node *newNode = new Node();

    newNode->data = new_data;

    newNode->next = *head_ref;

    *head_ref = newNode;
}

int main(){
    Node *head = nullptr;

    insertAtFront(&head, 30); // 30 > NULL
    insertAtFront(&head, 20); // 20 > 30 > NULL
    insertAtFront(&head, 10); // 10 > 20 > 30 > NULL

    printList(head);

    return 0;
}