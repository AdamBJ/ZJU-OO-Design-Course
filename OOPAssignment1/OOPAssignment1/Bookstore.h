#ifndef BOOKSTORE_H_
#define BOOKSTORE_H_
#include <string>
#include "Book.h"

using namespace std;

class Bookstore {
	public:
		//CHECKING FOR BAD INPUT NOT IMPLEM'D. What if index== but title dif? EORRROR
		Bookstore();
		void initialize();
		bool verify(Book current); //checks books before they are added to the library

		void addnewBook ();//@Puts new book in the global array "inventory". calls Book() from book class
		void removeBook(int targetindex);//@uses global variable *Book database !!
		void removeBook(string targettitle);

		void listBooks (); //@Lists inventory from start to finish. All information is included. *Call private method printBookinfo() repeatedly.*
		
		int findBook(int targetindex); //@
		int findBook(string title); //@overloaded method, lets user search by index or title.
		
		void sellBook(int targetindex);//@same as remove book but updates cash
		void sellBook(string title);
		void buyBook();// @same as addnewbook but updates cash
		void refundBook(int bookindex);//same as addnewBook but updates cash
		void refundBook(string title);
		
		double getcash();
		bool exit();

	private:
		int getbook(int targetindex);//same as find book, but doesn't display info the to user
		int getbook(string targettitle);//returns index of book with target title
		bool add_duplicatebook(Book current);
		
		bool remove_duplicatebook(int target);
		bool remove_duplicatebook(string title);
		bool sell_duplicatebook(int bookindex);
		bool sell_duplicatebook(string title);

		void printBookinfo(int targetindex);
		
		double cash;
};
#endif /* BOOKSTORE_H_ */