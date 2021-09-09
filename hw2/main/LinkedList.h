#include <string>
using namespace std;

struct Node {
    string word;
    Node* next;

    Node() {
        next = nullptr;
    }

    Node(string value) {
        word = value;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    LinkedList();
    bool isEmpty();
    int getSize();
    bool print();
    void addToFront(string);
    void addToEnd(string);
    bool addAt(int index, string word);
    string removeFromFront();
    string removeFromEnd();
    string removeAt(int index);

};