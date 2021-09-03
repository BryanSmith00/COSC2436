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
string removeSpace(string word);

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

	matchingBooks = readCommandFile(command, books);

	ofstream outputFile(output);

	for (unsigned int i = 0; i < matchingBooks.size(); i++)
	{
		outputFile << matchingBooks.at(i).text << endl;
	}

	for (unsigned int i = 0; i < matchingBooks.size(); i++)
	{
		cout << matchingBooks.at(i).text << endl;
	}

	outputFile.close();
    
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
				//word.erase(remove(word.begin(), word.end(), ' '), word.end());
				word = removeSpace(word);

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

		cout << "Commands: " << genres.size() << " " << titles.size() << " " << authors.size() << " " << years.size() << endl;

		if (genres.empty() && titles.empty() && authors.empty() && years.empty()) {
			return bookList;
		}
		else {

			///////////////////////
			//Matching goes here//
			//////////////////////
			
			if (!genres.empty() && !titles.empty() && !authors.empty() && !years.empty()) {
				for (unsigned int i = 0; i < bookList.size(); i++)
				{
					bool genreFlag = false;
					bool titleFlag = false;
					bool authorFlag = false;
					bool yearFlag = false;

					for (unsigned int j = 0; j < genres.size(); j++)
					{
						if (bookList.at(i).genre == genres.at(j)) {
							genreFlag = true;
						}
					}

					for (unsigned int j = 0; j < titles.size(); j++)
					{
						if (bookList.at(i).title == titles.at(j)) {
							titleFlag = true;
						}
					}

					for (unsigned int j = 0; j < authors.size(); j++)
					{
						if (bookList.at(i).author == authors.at(j)) {
							authorFlag = true;
						}
					}

					for (unsigned int j = 0; j < years.size(); j++)
					{
						if (bookList.at(i).year == years.at(j)) {
							yearFlag = true;
						}
					}

					if (genreFlag && titleFlag && authorFlag && yearFlag) {
						matchingBooks.push_back(bookList.at(i));
					}
				}
			}

		}
		return matchingBooks;
	}
	else {
		commandFile.close();
		return bookList;
	}
}

string removeSpace(string word) {
	string newWord = "";

	for (unsigned int i = 0; i < word.size(); i++)
	{
		if (word[i] != ' ') {
			newWord += word[i];
		}
	}
	return newWord;
}