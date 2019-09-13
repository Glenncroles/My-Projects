//============================================================================
// Name        : Project3.cpp
// Author      : Glenn Roles
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

template<class T>
class LinkedList
{
	//protect fields of the linked list "info next and size"
protected:
	//the information stored in the postion
	T* info;

	//the position of the next link
	LinkedList<T>* next;

	//the public fields of the linked list
public:
	LinkedList();   //default constructor
	LinkedList(T& inf);
	LinkedList(T* info, LinkedList<T>* in);  //constructor that bring in info and next pos
	LinkedList(const LinkedList<T>& in);   //copy constructor
	virtual ~LinkedList();   //destructor

	void add(T in); //adds the node or link in the last position
	T remove();  //removes the first link
	int size();  //returns the size of the linked list
	T& infoAt(int pos); //returns the information at that position
	void insertAt(int pos,T in);  //inserts the link at that position
	void removeAt(int pos);  //removes the link at that position

	//overladed operators
	void operator=(const LinkedList<T>& in); // find out what this is supposed to do
	T& operator[](int pos); // the insert at method

	//getters
	T getInfo();
	LinkedList<T>* getNext();

	int isEmpty();//returns 1 if it is empty

	bool hasNext(int pos);
	void push_back(T in);
};

//default constructor
template <class T>
LinkedList<T> :: LinkedList()
{
	info = NULL;
	next = NULL;
}

//a constructor
template<class T>
LinkedList<T> :: LinkedList(T& inf)
{
	info = inf;
	next = NULL;
}

//Constructor
template <class T>
LinkedList<T> :: LinkedList(T* inf, LinkedList<T>* in)
{
	info = inf;
	next = in;
}

//copy constructor
template <class T>
LinkedList<T> :: LinkedList(const LinkedList<T>& in)
{
	info = in->info;
	next = in->next;
}

//the destructor
template <class T>
LinkedList <T> :: ~LinkedList()//TODO look at this
{
	//if the information is already null no need to destruct
	if(info == NULL)
		return;

	//if not then delete info and set it to null then the same for next
	else
	{
		delete info;
		info = NULL;
		delete next;
		next = NULL;
	}
}

//adds the to the end
template <class T>
void LinkedList <T> :: add(T in)
{
	//if info is null add to info
	if(info == NULL)
	{
		info = new T(in);
	}
	else
	{
		LinkedList<T>* nl = new LinkedList(info, next);
		info = new T(in);
		next = nl;
	}
}

//removes the last position
template<class T>
T LinkedList<T> :: remove()//TODO look at this
{
	T temp = *info;

	//delete the info
	delete info;

	if(next == NULL)
	{
		info = NULL;
	}
	else
	{
		//create a temp of the next link to keep the chain going
		LinkedList<T>* lTemp = next;
		info = next->info;
		next = next->next;

		//deleting the temp we just created
		lTemp->info = NULL;
		lTemp->next = NULL;
		delete lTemp;
	}
	return temp;
}

//returns the size of the linkedList
//it does this by counting how many times it is called till it sees NULL
template<class T>
int LinkedList<T> :: size()
{
	//calls if next is null
	if(next == NULL)
	{
		//calls if info = null if it does the size is 0
		if(info == NULL)
		{
			return 0;
		}

		//if it doesn't but next is null then the size is 1
		else
		{
			return 1;
		}
	}

	//recursivly calls the size in the next pos and adds 1 everytime
	//this counts the number of postions in the object or data structure
	else
	{
		return (1 + (*next).size());
	}
}


//returns the info found at a certain position
//it also does this by recursivly calling inself at pos - 1
template<class T>
T& LinkedList<T> :: infoAt(int pos)
{
	//if pos = 0 the its the info we have
	if(pos == 0)
		return *info;

	//otherwise just keep calling the next till pos-1 ends up being 0
	else
		return next->infoAt(pos-1);
}


//puts a link in the postion you want it to be in
//does recursize at pos - 1
template<class T>
void LinkedList<T> :: insertAt(int pos,T in)
{
	//if pos is zero then add to the postion in front of it
	if(pos == 0)
	{
		add (in);
	}

	//if not just call next at pos -1 until it is zero
	else
	{
		next->insertAt(pos - 1, in);
	}

}


//deltes a certain link
//calls itself as many times as pos is then calls the remove method
template<class T>
void LinkedList<T> :: removeAt(int pos)
{
	if(pos == 0)
		remove();
	else
		next->removeAt(pos - 1);
}


//overloaded brackets operator
//calls infoAt
template<class T>
T& LinkedList<T> :: operator[](int pos)
{
	return infoAt(pos);
}


//overloaded = operator
template<class T>
void LinkedList<T> :: operator=(const LinkedList<T>& in)
{
	info = in->info;
	next = in->next;

}

template<class T>
void LinkedList<T> :: push_back(T in)
{
	//	LinkedList<T>* nl = new LinkedList(info, next);
	//	info = new T(in);
	//	next = nl;

	if(next != NULL)
	{
		next->push_back(in);

	}
	else
	{
		LinkedList<T>* nl = new LinkedList(new T(in), NULL);
		next = nl;
	}


}

//checks to see if there is a next postion
template<class T>
bool LinkedList<T> :: hasNext(int pos)//TODO this doesnt work like at all
{
	//a varaible to see if its found or not
	bool found = false;

	//??
	if(next == NULL)
		return found = false;
	else
		return next->hasNext(pos -1);

}

//a getter for next
template<class T>
LinkedList<T>* LinkedList<T> :: getNext()
{
	return next;
}

//a getter for info
template<class T>
T LinkedList<T> :: getInfo()
{
	return info;
}

//sees if there is anything in the data structure
template<class T>
int LinkedList<T> :: isEmpty()//TODO take a look at this test it
{
	//makes and sets the found to false
	int notFound = 0;

	//if the info is null then i
	if(info == NULL)
		if(next == NULL)
			notFound = 1;
	return notFound;
}

//NOTE: this will be similar to the SparseRow class
//The class that stores the coefficient and exponent
class Term
{
	//the coefficient and exponent
protected:
	int coef;
	int exp;

public:
	Term(); //defoult constructor: setting coeff = -1 and exp = -1
	Term(int c, int e); //a constructor setting coeff to the terms given
	Term(const Term* in); //copy constructor
	virtual ~Term(); //destructor
	void display(); //displays the (coeff,exp)

	//getters
	int getCoef();
	int getExp();

	//setters if needed
	void setCoef(int in);
	void setExp(int in);

	//seeing if the Term exists
	int exists();

};

//default constructor
Term :: Term()
{
	coef = -1;
	exp = -1;
}

//Constructor
Term :: Term(int c, int e)
{
	coef = c;
	exp = e;
}

//copy constructor
Term :: Term(const Term* in)
{
	coef = in->coef;
	exp = in->exp;
}

//destructor empty nothing is dinamically created
Term :: ~Term()
{

}

//displays the terms int the (coef,exp) format
void Term :: display()
{
	cout << "(" << getCoef() << "," << getExp()<< ")";
}

//getter for coefficiant
int Term :: getCoef()
{
	return coef;
}

//getter for exponent
int Term :: getExp()
{
	return exp;
}

//sets the coeff
void Term :: setCoef(int in)
{
	coef = in;
}

//sets the exp
void Term :: setExp(int in)
{
	exp = in;
}

//idk if this even works
int Term :: exists()//TODO
{

	for(int i = 0; i < 100; i++)
	{
		if(coef == i)
		{
			return 1;
		}
	}
	return 0;
}

//NOTE: this will be similar to the SparesMatrix class

class Polynomial
{
protected:
	//a linkedList of terms named myPoly
	LinkedList<Term >* myPoly;
public:
	Polynomial(); //default constructor sets myPoly to size 0
	Polynomial(int c, int e);
	Polynomial(const Polynomial* in); //copy constructor
	virtual ~Polynomial(); //destructor

	void addTerm(int c, int e); //add the term to myPoly
	void deleteTerm(int e); //deletes the selected expoenent

	int evaluatePoly(int value); //Given a value for x evaluate the polynomial and print the result.

	Polynomial addPolynomial(Polynomial& other); //adds the polynomials
	Polynomial operator+(Polynomial& in); //calls the add method TODO

	Polynomial multiplyPolynomial(Polynomial& other); //multiplies the polynomails
	Polynomial operator*(Polynomial& in); //calls the multiply method TODO

	void printPolynomial(); // prints the polynomail

	Polynomial operator[](int pos);

	//the overloaded operator for cout
	//TODO idk if this will work
	friend ostream& operator<<(ostream& M, const Polynomial& poly)
	{
		//a for loop to go through each positionn in the polynomail
		for(int i = 0; i < poly.myPoly->size(); i++)
		{
			poly.myPoly->infoAt(i).display();

			//Puts a + after each poly but the last one
			if(i < poly.myPoly->size() - 1)
				cout << " + ";
		}
		return M;
	}

	//a getter for myPoly
	LinkedList<Term >* getMyPoly();

};

//defalt constructor
Polynomial :: Polynomial()
{
	myPoly = new LinkedList<Term>(0,0);
}

//copy constructor
Polynomial :: Polynomial(const Polynomial* in)
{
	myPoly = in->myPoly;
}

//destructor deletes the linkList myPoly
Polynomial :: ~Polynomial()
{
	delete myPoly;
}

//add a term to the polynomial and make sure that the polynomial is kept in sorted order of the exponent.
void Polynomial :: addTerm(int c, int e)//TODO redo this think about it differently
{

	bool found = false;

	Term* term = new Term(c,e);

	//cout << "before first for loop " << endl;
	for(int i = 0; i < myPoly->size(); i++)
	{
		//cout << "in the for loop" << endl;
		if(myPoly->infoAt(i).getExp() == e)
		{
			int nc = c + myPoly->infoAt(i).getCoef();
			//myPoly->infoAt(i).setCoef(nc);

			Term* nt = new Term(nc, e);

			myPoly->removeAt(i);
			myPoly->insertAt(i, nt);
			found = true;
			return;
		}
	}
	//cout << "after the 1st loop" << endl;

	for(int i = 0; i < myPoly->size(); i++)
	{
		if(e < myPoly->infoAt(i).getExp() && !found)
		{
			myPoly->push_back(term);
			found = true;
			return;
		}
		else
		{
			myPoly->insertAt(i,term);
			found = true;
			return;
		}
	}

//	for(int i = 0; i < myPoly->size(); i++)
//	{
//		if(e > myPoly->infoAt(i).getExp())
//		{
//
//		}
//	}
	//cout << "after the 2nd loop" << endl;

	if(!found)
	{
		myPoly->add(term);
	}

}

//delete the term, that is set the coefficient to be zero for the term containing the exponent specified as the parameter.
void Polynomial :: deleteTerm(int e)
{
	bool found = false;
	for(int i = 0; i<myPoly->size(); i++)
	{
		if(myPoly->infoAt(i).getExp() == e)
		{
			myPoly->removeAt(i);
			found = true;
		}
	}

	if(!found)
		cout << "there is no term in the polynomial with an exponent of " << e << "." << endl;

}

//a getter for myPoly
LinkedList<Term >* Polynomial :: getMyPoly()
{
	return myPoly;
}

// Given a value for x evaluate the polynomial and print the result.
int Polynomial :: evaluatePoly(int x)
{
	//make and declare a sum exponent and coefficient
	int sum = 0;
	int c = 0;
	int e = 0;

	//a new x for multiplication
	int nx;

	//a for loop that goes threw each postion in the linked list
	for(int i = 0; i < myPoly->size(); i++)
	{

		if(myPoly->infoAt(i).getExp() > 1)
		{

			//resetting nx = x
			nx = x;

			//setting coef to the term coef in the ith postion
			c = myPoly->infoAt(i).getCoef();

			//same thing for the expnent
			e = myPoly->infoAt(i).getExp();

			//for loop that multiplies the c as many times as the exponent is
			//basically what ^ does
			for(int j = 0; j < e-1; j++)
			{
				nx *= x;
			}
			//multiplying the coef times the new x and adding in the old sum
			sum = sum + (c*nx);
		}

		//if the exp is = to 1
		else if(myPoly->infoAt(i).getExp() == 1)
		{
			//setting the new x to coef * x
			nx = myPoly->infoAt(i).getCoef() * x;

			//adding the old sum + the new x
			sum = sum + nx;
		}

		//goes in if the exp is 0 therefore just adds the coef to the old sum
		else
			sum = sum + myPoly->infoAt(i).getCoef();
	}

	//Prints the answer and makes it look pretty
	cout<< "When x = " << x << ", the answer is " << sum << "." << endl;
	return sum;
}


//adds the polynomails and returns another polynomail
Polynomial Polynomial :: addPolynomial(Polynomial& other)
{
	//a temp of type polynomial to return basically
	Polynomial* temp = new Polynomial();

	//a for loop to go through the myPoly that we have
	//The add term will add the exp that are the same and add what is not in the other
	//therefore this is all that is needed to add the polynomails
	for (int i = 0; i < myPoly->size(); i++)
		temp->addTerm(myPoly->infoAt(i).getCoef(),myPoly->infoAt(i).getExp());

	//a for loop to go through the other myPoly
	for(int j = 0; j < other.myPoly->size(); j++)
		temp->addTerm(other.myPoly->infoAt(j).getCoef(),other.myPoly->infoAt(j).getExp());

	//prints out the polynomial
	cout << "Add = ";
	temp->printPolynomial();
	cout << endl;

	return (*temp);

}


//calls the add polynomails method and makes it to only call the +
Polynomial Polynomial :: operator+(Polynomial& in)
{
	return addPolynomial(in);
}


//Prints the Polynomails in (c,e) + (c,e) format
void Polynomial :: printPolynomial()
{
	//a for loop to go through each positionn in the polynomail
	for(int i = 0; i < myPoly->size(); i++)
	{
		myPoly->infoAt(i).display();

		//Puts a + after each poly but the last one
		if(i < myPoly->size() - 1)
			cout << " + ";
	}
}


//Multiplies the polynomials and returns a new polynomial
Polynomial Polynomial :: multiplyPolynomial(Polynomial& other)//TODO delete the couts
{
	//make a temp poly to put in the new values and return
	Polynomial* temp = new Polynomial();

	//variables for coef and exp to be added and multiplied later
	int nc, ne, mc, me, newC, newE;

	//a for loop threw myPoly
	for(int i = 0; i < myPoly->size(); i++)
	{
		//a for loop through the my poly we are bringing in
		for(int j = 0; j < other.myPoly->size(); j++)
		{
			//setting myPoly coef and exp
			nc = myPoly->infoAt(i).getCoef();
			ne = myPoly->infoAt(i).getExp();

			//setting other myPoly coef and exp
			mc = other.myPoly->infoAt(j).getCoef();
			me = other.myPoly->infoAt(j).getExp();

			//multiplying coef and adding exp
			newC = nc * mc;
			newE = ne + me;

			//adding the new values to the temp
			//addTerm will put it in order and add coef if exp are the same
			temp->addTerm(newC,newE);
		}
	}
	cout << "Multiply = ";
	temp->printPolynomial();
	cout << endl;
	return temp;
}


//calls the multiply method
Polynomial Polynomial :: operator*(Polynomial& in)
{
	//calling the multiply
	return multiplyPolynomial(in);
}

//does nothing
Polynomial Polynomial :: operator[](int pos)
{
	Polynomial temp = new Polynomial();
	temp.addTerm(myPoly->infoAt(pos).getCoef(), myPoly->infoAt(pos).getExp());
	return temp;
}


int main() {

	//giiven in the pdf
	//Create an array of polynomials the maximum being 10.
	Polynomial Polynomials[10];
	char command;
	int polynum, coefficient, exponent,value,i,j;
	cin >> command;
	while (!cin.eof())
	{
		switch (command)
		{
		case 'I':

			cin >> polynum;

			cin >> coefficient;

			cin >> exponent;

			Polynomials[polynum].addTerm(coefficient, exponent);
			break;
			//continue;
		case 'D':
			cin >> i >> j;
			Polynomials[i].deleteTerm(j);
			break;
		case 'A':
			cin >> i >> j;
			Polynomials[i] + Polynomials[j];
			break;
		case 'M':
			cin >> i >> j;
			Polynomials[i] * Polynomials[j];
			break;
		case 'E':
			cin >> polynum >> value;
			Polynomials[polynum].evaluatePoly(value);
			break;
		case 'P':
			cin >> polynum;
			cout << Polynomials[polynum] << endl;
			break;
		default:
			cout <<"I missed something" << endl;

		}
		cin >> command;

	}

	return 0;
}
