#include <string>
using namespace std;

struct Node 
{
    string id;
    Node* next;

    Node() 
    {
        next = nullptr;
    }

    Node(string x)
    {
        id = x; 
        next = nullptr;
    }
};

class LinkedList 
{
private:
    Node* head;
    Node* tail;
    int size;

public:
    LinkedList();
    Node* getHead();
    Node* getTail();
    bool isEmpty();
    int getSize();
    void print();
    void addToFront(string);
    bool addToEnd(string, Node*);
    string at(int, Node*);

};