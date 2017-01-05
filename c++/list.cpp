#include <iostream>
#include <map>
#include <string>

using namespace std;

enum position {
    HEAD,
    TAIL
};
typedef enum position Position;

struct node {
    int value;
    struct node* next;
};
typedef struct node Node;

class LinkedList
{
    private:
        Node* head;
        Node* tail;
        int count;
    public:
        LinkedList();
        ~LinkedList();
        int insert(Position pos, int value);
        int show();
};

LinkedList::LinkedList() {
    cout << "CONSTRUCTOR" << endl;
    head = tail = NULL;
    count = 0;
}

LinkedList::~LinkedList() {
    cout << "DESTRUCTOR" << endl;
    Node * it = head;
    Node * next = head;
    while (count) {
        it = next;
        next = it->next;
        delete it;
        count--;
    }
    head = tail = NULL;
}

int LinkedList::insert(Position pos, int value) {
    cout << "INSERT - " << value << endl;
    Node * tmp = new Node;
    tmp->value = value;
    tmp->next = NULL;
    if (pos == HEAD) {
        tmp->next = head;
        head = tmp;
        if (!count) tail = head;
    }
    else {
        tail->next = tmp;
        tail = tmp;
        if (!count) head = tail;
    }
    count++;
    return count;
}

int LinkedList::show() {
    cout << "SHOW TOTAL ELEMENT - " << count << endl;
    Node* it = head;
    while (it) {
        cout << it->value << ", ";
        it = it->next;
    }
    cout << endl;
    return count;
}

int main () {
    LinkedList l;
    l.insert(HEAD, 3);
    l.insert(TAIL, 7);
    l.insert(HEAD, 2);
    l.insert(TAIL, 8);
    l.insert(HEAD, 1);
    l.insert(TAIL, 9);
    l.show();
    return 0;
}
