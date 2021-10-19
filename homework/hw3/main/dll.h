#include <string>
#include <fstream>
using namespace std;

struct Node {
    string type;
    string equation;
    Node* next;
    Node* prev;

    Node() {
        next = nullptr;
        prev = nullptr;
    }

    Node(string t, string e) {
        type = t;
        equation = e;
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
    const Node* getHead();
    bool isEmpty();
    int getSize();
    int getNumPrefix();
    int getNumPostfix();

    bool print();    
    bool print(ofstream& output);

    bool printRev();
    bool printRev(ofstream& output);

    void addToFront(string, string);
    void addToEnd(string, string);
    bool addAt(int index, string t, string e);
    bool removeFromFront();
    bool removeFromEnd();
    bool removeAt(int index);
    Node* at(int index);
    bool contains(string sentence);
    void swap(int index1, int index2);
    void changeValue(int index, string data);
    void sort();
    void sortLength();

    //hw3
    void convertList(string param);

    string prefixToPostfix(string eq);
    string postfixToPrefix(string eq);

};