#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ArgumentManager.h"
#include "LinkedList.h"
using namespace std;

void readInputFile(LinkedList & gameData, string);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	input = "input1.txt";
	output = "ans1.txt";

	LinkedList gameData;

	readInputFile(gameData, input);

	gameData.print();

	return 0;
}

void readInputFile(LinkedList& gameData, string inputFile) {
	ifstream input(inputFile);

	if (input) {
		while (!input.eof()) {
			string temp = "";
			string line = "";

			getline(input, temp);

			for (unsigned int i = 0; i < temp.length(); i++)
				if (temp[i] != ' ')
					line += temp[i];
		}
	}
}