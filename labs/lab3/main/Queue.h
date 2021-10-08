#include <iostream>
#include <string>
using namespace std;

struct Node
{
	string value;
	Node* next;
	Node() { next = nullptr; }
	Node(string v) { next = nullptr; value = v; }
};

class Queue
{
private:
	Node* front;
	Node* tail;
	int size;

public:
	Queue()
	{
		front = tail = nullptr;
		size = 0;
	}

	bool isEmpty()
	{
		return (front == nullptr && tail == nullptr);
	}

	int getSize()
	{
		return size;
	}

	Node* getFront()
	{
		return front;
	}

	void enqueue(string value)
	{
		Node* temp = new Node(value);

		if (isEmpty())
		{
			tail = temp;
			front = tail;
			size++;
		}
		else
		{
			tail->next = temp;
			tail = temp;
			size++;
		}
	}

	bool dequeue()
	{
		if (isEmpty())
		{
			return false;
		}
		else if (size == 1)
		{
			delete front;
			front = tail = nullptr;
			size--;
			return true;
		}
		else
		{
			Node* temp = new Node;

			temp = front;
			front = front->next;
			delete temp;
			size--;
			return true;
		}
	}

	void print()
	{
		Node* curr = front;

		while (curr != nullptr) 
		{
			cout << curr->value << " ";
			curr = curr->next;
		}
		cout << endl;
	}
};