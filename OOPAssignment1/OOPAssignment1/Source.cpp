#include "Book.h"
#include "Bookstore.h"
#include "GlobalVariables.h"
#include <iostream>
#include <string>

;using namespace std;

int main()
{
	Bookstore SFU = Bookstore();
	Book test = Book(2.99,1,"Adam","The Life and Death of Adam");
	//test.getprice();
	//test.getauthor();
	test.gettitle();
	//test.getindex();*/
	SFU.addnewBook();
	cin.get();
}



