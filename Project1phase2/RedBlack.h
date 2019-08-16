
#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings
using namespace std;
#pragma once

struct node {
	string discipline, gender, team_or_ind, event, venue, medal, athlete, country;
	node *parent;
	node *left;
	node *right;
	string color;
};
class RedBlack
{

public:
	int count;
	struct node *root;
	RedBlack();
	~RedBlack();
	void deleteMethod(node* delnode);
	void insert(string disc, string gen, string t_i, string even, string venue, string medal, string athlete, string country);
	char compare(node*, node*);
	void leftRotate(node* node1);
	void rightRotate(node* node1);
	bool binaryInsert(node* n);
	node* treeSearch(string disc, string gen, string even, string ath);
	void search(string disc, string gen, string even, string ath);
	node* maximum(node*node1);
	void max();
	node* minimum(node*node1);
	void min();
	void in_order(node *x);
	void inOrder();
	void postOrder();
	void post_order(node* x);
	void pre_order(node* x);
	void preOrder();
	node* treePredecessor(string disc, string gen, string eve, string athl);
	void callPred(string disc, string gen, string eve, string athl);
	node* treeSuccessor(string disc, string gen, string eve, string athl);
	void callSucc(string disc, string gen, string eve, string athl);
};
RedBlack::~RedBlack()
{
	deleteMethod(root);
	cout << "The number nodes deleted "+count << endl; 
}
RedBlack::RedBlack()
{
	root = NULL;
	count=0;

}
void RedBlack::deleteMethod(node* delnode)
{
	if (delnode != NULL)
	{
		deleteMethod(delnode->left);
		deleteMethod(delnode->right);
		delete delnode;
		count++;
	}
	return;
}
/*compare function used to compare two nodes which is used in the binaryInsert function to correctly place the nodes in a tree.
Two nodes are being compared and returns a char t if smaller, f if greater, or n if the two nodes are the same.
*/
char RedBlack::compare(node *node1, node* node2)
{
	if ((node1->discipline).compare(node2->discipline)<0)
	{
		return 't';
	}
	else if (node1->discipline.compare(node2->discipline) == 0)
	{
		if (node1->event.compare(node2->event)<0)
		{
			return 't';
		}
		else if (node1->event.compare(node2->event) == 0)
		{
			if (node1->gender.compare(node2->gender)<0)
			{
				return 't';
			}
			else if (node1->gender.compare(node2->gender) == 0)
			{
				if (node1->athlete.compare(node2->athlete)<0)
				{
					return 't';
				}
				else if (node1->athlete.compare(node2->athlete) == 0)//nodes are exactly the same so it returns a char 'n' which represents null
				{
					return 'n';
				}
				else
				{
					return 'f';
				}
			}
			else
			{
				return 'f';
			}
		}
		else
		{
			return 'f';
		}
	}
	else
	{
		return 'f';
	}
}
/*The function binaryInsert is used by the function insert. It places the inserted nodes in a binary tree.
*/
bool RedBlack::binaryInsert(node* n)
{

	if (root == NULL)//emptytree
	{
		root = n;
		n->parent = NULL;
		n->left = NULL;
		n->right = NULL;
		return true;
	}
	else//there exists a node or several nodes in the tree
	{
		node *x = root;
		node *y = NULL;
		while (x != NULL)
		{
			y = x;
			if (compare(n, y) == 't')
			{
				x = x->left;
			}
			else if (compare(n, y) == 'f')
			{
				x = x->right;
			}
			else if (compare(n, y) == 'n')//nodes are exactly the same it will not be inserted
			{
				return false;
			}
		}
		n->parent = y;
		if (compare(n, y) == 't')//places the new node to the left. 
		{
			y->left = n;
			return true;
		}
		else if (compare(n, y) == 'f')//places the new node to the right
		{
			y->right = n;
			return true;
		}

	}
}
/*The function leftRotate fixes violations of the red-black tree properties by rotating a node to the left.
*/
void RedBlack::leftRotate(node* node1)
{
	if (node1->right == NULL)
	{
		return;
	}
	else
	{
		node *y = new node;
		y = node1->right;
		node1->right = y->left; //turns y's left subtree into node1's right subtree 
		if (y->left != NULL)
		{
			y->left->parent = node1;

		}

		y->parent = node1->parent;//sets y's parent as node1's parent
		if (node1->parent == NULL)
		{
			root = y;
		}

		else
		{
			if (node1 == node1->parent->left)//if node1 is a left child
			{
				(node1->parent)->left = y;
			}
			else
			{
				(node1->parent)->right = y;
			}

		}
		y->left = node1;//puts node1 as left child of y
		node1->parent = y;
	}
}
/*The function leftRotate fixes violations of the red-black tree properties by rotating a node to the right.
*/
void RedBlack::rightRotate(node* node1)
{
	node*y = new node;
	y = node1->left;
	node1->left = y->right;
	if (y->right != NULL)
	{
		(y->right)->parent = node1;
	}
	y->parent = node1->parent;
	if (node1->parent == NULL)
	{
		root = y;
	}
	else
	{
		if (node1 == (node1->parent)->right)
		{
			(node1->parent)->right = y;
		}
		else
		{
			(node1->parent)->left = y;
		}

	}
	y->right = node1;
	node1->parent = y;
}


void RedBlack::insert(string disc, string gen, string t_i, string even, string venue, string medal, string athlete, string country)
{
	node *n = new node;
	n->discipline = disc;
	n->gender = gen;
	n->team_or_ind = t_i;
	n->event = even;
	n->venue = venue;
	n->medal = medal;
	n->athlete = athlete;
	n->country = country;
	n->left = NULL;
	n->right = NULL;

	if (binaryInsert(n) == true) {
		cout << "The medal recipient " + n->athlete + " for " + n->discipline + " with event " + n->event + " inserted" << endl;
		n->color = "RED";

		while (n->parent != NULL && (n->parent->color).compare("RED") == 0)
		{
			node *y = new node;
			if (n->parent == n->parent->parent->left)//if the parent of the new node is a left child
			{
				y = n->parent->parent->right;//y=the new node's uncle
				if (y != NULL && (y->color).compare("RED") == 0)
				{
					n->parent->color = "BLACK";
					y->color = "BLACK";//
					n->parent->parent->color = "RED";//the color of the new nodes gradparent is red
					n = n->parent->parent;//n=n's grandparent
				}
				else
				{
					if (n == n->parent->right)//if x is the right child
					{
						n = n->parent;
						leftRotate(n);//after left rotate, n will be a left child
					}
					n->parent->color = "BLACK";
					n->parent->parent->color = "RED";//change the color of n's grandparent to red
					rightRotate(n->parent->parent);
				}
			}
			else
			{
				y = n->parent->parent->left;//y=the new node's uncle
				if (y != NULL && (y->color).compare("RED") == 0)
				{
					n->parent->color = "BLACK";
					y->color = "BLACK";
					n->parent->parent->color = "RED";//the color of the new nodes gradparent is red
					n = n->parent->parent;//n=n's grandparent
				}
				else
				{
					if (n == n->parent->left)//if x is the right child
					{
						n = n->parent;
						rightRotate(n);//after left rotate, n will be a left child
					}
					n->parent->color = "BLACK";
					n->parent->parent->color = "RED";//change the color of n's grandparent to red
					leftRotate(n->parent->parent);
				}
			}

		}
		root->color = "BLACK";

	}
	else
	{
		cout << "The medal recipient " + n->athlete + " for " + n->discipline + " with event " + n->event + " NOT inserted" << endl;
	}
}
void RedBlack::search(string disc, string gen, string even, string ath)
{
	if (root == NULL)
	{
		cout << "tree is empty" << endl;
	}
	else
	{
		node *x = new node;
		x = treeSearch(disc, gen, even, ath);
		if (x != NULL)
		{
			cout << "The medal recipient " + ath + " has the medal of " + x->medal << endl;
		}
		else
		{
			cout << ath + " for " + disc + " with event " + even + " not found" << endl;
		}
	}


}
node* RedBlack::treeSearch(string disc, string gen, string even, string ath)
{

	node *node1 = root;

	while (node1 != NULL)
	{
		if ((node1->discipline + node1->gender + node1->event + node1->athlete).compare(disc + gen + even + ath) == 0)
		{

			return node1;

		}
		else if ((node1->discipline + node1->gender + node1->event + node1->athlete).compare(disc + gen + even + ath)<0)
		{
			node1 = node1->right;
		}
		else
		{
			node1 = node1->left;
		}
	}
	return NULL;

}

node* RedBlack::minimum(node*node1)
{

	while (node1->left != NULL)
	{
		node1 = node1->left;
	}
	return node1;

}
void RedBlack::min()
{
	node *x = minimum(root);
	cout << endl;
	cout << "discipline:\t " << x->discipline << endl;
	cout << "gender: \t" << x->gender << endl;
	cout << "team_or_ind:\t" << x->team_or_ind << endl;
	cout << "event:\t" << x->event << endl;
	cout << "venue:\t" << x->venue << endl;
	cout << "medal:\t" << x->medal << endl;
	cout << "athlete:\t" << x->athlete << endl;
	cout << "country:\t" << x->country << endl;
	cout << "color:\t" << x->color << endl;
}
void RedBlack::max()
{
	node *x = maximum(root);
	cout << endl;
	cout << "discipline:\t " << x->discipline << endl;
	cout << "gender: \t" << x->gender << endl;
	cout << "team_or_ind:\t" << x->team_or_ind << endl;
	cout << "event:\t" << x->event << endl;
	cout << "venue:\t" << x->venue << endl;
	cout << "medal:\t" << x->medal << endl;
	cout << "athlete:\t" << x->athlete << endl;
	cout << "country:\t" << x->country << endl;
	cout << "color:\t" << x->color << endl;

}


node* RedBlack::maximum(node*node1)
{

	while (node1->right != NULL)
	{
		node1 = node1->right;
	}
	return node1;
	//cout << node1->athlete;
}
void RedBlack::in_order(node* x)
{
	if (x != NULL)
	{
		in_order(x->left);
		cout << endl;
		cout << "discipline:\t " << x->discipline << endl;
		cout << "gender: \t" << x->gender << endl;
		cout << "team_or_ind:\t" << x->team_or_ind << endl;
		cout << "event:\t" << x->event << endl;
		cout << "venue:\t" << x->venue << endl;
		cout << "medal:\t" << x->medal << endl;
		cout << "athlete:\t" << x->athlete << endl;
		cout << "country:\t" << x->country << endl;
		cout << "color:\t" << x->color << endl;
		in_order(x->right);
	}
	return;
}
//calls the in_order function to return the 
void RedBlack::inOrder()
{
	if (root == NULL)
	{
		cout << "tree is empty" << endl;
	}
	else
	{
		in_order(root);
	}
}




void RedBlack::pre_order(node* x)
{
	if (x != NULL)
	{
		cout << endl;
		cout << "discipline:\t " << x->discipline << endl;
		cout << "gender: \t" << x->gender << endl;
		cout << "team_or_ind:\t" << x->team_or_ind << endl;
		cout << "event:\t" << x->event << endl;
		cout << "venue:\t" << x->venue << endl;
		cout << "medal:\t" << x->medal << endl;
		cout << "athlete:\t" << x->athlete << endl;
		cout << "country:\t" << x->country << endl;
		cout << "color:\t" << x->color << endl;
		pre_order(x->left);
		pre_order(x->right);
	}
	return;
}

void RedBlack::preOrder()
{
	if (root == NULL)
	{
		cout << "tree is empty" << endl;
	}
	else
	{
		pre_order(root);
	}
}


void RedBlack::postOrder()
{
	if (root == NULL)
	{
		cout << "tree is empty" << endl;
	}
	else
	{
		post_order(root);
	}

}
void RedBlack::post_order(node* x)
{

	if (x != NULL)
	{
		post_order(x->left);
		post_order(x->right);
		cout << endl;
		cout << "discipline:\t " << x->discipline << endl;
		cout << "gender: \t" << x->gender << endl;
		cout << "team_or_ind:\t" << x->team_or_ind << endl;
		cout << "event:\t" << x->event << endl;
		cout << "venue:\t" << x->venue << endl;
		cout << "medal:\t" << x->medal << endl;
		cout << "athlete:\t" << x->athlete << endl;
		cout << "country:\t" << x->country << endl;
		cout << "color:\t" << x->color << endl;

	}
	return;
}


node* RedBlack::treePredecessor(string disc, string gen, string eve, string athl)
{
	node *y = new node;
	node *person = treeSearch(disc, gen, eve, athl);
	if (person != NULL)
	{
		if (person->left != NULL)
		{
			return maximum(person->left);
		}
		else
		{
			y = person->parent;
			while (y != NULL && person == y->left)
			{
				person = y;
				y = y->parent;
			}
			return y;
		}
	}
	else
		return NULL;
}
node* RedBlack::treeSuccessor(string disc, string gen, string eve, string athl)
{
	node *y = new node;
	node *person = treeSearch(disc, gen, eve, athl);
	if (person != NULL)
	{
		if (person->right != NULL)
		{
			return minimum(person->right);
		}
		else
		{
			y = person->parent;
			while (y != NULL && person == y->right)
			{
				person = y;
				y = y->parent;
			}
			return y;
		}
	}
	else
	{
		return NULL;
	}
}

void RedBlack::callPred(string disc, string gen, string eve, string athl)
{
	if (root == NULL)
	{
		cout << "tree is empty" << endl;
	}
	else
	{
		node* x = treePredecessor(disc, gen, eve, athl);
		if (x != NULL)
		{
			cout << "The predecessor of the medal recipient " + athl + " for " + disc + " with event " + eve + " is " << endl;
			cout << "discipline:\t " << x->discipline << endl;
			cout << "gender: \t" << x->gender << endl;
			cout << "team_or_ind:\t" << x->team_or_ind << endl;
			cout << "event:\t" << x->event << endl;
			cout << "venue:\t" << x->venue << endl;
			cout << "medal:\t" << x->medal << endl;
			cout << "athlete:\t" << x->athlete << endl;
			cout << "country:\t" << x->country << endl;
			cout << "color:\t" << x->color << endl;
		}
		else
		{
			cout << "The medal recipient " + athl + " for " + disc + " with event " + eve + " does not have any predecessor" << endl;
		}

	}



}
void RedBlack::callSucc(string disc, string gen, string eve, string athl)
{

	if (root == NULL)
	{
		cout << "tree is empty" << endl;
	}
	else
	{
		node* x = treeSuccessor(disc, gen, eve, athl);
		if (x != NULL)
		{
			cout << "The successor of the medal recipient " + athl + " for " + disc + " with event " + eve + " is " << endl;
			cout << "discipline:\t " << x->discipline << endl;
			cout << "gender: \t" << x->gender << endl;
			cout << "team_or_ind:\t" << x->team_or_ind << endl;
			cout << "event:\t" << x->event << endl;
			cout << "venue:\t" << x->venue << endl;
			cout << "medal:\t" << x->medal << endl;
			cout << "athlete:\t" << x->athlete << endl;
			cout << "country:\t" << x->country << endl;
			cout << "color:\t" << x->color << endl;
		}
		else
		{
			cout << "The medal recipient " + athl + " for " + disc + " with event " + eve + " does not have any successor" << endl;
		}

	}
}

