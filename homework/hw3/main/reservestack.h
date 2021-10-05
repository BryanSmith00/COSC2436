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
    void push(string, string);
    bool pop();
    char peek();
    void print();
    void flipReserve();
    int getSize();
    void convert();


};
