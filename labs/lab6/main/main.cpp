#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	input = "input1.txt";
	output = "output1.txt";


}