/*
 * Project2.cpp
 *
 *  Created on: Mar 8, 2019
 *      Author: coysmac
 */


#include <iostream>
using namespace std;
#include <vector>
#include <ostream>
#include <exception>


template < class B>
class ExceptionAdd {};

//this one
template < class B>
class ExceptionMultiply {};

template < class B>
class ExceptionCV{};

template <class B>
class SparseRow
{
protected:
	int row; //Row#
	int col; //Column#
	B value; //We will assume that all our values will be integers
public:
	SparseRow (); //default constructor; row=-1;col=-1;value=0
	SparseRow(int r, int c, B& v);
	virtual ~SparseRow(); //Destructor
	void display(); // print Row#, Column#, value
	//other methods as you deem fit

	//getters and setters
	int getRow();
	int getCol();
	int getVal();

	void setRow(int r);
	void setCol(int c);
	void setVal(B v);

};


//The display for sparseRow
template <class B>
void SparseRow<B>:: display()
{
	cout << getRow()  << ", " << getCol() << ", " << getVal() << endl;
}


//a default constructor for sparserow
template <class B>
SparseRow<B>::SparseRow()
{
	row = -1;
	col = -1;
	value = -1;
}


//destrustor for sparseRow but eclipse already does it therefore wont allow you to do it again
template<class B>
SparseRow<B> :: ~SparseRow()
{

}


//a constructor for sparserow
template <class B>
SparseRow<B> :: SparseRow(int r, int c, B& v)
{
	row = r;
	col = c;
	value = v;
}


//getters for SparseRow
template <class B>
int SparseRow<B> :: getRow()
{
	return row;
}

template <class B>
int SparseRow<B> :: getCol()
{
	return col;
}

template <class B>
int SparseRow<B> :: getVal()
{
	return value;
}

template <class B>
void SparseRow<B> :: setRow(int r)
{
	row = r;
}

template <class B>
void SparseRow<B>::setCol(int c)
{
	col = c;
}

template <class B>
void SparseRow<B>::setVal(B v)
{
	value = v;
}



template <class B>
class SparseMatrix
{

protected:
	int noRows; //Number of rows of the original matrix
	int noCols; //Number of columns of the original matrix
	B commonValue; //read from input
	int noNonSparseValues;
	vector<SparseRow<B> >* myMatrix;  //Array–should be dynamic
	int currSize;

public:
	SparseMatrix ();
	SparseMatrix (int n, int m, int cv);
	virtual ~SparseMatrix(); //Destructor
	void setSparseRow (int pos, int r, int c, B& v);


	//for multiplicationand similar for addition and transpose
	void mdisplay();//Display the sparse matrix
	void displayMatrix (); //Display the matrix in its original format

	//other methods as you deem fit
	void setMyMatrix(SparseRow<B> r, int c);
	vector<SparseRow<B> >* getMyMatrix();
	int finder(int i, int j);



	//overload methods
	SparseMatrix<B>* operator*(SparseMatrix<B> M);
	SparseMatrix<B>* operator+(SparseMatrix<B>& M);
	SparseMatrix<B>* operator!();
	friend ostream& operator<<(ostream& M, const SparseMatrix<B>& Mat)
	{
		//loops thre the matrix and calls row display
		for(int i = 0; i < Mat.myMatrix->size(); i++)
		{
			Mat.myMatrix->at(i).display();
		}
		return M;
	}


	//getters and setters
	int getnoRows();
	int getnoCols();


};

//default constructor
template <class B>
SparseMatrix<B>:: SparseMatrix()
{
	//setting all the variables to a default amount
	noRows = -1;
	noCols = -1;
	commonValue = -1;
	noNonSparseValues = 0;
	myMatrix = new vector<SparseRow<B> >(0);
	currSize = 0;

}
//default sparseMatrix
template <class B>
SparseMatrix<B>::SparseMatrix (int n, int m, int cv)
{
	//setting the variables to the inputs
	noRows = n;
	noCols = m;
	commonValue = cv;
	noNonSparseValues = 0;
	myMatrix =  new vector<SparseRow<B> >(0);
	currSize = 0;
}


//getter for myMatrix
template <class B>
vector<SparseRow<B> >* SparseMatrix<B> :: getMyMatrix()
{
	return myMatrix;
}


//display for matrix
template <class B>
void SparseMatrix<B> :: mdisplay()
{
	//loops thre the matrix and calls row display
	for(int i = 0; i < myMatrix->size(); i++)
	{
		myMatrix->at(i).display();
	}
}


//destructor
template <class B>
SparseMatrix<B> :: ~SparseMatrix()
{
	delete myMatrix;
}


//displays the matrix in its original state
template <class B>
void SparseMatrix<B> :: displayMatrix()
{
	//making a matrix array
	int array[noRows][noCols];

	//a boolean to see if the value is there
	bool found = false;

	//an incrementer to find the position
	int k;

	//looping through the rows and columns
	for(int i = 0; i < noRows; i++)
	{
		for(int j = 0; j < noCols; j++)
		{
			//loops threw the values @ k to check if they are equal
			found = false;

			for(k = 0; k < getMyMatrix()->size(); k++)
			{
				if((getMyMatrix()->at(k).getRow() == i) && (getMyMatrix()->at(k).getCol() == j))
				{
					//if they are change to true
					found = true;

					//break so it doesnt keep going through and overrighting the ones before
					break;
				}
			}

			//if they are the same then put the value in that spot
			if(found)
			{
				array[i][j] = myMatrix->at(k).getVal();
			}
			//if not then put in a commonValue
			else
			{
				array[i][j] = commonValue;

			}

		}
	}

	//go threw the array matrix to display the matrix
	for(int i = 0; i < noRows; i++)
	{
		for(int j = 0; j < noCols; j++)
		{
			cout << array[i][j] << " " ;
		}
		cout << endl;
	}
}


template <class B>
void SparseMatrix<B>:: setSparseRow (int pos, int r, int c, B& v)
{
	//making a row with the spacific row col and value
	SparseRow<B>* row = new SparseRow<B>(r, c, v);

	//pushing the row to the last position
	myMatrix->push_back(*row);

	currSize++;
}

//add method
template <class B>
SparseMatrix<B>* SparseMatrix<B> :: operator!()
{

	//creating a temp sparseMatrix
	SparseMatrix<B>* tempTra = new SparseMatrix(noRows, noCols, commonValue);
	B v = 0;
	int count = 0;


	//for loop to go threw myMatrix
	for(int i = 0; i < noRows; i++ )
	{
		for(int j = 0; j < noCols; j++)
		{
			if(myMatrix->at(count).getRow() == i && myMatrix->at(count).getCol() == j)
			{
			//setting value to v
			v = myMatrix->at(count).getVal();

			//setting myMatrix into tempTran
			tempTra->setSparseRow(count, j, i, v);

			//keeps the count the right size
			if(count < myMatrix->size()-1)
			{
				count++;
			}
			}
		}

	}

	//resizing the vector to the counter +1
	(*tempTra).myMatrix->resize(count + 1);

	//returning the the new SparseMatrix
	return tempTra;
}

template <class B>
SparseMatrix<B>* SparseMatrix<B> :: operator+(SparseMatrix<B>& M)
{
	//else if for what to throw for the try catch in the main
	if(noCols != M.noCols || noRows != M.noRows)
		throw ExceptionAdd<B>();
	else if(commonValue != M.commonValue)
		throw ExceptionCV<B>();


	//creating a temp sparematrix
	SparseMatrix* temp = new SparseMatrix(noRows, noCols, M.commonValue);

	//a counter for size on the resize
	int count = 0;

	//value for adding together
	int Value = 0;

	//for loop looping through the points in the matrix
	for(int i = 0; i < currSize; i++)
	{
		for(int j = 0; j < currSize; j++)
		{
			//adds all values together
			Value = finder(i, j) + M.finder(i, j);

			//puts the values into the matrix that are not commonvalue at postion count
			if(Value != commonValue)
			{
				temp->setSparseRow(count, i, j, Value);
				count++;
			}
		}

	}

	//resizes the matrix to the correct size
	temp->myMatrix->resize(count);

	//returning the new array
	return temp;
}

template <class B>
SparseMatrix<B>* SparseMatrix<B> :: operator*(SparseMatrix<B> M)
{
	//else if for what to throw for the try catch in the main
	if(noRows != M.noCols)
		throw ExceptionMultiply<B>();
	else if(commonValue != M.commonValue)
		throw ExceptionCV<B>();


	//a resulting matrix
	SparseMatrix* result = new SparseMatrix(noRows, noCols, commonValue);

	//an incrementing counter
	int count = 0;

	//the sum value to be added into the Matrix
	B sum = 0;

	//making k so we can access it outside the for loop it is being used in
	int k;

	//double for loop through rows and cols
	for(int i = 0; i < noRows; i++)
	{
		for(int j = 0; j < noCols; j++)
		{
			//reset the sum
			sum = 0;

			for(k = 0; k < myMatrix->size(); k++)
			{
				//add the values into sum
				sum += (this->finder(i, k) * M.finder(k, j));
			}

			//check to see if sum == commonValue
			if(sum != M.commonValue)
			{
				//setting the sum in the result Matrix
				(*result).setSparseRow(count, i, j, sum);
				count++;
			}
		}
	}


	return result;

}

//finds the postions
template <class B>
int SparseMatrix<B>:: finder(int i, int j)
{
	//setting value to commonValue in case there is no set row or col
	B value = commonValue;

	for(int k = 0; k < myMatrix->size(); k++)
	{
		if((myMatrix->at(k).getRow() == i) && (myMatrix->at(k).getCol() == j))
		{
			value = myMatrix->at(k).getVal();
		}
	}


	//returns commonValue if its not the same
	return value;
}

//getters
template<class B>
int SparseMatrix<B> :: getnoRows()
{
	return noRows;
}

template<class B>
int SparseMatrix<B> :: getnoCols()
{
	return noCols;
}


int main() {
	int n, m, cv;
	SparseMatrix<int>* temp = new SparseMatrix<int>();


	cin >> n >> m >> cv;
	SparseMatrix<int>* firstOne = new SparseMatrix<int>(n, m, cv);
	SparseMatrix<int>* firstOne1 = new SparseMatrix<int>(n, m, cv);

	//Write the Statements to read in the first matrix
	int val = 0;
	int count = 0;

	//bringing in the values and setting them into the correct position
	for (int i=0; i < n; i++)
	{
		for (int j=0; j < m; j++)
		{
			cin >> val;

			if(val != cv)
			{

				//putting the values into firstOne
				(*firstOne).setSparseRow(count, i, j, val);
				(*firstOne1).setSparseRow(count, i, j, val);

				//keeps track what position first one row is on
				count++;

			}

		}

	}


	cout << "First one in sparse matrix format" << endl;
	cout << (*firstOne);

	cout << "First one in normal matrix format" << endl;
	(*firstOne).displayMatrix();


	//brings in the secound values
	cin >> n >> m >> cv;
	SparseMatrix<int>* secondOne = new SparseMatrix<int>(n, m, cv);

	int val2 = 0;
	//Write the Statements to read in the second matrix
	//same as the top
	for (int i=0; i < n; i++)
	{
		for (int j=0; j < m; j++)
		{
			cin >> val2;

			if(val2 != cv)
			{
				//putting the row in the array
				(*secondOne).setSparseRow(count, i, j, val2);

				//keeps track of the amount of val
				count++;

			}

		}

	}



	cout <<"Second one in sparse matrix format" << endl;
	cout << (*secondOne);

	cout << "Second one in normal matrix format" << endl;
	(*secondOne).displayMatrix();

	temp = !(*firstOne);
	cout << "After Transpose first one in normal format" << endl;
	(*temp).displayMatrix();


	temp = !(*secondOne);
	cout << "After Transpose second one in normal format" << endl;
	(*temp).displayMatrix();

	cout << "Multiplication of matrices in sparse matrix form:" << endl;

	//try catch to catch our custom exceptions
	try{
		temp = (*secondOne) * (*firstOne);
		cout << (*temp);
	}
	catch(ExceptionMultiply<int>& e)
	{
		//happens when the ExceptionMultiply is thrown and couts our message
		cout << "Error: Columns of first matrix do not match rows of second matrix. \n";
	}
	catch(ExceptionCV<int>& e)
	{
		//happens when the ExceptionCV is thrown and couts our message
		cout << "Error: Common values do not match \n";
	}

	cout << "Addition of matrices in sparse matrix form:" << endl;

	//try catch to catch our custom exceptions
	try{
		//multiplies our secound matrix times our firstMatrix
		temp = (*secondOne) + (*firstOne1);
		cout << (*temp);
	}
	catch(ExceptionAdd<int>& e)
	{
		//happens when the ExceptionAdd is thrown and couts our message
		cout << "Error: Rows or columns don't match. \n" << endl;
	}
	catch(ExceptionCV<int>& e)
	{
		//happens when the ExceptionCV is thrown and couts our message
		cout << "Error: Common values don't match. \n";
	}

	return 0;
}
