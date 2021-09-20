#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ArgumentManager.h"
#include "LinkedList.h"
using namespace std;

void readInputFile(LinkedList & gameData, string, string);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	LinkedList gameData;

	readInputFile(gameData, input, output);

	ofstream of(output);

	if (gameData.getSize() > 0) {
		gameData.sort();

		for (int i = 0; i < gameData.getSize(); i++)
		{
			of << gameData.at(i)->name << "," << gameData.at(i)->score << endl;
			//cout << gameData.at(i)->name << "," << gameData.at(i)->score << endl;
		}
	}
	else {
		of << "No valid data in input";
		//cout << "No valid data in input";
		of.close();
	}

	return 0;
}

void readInputFile(LinkedList& gameData, string inputFile, string outputFile) {
	ifstream input(inputFile);
	string score;

	if (input) {
		while (!input.eof()) {
			string temp = "";
			string line = "";
			string strScore;
			int score;
			string name;
			int comma1 = -1;
			int comma2 = -1;

			getline(input, temp);

			for (unsigned int i = 0; i < temp.length(); i++)
				if (temp[i] != ' ')
					line += temp[i];

			comma1 = line.find(',');
			comma2 = line.find(',', comma1 + 1);

			if ((comma1  >= 0 && comma1 <= line.length()) && !(comma2 >= 0)) {

				stringstream ss(line);
				getline(ss, name, ',');
				getline(ss, strScore);
				score = stoi(strScore);

				//cout << "Name: " << name << ", Score:" << score << endl;

				gameData.addToEnd(name, score);
			}



		}
	}
	else {
		ofstream output(outputFile);
		output << "No valid data in input";
		output.close();
	}
}