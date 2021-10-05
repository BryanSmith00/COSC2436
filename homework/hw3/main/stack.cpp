#include <iostream>
#include <string>
#include "stack.h"
using namespace std;

Stack::Stack()
{
    top = nullptr;
    size = 0;
}

Stack::Stack(int s) 
{
    size = s;
    
}

//Returns true if the stack is empty and false otherwise
bool Stack::isEmpty()
{
    return top == nullptr;
}

//Pushes data onto the top of the stack
//Need to find data to push and add it to function args
void Stack::push(string elem) {
    stackNode* temp = new stackNode;
    temp->element = elem;
    temp->next = top;
    top = temp;
    size++;
}

//Pops the top node off of the stack
// Returns bool if a node has been popped 
//Add return of data stored in the stack node
string Stack::pop()
{
    if(isEmpty())
    {
        return "";
    }
    else
    {
        stackNode* temp = top;
        string val = temp->element;
        top = temp->next;
        delete temp;
        size--;
        return val;
    }
}

//Returns the value of the top of the stack
string Stack::peek()
{
    if (isEmpty())
    {
        cout << "EMPTY" << endl;
        return "";
    }
    else
        return top->element;
}

void Stack::print()
{
    stackNode* curr = top;

    while (curr != nullptr)
    {
        cout << curr->element << endl;
        curr = curr->next;
    }
}