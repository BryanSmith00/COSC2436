#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "ArgumentManager.h"
#include "btree.h"
using namespace std;

void ReadCommandFile(vector<string>&, int&, string);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	input = "input51.txt";
	command = "command51.txt";
	output = "output51.txt";

	int degree = 0;
	vector<string> commands;

	ReadCommandFile(commands, degree, command);

}

void ReadCommandFile(vector<string>& commands, int& degree, string commandFile)
{
	ifstream command(commandFile);
	string line;
	getline(command, line);

	degree = stoi(line.substr(line.find('=') + 1));

	while (!command.eof())
	{
		string temp;
		getline(command, temp);
		commands.push_back(temp);
	}

	command.close();
}