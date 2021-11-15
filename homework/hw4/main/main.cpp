#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;

class node
{
public:
	string command;
	int priority;

	bool operator>(const node& rhs)
	{
		return priority > rhs.priority;
	}
};

string Replace(string message, string orig, string newChar)
{
	string newMessage = "";
	for (unsigned int i = 0; i < message.size(); i++)
	{
		string temp = "";
		temp += message[i];
		if ((temp == orig))
			newMessage += newChar;
		else
			newMessage += message[i];
	}
	return newMessage;
}

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	queue<string> q;
	ifstream inputFile(input);
	ofstream outputFile(output);
	string temp;

	queue<node> comms[10];

	while (!inputFile.eof())
	{
		getline(inputFile, temp);
		if (temp != "")
		{

			string num = temp.substr(temp.find('(') + 1);
			string noparen = "";

			for (unsigned int i = 0; i < num.size(); i++)
			{
				if (num[i] != ')')
					noparen += num[i];
			}

			node a1;
			a1.command = temp;
			a1.priority = stoi(noparen);

			switch (stoi(noparen))
			{
			case 1:
				comms[0].push(a1);
				break;
			case 2:
				comms[1].push(a1);
				break;
			case 3:
				comms[2].push(a1);
				break;
			case 4:
				comms[3].push(a1);
				break;
			case 5:
				comms[4].push(a1);
				break;
			case 6:
				comms[5].push(a1);
				break;
			case 7:
				comms[6].push(a1);
				break;
			case 8:
				comms[7].push(a1);
				break;
			case 9:
				comms[8].push(a1);
				break;
			case 10:
				comms[9].push(a1);
				break;
			}
		}
	}

	for (unsigned int i = 0; i < 10; i++)
	{
		while (!comms[i].empty())
		{
			string command = comms[i].front().command;
			stringstream ss(command);
			string garbage = "";

			if (command.find("DECODE") != string::npos)
			{
				string message = command.substr(command.find('[') + 1, (command.find(']') - command.find('[') - 1));
				q.push(message);
			}
			else if (command.find("REPLACE") != string::npos)
			{
				if (!q.empty())
				{
					string orig;
					string newChar;
					string message = q.front();
					q.pop();
					getline(ss, garbage, '[');
					getline(ss, orig, ',');
					getline(ss, newChar, ']');

					q.push(Replace(message, orig, newChar));
				}
			}
			else if (command.find("ADD") != string::npos)
			{
				if (!q.empty())
				{
					string message = q.front();
					q.pop();
					string orig;
					string newChar;
					string newMessage = "";
					getline(ss, garbage, '[');
					getline(ss, orig, ',');
					getline(ss, newChar, ']');

					for (unsigned int i = 0; i < message.size(); i++)
					{
						string temp = "";
						temp += message[i];
						if (temp == orig)
						{
							newMessage += message[i];
							newMessage += newChar;
						}
						else
						{
							newMessage += message[i];
						}
					}
					q.push(newMessage);
				}
			}
			else if (command.find("REMOVE") != string::npos)
			{
				if (!q.empty())
				{
					string toRemove;
					string message = q.front();
					q.pop();
					getline(ss, garbage, '[');
					getline(ss, toRemove, ']');
					string newMessage = "";

					for (unsigned int i = 0; i < message.size(); i++)
					{
						string temp = "";
						temp += message[i];
						if (temp != toRemove)
							newMessage += message[i];
					}
					q.push(newMessage);
				}
			}
			else if (command.find("SWAP") != string::npos)
			{
				if (!q.empty())
				{
					string orig;
					string newChar;
					string message = q.front();
					q.pop();
					string newMessage = "";
					getline(ss, garbage, '[');
					getline(ss, orig, ',');
					getline(ss, newChar, ']');

					for (unsigned i = 0; i < message.size(); i++)
					{
						string temp = "";
						temp += message[i];
						if (temp == orig)
							newMessage += newChar;
						else if (temp == newChar)
							newMessage += orig;
						else
							newMessage += message[i];
					}
					q.push(newMessage);
				}
			}
			else if (command.find("PRINT") != string::npos)
			{
				if (!q.empty())
				{
					string message = q.front();
					q.pop();
					outputFile << message << endl;
				}
			}

			if(!comms[i].empty())
				comms[i].pop();
		}
	}
}