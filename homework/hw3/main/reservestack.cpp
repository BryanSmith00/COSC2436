#include <iostream>
#include <string>
#include "reservestack.h"
#include "stack.h"
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

int ReserveStack::getSize()
{
    return size;
}

void ReserveStack::setSize(int s) 
{
    size = s;
}

reserveStackNode* ReserveStack::getTop()
{
    return top;
}

reserveStackNode* ReserveStack::peek()
{
    return top;
}

void ReserveStack::push(string t, string equation) {
    reserveStackNode* temp = new reserveStackNode;
    temp->typ = t;
    temp->eq = equation;

    temp->next = top;
    top = temp;
    size++;
}

bool ReserveStack::pop()
{
    if (size >= 1)
    {
        reserveStackNode* temp = top;
        top = top->next;
        delete temp;
        size--;
        return true;
    }
    else
        return false;
}

void ReserveStack::convert()
{
    if (top->typ == "prefix")
    {
        top->typ = "postfix";
        top->eq = prefixToPostfix(top->eq);
    }
    else
    {
        top->typ = "prefix";
        top->eq = postfixToPrefix(top->eq);
    }
}

string ReserveStack::prefixToPostfix(string eq)
{
    Stack stack;

    for (int i = eq.size() - 1; i >= 0; i--)
    {
        if (eq[i] == '*' || eq[i] == '/' || eq[i] == '+' || eq[i] == '-')
        {
            string one = stack.peek();
            stack.pop();
            string two = stack.peek();
            stack.pop();

            string temp = one + two + eq[i];

            stack.push(temp);
        }
        else
            stack.push(string(1, eq[i]));
    }

    return stack.peek();
}

string ReserveStack::postfixToPrefix(string eq)
{
    Stack stack;

    for (unsigned int i = 0; i < eq.size(); i++)
    {
        //Checks if the current letter is an operator or not
        if (eq[i] == '*' || eq[i] == '/' || eq[i] == '+' || eq[i] == '-')
        {
            string one = stack.pop();
            string two = stack.pop();
            string temp = eq[i] + two + one;
            stack.push(temp);
        }
        else
            stack.push(string(1, eq[i]));
    }
    string prefix = "";

    while (!(stack.isEmpty()))
        prefix += stack.pop();

    return prefix;
}

void ReserveStack::operator= (reserveStackNode* t) {
    top = t;
}