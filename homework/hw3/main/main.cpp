#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
#include "dll.h"
#include "stack.h"
#include "reservestack.h"
using namespace std;

void readInputFile(string inputFile, DoublyLinkedList& list, ReserveStack& reserveStack);
void readCommandFile(string commandFile, string outputFile, DoublyLinkedList& list, ReserveStack& stack);
string RemoveSpace(string word);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	//Temporary, delete this when uploading
	//input = "input32.txt";
	//command = "command32.txt";
	//output = "ans32.txt";

	DoublyLinkedList list;
	ReserveStack reserveStack;

	readInputFile(input, list, reserveStack);
	readCommandFile(command, output, list, reserveStack);

}

void readInputFile(string inputFile, DoublyLinkedList& list, ReserveStack& reserveStack) 
{
	string type;
	string line;
	string equation;
	ifstream input(inputFile);

	if (input) 
	{
		//This will read all valid input lines from the file and add them to the Doubly Linked List
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

				list.addToEnd(type, equation);
				reserveStack.push(type, equation);
			}
		}
	}

	input.close();
}

void readCommandFile(string commandFile, string outputFile, DoublyLinkedList& list, ReserveStack& stack)
{
	string line;
	string temp;
	string param;
	ifstream command(commandFile);
	ofstream output(outputFile);

	if (command)
	{
		//This will read all valid input lines from the file and add them to the Doubly Linked List
		while (!command.eof())
		{
			getline(command, line);
			stringstream ss(line);

			if (line.find("convertList") != std::string::npos) 
			{
				getline(ss, temp, '(');
				getline(ss, param, ')');
				
				list.convertList(param);
			}
			else if (line.find("removeList") != string::npos)
			{
				getline(ss, temp, '(');
				getline(ss, param, ')');

				list.removeList(param);
			}
			else if (line == "printList")
			{
				cout << "List:" << endl; list.print(); cout << endl;
				output << "List:" << endl; list.print(output); output << endl;
			}
			else if (line == "printListBackwards")
			{
				cout << "Reversed List:" << endl; list.printRev(); cout << endl;
				output << "Reversed List:" << endl; list.printRev(output); output << endl;
			}
			else if (line.find("pushReserve") != string::npos)
			{

			}
			else if (line.find("popReserve") != string::npos)
			{

			}
			else if (line.find("flipReserve") != string::npos)
			{

			}
			else if (line.find("printReserveSize") != string::npos)
			{

			}
			else if (line.find("convertReserve") != string::npos)
			{

			}
			else if (line.find("printReserveTop") != string::npos)
			{

			}
			else if (line.find("emptyReserve") != string::npos)
			{

			}
			
		}
	}

	command.close();
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