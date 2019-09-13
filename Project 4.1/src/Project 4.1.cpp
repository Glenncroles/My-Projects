//============================================================================
// Name        : 1.cpp
// Author      : Glenn Roles
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : Project.cpp
// Author      : Glenn Roles
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;



class Tree
{
protected:
	int* parent;
	int numNodes;
	int c;

public:
	Tree(); //default constructor
	Tree(int a); // non default constructor
	Tree(const Tree* in); // copy constructor
	virtual ~Tree(); // Destructor
	int LCA(int a, int b); //least common ancestor of a and b
	int Parent(int a); //parent of a
	void children(int a); //children of a
	void siblings(int a); //siblings of a
	int Root(); //the root of the tree or top
	void setRoot(int node); //set the root to node
	void setParent(int n, int p); //sets the parent of the node
	void nodesAtLevel(int lev); //gives the nodes at level
	int level(int a); //the level a is at
	int height(); //the height of the tree
	void preOrder(int in); //gives the preorder traverasal of the tree(BONUS) do this

	//prints the parent array when called
	friend ostream& operator<<(ostream& M, const Tree& mt)
	{
		//a for loop to go through each positionn in the Tree
		for(int i = 0; i < mt.numNodes; i++)
		{
			//cout the way he wants it
			cout << i << ":" << mt.parent[i];
			if(mt.numNodes - 1)
			{
				cout << " ";
			}
		}
		return M;
	}
};

//Default constructor
Tree :: Tree()
{
	parent = new int[0];
	numNodes = 0;
	c = 0;
}

//Non Default constructor
Tree :: Tree(int a)
{
	parent = new int[a];
	numNodes = a;
	c = 0;
}


//Copy Constructor
Tree :: Tree(const Tree* in)
{
	parent = in->parent;
	numNodes = in->numNodes;
	c = in->c;
}

// destructor
Tree :: ~Tree()
{
	//if the tree is not null
	//make everything null and delete the pointer
	if(parent != NULL)
	{
		c = 0;
		for(int i = 0; i< numNodes; i++)
		{
//			delete &parent[i];
			parent = NULL;
		}

		numNodes = 0;

	}

}


//least common ancestor of a and b
int Tree :: LCA(int a, int b)
{
	//checking to see if a or b is in the Tree if not return
	if(level(a) == -1)
		return -1;
	if(level(b) == -1)
		return -1;

	//if a = b then return the parent of either of them
	if(a == b)
	{
		return Parent(a);
	}
	//variables for higher and lower
	int higher;
	int lower;

	//if level of a is bigger than level of b
	if(level(a) >= level(b))
	{
		//a is lower in the tree and b is higher
		lower = a;
		higher = b;
	}
	else
	{
		//if it is not b is lower in the tree and a is higher
		lower = b;
		higher = a;
	}

	//making variables for least and our current lower and curr higher;
	int least, cl, ch;

	//setting our variables to their amounts
	least = 0;
	cl = lower;
	ch = higher;

	//variable for the levels of the current lower and current higher
	int levelh = level(ch);
	int levell = level(cl);

	//loopint through the bigger level
	for(int i = 0; i < levelh; i++)
	{
		//looping through the smaller level
		for(int j = 0; j < levell; j++)
		{
			//resetting the cl to lower if j == 0
			//basically when the higher gets to the parent
			if(j == 0)
			{
				cl = lower;
			}
			//changes cl to the parent of itself
			cl = parent[cl];

			//if they are equal return the cl
			if(cl == ch)
			{
				least = cl;
				return least;
			}
		}

		//change the higher to the parent of itself
		ch = parent[ch];

	}

	if(least == 0)
	{
		cout << "There were ";
	}
	return least;
}

//parent of a
int Tree :: Parent(int a)
{
	return parent[a];
}

//children of a
void Tree :: children(int a)
{
	int* child = new int[numNodes];
	int size = 0;
	for(int i = 0; i < numNodes; i++)
	{
		if(parent[i] == a)
		{
			child[size] = i;
			size++;
		}
	}

	for(int i = 0; i < size; i++)
	{
		cout << child[i] << " ";
	}

	if(size == 0)
	{
		cout << "Error: There are no children at node " << a << ".";
	}
}

//siblings of a //think it can be void just cout each one
void Tree :: siblings(int a)
{
	//an array to store the siblings in
	int *sib = new int[numNodes];

	//the parent of a
	int p = parent[a];

	//keeps track of the amount of siblings put in the array
	int size = 0;

	//a for loop that goes through the numNodes
	for(int i = 0; i < numNodes; i++)
	{

		//if the parent is the same as the ith parent
		if(parent[i] == p)
		{
			//skip when i == a because we already know that
			if(i != a)
			{
				//put the value in the sib array @ position size
				sib[size] = i;

				//make size bigger
				size++;
			}
		}
	}

	//a for loop through size so it only prints what we put in it
	for(int i = 0; i < size; i++)
	{
		//cout each postion of sibling
		cout << sib[i] << " ";
	}

	//if there is nothing in it print out a message saying there are no siblings of the node
	if(size == 0)
	{
		cout << "Error: There are no siblings at node " << a << ".";
	}
}

//the root of the tree or top
int Tree :: Root()
{
	//making an int varaible for root
	int root = -1;

	//a for loop through each postion
	for(int i = 0; i < numNodes; i++)
	{
		//if the parent of the postion is -1 its the root
		if(parent[i] == -1)
		{
			//root equals i where its parent is -1
			root = i;
		}
	}
	//retutn the root
	return root;
}

//set the root to node
void Tree :: setRoot(int node)
{
	//sets the parent arrays postion at node to -1 saying its the root
	parent[node] = -1;
}

//sets the parent of the node
void Tree :: setParent(int n, int p)
{
	//sets the array parent postion at node to parent
	parent[n] = p;

}

//gives the nodes at level
void Tree :: nodesAtLevel(int lev)
{
	//a for loop through the number of nodes each potion
	for(int i = 0; i < numNodes; i++)
	{
		//creating a temp of the level at the postion
		int temp = level(i);

		//if the postion is the same as the one we are looking for print it
		if(temp == lev)
			cout << i << " ";
	}

}

//the level a is at
int Tree :: level(int a)
{
	//Noah helped me with this one
	int l = -1;
	if(a > numNodes)
	{
		cout << "There is no " << a << " in the tree.";
		return l;
	}
	//if the parent at the postion or the parent of the number is not equal to the root
	if(parent[a] != -1)
	{
		//then recursivly call the level till it is -1 and add one everytime
		//this adds the number of levels till the top
		l = 1 + level(parent[a]);
	}
	else if(parent[a] == -1)
	{
		//if the parent at position is -1 then its parent is the root
		l = 1;
	}

	return l;
}

//the height of the tree
int Tree :: height()
{
	//a variable for level
	int lev = -1;

	//a for loop to check each position in the number of nodes
	for(int i = 0; i < numNodes; i++)
	{
		//a varaible to store the level of each postion in numNodes
		int temp = level(i);

		//if statement that checks to see if the current level(i) is bigger than last if so change to temp
		if(temp > lev)
			lev = temp;
	}

	//return the level
	return lev;
}

void Tree :: preOrder(int in)
{
	//loopint through the numNodes
	for(int i = 0; i < numNodes; i++)
	{
		//if our parent is equal to our in then print
		//then recall recursivly the position so it can find all the children
		if(Parent(i) == in)
		{
			cout << i << " ";
			preOrder(i);
		}
	}
}


int main() {
	Tree* myTree;
	int numNodes,node, parent;

	cin >> numNodes;
	myTree = new Tree(numNodes);
	for(int i=0; i < numNodes; i++)
	{
		cin >> node >> parent;
		(*myTree).setParent(node,parent);
		if(parent == -1)
		{
			(*myTree).setRoot(node);
		}
	}

	cout << "The tree that we just read is:" << endl;
	cout << *myTree << endl;

	Tree* newTree = new Tree(*myTree);
	cout << "The tree that we just copied is:" << endl;
	cout << *newTree << endl;

	cout << "The root of the tree is: " << (*myTree).Root() << endl;



	cout << "The least common ancestor of node 3 and 8 is: " << (*newTree).LCA(3,8) << endl;
	cout << "The least common ancestor of node 13 and 8 is: " << (*newTree).LCA(13,8) << endl;
	cout << "The least common ancestor of node 13 and 11 is: " << (*newTree).LCA(13, 11) << endl;



	cout << "The children of node 12 is/are: " << endl;
	(*myTree).children(12) ;
	cout << endl;

	cout << "The children of node 10 is/are: "  << endl;
	(*myTree).children(10);
	cout << endl;



	cout << "The siblings of node 3 is/are:  " << endl;
	(*myTree).siblings (3);
	cout << endl;

	cout << "The siblings of node 12 is/are: "  << endl;
	(*myTree).siblings (12);
	cout << endl;



	cout << "The nodes at level 3 is/are: "  << endl;
	(*myTree).nodesAtLevel (3);
	cout << endl;



	cout << "The height of the tree is: " << (*myTree).height() << endl;


	cout << "The level of node 3 in the tree is: " << (*myTree).level(3) << endl;
	cout << "The level of node 12 in the tree is: " << (*myTree).level(12) << endl;


	cout << "The preorder traversal of the tree is " << endl;
	cout << (*myTree).Root() << " ";
	(*myTree).preOrder((*myTree).Root());
	cout << endl;

	delete myTree;
	delete newTree;


	return 0;
}
