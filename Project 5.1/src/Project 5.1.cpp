//============================================================================
// Name        : 1.cpp
// Author      : Glenn Roles
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
#include <list>
using namespace std;

//Adjacency Matrix
class AdjMatrix
{
protected:
	int numNodes;  //the number of verticies
	int** Amatrix;  //the matrix of the edges
	int** Dmatrix;  //the matrix for display
	int NSize;  //keep track of the array size in neighbors
	bool* Visited;  //a global visited array for dfs and bfs
	int* parent; // a global parent array for dfs and bfs
	list<int>* MDFS;  //a global list for DFS
public:
	AdjMatrix(); //default Constructor
	AdjMatrix(int in); //Non default Constructor
	AdjMatrix(const AdjMatrix* in); //Copy Constructor
	virtual ~AdjMatrix(); //Deconstructor
	void addEdge(int u, int v); //add the edges
	bool isEdge(int u, int v);
	void BFS(int u); //Breadth first search
	void DFS(int u); //just display at the bottom
	void inDFS(int u); //the recursive part of DFS
	int* neighbors(int v);//returns the neighbors of v
	friend ostream& operator<<(ostream& M, const AdjMatrix& mt)
	{
		//a for loop to go through each positionn in the Tree
		for(int i = 0; i < mt.numNodes; i++)
		{
			for(int j = 0; j < mt.numNodes; j++)
			{
				if(mt.Dmatrix[i][j] == 1)
					//cout the postions and if the postions
					cout << "(" << i << "," << j << ")";
			}
		}
		cout << endl;
		return M;
	}
};

//Default constructor
AdjMatrix :: AdjMatrix()
{
	//sets the numNodes to -1
	numNodes = 0;

	//makes an empty 2d array
	Amatrix = new int*[0];
	Amatrix[0] = new int[0];

	NSize = 0;
	Visited = new bool[0];
	parent = new int[0];
	MDFS = new list<int>[0];
	//makes an empty 2d array
	Dmatrix = new int*[0];
	Dmatrix[0] = new int[0];
}

//non-default constructor
AdjMatrix :: AdjMatrix(int in)
{
	//setting the numNodes to our in
	numNodes = in;

	//makes a 2d matrix of size inxin
	Amatrix = new int*[in];
	for(int i = 0; i < in; i++)
	{
		Amatrix[i] = new int[in];
	}

	NSize = 0;
	Visited = new bool[in];
	parent = new int[in];
	MDFS = new list<int>[in];
	//makes a 2d matrix of size inxin
	Dmatrix = new int*[in];
	for(int i = 0; i < in; i++)
	{
		Dmatrix[i] = new int[in];
	}
}



//Copy Constructor
AdjMatrix :: AdjMatrix(const AdjMatrix* in)
{
	//copy over all the protected from in
	numNodes = in->numNodes;
	Amatrix = in->Amatrix;
	NSize = in->NSize;
	Visited = in->Visited;
	parent = in->parent;
	MDFS = in->MDFS;
	Dmatrix = in->Dmatrix;
}

//Destructor
AdjMatrix :: ~AdjMatrix()
{
	//delete all the arrays
	delete[] Amatrix;
	delete[] MDFS;
	delete[] Visited;
	delete[] parent;
	delete[] Dmatrix;
}


//addEdge adds the edge from u to v
void AdjMatrix :: addEdge(int u, int v)
{
	//sets the postion of u v and v u to 1
	Amatrix[u][v] = 1;
	Amatrix[v][u] = 1;

	//push v at u into the list
	MDFS[u].push_back(v);

	//set the display at u v to 1
	Dmatrix[u][v] = 1;
}

//the neighbors of v
int* AdjMatrix :: neighbors(int v)
{
	//reset the NSize to 0
	NSize = 0;

	//an array to put them in
	int* result1 = new int[numNodes-1];

	//if its less than 0 or bigger than numNodes then wont work
	if((v < 0) || (v >= numNodes)) return result1;

	//for loop through numnodes
	for(int i = 0; i < numNodes; i++)
	{
		//if v at i = 1 then its neighbors of v
		if(Amatrix[v][i] == 1)
		{
			//add i to the result and increment it
			result1[NSize] = i;
			NSize++;
		}
	}

	//resize the array to NSize
	int* result = new int[NSize];
	for(int i =0; i < NSize; i++)
	{
		result[i] = result1[i];
	}

	//return the result
	return result;
}

//BFS
void AdjMatrix :: BFS(int u)
{
	//make a visited bool array and set to false
	bool* Visited = new bool[numNodes];
	for(int i = 0; i < numNodes; i++)
	{
		Visited[i] = false;
	}

	//create a q
	queue<int>* Q = new queue<int>();

	//set the visited at u to true
	Visited[u] = true;

	//push u into the q
	Q->push(u);

	//make a parent array
	int* parent = new int[numNodes];
	parent[u] = -1;

	//while q is not empty
	while(!Q->empty())
	{
		//deque and set to k
		int k = Q->front();
		Q->pop();

		//create and array of the neighbors of the k
		int* neighbor = neighbors(k);
		int size = NSize;

		//for each neighbor
		for(int i = 0; i < size; i++)
		{
			//set the y to each neighbor
			int y = neighbor[i];

			//if visited at y = false
			if(Visited[y] == false)
			{
				//set the parent at y to k
				parent[y] = k;

				//visited at y = to true
				Visited[y] = true;

				//push y into the q
				Q->push(y);
			}

		}
	}

	//print out the parent array
	for(int i = 0; i < numNodes; i++)
	{
		cout << i << ":" << parent[i] << " ";
	}
}

//DFS
void AdjMatrix :: DFS(int u)
{
	//reset the visited array and set all pos to false
	Visited = new bool[numNodes];
	for(int i = 0; i < numNodes; i++)
	{
		Visited[i] = false;
	}

	//set the parent at u to -1
	parent[u] = -1;

	//set visited at u to true
	Visited[u] = true;

	//call the recursion
	inDFS(u);

	//cout the parent array
	for(int i = 0; i < numNodes; i++)
	{
		cout << i << ":" << parent[i] << " ";
	}

}

//void inDFS();
void AdjMatrix :: inDFS(int u)
{
	//vistited at u set to true
	Visited[u] = true;

	//iterator to look at each postion
	list<int>::iterator i;

	//for each i
	for(i = MDFS[u].begin(); i != MDFS[u].end(); ++i)
	{
		//if i has not been visited
		if(Visited[*i] == false)
		{
			//parent at i = u
			parent[*i] = u;

			//recursivly the i to see its children
			inDFS(*i);
		}
	}
}

bool AdjMatrix :: isEdge(int u, int v)
{
	return Amatrix[u][v] = 1;
}

//Adjacency LinkedList
class AdjList
{
protected:
	int numNodes;
	int NSize;
	list<int>** LList;
	list<int>** DList;
	list<int>* LDFS;
	bool* Visited;
	int* parent;
public:
	AdjList(); //default Constructor
	AdjList(int in); //Non default Constructor
	AdjList(const AdjList& in); //Copy Constructor
	virtual ~AdjList(); //Deconstructor
	void addEdge(int u, int v); //add the edges to the lists
	int* neighbors(int u);  //get the neighbors of the u
	void BFS(int u);  //Breadth first search
	friend ostream& operator<<(ostream& M, const AdjList& mt)
	{
		//a for loop to go through each positionn in the graph
		for(int i = 0; i < mt.numNodes; i++)
		{

			//creat an array
			int* list = new int[0];

			//creat a postion
			int pos = 0;

			//each list is not empty
			//print put the front in the array
			//then pop the front to see the next positon
			while(!mt.DList[i]->empty())
			{
				cout << "(" << i << "," << mt.DList[i]->front() << ")";
				list[pos++] = mt.DList[i]->front();
				mt.DList[i]->pop_front();
			}

			//putting the contents of the array back into each list
			for(int j = 0; j < pos; j++)
			{
				mt.DList[i]->push_back(list[j]);
			}

		}

		cout << endl;
		return M;
	}

	void DFS(int u); //Depth first search
	void inDFS(int u);  //recursivly calling inside the dfs
};

//Default Constructor
AdjList :: AdjList()
{
	numNodes = 0;
	LList = new list<int>*[0];
	DList = new list<int>*[0];
	NSize = 0;
	LDFS = new list<int>[0];
	Visited = new bool[0];
	parent = new int[0];
}

//Non-Default constructor
AdjList :: AdjList(int in)
{
	//setting the numNodes to our in
	numNodes = in;

	//makes a 2d matrix of size inxin
	LList = new list<int>*[in];
	for(int i = 0; i < in; i++)
	{
		LList[i] = new list<int>();
	}

	DList = new list<int>*[in];
	for(int i = 0; i < in; i++)
	{
		DList[i] = new list<int>();
	}

	//size of the the neighbor array
	NSize = 0;
	LDFS = new list<int>[in];
	Visited = new bool[in];
	parent = new int[in];
}

//Copy Constructor
AdjList :: AdjList(const AdjList& in)
{
	//set all the protected to the in.
	numNodes = in.numNodes;
	NSize = in.NSize;
	LList = in.LList;
	LDFS = in.LDFS;
	Visited = in.Visited;
	parent = in.parent;
	DList = in.DList;
}

//Destructor
AdjList :: ~AdjList()
{
	//delete all the arrays
	delete[] LList;
	delete[] LDFS;
	delete[] Visited;
	delete[] parent;
	delete[] DList;
}


//Add Edge
void AdjList :: addEdge(int u, int v)
{
	//add edge of u v and v u to the LList
	LList[u]->push_back(v);
	LList[v]->push_back(u);

	//add u v to the display and the dfs
	LDFS[u].push_back(v);
	DList[u]->push_back(v);
}

//neighbors
int* AdjList :: neighbors(int u)
{
	//reset the nsize to 0
	NSize = 0;

	//a result array
	int* result = new int[numNodes-1];

	//the list at position u
	list<int>* L = LList[u];

	//an array
	int* list = new int[0];

	//a position tracer
	int pos = 0;

	//
	while(!L->empty())
	{
		result[NSize++] = L->front();
		list[pos++] = L->front();
		L->pop_front();
	}

	//resetting the list back to what it was before
	for(int i = 0; i < pos; i++)
	{
		L->push_back(list[i]);
	}

	return result;
}

//BFS
void AdjList :: BFS(int u)
{
	//variables for y and k
	int y;
	int k;

	//a visited array of booleans and set them all to false
	bool* Visited = new bool[numNodes];
	for(int i = 0; i < numNodes; i++)
	{
		Visited[i] = false;
	}

	//a queue
	queue<int>* Q = new queue<int>();

	//set visited at u to true
	Visited[u] = true;

	//push u into the q
	Q->push(u);

	//a parent array and set u to 0
	int* parent = new int[numNodes];
	parent[u] = -1;

	//while the q is not empty
	while(!Q->empty())
	{
		//deque and set the k to it
		k = Q->front();
		Q->pop();

		//an array of neighbors
		int* neighbor = neighbors(k);
		int size = NSize;

		//for each neighbor
		for(int i = 0; i < size; i++)
		{
			y = neighbor[i];

			//see if visited at y is false
			if(!Visited[y])
			{
				//set the parent at y to k
				parent[y] = k;

				//set visited at y to true
				Visited[y] = true;

				//push y into the q
				Q->push(y);
			}

		}
	}

	//cout the parent array
	for(int i = 0; i < numNodes; i++)
	{
		cout << i << ":" << parent[i] << " ";
	}
}

//DFS
void AdjList :: DFS(int u)
{
	//reset visited and set them all the false
	Visited = new bool[numNodes];
	for(int i = 0; i < numNodes; i++)
	{
		Visited[i] = false;
	}

	//set parent at u to -1
	parent[u] = -1;

	//set visited at u equal to true
	Visited[u] = true;

	//go to the the inDFS so you can call it recursivly
	inDFS(u);

	//cou the parent array
	for(int i = 0; i < numNodes; i++)
	{
		cout << i << ":" << parent[i] << " ";
	}

}

//void inDFS();
void AdjList :: inDFS(int u)
{
	//set visited at the u position to true
	Visited[u] = true;

	//create an iterator to go through list
	list<int>::iterator i;

	//go through LDFS
	for(i = LDFS[u].begin(); i != LDFS[u].end(); ++i)
	{
		//if visited at i == false
		if(Visited[*i] == false)
		{
			//set parent at i to u
			parent[*i] = u;

			//recursivly call at i
			inDFS(*i);
		}
	}
}

int main() {

	AdjMatrix* myMatrix;
	myMatrix = new AdjMatrix(7);
	myMatrix->addEdge(2,4);
	myMatrix->addEdge(0,1);
	myMatrix->addEdge(3,0);
	myMatrix->addEdge(3,6);
	myMatrix->addEdge(6,4);
	myMatrix->addEdge(3,4);
	myMatrix->addEdge(1,3);
	myMatrix->addEdge(1,2);
	myMatrix->addEdge(2,4);
	myMatrix->addEdge(5,2);
	myMatrix->addEdge(4,5);


	AdjList* myList;
	myList = new AdjList(7);
	myList->addEdge(2,4);
	myList->addEdge(0,1);
	myList->addEdge(3,0);
	myList->addEdge(3,6);
	myList->addEdge(6,4);
	myList->addEdge(3,4);
	myList->addEdge(1,3);
	myList->addEdge(1,2);
	myList->addEdge(5,2);
	myList->addEdge(4,5);


	//	//creates the AdjMatrix and the AdjList
	//	AdjMatrix* myMatrix;
	//	AdjList* myList;
	//
	//	//creating variables for numNodes the u and v
	//	int numNodes, u, v;
	//
	//	//cin the numNodes
	//	cin >> numNodes;
	//
	//	//set the size of our matrix and list to numNodes
	//	myMatrix = new AdjMatrix(numNodes);
	//	myList = new AdjList(numNodes);
	//
	//	while(!cin.eof())
	//	{
	//		//cin each postion
	//		cin >> u >> v;
	//
	//		//set them to each with addEdge
	//		myMatrix->addEdge(u,v);
	//		myList->addEdge(u,v);
	//	}



	//showing the graph using the overlaoded operator for both linkedlist and matrix
	cout << "The graph in adjacency matrix that we just read is:" << endl;
	cout << *myMatrix;

	cout << "The graph in adjacency list that we just read is:" << endl;
	cout << *myList;



	//showing the copy constructors work for both linkedlist and matrix
	AdjMatrix* newMatrix = new AdjMatrix(*myMatrix);
	cout << "The graph in adjacency matrix that we just copied is:" << endl;
	cout << *newMatrix;

	AdjList* newList = myList;
	cout << "The graph in adjacency list that we just copied is:" << endl;
	cout << *newList;


	//calling BFS on both
	cout << "The BFS in adjacency matrix is:" << endl;
	(*myMatrix).BFS(0);
	cout << endl;

	cout << "The BFS in adjacency list is:" << endl;
	(*myList).BFS(0);
	cout << endl;



	//calling DFS on both
	cout << "The DFS in adjacency matrix is:" << endl;
	(*myMatrix).DFS(0);
	cout << endl;

	cout << "The DFS in adjacency list is:" << endl;
	(*myList).DFS(0);
	cout << endl;


	return 0;
}
