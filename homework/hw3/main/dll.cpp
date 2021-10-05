#include <iostream>
#include <string>
#include "dll.h"
#include "stack.h"
using namespace std;

DoublyLinkedList::DoublyLinkedList() 
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

const Node* DoublyLinkedList::getTail() 
{
    return tail;
}

bool DoublyLinkedList::isEmpty() 
{
    return head == nullptr;
}

int DoublyLinkedList::getSize()
{
    return size;
}

bool DoublyLinkedList::print()
{
    Node* cu = head;
    if (head == nullptr) 
    {
        cout << "EMPTY" << endl;
        return false;
    }
    else 
    {
        while (cu != nullptr) 
        {
            //Print out the current value
            cout << cu->type << ":" << cu->equation << endl;

            //Move the pointer forward 1
            cu = cu->next;
        }
        return true;
    }
}

bool DoublyLinkedList::print(ofstream& output)
{
    Node* cu = head;
    if (head == nullptr)
    {
        output << "EMPTY" << endl;
        return false;
    }
    else
    {
        while (cu != nullptr)
        {
            //Print out the current value
            output << cu->type << ":" << cu->equation << endl;

            //Move the pointer forward 1
            cu = cu->next;
        }
        return true;
    }
}

bool DoublyLinkedList::printRev() 
{
    Node* cu = tail;
    if (head == nullptr)
    {
        cout << "EMPTY" << endl;
        return false;
    }
    else
    {
        while (cu != nullptr)
        {
            //Print out the current value
            cout << cu->type << ":" << cu->equation << endl;

            //Move the pointer forward 1
            cu = cu->prev;
        }
        return true;
    }
}

bool DoublyLinkedList::printRev(ofstream& output)
{
    {
        Node* cu = tail;
        if (head == nullptr)
        {
            output << "EMPTY" << endl;
            return false;
        }
        else
        {
            while (cu != nullptr)
            {
                //Print out the current value
                output << cu->type << ":" << cu->equation << endl;

                //Move the pointer forward 1
                cu = cu->prev;
            }
            return true;
        }
    }
}

//Appends a node to the front of the linked list
void DoublyLinkedList::addToFront(string t, string e) 
{
    //Create a node
    Node* tmp = new Node(t, e);

    //Link node to Linked list
    if (head == 0) 
    {
        head = tmp;
        tail = head;
    }
    else
    {
        tmp->next = head;
        head = tmp;
        head->next->prev = head;
    }
    size++;
}

void DoublyLinkedList::addToEnd(string t, string e) 
{

    //Create a node
    Node* tmp = new Node(t, e);

    if (head == 0) 
    {
        addToFront(t, e);
    }
    else
    {
        Node* cu = head;

        while (cu->next != 0)
        {
            cu = cu->next;
        }

        tmp->prev = cu;
        cu->next = tmp;
        tail = cu->next;
        size++;
    }
}

//Deletes the first node if it exists
bool DoublyLinkedList::removeFromFront() {

    if (head == nullptr) {
        return false;
    }
    else {
        Node* temp = head;

        head = head->next;
        head->prev = nullptr;
        delete temp;
        size--;

        return true;
    }
}

//Deletes the last node of the list if it exists
bool DoublyLinkedList::removeFromEnd() {

    if (head == nullptr) {
        return false;
    }
    else if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return true;
    }
    else {
        Node* curr = head;

        while (curr->next->next != nullptr) {
            curr = curr->next;
        }
        delete curr->next;
        curr->next = nullptr;
        tail = curr;

        size--;
        return true;
    }
}

//Deletes the node at a specified index
bool DoublyLinkedList::removeAt(int index) {

    if (index == 0) {
        this->removeFromFront();
        return true;
    }
    else if (head == nullptr || index < 0 || index >= size) {
        return false;
    }
    else if (index == size - 1) {
        this->removeFromEnd();
        return true;
    }
    else {

        Node* curr = head;

        for (int i = 0; i < index - 1; i++)
        {
            curr = curr->next;
        }

        Node* toDelete = curr->next;
        curr->next = toDelete->next;
        delete toDelete;

        size--;
        return true;
    }
}

//Returns the pointer to the node at index provided
Node* DoublyLinkedList::at(int index) 
{
    Node* curr = new Node;
    curr = head;

    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr;
}

void DoublyLinkedList::convertList(string param) 
{
    if (param == "prefix")
    {
        for (int i = 0; i < size; i++)
        {
            if (this->at(i)->type == "prefix")
            {
                this->at(i)->equation = prefixToPostfix(this->at(i)->equation);
                this->at(i)->type = "postfix";
            }
        }
    }
    else if (param == "postfix")
    {
        for (int i = 0; i < size; i++)
        {
            if (this->at(i)->type == "postfix")
            {
                this->at(i)->equation = postfixToPrefix(this->at(i)->equation);
                this->at(i)->type = "prefix";
            }
        }
    }
    else if (param == "all")
    {
        for (int i = 0; i < size; i++)
        {
            if (this->at(i)->type == "postfix")
            {
                this->at(i)->equation = postfixToPrefix(this->at(i)->equation);
                this->at(i)->type = "prefix";
            }
            else
            {
                this->at(i)->equation = prefixToPostfix(this->at(i)->equation);
                this->at(i)->type = "postfix";
            }
        }
    }
    else
    {
        int position = stoi(param);

        if (position <= 0)
        {
            //Modify first node
            if (this->at(position)->type == "prefix")
            {
                this->at(0)->equation = prefixToPostfix(this->at(0)->equation);
                this->at(0)->type = "postfix";
            }
            else
            {
                this->at(0)->equation = postfixToPrefix(this->at(0)->equation);
                this->at(0)->type = "prefix";
            }
        }
        else if (position >= size)
        {
            return;
        }
        else 
        {
            if (this->at(position)->type == "prefix")
            {
                this->at(position)->equation = prefixToPostfix(this->at(position)->equation);
                this->at(position)->type = "postfix";
            }
            else
            {
                this->at(position)->equation = postfixToPrefix(this->at(position)->equation);
                this->at(position)->type = "prefix";
            }
        }
    }
}

void DoublyLinkedList::removeList(string param)
{
    if (param == "prefix")
    {
        for (int i = 0; i < size; i++)
        {
            if (this->at(i)->type == "prefix")
            {
                this->removeAt(i);
            }
        }
    }
    else if (param == "postfix")
    {
        for (int i = 0; i < size; i++)
        {
            if (this->at(i)->type == "postfix")
            {
                this->removeAt(i);
            }
        }
    }
    else if (param == "all")
    {
        for (int i = 0; i < size; i++)
            this->removeAt(i);
    }
    else
    {
        int position = stoi(param);

        if (position <= 0)
        {
            this->removeFromFront();
        }
        else if (position >= size)
        {
            return;
        }
        else
            this->removeAt(position);
    }
}

string DoublyLinkedList::prefixToPostfix(string eq)
{
    Stack stack;

    for (int i = eq.size() - 1; i >= 0; i--)
    {
        if (eq[i] == '*' || eq[i] == '/' || eq[i] == '+' || eq[i] == '-')
        {
            string one = stack.pop();
            string two = stack.pop();

            string temp = eq[i] + one + two;

            stack.push(temp);
        }
        else 
            stack.push(string(1, eq[i]));
    }

    return stack.peek();
}

string DoublyLinkedList::postfixToPrefix(string eq)
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

/* Test

bool DoublyLinkedList::addAt(int index, string word) {
    Node* temp = new Node(word);
    Node* curr = new Node;
    curr = head;

    if (index < 0)
        return false;

    //If the List is empty or the index specified is 0, adds te node to the beginning of the list
    if (head == nullptr || index == 0) {
        addToFront(word);
    }

    //If the index is within the list iterate to the correct position and add the new node
    else if (index >= 0 && index <= size - 1) {
        for (int i = 0; i < index - 1; i++)
        {
            curr = curr->next;
        }
        temp->next = curr->next;
        curr->next = temp;
        size++;
    }

    //If the user tries to add beyond the endd of the list it appends it to the end with the AddToEndfunction
    else if (index > size - 1) {
        addToEnd(word);
    }
    return true;
}

//Checks if any node in the linked list contains the specified string
bool DoublyLinkedList::contains(string sentence) {
    Node* curr = head;

    for (int i = 0; i < size; i++)
    {
        if (curr->word == sentence)
            return true;

        curr = curr->next;
    }
    return false;
}

//Given an index and a new value changes the value of a node
void DoublyLinkedList::changeValue(int index, string data) {
    Node* curr = head;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    curr->word = data;
}

//Swaps the values of two nodes, useful for bubble sort
void DoublyLinkedList::swap(int index1, int index2) {
    string data1 = this->at(index1);
    string data2 = this->at(index2);

    this->changeValue(index1, data2);
    this->changeValue(index2, data1);
}

//Sorts the Linked List alphabetically
void DoublyLinkedList::sort() {
    for (int i = 0; i < this->getSize() - 1; i++) {
        for (int j = 0; j < this->getSize() - i - 1; j++) {
            if (this->at(j) > this->at(j + 1))
            {
                this->swap(j, j + 1);
            }
        }
    }
}

//Sorts the Linked List based on the leangth of each element
void DoublyLinkedList::sortLength() {
    for (int i = 0; i < this->getSize() - 1; i++) {
        for (int j = 0; j < this->getSize() - i - 1; j++) {
            if (this->at(j).length() > this->at(j + 1).length())
            {
                this->swap(j, j + 1);
            }
        }
    }
}

*/