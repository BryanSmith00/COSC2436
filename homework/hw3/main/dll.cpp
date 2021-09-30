#include <iostream>
#include <string>
#include "dll.h"
using namespace std;

DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

const Node* DoublyLinkedList::getTail() {
    return tail;
}

bool DoublyLinkedList::isEmpty() {
    return head == nullptr;
}

int DoublyLinkedList::getSize() {
    return size;
}

bool DoublyLinkedList::print() {
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
void DoublyLinkedList::addToFront(string word) {

    //Create a node
    Node* tmp = new Node(word);

    //Link node to Linked list
    if (head == 0) {
        head = tmp;
        tail = head;
    }
    else {
        tmp->next = head;
        head = tmp;
        head->next->prev = head;
    }
    size++;
}

void DoublyLinkedList::addToEnd(string word) {

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

        tmp->prev = cu;
        cu->next = tmp;
        tail = cu->next;
        size++;
    }
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

//Deletes the first node if it exists
string DoublyLinkedList::removeFromFront() {

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
        //cout << "+---------+ Node to be deleted: " << toDelete->word << endl << endl;
        delete toDelete;

        size--;
        return true;
    }
}

//Returns the string value of the node at index passed in
string DoublyLinkedList::at(int index) {
    Node* curr = new Node;
    curr = head;

    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr->word;
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