#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Stack.h"
using namespace std;

LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

//Returns pointer to the head node
Node* LinkedList::getHead() { return head; }

//Returns pointer to tail node
Node* LinkedList::getTail() { return tail; }

bool LinkedList::isEmpty() { return head == nullptr; }

int LinkedList::getSize() { return size; }

//----------------------------------
//Need to implement this recursively
//----------------------------------
void LinkedList::print()
{
	Node* curr = head;
	while (curr != nullptr)
	{
		cout << curr->id << endl;
		curr = curr->next;
	}
}

void LinkedList::addToFront(string id)
{
	Node* tmp = new Node(id);

	if (isEmpty())
	{
		head = tmp;
		tail = head;
	}
	else
	{
		tmp->next = head;
		head = tmp;
	}
	size++;
}

bool LinkedList::addToEnd(string id, Node* h)
{
	if (h == nullptr) 
	{
		addToFront(id);
		return true;
	}
	else if (h->next == nullptr)
	{
		Node* tmp = new Node(id);
		h->next = tmp;
		tail = h->next;
		size++;

		return true;
	}
	else
		addToEnd(id, h->next);

	return false;
}

string LinkedList::at(int index, Node* h)
{
	if (index == 0)
	{
		string temp = h->id;
		return temp;
	}
	else
		return at(--index, h->next);
}

bool LinkedList::contains(string ID, Node* h)
{
	if (size == 0) {
		return false;
	}

	if (h->id == ID) {
		return true;
	}
	else if (h->next == nullptr)
	{
		return false;
	}
	else
		return contains(ID, h->next);
}

void LinkedList::changeValue(int index, string data, Node* h) 
{
	if (index == 0)
	{
		h->id = data;
		return;
	}
	else
		return changeValue(--index, data, h->next);
}

void LinkedList::swap(int index1, int index2) 
{
	string data1 = at(index1, head);
	string data2 = at(index2, head);

	this->changeValue(index1, data2, head);
	this->changeValue(index2, data1, head);
}