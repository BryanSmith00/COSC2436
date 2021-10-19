#include <iostream>
#include <string>
using namespace std;

struct reserveStackNode
{
    string typ;
    string eq;
    reserveStackNode* next;
};

//Stack as a linked list
class ReserveStack
{
private:
    reserveStackNode* top;
    int size;

public:
    ReserveStack();
    bool isEmpty();
    int getSize();
    void setSize(int);
    reserveStackNode* getTop();
    reserveStackNode* peek();
    void push(string, string);
    bool pop();
    void print();
    void flipReserve();
    void convert();
    string prefixToPostfix(string eq);
    string postfixToPrefix(string eq);
    void operator = (reserveStackNode*);
};
