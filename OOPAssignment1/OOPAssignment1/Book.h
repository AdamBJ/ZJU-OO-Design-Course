#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include <iostream>

using namespace std;

class Book { //client class of Bookstore.
	public:
		Book( double price, int index ,string author,string title); //create new book with price and index as args
		Book(); //overloaded constructor for in initializing our global array inventory. As real book are added dummy book contructed here are overwritten.
		~Book();
		double getprice();
		int getindex();
		string gettitle();
		string getauthor();
		bool getdeletestatus();
		void setdeletestatus(bool deletestatus);//sets deleted field to true
		int getnumcopies();
		int getcopiessold();
		
		void inccopiessold();
		void deccopiessold();
		void incnumcopies();
		void decnumcopies();

		
		void printprice();
		void printindex();
		void printtitle();
		void printauthor();
		void printnumcopies();
		
	private:
		double price;
		int index;
		int numbercopies;
		int copiessold;//tracks number copies sold
		
		string title;
		string author;
		bool deleted;//used when searching the inventory for a place to insert a new book.
};
#endif /* BOOK_H_ */