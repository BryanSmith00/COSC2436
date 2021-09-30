#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
#include "dll.h"
using namespace std;

void ReadInputFile(string inputFile, DoublyLinkedList& list);
string RemoveSpace(string word);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	//Temporary, delete this when uploading
	input = "input31.txt";
	command = "command31.txt";

	DoublyLinkedList list;

	ReadInputFile(input, list);

}

void ReadInputFile(string inputFile, DoublyLinkedList& list) 
{
	string type;
	string line;
	string equation;
	ifstream input(inputFile);

	if (input) 
	{
		while (!input.eof())
		{
			getline(input, line);

			if (line != "")
			{
				stringstream ss(line);

				//Reads the equation from the string stream line and removes all of the spaces
				getline(ss, type, ':');
				getline(ss, equation);
				equation = RemoveSpace(equation);

				if (type == "prefix")
				{

				}
				else if (type == "postfix")
				{

				}
			}
		}
	}

	input.close();
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