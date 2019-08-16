#include "RedBlack.h"



//Project1P2::Project1P2()
//{
//}

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings
#include <stdio.h>
#include <cstring>
using namespace std;

int main()
{
	RedBlack * tree = new RedBlack();
	string userinput;
	getline(cin, userinput);
	while (userinput.compare("quit") != 0)
	{
		string delimiter = ",";
		int pos = userinput.find(delimiter);
		if (pos == string::npos)
		{
			if (userinput.compare("tree_inorder") == 0)
			{
				cout << "next command: tree_inorder" << endl;
				cout << endl;
				tree->inOrder();
				cout << endl;
			}
			else if (userinput.compare("tree_preorder") == 0)
			{
				cout << "next command: tree_preorder" << endl;
				cout << endl;
				tree->preOrder();
				cout << endl;
			}
			else if (userinput.compare("tree_postorder") == 0)
			{
				cout << "next command: tree_postorder" << endl;
				cout << endl;
				tree->postOrder();
				cout << endl;
			}
			else if (userinput.compare("tree_maximum") == 0)
			{
				cout << "next command: tree_maximum" << endl;
				cout << endl;
				cout << "The last athlete is" << endl;
				cout << endl;
				tree->max();
				cout << endl;
			}
			else if (userinput.compare("tree_minimum") == 0)
			{
				cout << "next command: tree_minimum" << endl;
				cout << endl;
				cout << "The first athlete is" << endl;
				cout << endl;
				tree->min();
				cout << endl;
			}

		}
		else
		{
			string user = userinput;
			string token = userinput.substr(0, pos);
			if (token.compare("tree_insert") == 0)
			{
				userinput.erase(0, pos + delimiter.length());

				pos = userinput.find(delimiter);
				string discipline = userinput.substr(0, pos);
				userinput.erase(0, pos + delimiter.length());
				pos = userinput.find(delimiter);
				string gender = userinput.substr(0, pos);
				userinput.erase(0, pos + delimiter.length());
				pos = userinput.find(delimiter);
				string ind_team = userinput.substr(0, pos);
				userinput.erase(0, pos + delimiter.length());
				pos = userinput.find(delimiter);
				string event = userinput.substr(0, pos);
				userinput.erase(0, pos + delimiter.length());
				pos = userinput.find(delimiter);
				string venue = userinput.substr(0, pos);
				userinput.erase(0, pos + delimiter.length());
				pos = userinput.find(delimiter);
				string medal = userinput.substr(0, pos);
				userinput.erase(0, pos + delimiter.length());
				pos = userinput.find(delimiter);
				string athlete = userinput.substr(0, pos);
				userinput.erase(0, pos + delimiter.length());
				pos = userinput.find(delimiter);
				string country = userinput.substr(0, pos);
				cout << "next command : " + user << endl;
				cout << endl;
				tree->insert(discipline, gender, ind_team, event, venue, medal, athlete, country);
				cout << endl;

			}
			else
			{
				userinput.erase(0, pos + delimiter.length());
				pos = userinput.find(delimiter);
				string discipline = userinput.substr(0, pos);
				userinput.erase(0, pos + delimiter.length());
				pos = userinput.find(delimiter);
				string gender = userinput.substr(0, pos);
				userinput.erase(0, pos + delimiter.length());
				pos = userinput.find(delimiter);
				string event = userinput.substr(0, pos);
				userinput.erase(0, pos + delimiter.length());
				pos = userinput.find(delimiter);
				string athlete = userinput.substr(0, pos);

				if (token.compare("tree_predecessor") == 0)
				{
					cout << "next command : " + user << endl;
					cout << endl;
					tree->callPred(discipline, gender, event, athlete);
					cout << endl;

				}
				else if (token.compare("tree_successor") == 0)
				{
					cout << "next command : " + user << endl;
					cout << endl;
					tree->callSucc(discipline, gender, event, athlete);
					cout << endl;

				}
				else if (token.compare("tree_search") == 0)
				{
					cout << "next command : " + user << endl;
					cout << endl;
					tree->search(discipline, gender, event, athlete);
					cout << endl;
				}

			}



		}

		getline(cin, userinput);
	}

	if (userinput.compare("quit") == 0)
	{
		cout << "next command : quit" << endl;		cout<<endl;		delete tree;		
	}


}
