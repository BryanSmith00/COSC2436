#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

int main() {
	LinkedList prime; //Prime will be created head=0
	prime.addToFront("five");
	prime.addToFront("four");
	prime.addToFront("three");
	prime.addToFront("two");
	prime.addToFront("one");
	prime.addToEnd("six");

	prime.addAt(3, "ten");
	prime.addAt(1, "one hundred");
	prime.addAt(8, "ten thousand");
	prime.addAt(0, "negative ten");

	prime.print();
	cout << "Size of list: " << prime.getSize() << endl;

	cout << "Value removed: " << prime.removeFromFront() << endl;

	prime.print();
	cout << "Size of list: " << prime.getSize() << endl;

	cout << "Removed from end: " << prime.removeFromEnd() << endl << endl;
	prime.print();
}