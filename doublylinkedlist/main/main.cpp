#include <iostream>
#include <string>
#include "dll.h"

using namespace std;

int main() {

    DoublyLinkedList data;

    data.addToFront("one");
    data.addToEnd("two");
    data.addToEnd("three");
   

    data.print();

    return 0;
}