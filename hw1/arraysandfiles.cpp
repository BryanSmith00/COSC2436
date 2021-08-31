#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;

struct Book {
	string text = "";
	string genre = "";
	string title = "";
	string author = "";
	string year = "";

	Book(string text, string genre, string title, string author, string year) :
		text(text), genre(genre), title(title), author(author), year(year) {}
};

vector<Book> readInputFile(string);
vector<Book> readCommandFile(string, vector<Book>);
void printResults(string, vector<Book>);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	vector<Book> books;
	vector<Book> matchingBooks;

	//Temp hardcoded file name CHANGE THIS BEFORE SUBMITTING
	input = "input11.txt";
	output = "ans11.txt";
	command = "command11.txt";

	books = readInputFile(input);

	/*for (unsigned int i = 0; i < books.size(); i++)
	{
		cout << books.at(i).genre << " " << books.at(i).title << " " << books.at(i).author << " " << books.at(i).year << endl;
	}*/

	matchingBooks = readCommandFile(command, books);

	printResults(output, matchingBooks);
    
}

vector<Book> readInputFile(string input) {
	ifstream inputFile(input);
	vector<Book> books;
	string word;
	string genre;
	string title;
	string author;
	string year;
	int counter = 0;

	if (inputFile) {
		while (!inputFile.eof()) {
			getline(inputFile, word);

			//Only moves on to process the line if it is not empty indicating a book entry
			if (word != "") {

				//Removes all of the spaces from the book entry
				word.erase(remove(word.begin(), word.end(), ' '), word.end());
				stringstream ss(word);

				getline(ss, genre, ':');

				if (genre == "{genre") {

					getline(ss, genre, ',');
					getline(ss, title, ':');

					if (title == "title") {

						getline(ss, title, ',');
						getline(ss, author, ':');

						if (author == "author") {

							getline(ss, author, ',');
							getline(ss, year, ':');

							if (year == "year") {

								getline(ss, year, '}');

								//Add all of this information to a new book struct and push it to the back of the vector 
								Book book(word, genre, title, author, year);
								books.push_back(book);
							}
						}
					}
				}
			}
		}
	}
	inputFile.close();
	return books;
}

vector<Book> readCommandFile(string fileName, vector<Book> bookList) {

	string line;
	string word;
	string temp;
	vector<string> genres;
	vector<string> titles;
	vector<string> authors;
	vector<string> years;

	vector<Book> matchingBooks;

	//Open the command file with the name given by argument manager
	ifstream commandFile(fileName);

	if (commandFile) {
		while (!commandFile.eof()) {

			getline(commandFile, line);
			stringstream ss(line);
			getline(ss, word, ':');

			if (word == "genre") {
				getline(ss, temp);
				genres.push_back(temp);
			}
			else if (word == "title") {
				getline(ss, temp);
				titles.push_back(temp);
			}
			else if (word == "author") {
				getline(ss, temp);
				authors.push_back(temp);
			}
			else if (word == "year") {
				getline(ss, temp);
				years.push_back(temp);
			}
		}

		if (genres.empty() && titles.empty() && authors.empty() && years.empty())
			return bookList;
		else {

			///////////////////////
			//Matching goes here//
			//////////////////////
			
			if (!genres.empty() && !titles.empty() && !authors.empty() && !years.empty()) {

			}

		}
	}

	commandFile.close();
	return matchingBooks;
}

void printResults(string fileName, vector<Book> correctBooks) {

	//Create the output file with the name given by argument manager
	ofstream outputFile(fileName);

	for (unsigned int i = 0; i < correctBooks.size(); i++)
	{
		outputFile << correctBooks.at(i).text << endl;
	}

	outputFile.close();
}