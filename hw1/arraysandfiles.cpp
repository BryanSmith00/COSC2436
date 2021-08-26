#include <iostream>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	const string input = am.get("input");
	const string output = am.get("output");
	const string command = am.get("command");

    
}
