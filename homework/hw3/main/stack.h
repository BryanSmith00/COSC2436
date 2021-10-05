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
    void push(string);
    string pop();
    string peek();
    void print();
    void flipReserve();
    int getSize();
    void convert();


};