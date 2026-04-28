#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

int main()
{
    Node *head = new Node();
    Node *sec = new Node();
    Node *third = new Node();

    head->data = 10;
    head->next = sec;

    sec->data = 20;
    sec->next = third;

    third->data = 30;
    third->next = nullptr;

    cout << "secData: " << head->next->data << endl;
    cout << "thirdData: " << head->next->next->data << endl;

    delete head; delete sec; delete third;
    return 0;
}