#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
#include "PriorityQueue.h"
using namespace std;

string RemoveSpace(string word);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	input = "input1.txt";
	output = "output1.txt";


}

string RemoveSpace(string word)
{
	string temp;
	for (unsigned int i = 0; i < word.length(); i++)
	{
		if (word[i] != ' ')
			temp += word[i];
	}
	return temp;
}