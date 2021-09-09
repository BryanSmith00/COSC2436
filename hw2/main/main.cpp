#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;



int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");


}