#include "Project2.h"



#pragma once






#include <iostream> 
#include <iomanip> 
#include <string> 
#include <stdio.h>
#include <cstring>
using namespace std;
#include <fstream>


int main(int argc, char* argv[])
{
	char* filename1 = argv[1];
	char* filename2 = argv[2];
	ifstream inFile1;
	inFile1.open(filename1);
	string line;
	while (getline(inFile1, line, '\n'));
	{
		string line1 = line;
		string delimiter = ",";
		int pos = line1.find(delimiter);
		if (pos == string::npos)//string has no commas
		{
			if (line1.compare("end_graph"))
			{
				cout << "endgraph" << endl;
			}
			else if (line1.compare("print_graph"))
			{
				cout << "printgraph" << endl;
			}
			else if (line1.compare("depth_first_search"))
			{

			}
		}

		else
		{
			string graph = line1.substr(0, pos);
			line1.erase(0, pos + delimiter.length());
			int pos = line1.find(delimiter);
			int start = stoi(line1.substr(0, pos));
			line1.erase(0, pos + delimiter.length());
			int end = stoi(line1.substr(0, pos));
			int size = end - start + 1;

			ifstream inFile2;
			string data;
			inFile2.open(filename2);

			int count = 0;
			if (start == 0)
			{

				Graph thegraph(size);
				while (getline(inFile2, data, '\n') && count <= end)
				{

					int pos = data.find(delimiter);
					string winner = data.substr(0, pos);
					data.erase(0, pos + delimiter.length());
					int score1 = stoi(data.substr(0, pos));
					data.erase(0, pos + delimiter.length());
					string loser = data.substr(0, pos);
					data.erase(0, pos + delimiter.length());
					int score2 = stoi(data.substr(0, pos));
					thegraph.add(winner, loser, score1, score2);
					count++;
				}
			}
			else
			{
				Graph thegraph(size);
				for (int i = 0; i < start; i++)
				{
					getline(inFile2, data, '\n');
					count++;
				}

				while (getline(inFile2, data, '\n') && count <= end)
				{

					int pos = data.find(delimiter);
					string winner = data.substr(0, pos);
					data.erase(0, pos + delimiter.length());
					int score1 = stoi(data.substr(0, pos));
					data.erase(0, pos + delimiter.length());
					string loser = data.substr(0, pos);
					data.erase(0, pos + delimiter.length());
					int score2 = stoi(data.substr(0, pos));
					thegraph.add(winner, loser, score1, score2);
					count++;
				}

			}
			inFile2.close();




		}


		//getnextline???ask
	}

	inFile1.close();

}