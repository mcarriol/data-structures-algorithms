

#pragma once

#include <iostream> 
#include <iomanip> 
#include <string> 
#include <stdio.h>
#include <cstring>
using namespace std;



struct Loser
{
	string name;
	int score1;
	int score2;
	struct Loser * next;
	char color = NULL;
	int discovery = NULL;
	int finish = NULL;
	string pi = NULL;
};

//creates linked list of losers
class TheLosers
{
private:
	struct Loser * head;

public:
	TheLosers();
	~TheLosers();
	bool addLoser(string, int, int);
	void printList();



};
TheLosers::TheLosers()
{
	head = NULL;
}

TheLosers::~TheLosers()
{
	struct Loser *temp = head;
	while (temp != NULL)
	{
		temp = temp->next;
		delete head;
		head = temp;
	}

}

//losers added into linked list
bool TheLosers::addLoser(string state, int num, int num2)
{
	try {
		struct Loser *addloser;
		addloser = new struct Loser;
		addloser->name = state;
		addloser->score1 = num;
		addloser->score2 = num2;
		addloser->next = NULL;


		if (head == NULL) {
			head = addloser;
			head->next = NULL;
			return true;
		}
		else if (head != NULL && head->next == NULL)//one item in linked list
		{
			if (addloser->name.compare(head->name) < 0) { //add before
				addloser->next = head;
				head = addloser;
				return true;
			}
			else { //add after
				head->next = addloser;
				return true;
			}
		}
		//inserting loser between other losers
		struct Loser *temp = head;
		struct Loser *follow = NULL;
		while (temp != NULL) {
			if (addloser->name.compare(temp->name) < 0) {
				addloser->next = temp;
				if (follow == NULL) {
					head = addloser;
					return true;
				}
				follow->next = addloser;
				return true;


			}

			follow = temp;
			temp = temp->next;
		}
		//inserting loser last
		follow->next = addloser;
		return true;
	}
	catch (bad_alloc &ba) {
		cout << "bad alloc" << endl;
		return false;
	}
	return false;

}
void TheLosers::printList()
{
	//Florida State(43 - 14), New Mexico(58 - 23), Oregon(12 - 9)
	Loser * current = head;
	if (head == NULL)
	{
		cout << "none" << endl;
	}
	else
	{
		while (current != NULL)
		{
			cout << current->name + "(" << current->score1 << " - " << current->score2 << "), ";
			current = current->next;
		}
		return;
	}
}


struct Winner
{
	string statewinner;
	TheLosers *loser;
	char color = NULL;
	int discovery = NULL;
	int finish = NULL;
	string pi = NULL;
};

class Graph
{
private:
	Winner **array;
public:
	int count = 0;
	int size = 0;
	Graph(int n)
	{
		array = new Winner*[n];
		size = n - 1;
		for (int i = 0; i <= n - 1; i++)
		{
			array[i] = new Winner;
			array[i]->statewinner = "";
			array[i]->loser = NULL;
		}
	}
	void add(string winner, string loser, int score1, int score2);
	void sort();
	void printgraph();
	void DFS(Graph *thegraph);
	void DFSS(Winner * node);
};

void Graph::add(string winner, string loser, int score1, int score2)
{

	array[count]->statewinner = winner;
	array[count]->loser->addLoser(loser, score1, score2);
	count++;
	sort();
}
void Graph::sort()
{
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			if (array[j - 1]->statewinner.compare(array[j]->statewinner)>0)
			{
				Winner **temp = new Winner*[1];
				temp[0] = array[j - 1];
				array[j - 1] = array[j];
				array[j] = temp[0];

			}
		}
	}
}

void Graph::printgraph()
{
	for (int i = 0; i <= size; i++)
	{
		TheLosers *temp = array[i]->loser;
		cout << array[i]->statewinner << ": ";
		temp->printList();
		cout << endl;
	}
}

void Graph::DFS(Graph *thegraph)
{
	int time;
	for (int i = 0; i <= size; i++)
	{
		thegraph->array[i]->color= 'w';
		time = 0;
	}

	for (int i = 0; i <= size; i++)
	{
		if (array[i]->color == 'w')
		{
			DFSS(thegraph->array[i]);
		}
	}
	
}

void Graph::DFSS(Winner *node)//only one * ???
{
	node->color = 'g';
	
}
