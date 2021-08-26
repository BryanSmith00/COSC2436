#include <iostream>
#include <fstream>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

struct Book {
	string text = "";
	string genre = "";
	string title = "";
	string author = "";
	int year = 0000;

	Book(string text, string genre, string title, string author, int year) :
		text(text), genre(genre), title(title), author(author), year(year) {}
};

void readCommandFile(string);
void printResults(string);
void readInputFile(string input, vector<Book>);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	const string output = am.get("output");
	const string command = am.get("command");

	vector<Book> books;

	//Temp hardcoded file name CHANGE THIS BEFORE SUBMITTING
	input = "input11.txt";

	readInputFile(input, books);

	readCommandFile(command);

	printResults(output);
    
}

void readInputFile(string input, vector<Book> books) {
	ifstream inputFile(input);
	string word;
	int counter = 0;
	int comma1;
	int comma2;

	if (inputFile) {
		while (!inputFile.eof()) {
			getline(inputFile, word);

			//Only moves on to process the line if it is not empty indicating a book entry
			if (word != "") {

				//Removes all of the spaces from the book entry
				word.erase(remove(word.begin(), word.end(), ' '), word.end());

				cout << word << endl;

				comma1 = word.find(',');

				//Change so the substr values arent hardcoded
				if (word.substr(1, 5) == "genre") {
					if (word.substr(comma1 + 1, 5) == "title") {
						comma2 = word.find(',', comma1 + 1);
						

						//These are the two slices for the genre and title of the book
						cout << word.substr(7, (comma1 - 7)) << endl;
						cout << word.substr(comma1 + 7, (comma2 - comma1 - 7)) << endl;


						//These should be nested in the deepest loop after I identify that the entire word is a valid book entry
						//books[counter].text = word;
						//books.push_back(  //need to put a book in here  );
						counter++;
					}
					
				}
			}
		}
	}
	inputFile.close();
}

void readCommandFile(string fileName) {

	//Open the command file with the name given by argument manager
	ifstream commandFile(fileName);



	commandFile.close();
}

void printResults(string fileName) {

	//Create the output file with the name given by argument manager
	ofstream outputFile(fileName);


	outputFile.close();
}