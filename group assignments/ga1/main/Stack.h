#include <iostream>
#include <string>
using namespace std;

struct stackNode
{
    string element;
    stackNode* next;
};

//Stack as a linked list
class Stack
{
private:
    stackNode* top;
    int size;

public:
    Stack();
    Stack(int);
    bool isEmpty();
    int getSize();
    string peek();
    void push(string);
    bool pop();
    void print();

};