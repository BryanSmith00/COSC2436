#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

void readCommandFile();
void printResults();
void readInputFile(string input, string[]);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	const string output = am.get("output");
	const string command = am.get("command");

	string books[10000];

	//Temp hardcoded file name
	input = "input11.txt";

	readInputFile(input, books);
    
}

void readInputFile(string input, string books[]) {
	ifstream inputFile(input);
	string word;
	int counter = 0;
	int commaLocation;
	int comma2;
	int comma3;

	if (inputFile) {
		while (!inputFile.eof()) {
			getline(inputFile, word);

			//Only moves on to process the line if it is not empty indicating a book entry
			if (word != "") {

				//Removes all of the spaces from the book entry
				word.erase(remove(word.begin(), word.end(), ' '), word.end());

				cout << word << endl;

				commaLocation = word.find(',');

				if (word.substr(1, 5) == "genre") {
					if (word.substr(commaLocation + 1, 5) == "title") {
						comma2 = word.find(',', commaLocation + 1);
						

						//These are the two slices for the genre and title of the book
						cout << word.substr(7, (commaLocation - 7)) << endl;
						cout << word.substr(commaLocation + 7, (comma2 - commaLocation - 7)) << endl;


						//These should be nested in the deepest loop after I identify that the entire word is a valid book entry
						books[counter] = word;
						counter++;
					}
					
				}
			}
		}
	}
	inputFile.close();
}

void readCommandFile() {

}

void printResults() {

}