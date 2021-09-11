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

bool LinkedList::removeAt(int index) {

    if (head == nullptr) {
        return false;
    }
    else {

        Node* curr = head;

        for (int i = 0; i < index - 1; i++)
        {
            curr = curr->next;
        }
        Node* prev = curr;
        curr = curr->next;
        prev->next = curr->next;
        delete curr;

        size--;
        return true;
    }
}

string LinkedList::at(int index) {
    Node* curr = new Node;
    curr = head;

    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr->word;
}

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

void LinkedList::changeValue(int index, string data) {
    Node* curr = head;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    curr->word = data;
}

void LinkedList::swap(int index1, int index2) {
    string data1 = this->at(index1);
    string data2 = this->at(index2);

    this->changeValue(index1, data2);
    this->changeValue(index2, data1);
    /*
    Node* curr = head;
    Node* temp = new Node;
    Node* start = new Node;

    for (int i = 0; i < index1 - 1; i++)
    {
        curr = curr->next;
    }

    if (index1 == 0) {

    }
    else {

    }*/
}

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