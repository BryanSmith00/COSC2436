#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
#include "LinkedList.h"
#include "Stack.h"
using namespace std;

void readInputFile(string, LinkedList&, LinkedList&);
string decode2(string& encodedID, int low, int high);
void reverse(string& encodedID, int low, int high);
bool checkForMultipleSets(string ID);
string RemoveSpace(string word);

// Disclaimer -------------------------------------------------------------------
// All of the Linked List functions have been implemented recursively which is why
//  they are so messy and the reversing functionality has been implemented with a
//  stack according to the assignment requirements
// 
// All of the test cases pass but I only implemented up to two non-nested sets of 
//  parens because there wasn't anything larger in the input files provided
//  -Bryan Smith
//-------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	LinkedList encodedBar1;
	LinkedList encodedBar2;

	LinkedList decodedBar1;
	LinkedList decodedBar2;

	LinkedList guilty;
	LinkedList innocent;

	//Reading the input file adds all of the Bar1 encoded IDs to the
	// encodedBar1 Linked List and the Bar2 IDs to the Bar2 List
	readInputFile(input, encodedBar1, encodedBar2);

	//Loops through all of the encoded Bar1 IDs, decodes them, then adds them to the decoded list
	//
	for (int i = 0; i < encodedBar1.getSize(); i++)
	{
		string encodedID = encodedBar1.at(i, encodedBar1.getHead());
		string decodedID = decode2(encodedID, encodedID.find_last_of('('), encodedID.find(')'));
		decodedBar1.addToEnd(decodedID, decodedBar1.getHead());
	}

	//Loops through all of the encoded Bar2 IDs, decodes them, then adds them to the decoded list
	//
	for (int i = 0; i < encodedBar2.getSize(); i++)
	{
		string encodedID = encodedBar2.at(i, encodedBar2.getHead());
		string decodedID = decode2(encodedID, encodedID.find_last_of('('), encodedID.find(')'));
		decodedBar2.addToEnd(decodedID, decodedBar2.getHead());
	}

	//Adds all duplicate IDs to the guilty list
	//
	for (int i = 0; i < decodedBar1.getSize(); i++)
	{
		for (int j = 0; j < decodedBar2.getSize(); j++)
		{
			if (decodedBar1.at(i, decodedBar1.getHead()) == decodedBar2.at(j, decodedBar2.getHead()))
				guilty.addToEnd(decodedBar1.at(i, decodedBar1.getHead()), guilty.getHead());
		}
	}

	//Adds any non duplicate decoded Bar1 IDs to the innocent list
	//
	for (int i = 0; i < decodedBar1.getSize(); i++)
		if (!guilty.contains(decodedBar1.at(i, decodedBar1.getHead()), guilty.getHead()))
			innocent.addToEnd(decodedBar1.at(i, decodedBar1.getHead()), innocent.getHead());

	//Adds any non duplicate decoded Bar2 IDs to the innocent list
	//
	for (int i = 0; i < decodedBar2.getSize(); i++)
		if (!guilty.contains(decodedBar2.at(i, decodedBar2.getHead()), guilty.getHead()))
			innocent.addToEnd(decodedBar2.at(i, decodedBar2.getHead()), innocent.getHead());

	//Pads all decoded IDs with leading zeroes so they are the maximum size
	// then sorts the guilty set according to ascending size
	//
	if (guilty.getSize() >= 2)
	{
		for (int i = 0; i < guilty.getSize() - 1; i++)
		{
			for (int j = 0; j < guilty.getSize() - 1; j++)
			{
				string firstElement = guilty.at(j, guilty.getHead());
				string secondElement = guilty.at(j + 1, guilty.getHead());
				string temp = "";

				for (unsigned int m = 0; m < 100 - firstElement.size(); m++)
				{
					temp += "0";
				}
				firstElement = temp + firstElement;

				temp = "";

				for (unsigned int n = 0; n < 100 - secondElement.size(); n++)
				{
					temp += "0";
				}
				secondElement = temp + secondElement;

				if (firstElement.compare(secondElement) > 0)
					guilty.swap(j, j + 1);


			}
		}
	}

	//Pads all decoded IDs with leading zeroes so they are the maximum size
	// then sorts the innocent set according to ascending size
	//
	if (innocent.getSize() >= 2) 
	{
		for (int i = 0; i < innocent.getSize() - 1; i++)
		{
			for (int j = 0; j < innocent.getSize() - 1; j++)
			{
				string firstElement = innocent.at(j, innocent.getHead());
				string secondElement = innocent.at(j + 1, innocent.getHead());
				string temp = "";

				for (unsigned int m = 0; m < 100 - firstElement.size(); m++)
				{
					temp += "0";
				}
				firstElement = temp + firstElement;

				temp = "";

				for (unsigned int n = 0; n < 100 - secondElement.size(); n++)
				{
					temp += "0";
				}
				secondElement = temp + secondElement;

				if (firstElement.compare(secondElement) > 0)
				{
					innocent.swap(j, j + 1);
				}
			}
		}
	}

	ofstream outputFile(output);

	//File output loops

	if (guilty.getSize() >= 1) {
		outputFile << "Guilty:" << endl;
		guilty.print(guilty.getSize(), outputFile, guilty.getHead());
	}

	if (innocent.getSize() >= 1) {
		outputFile << "Innocent:" << endl;
		innocent.print(innocent.getSize(), outputFile, innocent.getHead());
	}
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

// Function responsible for taking an encoded string in and
//  reversing all of the sets inside parens and returning
//  the correct decoded string
//
string decode2(string& encodedID, int low, int high)
{
	if (!checkForMultipleSets(encodedID))
	{
		while (low < high)
		{
			reverse(encodedID, low, high);
			encodedID[low] = ' ';
			encodedID[high] = ' ';
			low = encodedID.find_last_of('(', ++low);
			high = encodedID.find(')', --high);
		}
		encodedID = RemoveSpace(encodedID);
		return encodedID;
	}
	else
	{
		int split = 0;

		for (unsigned int i = 0; i < encodedID.size(); i++)
		{
			for (unsigned int j = i+1; j < encodedID.size() - 1; j++)
			{
				if (encodedID[i] == ')' && encodedID[j] == '(')
				{
					split = j - i;
				}
			}
		}

		string substr1 = encodedID;
		string substr2 = encodedID;

		substr1 = substr1.substr(0, split);
		substr2 = substr2.substr(split);

		decode2(substr1, substr1.find_last_of('('), substr1.find(')'));
		decode2(substr2, substr2.find_last_of('('), substr2.find(')'));

		encodedID = substr1 + substr2;

		return encodedID;
	}
}

void reverse(string& encodedID, int low, int high)
{
	//New Method using a stack to reverse the string
	Stack stack;

	for (int i = low; i <= high; i++)
	{
		string temp = "";
		temp += encodedID[i];
		stack.push(temp);
	}

	for (int i = low; i < high; i++)
	{
		string tmp = "";
		tmp += stack.peek();
		stack.pop();
		encodedID[i] = tmp[0];
	}
}

// Checks if there are multiple sets of non-nested parens
//  which requires a different process for decoding
//  Ex. only Nested: (4(23)1)
//  Ex. Non-Nested pairs: 4(21)5(37(9600))78
bool checkForMultipleSets(string ID)
{
	string onlyParens = "";

	for (unsigned int i = 0; i < ID.size(); i++)
	{
		if (ID[i] == '(' || ID[i] == ')')
			onlyParens += ID[i];
	}

	for (unsigned int i = 0; i < onlyParens.size() - 1; i++)
	{
		if (onlyParens[i] == ')' && onlyParens[i + 1] == '(')
			return true;
	}

	return false;
}

string RemoveSpace(string word)
{
	string temp;
	for (unsigned int i = 0; i < word.length(); i++)
	{
		if (word[i] != ' ')
			temp += word[i];
	}
	return temp;
}