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
void reverse(string& encodedID, int low, int high);
string decode2(string& encodedID, int low, int high);
string RemoveSpace(string word);
bool checkForMultipleSets(string ID);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	//Temporary, delete this when uploading
	input = "input13.txt";
	output = "output13.txt";

	LinkedList encodedBar1;
	LinkedList encodedBar2;

	LinkedList decodedBar1;
	LinkedList decodedBar2;

	LinkedList guilty;
	LinkedList innocent;

	readInputFile(input, encodedBar1, encodedBar2);

	for (int i = 0; i < encodedBar1.getSize(); i++)
	{
		string encodedID = encodedBar1.at(i, encodedBar1.getHead());
		string decodedID = decode2(encodedID, encodedID.find_last_of('('), encodedID.find(')'));
		decodedBar1.addToEnd(decodedID, decodedBar1.getHead());
	}

	for (int i = 0; i < encodedBar2.getSize(); i++)
	{
		string encodedID = encodedBar2.at(i, encodedBar2.getHead());
		string decodedID = decode2(encodedID, encodedID.find_last_of('('), encodedID.find(')'));
		decodedBar2.addToEnd(decodedID, decodedBar2.getHead());
	}


	//Sorting the decodedIDs into the guilty and innocent lists
	//Needs work
	//This nested loop finds all of the duplicate IDs and marks them guilty
	for (int i = 0; i < decodedBar1.getSize(); i++)
	{
		for (int j = 0; j < decodedBar2.getSize(); j++)
		{
			if (decodedBar1.at(i, decodedBar1.getHead()) == decodedBar2.at(j, decodedBar2.getHead()))
				guilty.addToEnd(decodedBar1.at(i, decodedBar1.getHead()), guilty.getHead());
		}
	}

	for (int i = 0; i < decodedBar1.getSize(); i++)
		if (!guilty.contains(decodedBar1.at(i, decodedBar1.getHead()), guilty.getHead()))
			innocent.addToEnd(decodedBar1.at(i, decodedBar1.getHead()), innocent.getHead());

	for (int i = 0; i < decodedBar2.getSize(); i++)
		if (!guilty.contains(decodedBar2.at(i, decodedBar2.getHead()), guilty.getHead()))
			innocent.addToEnd(decodedBar2.at(i, decodedBar2.getHead()), innocent.getHead());


	for (int i = 0; i < guilty.getSize(); i++)
	{
		for (int j = 0; j < guilty.getSize() - i - 1; j++)
		{
			if (guilty.at(j, guilty.getHead()) > guilty.at(j + 1, guilty.getHead()))
				guilty.swap(j, j + 1);
		}
	}

	for (int i = 0; i < innocent.getSize(); i++)
	{
		for (int j = 0; j < innocent.getSize() - i - 1; j++)
		{
			if (innocent.at(j, innocent.getHead()) > innocent.at(j + 1, innocent.getHead()))
				innocent.swap(j, j + 1);
		}
	}

	guilty.print();
	cout << endl;
	innocent.print();

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
	//low++;
	//high--;
	while (low < high)
	{
		char temp = encodedID[low];
		encodedID[low] = encodedID[high];
		encodedID[high] = temp;
		low++;
		high--;
	}
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