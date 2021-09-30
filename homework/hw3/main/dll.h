#include <string>
using namespace std;

struct Node {
    string word;
    Node* next;
    Node* prev;

    Node() {
        next = nullptr;
        prev = nullptr;
    }

    Node(string value) {
        word = value;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList();
    const Node* getTail();
    bool isEmpty();
    int getSize();
    bool print();
    void addToFront(string);
    void addToEnd(string);
    bool addAt(int index, string word);
    string removeFromFront();
    bool removeFromEnd();
    bool removeAt(int index);
    string at(int index);
    bool contains(string sentence);
    void swap(int index1, int index2);
    void changeValue(int index, string data);
    void sort();
    void sortLength();

};