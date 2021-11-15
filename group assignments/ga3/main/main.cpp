#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ArgumentManager.h"
#include "bst.h"
using namespace std;

void readInputFile(bst&, string);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	bst tree;
	tree.setRoot();
	
	readInputFile(tree, input);

	ofstream outputFile(output);
	tree.preOrder(tree.getRoot(), "x", outputFile);

	outputFile.close();
}

void readInputFile(bst &tree, string inputFile)
{
	ifstream input(inputFile);

	while (!input.eof())
	{
		int num;
		input >> num;
		
		if (tree.getRoot() == nullptr)
		{
			tree.setRoot(tree.insert(tree.getRoot(), num));
		}
		else
		{
			tree.insert(tree.getRoot(), num);
		}
	}

	input.close();
}