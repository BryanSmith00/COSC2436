#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

void readInputFile(string);
void readCommandFile();
void printResults();



int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	const string output = am.get("output");
	const string command = am.get("command");

	//Temp hardcoded file name
	input = "input12.txt";

	readInputFile(input);
    
}

void readInputFile(string input) {
	ifstream inputFile(input);
	string word;

	if (inputFile) {
		while (!inputFile.eof()) {
			cin >> word;
			cout << word << endl;
		}
	}

	inputFile.close();
}

void readCommandFile() {

}

void printResults() {

}