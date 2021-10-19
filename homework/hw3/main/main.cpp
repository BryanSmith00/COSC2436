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
				
				if (list.getSize() >= 1)
					list.convertList(param);
			}
			else if (line.find("removeList") != string::npos)
			{
				getline(ss, temp, '(');
				getline(ss, param, ')');

				if (param == "postfix")
				{
					int i = 0;
					while (list.getNumPostfix() > 0)
					{
						if (list.at(i)->type == "postfix")
						{
							list.removeAt(i);
						}
						else
							i++;
					}
				}
				else if (param == "prefix")
				{
					int i = 0;
					while (list.getNumPrefix() > 0)
					{
						if (list.at(i)->type == "prefix")
						{
							list.removeAt(i);
						}
						else
							i++;
					}
				}
				else if (param == "all")
				{
					while (list.getSize() > 0)
					{
						list.removeFromFront();
					}
				}
				else //Param must be a position
				{
					int pos = stoi(param);

					if (pos <= 0)
					{
						list.removeFromFront();
					}
					else if (pos >= list.getSize())
					{

					}
					else
					{
						list.removeAt(pos);
					}

				}
			}
			else if (line == "printList")
			{
				output << "List:" << endl; list.print(output); output << endl;
			}
			else if (line == "printListBackwards")
			{
				output << "Reversed List:" << endl; list.printRev(output); output << endl;
			}
			else if (line.find("pushReserve") != string::npos)
			{
				getline(ss, temp, '(');
				getline(ss, param, ')');

				if (param == "postfix")
				{
					int i = 0;
					while (list.getNumPostfix() > 0)
					{
						if (list.at(i)->type == "postfix")
						{
							stack.push(list.at(i)->type, list.at(i)->equation);
							list.removeAt(i);
						}
						else
							i++;
					}
				}
				else if (param == "prefix")
				{
					int i = 0;
					while (list.getNumPrefix() > 0)
					{
						if (list.at(i)->type == "prefix")
						{
							stack.push(list.getHead()->type, list.getHead()->equation);
							list.removeAt(i);
						}
						else
							i++;
					}
				}
				else if (param == "all")
				{
					int size = list.getSize();

					while(list.getSize() > 0)
					{
						stack.push(list.getHead()->type, list.getHead()->equation);
						list.removeFromFront();
					}
				}
				else //Param must be a position
				{
					int pos = stoi(param);

					if (pos <= 0)
					{
						if (list.getSize() >= 1)
						{
							stack.push(list.at(0)->type, list.at(0)->equation);
							list.removeAt(0);
						}
					}
					else if (pos >= list.getSize())
					{

					}
					else 
					{
						stack.push(list.at(pos)->type, list.at(pos)->equation);
						list.removeAt(pos);
					}
				}


			}
			else if (line.find("popReserve") != string::npos)
			{ 
				getline(ss, temp, '(');
				getline(ss, param, ')');
				int pos = stoi(param);

				if (stack.getSize() >= 1)
				{
					if (pos <= 0)
						list.addToFront(stack.peek()->typ, stack.peek()->eq);
					else if (pos >= list.getSize())
						list.addToEnd(stack.peek()->typ, stack.peek()->eq);
					else
						list.addAt(pos, stack.peek()->typ, stack.peek()->eq);

					stack.pop();
				}
			}
			else if (line == "flipReserve")
			{
				ReserveStack temp;
				int size = stack.getSize();

				for (int i = 0; i < size; i++)
				{
					temp.push(stack.peek()->typ, stack.peek()->eq);
					stack.pop();
				}

				stack.setSize(temp.getSize());
				stack = temp.getTop();
			}
			else if (line == "printReserveSize")
			{
				output << "Reserve Size: " << stack.getSize() << endl << endl;
			}
			else if (line == "convertReserve")
			{
				if(stack.getSize() >= 1)
					stack.convert();
			}
			else if (line == "printReserveTop")
			{
				if (stack.getSize() >= 1)
				{
					output << "Top of Reserve: " << stack.peek()->typ << ":" << stack.peek()->eq << endl << endl;
				}
				else
				{
					output << "Top of Reserve: EMPTY" << endl << endl;
				}
			}
			else if (line.find("emptyReserve") != string::npos)
			{
				getline(ss, temp, '(');
				getline(ss, param, ')');
				int pos = stoi(param);

				while (stack.getSize() != 0)
				{
					if (pos <= 0)
						list.addToFront(stack.peek()->typ, stack.peek()->eq);
					else if (pos >= list.getSize())
						list.addToEnd(stack.peek()->typ, stack.peek()->eq);
					else
						list.addAt(pos, stack.peek()->typ, stack.peek()->eq);

					stack.pop();
				}
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