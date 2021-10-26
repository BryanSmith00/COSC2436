#include <iostream>
#include <string>
#include <fstream>
#include "ArgumentManager.h"
#include "Queue.h"
using namespace std;

void readInputFile(string, Queue&, Queue&);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	input = "input4.txt";
	output = "output4.txt";

	Queue queue1;
	Queue queue2;
	Queue discardQueue;
	unsigned int totalTime = 0;
	ofstream of(output);
	int flag = 1;
	string end = "";

	readInputFile(input, queue1, queue2);


	while (!queue1.isEmpty() || !queue2.isEmpty())
	{
		if (!queue1.isEmpty() && flag == 1)
		{
			if (queue1.getFront()->value.find("compsci") != string::npos)
			{
				totalTime += 20;
				end += queue1.getFront()->value;

				if (queue1.getFront()->next != nullptr || !queue2.isEmpty())
				{
					end += ',';
				}
			}
			else
			{
				discardQueue.enqueue(queue1.getFront()->value);
			}

			queue1.dequeue();
			flag = 2;
		}
		else if (!queue2.isEmpty())
		{
			if (queue2.getFront()->value.find("compsci") != string::npos)
			{
				totalTime += 20;
				end += queue2.getFront()->value;

				if (queue2.getFront()->next != nullptr || !discardQueue.isEmpty())
				{
					end += ',';
				}
			}
			else
			{
				discardQueue.enqueue(queue2.getFront()->value);
			}

			queue2.dequeue();
			flag = 1;
		}
	}

	while (!discardQueue.isEmpty())
	{
		totalTime += 30;
		end += discardQueue.getFront()->value;
		discardQueue.dequeue();

		if (!discardQueue.isEmpty())
		{
			end += ',';
		}
	}

	of << totalTime << endl << end << endl;
}

void readInputFile(string inputFile, Queue& queue1, Queue& queue2)
{
	ifstream input(inputFile);

	if (input) 
	{
		//Reads in the first line of input for queue1
		string line;
		getline(input, line);

		stringstream ss(line);

		while (!ss.eof())
		{
			string temp;
			getline(ss, temp, ',');

			queue1.enqueue(temp);
		}

		//Reads in the second line of input, for queue2
		getline(input, line);

		stringstream ss2(line);

		while (!ss2.eof())
		{
			string temp;
			getline(ss2, temp, ',');

			queue2.enqueue(temp);
		}
	}
}