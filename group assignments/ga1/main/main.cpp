//Disclaimer this code is way too messy becuse of my recursive 
// Linked List functions 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
#include "LinkedList.h"
#include "Stack.h"
using namespace std;

void readInputFile(string, LinkedList&, LinkedList&);
string decode(string);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	//Temporary, delete this when uploading
	input = "input11.txt";
	output = "output11.txt";

	LinkedList encodedBar1;
	LinkedList encodedBar2;

	LinkedList decodedBar1;
	LinkedList decodedBar2;

	readInputFile(input, encodedBar1, encodedBar2);

	encodedBar1.addToEnd("one", encodedBar1.getHead());
	encodedBar1.addToEnd("two", encodedBar1.getHead());

	cout << decode("10(01)");
	cout << decode("(01)10");

	//encodedBar1.addToEnd("three", encodedBar1.getHead());

	//cout << encodedBar1.at(3, encodedBar1.getHead());

	//Iterates through each encoded string in the list
	//	gets it, decodes it, and adds it to the decoded list
	//for (int i = 0; i < encodedBar1.getSize(); i++)
		//decodedBar1.addToEnd(encodedBar1.at(i, encodedBar1.getHead()), decodedBar1.getHead());

	//for (int i = 0; i < encodedBar2.getSize(); i++)
		//decodedBar2.addToEnd(decode(encodedBar2.at(i, encodedBar2.getHead())), decodedBar2.getHead());
	

}

void readInputFile(string inputFile, LinkedList& encodedBar1, LinkedList& encodedBar2)
{
	ifstream input(inputFile);
	string curr;
	string line;
	string temp;

	if (input)
	{
		while (!input.eof())
		{
			getline(input, temp);

			if (temp != "")
			{
				if (temp == "Bar1")
					curr = "Bar1";
				else if (temp == "Bar2")
					curr = "Bar2";

				if (curr == "Bar1" && temp != "Bar1" && temp != "Bar2")
				{
					encodedBar1.addToEnd(temp, encodedBar1.getHead());
				}
				else if (curr == "Bar2" && temp != "Bar1" && temp != "Bar2")
				{
					encodedBar2.addToEnd(temp, encodedBar2.getHead());
				}
			}
		}
	}
}

string decode(string encodedID)
{
	Stack stack;
	string temp;
	string finalProduct = "";
	string reversed = "";
	bool inParen = false;

	for (unsigned int i = 0; i < encodedID.size(); i++)
	{
		string temp = "";
		temp = encodedID[i];

		if (temp == "(" || inParen)
		{
			inParen = true;
			stack.push(temp);

			
		}
		else {
			finalProduct += temp;
		}
	}

	return finalProduct;
}