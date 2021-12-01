#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include "ArgumentManager.h"
#include "avl.h"
using namespace std;

void ReadInputFile(string, Node*);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	Node* root;
	root = nullptr;

	ifstream inputFile(input);
	string num;

	if (inputFile)
	{
		inputFile >> num;

		while (!inputFile.eof())
		{
			string temp;
			inputFile >> temp;
			root = insert(root, stoi(temp));
		}

		ofstream outputFile(output);
		LevelOrder(root, outputFile);
	}
}