#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

const Score* LinkedList::getTail() {
    return tail;
}

bool LinkedList::isEmpty() {
    return head == nullptr;
}

int LinkedList::getSize() {
    return size;
}

bool LinkedList::print() {
    Score* cu = head;
    if (head == nullptr) {
        return false;
    }
    else {
        while (cu != nullptr) {
            //Print out the current value


            //Move the pointer forward 1
            cu = cu->next;
        }
        return true;
    }
}

//Appends a node to the front of the linked list
void LinkedList::addToFront(string name, double score) {

    //Create a node
    Score* tmp = new Score(name, score);

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

void LinkedList::addToEnd(string name, double score) {

    //Create a node
    Score* tmp = new Score(name, score);

    if (head == 0) {
        addToFront(name, score);
    }
    else {
        Score* cu = head;

        while (cu->next != 0) {
            cu = cu->next;
        }
        cu->next = tmp;
        tail = cu->next;
        size++;
    }
}

bool LinkedList::addAt(int index, string name, double score) {
    Score* temp = new Score(name, score);
    Score* curr = new Score;
    curr = head;

    if (index < 0)
        return false;

    //If the List is empty or the index specified is 0, adds te node to the beginning of the list
    if (head == nullptr || index == 0) {
        addToFront(name, score);
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
        addToEnd(name, score);
    }
    return true;
}

//Given an index and a new value changes the value of a node
void LinkedList::changeValue(int index, string name, double score) {
    Score* curr = head;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    curr->name = name;
    curr->score = score;
}

Score* LinkedList::at(int index) {
    Score* curr = new Score;
    curr = head;

    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr;
}

//Swaps the values of two nodes, useful for bubble sort
void LinkedList::swap(int index1, int index2) {
    Score* data1 = this->at(index1);
    Score* data2 = this->at(index2);

    this->changeValue(index1, data2->name, data2->score);
    this->changeValue(index2, data1->name, data1->score);
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
            if (this->at(j)->score < this->at(j + 1)->score)
            {
                this->swap(j, j + 1);
            }
        }
    }
}