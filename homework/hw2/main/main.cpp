#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ArgumentManager.h"
#include "LinkedList.h"
using namespace std;

void readInputFile(LinkedList& sentences, string);
void readCommandFile(LinkedList&, string);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	LinkedList sentences;

	readInputFile(sentences, input);
	
	readCommandFile(sentences, command);

	ofstream outputFile(output);
	for (int i = 0; i < sentences.getSize(); i++)
	{
		outputFile << sentences.at(i) << endl;
	}
	outputFile.close();
}

void readInputFile(LinkedList &sentences, string input) {

	ifstream inputFile(input);
	string sentence;
	string addOrder;

	if (inputFile) {

		getline(inputFile, addOrder);

		while (!inputFile.eof()) {

			getline(inputFile, sentence);
			string temp;

			if (sentence != "") {

				if (!sentences.contains(sentence)) {

					if (addOrder == "Beginning")
						sentences.addToFront(sentence);

					else
						sentences.addToEnd(sentence);
				}
			}
		}
		if (addOrder == "Alphabetically") {
			sentences.sort();
		}
		else if (addOrder == "Length") {
			sentences.sortLength();
		}
	}
}

void readCommandFile(LinkedList& sentences, string fileName) {

	ifstream commandFile(fileName);
	string command;

	if (commandFile) {
		while (!commandFile.eof()) {
			getline(commandFile, command);
			stringstream ss(command);
			getline(ss, command, ' ');
			string temp;
			string sentence = "";

			if (command == "Add") {
				string location;
				getline(ss, temp, ')');

				for (unsigned int i = 0; i < temp.length(); i++)
				{
					if (temp[i] != ' ' && temp[i] != '(')
						location += temp[i];
				}
				int loc = stoi(location);

				getline(ss, temp, ']');
				sentence = temp.substr(temp.find('[') + 1);
				
				if (loc <= sentences.getSize()) {
					if (!(sentences.contains(sentence))) {
						sentences.addAt(loc, sentence);
					}
				}
			}
			else if (command == "Remove") {

				getline(ss, temp, ']');
				for (unsigned int i = 0; i < temp.length(); i++)
					if (temp[i] != '[')
						sentence += temp[i];

				for (int i = 0; i < sentences.getSize(); i++)
				{
					if (sentences.at(i).find(sentence) >= 0 && sentences.at(i).find(sentence) <= sentences.at(i).size()) {

						sentences.removeAt(i);
						i--;
					}
				}
			}
			else if (command == "Sort") {

				getline(ss, temp, ')');
				for (unsigned int i = 0; i < temp.length(); i++)
					if (temp[i] != '(')
						sentence += temp[i];

				if (sentence == "alphabetically")
					sentences.sort();
				else if (sentence == "length")
					sentences.sortLength();
			}	
		}
	}
}