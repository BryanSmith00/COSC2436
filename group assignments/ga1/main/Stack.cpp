#include <iostream>
#include <string>
#include "Stack.h"
using namespace std;

Stack::Stack()
{
    top = nullptr;
    size = 0;
}

Stack::Stack(int s) 
{ 
    top = nullptr;
    size = s;
}

//Returns true if the stack is empty and false otherwise
bool Stack::isEmpty() { return top == nullptr; }

//Returns the string stored in the top of the stack
string Stack::peek() { return top->element; }

int Stack::getSize() { return size; }

//Pushes data onto the top of the stack
void Stack::push(string elem) {
    stackNode* temp = new stackNode;
    temp->element = elem;
    temp->next = top;
    top = temp;
    size++;
}

//Pops the top node off of the stack
// Returns bool if a node has been popped 
bool Stack::pop()
{
    if (isEmpty())
    {
        return false;
    }
    else
    {
        stackNode* temp = top;
        string val = temp->element;
        top = temp->next;
        delete temp;
        size--;
        return true;
    }
}