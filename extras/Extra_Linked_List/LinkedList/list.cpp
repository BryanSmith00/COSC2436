#include "list.h"
#include <iostream>
using namespace std;

list::list() {
    head = nullptr;
}

nb* list::gethead() {
    return head;
}

void list::insertatbeg(int value) {

    //Create a node
    nb* tmp = new nb;

    //Fill node
    tmp->n = value;
    tmp->next = nullptr;

    //Link node to list
    if (head == 0) {
        head = tmp;
    }
    else {
        tmp->next = head;
        head = tmp;
    }

}

void list::print() {
    nb* cu = head;

    while (cu != nullptr) {
        //Print out the current value
        cout << cu->n << endl;

        //Move the pointer forward 1
        cu = cu->next;
    }
}

void list::insertatend(int value) {

    //Create a node
    nb* tmp = new nb;

    //Fill node
    tmp->n = value;
    tmp->next = nullptr;

    nb* cu = head;

    while (cu->next != 0) {
        cu = cu->next;
    }

    cu->next = tmp;
}