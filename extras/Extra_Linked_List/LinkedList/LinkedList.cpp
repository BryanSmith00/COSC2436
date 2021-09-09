#include <iostream>
#include "list.h"
using namespace std;

int main() {
	list prime; //Prime will be created head=0
	prime.insertatbeg(1);
	prime.insertatbeg(2);
	prime.insertatbeg(3);
	prime.insertatbeg(5);
	prime.insertatend(7);
	prime.insertatend(11);
	prime.insertatend(13);

	cout << "Printing out linked list normally" << endl;
	prime.print();

	cout << endl << "Printing recursively....." << endl;
	prime.printrec(prime.gethead());

	cout << endl << "Printing recursively in reverse order....." << endl;
	prime.printrec_rev(prime.gethead());
}