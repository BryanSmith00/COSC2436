#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

vector<string> permute(vector<string>&, string, int, int);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	ifstream inputFile(input);
	ofstream outputFile(output);
	string word = "";
	vector<string> permutations;

	if(inputFile)
		getline(inputFile, word);

	if (word != "") {

		permute(permutations, word, 0, word.size());

		//Sorts the vector of all unique permutations alphabetically
		sort(permutations.begin(), permutations.end());

		for (unsigned int i = 0; i < permutations.size(); i++)
			outputFile << permutations.at(i) << endl;
	}
	else
		outputFile << "no permutation";

	return 0;
}

//This function will find all the permutations of the string recursively and add them to a vector
vector<string> permute(vector<string>& permutations, string word, int begin, int end) {

	char temp;
	bool toAdd = true;

	//Recursion condition to stop
	if (begin == end) {

		//This for loop is checking if the solution is unique and if it is then it will be added
		for (unsigned int i = 0; i < permutations.size(); i++) {
			if (permutations.at(i) == word)
				toAdd = false;
		}
		
		//Adds the permutation only if it is a unique solution
		if (toAdd)
			permutations.push_back(word);

	} else {
		for (int i = begin; i < end; i++)
		{
			//First swaps the characters around
			temp = word[begin];
			word[begin] = word[i];
			word[i] = temp;

			permute(permutations, word, begin + 1, end);

			//Need to swap the letters back after the recursion phase
			temp = word[begin];
			word[begin] = word[i];
			word[i] = temp;
		}
	}
	return permutations;
}