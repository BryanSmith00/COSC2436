#include <iostream>
#include <string>
#include "reservestack.h"
using namespace std;

ReserveStack::ReserveStack()
{
    top = nullptr;
    size = 0;
}

//Returns true if the stack is empty and false otherwise
bool ReserveStack::isEmpty()
{
    return top == nullptr;
}

void ReserveStack::push(string t, string equation) {
    reserveStackNode* temp = new reserveStackNode;
    temp->typ = t;
    temp->eq = equation;

    temp->next = top;
    top = temp;
    size++;
}