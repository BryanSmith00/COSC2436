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

struct ComparePriority {
	bool operator()(node const& p1, node const& p2) {
		return p1.priority > p2.priority;
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

	input = "input41.txt";
	output = "output41.txt";

	priority_queue<node, vector<node>, ComparePriority> pq;
	queue<string> q;
	ifstream inputFile(input);
	string temp;

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
			pq.push(a1);
		}
	}

	//All commands should be in pq ordered correctly 
	// this loop extracts the commands and executes them in order
	while (!pq.empty())
	{
		string command = pq.top().command;
		stringstream ss(command);
		string garbage = "";

		if (command.find("DECODE") != string::npos)
		{
			string message = command.substr(command.find('[') + 1, (command.find(']') - command.find('[') - 1));
			q.push(message);
		}
		else if (command.find("REPLACE") != string::npos)
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
		else if (command.find("ADD") != string::npos)
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
		else if (command.find("REMOVE") != string::npos)
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
		else if (command.find("SWAP") != string::npos)
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
		else if (command.find("PRINT") != string::npos)
		{
			string message = q.front();
			q.pop();
			cout << message << endl;
		}

		pq.pop();
	}
	

}