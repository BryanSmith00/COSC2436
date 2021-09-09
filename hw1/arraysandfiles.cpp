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

	books = readInputFile(input);

	matchingBooks = readCommandFile(command, books);

	ofstream outputFile(output);

	for (unsigned int i = 0; i < matchingBooks.size(); i++)
	{
		outputFile << matchingBooks.at(i).text << endl;
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

		vector<Book> firstTest;
		vector<Book> secondTest;
		vector<Book> thirdTest;

		//If the command file has 1 or more genre entries then it will add all corresponding books to the firstTest vector
		//Else no genre commands means all valid books will progress to the next phase of testing
		if (genres.size() > 0) {
			for (unsigned int i = 0; i < bookList.size(); i++)
			{
				for (unsigned int j = 0; j < genres.size(); j++) {
					if (bookList.at(i).genre == genres.at(j))
						firstTest.push_back(bookList.at(i));
				}
			}
		}
		else if (genres.size() == 0)
			firstTest = bookList;

		//If the command file has 1 or more title entries then it will add all corresponding books from the firstTest vector to the secondTest vector
		//Else no title commands means all valid books will progress to the next phase of testing
		if (titles.size() > 0) {
			for (unsigned int i = 0; i < firstTest.size(); i++)
			{
				for (unsigned int j = 0; j < titles.size(); j++) {
					if (firstTest.at(i).title == titles.at(j))
						secondTest.push_back(firstTest.at(i));
				}
			}
		}
		else if (titles.size() == 0)
			secondTest = firstTest;

		//If the command file has 1 or more author entries then it will add all corresponding books from the secondTest vector to the thirdTest vector
		//Else no author commands means all valid books will progress to the next phase of testing
		if (authors.size() > 0) {
			for (unsigned int i = 0; i < secondTest.size(); i++)
			{
				for (unsigned int j = 0; j < authors.size(); j++) {
					if (secondTest.at(i).author == authors.at(j))
						thirdTest.push_back(secondTest.at(i));
				}
			}
		}
		else if (authors.size() == 0)
			thirdTest = secondTest;

		//If the command file has 1 or more year entries then it will add all corresponding books from the thirdTest vector to the matchingBooks vector
		//Else no year commands means all valid books will be added to matchingBooks
		if (years.size() > 0) {
			for (unsigned int i = 0; i < thirdTest.size(); i++)
			{
				for (unsigned int j = 0; j < years.size(); j++) {
					if (thirdTest.at(i).year == years.at(j))
						matchingBooks.push_back(thirdTest.at(i));
				}
			}
		}
		else if (years.size() == 0)
			matchingBooks = thirdTest;

		return matchingBooks;
	}
	else {

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