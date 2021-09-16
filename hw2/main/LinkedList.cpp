#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

const Node* LinkedList::getTail() {
    return tail;
}

bool LinkedList::isEmpty() {
    return head == nullptr;
}

int LinkedList::getSize() {
    return size;
}

bool LinkedList::print() {
    Node* cu = head;
    if (head == nullptr) {
        return false;
    }
    else {
        while (cu != nullptr) {
            //Print out the current value
            cout << cu->word << endl;

            //Move the pointer forward 1
            cu = cu->next;
        }
        return true;
    }
}

//Appends a node to the front of the linked list
void LinkedList::addToFront(string word) {

    //Create a node
    Node* tmp = new Node(word);

    //Link node to LinkedList
    if (head == 0) {
        head = tmp;
        tail = head;
    }
    else {
        tmp->next = head;
        head = tmp;
    }
    size++;
}

void LinkedList::addToEnd(string word) {

    //Create a node
    Node* tmp = new Node(word);

    if (head == 0) {
        addToFront(word);
    }
    else {
        Node* cu = head;

        while (cu->next != 0) {
            cu = cu->next;
        }
        cu->next = tmp;
        tail = cu->next;
        size++;
    }
}

bool LinkedList::addAt(int index, string word) {
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

//Deletes the first node if it exists
string LinkedList::removeFromFront() {

    if (head == nullptr) {
        return "";
    }
    else {
        Node* temp = head;

        string value = temp->word;
        head = head->next;
        delete temp;
        size--;

        return value;
    }
}

//Deletes the last node of the list if it exists
bool LinkedList::removeFromEnd() {

    if (head == nullptr) {
        return false;
    }
    else if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return true;
    } else {
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
bool LinkedList::removeAt(int index) {

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
        //cout << "+---------+ Node to be deleted: " << toDelete->word << endl << endl;
        delete toDelete;

        size--;
        return true;
    }
}

//Returns the string value of the node at index passed in
string LinkedList::at(int index) {
    Node* curr = new Node;
    curr = head;

    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr->word;
}

//Checks if any node in the linked list contains the specified string
bool LinkedList::contains(string sentence) {
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
void LinkedList::changeValue(int index, string data) {
    Node* curr = head;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    curr->word = data;
}

//Swaps the values of two nodes, useful for bubble sort
void LinkedList::swap(int index1, int index2) {
    string data1 = this->at(index1);
    string data2 = this->at(index2);

    this->changeValue(index1, data2);
    this->changeValue(index2, data1);
}

//Sorts the Linked List alphabetically
void LinkedList::sort() {
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
void LinkedList::sortLength() {
    for (int i = 0; i < this->getSize() - 1; i++) {
        for (int j = 0; j < this->getSize() - i - 1; j++) {
            if (this->at(j).length() > this->at(j + 1).length())
            {
                this->swap(j, j + 1);
            }
        }
    }
}