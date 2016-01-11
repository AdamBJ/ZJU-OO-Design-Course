#include "Book.h"
#include "GlobalVariables.h"
#include <iostream>
#include <string>

using namespace std;

/*Public Methods*/

Book::Book(double price, int index, string author, string title) : price(price), index(index), author(author), title(title)
{
	deleted = false;
	numbercopies = 1;
	copiessold = 0;
	bookcount++;
	bookcountwcopies++;
	lifetimebookcount++;
}

Book::Book()
{
}

Book::~Book()
{
}

double Book::getprice() 
{
	return price;
}

int Book::getindex() 
{
	return index;
}

string Book::getauthor()
{
	return author;
}

string Book::gettitle()
{
	return title;
}

bool Book::getdeletestatus()
{
	return deleted;
}

void Book::setdeletestatus(bool deletestatus)
{
	deleted = deletestatus;
}

void Book::printprice() 
{
	
	cout<< "Price: $" << price << endl;
}

void Book::printindex() 
{
	cout<< "Index number: " << index << endl;
}

void Book::printauthor()
{
	cout<< "Author: " << author << endl;
}

void Book::printtitle()
{
	cout<< "Title: " << title << endl;
}

void Book::printnumcopies()
{
	cout<< "Copies: " << numbercopies << endl;
}

int Book::getnumcopies()
{
	return numbercopies;
}

int Book::getcopiessold()
{
	return copiessold;
}

void Book::incnumcopies()
{
	numbercopies++;
}

void Book::decnumcopies()
{
	numbercopies--;
}

void Book::inccopiessold()
{
	copiessold++;
}

void Book::deccopiessold()
{
	copiessold--;
}