#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
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
        cout << "Value of head: " << head->word << endl;
        cout << "Value of tail: " << tail->word << endl;
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

string LinkedList::removeFromEnd() {

    if (head == nullptr) {
        return "";
    }
    else {
        Node* curr = head;
        Node* prev;

        while (curr->next != tail) {
            prev = curr;
            curr = curr->next;
        }
        string value = curr->next->word;
        tail = curr;
        tail->next = nullptr;
        delete curr->next;

        size--;
        return value;
    }
}

string LinkedList::removeAt(int index) {

    if (head == nullptr) {
        return "";
    }
    else {



        size--;
    }
}