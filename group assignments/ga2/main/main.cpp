//Group Assignment 2 Bryan Smith
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ArgumentManager.h"
#include "Stack.h"
using namespace std;

vector<string> readInputFile(string, bool&);
bool isBalanced(string);
int precedence(string);
string infixToPostfix(string);
int evaluateExpression(string);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	input = "input21.txt";
	output = "output21.txt";

	vector<int> results;
	bool validExp = true;
	bool same = true;

	//cout << evaluateExpression(infixToPostfix("a+b-(A+1)-(-3-B)")) << endl;
	cout << evaluateExpression("ab+A1+-3-B--") << endl;
/*
	vector<string> equations = readInputFile(input, validExp);

	if (validExp)
	{
		for (unsigned int i = 0; i < equations.size(); i++)
		{
			string postfix = infixToPostfix(equations.at(i));
			results.push_back(evaluateExpression(postfix));
		}

		for (unsigned int i = 0; i < results.size() - 1; i++)
		{
			if (results.at(i) != results.at(i + 1))
			{
				same = false;
			}
		}

		if (same == true)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}*/
}

vector<string> readInputFile(string inputFile, bool &validExp)
{
	vector<string> equations;
	ifstream input(inputFile);
	int lineNum = 1;

	while (!input.eof())
	{
		string line;
		getline(input, line);

		if (line != "")
		{
			if (isBalanced(line))
				equations.push_back(line);
			else
			{
				cout << "Error at: " << lineNum << endl;
				validExp = false;
			}

			lineNum++;
		}
	}

	return equations;
}

bool isBalanced(string eq)
{
	Stack stk;

	for (unsigned int i = 0; i < eq.size(); i++)
	{
		string tmp = "";

		if (eq[i] == '(' || eq[i] == '{' || eq[i] == '[')
		{
			tmp += eq[i];
			stk.push(tmp);
		}

		if (eq[i] == ')')
		{
			tmp = stk.peek();
			stk.pop();
			if (tmp == "{" || tmp == "[")
				return false;
		}
		else if (eq[i] == '}')
		{
			tmp = stk.peek();
			stk.pop();
			if (tmp == "(" || tmp == "[")
				return false;
		}
		else if (eq[i] == ']')
		{
			tmp = stk.peek();
			stk.pop();
			if (tmp == "(" || tmp == "{")
				return false;
		}
	}

	return stk.isEmpty();
}

int precedence(string c)
{
	if (c == "*" || c == "/")
		return 2;
	else if (c == "+" || c == "-")
		return 1;
	else
		return -1;
}

string infixToPostfix(string eq)
{
	string post = "";
	Stack stk;

	for (unsigned int i = 0; i < eq.size(); i++)
	{
		string tmp = ""; tmp += eq[i];

		if (eq[i] == '(' || eq[i] == '{' || eq[i] == '[')
			stk.push(tmp);
		else if (eq[i] == ')') {
			while (stk.peek() != "(")
			{
				post += stk.peek();
				stk.pop();
			}
			stk.pop();
		}
		else if (eq[i] == '}') {
			while (stk.peek() != "{")
			{
				post += stk.peek();
				stk.pop();
			}
			stk.pop();
		}
		else if (eq[i] == ']') {
			while (stk.peek() != "[")
			{
				post += stk.peek();
				stk.pop();
			}
			stk.pop();
		}
		else if (eq[i] == '+' || eq[i] == '-')
		{
			while (!stk.isEmpty() && precedence(tmp) <= precedence(stk.peek()))
			{
				post += stk.peek();
				stk.pop();
			}
			stk.push(tmp);
		}
		else
			post += tmp;
	}

	while (!stk.isEmpty()) {
		post += stk.peek();
		stk.pop();
	}

	return post;
}

int evaluateExpression(string eq)
{
	Stack stk;

	for (unsigned int i = 0; i < eq.size(); i++)
	{
		string tmp = "";
		tmp += eq[i];

		if (isdigit(eq[i]))
			stk.push(tmp);
		else if (isalpha(eq[i]))
			stk.push(to_string(int(eq[i])));

		// If the scanned character is an operator, pop two
		// elements from stack apply the operator
		else
		{
			int val1 = stoi(stk.pop());
			int val2 = stoi(stk.pop());
			switch (eq[i])
			{
			case '+': stk.push(to_string(val2 + val1)); break;
			case '-': stk.push(to_string(val2 - val1)); break;
			}
		}
	}
	return stoi(stk.pop());
}