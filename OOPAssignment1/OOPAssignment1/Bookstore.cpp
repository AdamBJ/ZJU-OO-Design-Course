#include "Bookstore.h"
#include "Book.h"
#include "GlobalVariables.h"
#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::cin;
using std::endl;

/*Constructor*/

Bookstore::Bookstore()
{
	initialize();
}

/*Public Methods*/

void Bookstore::addnewBook()//searches array until empty or removed entry found
{
	

	cout<<"What is the title of the book?"<<endl;
	string title;
	
	getline(cin, title);

	cout<<"Who is the author?"<<endl;
	string author;
	
	getline(cin, author);

	/* Test for bad input. Same happens for price*/
	int index = 0;
	
	cout<<"What is the index number?"<<endl;
	if (!(cin >> index)) 
	{
		cout << "Please enter an number!\n";
		while (!(cin >> index)) 
		{
		//cout << "Please enter an number!\n";
		cin.clear();   // prepare cin
		cin.ignore();  // ignore the bad character
		}
	} 
	cin.get();


	double price;
	
	cout<<"What is the book's price?"<<endl;

	if (!(cin>>price)) 
	{
		cout << "Please enter an numerical value for price!\n";
		while (!(cin>>price) )
		{
		//cout << "please enter an number!\n";
		cin.clear();   // prepare cin
		cin.ignore();  // ignore the bad character
		}
	} 
	cin.get();

	Book newbook = Book(price,index,author,title);
	bool gooddata = verify(newbook);
	if( gooddata)
	{
	bool alreadyHaveCopy = add_duplicatebook(newbook);//Increments quantity counter if the book is already in the library. Returns false if book not found.

	if(!alreadyHaveCopy)//If a copy doesn't already exisit in the library, add a new one.
		{
		int i = 0;
		bool found = false;
	
		if(bookcount==1 && !inventory[0].getdeletestatus()) //then put the put in the first position as long as there isn't a dormant node.
			{
				inventory[0] = newbook;
				found = true;
			}

		while (!found && i <100) //search inventory until an insertion point is found
			{	
				int index = inventory[i].getindex();
			

				if (index == -1) 
				{
					inventory[i] = newbook;
					found = true;
				}
				i++;
			}
		if (!found)//only way this is possible is if we have gone through the entire array and not found a position
			{
				cout<<"Maximum library size reached. Please sell some books!\n";
			}
		}
	cout<<"Success!\n";
} else
	{
		cout << "That book cannot be added to the store. It shares some but not all of its identifier information with another book already on the shelves.\n"
				"Did you enter all the information correctly?\n";
		
		/*These values are increm'd when the bad book is created. Decrement them*/
		bookcount--;
		bookcountwcopies--;
		lifetimebookcount--;
	}

}

int Bookstore::getbook(string targettitle)
{
	
	for (int i = 0; i<lifetimebookcount; i++)
	{
		string title = inventory[i].gettitle();
		bool delstatus = inventory[i].getdeletestatus();

		if (title == targettitle && !delstatus) 
		{
			return i;
		}
	}
	return -1;
}

int Bookstore::getbook(int targetindex)
{
	for (int i = 0; i<lifetimebookcount; i++)
	{
		if (inventory[i].getindex() == targetindex && !inventory[i].getdeletestatus()) //if we find the book and it hasn't been deleted
			{
					return i;
		} 
	}
	return -1;
}

int Bookstore::findBook(int targetindex) 
{
	for (int i = 0; i<bookcount; i++)
	{
		if (inventory[i].getindex() == targetindex && !inventory[i].getdeletestatus()) //if we find the book and it hasn't been deleted
		{
			cout<<"Book found! Do you want to display the book's information? Y/N\n";
			
			char resp;
			cin>>resp;

			if (resp=='Y') 
			{
				inventory[i].printtitle();
				inventory[i].printauthor();
				inventory[i].printprice();
				inventory[i].printindex();
				inventory[i].printnumcopies();
				cin.get();
				return i;
			}
		} 
	}
cout<<"We don't have that book.\n";
return -1;
}

int Bookstore::findBook(string title) 
{
	for (int i = 0; i<bookcount; i++)
	{
		if (inventory[i].gettitle() == title && !inventory[i].getdeletestatus()) 
		{
			cout<<"Book found! Do you want to display the book's information? Y/N\n";
			
			char resp;
			cin>>resp;

			if (resp=='Y') 
			{
				inventory[i].printtitle();
				inventory[i].printauthor();
				inventory[i].printprice();
				inventory[i].printindex();
				inventory[i].printnumcopies();
				cin.get();
				return i;
			} else
			{
				cin.get();
				return i;
			}
		} 
	}
	cout<<"We don't have that book.\n";
	return -1;
}

void Bookstore::sellBook(int targetindex)
{
	int target = getbook(targetindex);
	
	int numcopies = 0;

	bool removeduplicate = false;

	if (target != -1) //if target exists
	{
	numcopies = inventory[target].getnumcopies();//first check if duplicate exists.
	}

	if (numcopies > 1)
	{
	int targetindex = inventory[target].getindex();
	removeduplicate = sell_duplicatebook(targetindex); //If it does, this function deals with the removal. If not it returns false.
	}

	if (removeduplicate)//update cash
	{ 
		cash += inventory[target].getprice();
		cout<<"The register now holds $" << getcash() << "." << endl;
	} else
		{
		if (target == -1) 
			{
				cout<<"We don't own a copy of that book!\n";
		} else 
			{
				bookcount--;

				inventory[target].setdeletestatus(true);//delete the book at specified location in library.
				inventory[target].decnumcopies();
				inventory[target].inccopiessold();

				cash += inventory[target].getprice();
				cout<<"One copy of index \"" << targetindex << "\" has been sold.\n";
				cout<<"The register now holds $" << getcash() << "." << endl;
			}
		}
}

void Bookstore::sellBook(string targettitle)
{
	int target = getbook(targettitle);//return the index of our target in the storage array. NOT THE "INDEX" of the book

	int numcopies = 0;

	bool removeduplicate = false;
	
	if (target != -1) //if target exists
	{
	numcopies = inventory[target].getnumcopies();//first check if duplicate exists.
	}

	if (numcopies > 1)
	{
	removeduplicate = sell_duplicatebook(targettitle);//first check if duplicate exists. if it does, this function deals with the removal. if not it returns false.
	}

	if (removeduplicate)//update cash
	{ 
		cash += inventory[target].getprice();
		cout<<"The register now holds $" << getcash() << "." << endl;
	} else
		{
		if (target == -1) 
			{
				cout<<"We don't own a copy of that book!\n";
		} else 
			{
				bookcount--;
				inventory[target].setdeletestatus(true);//delete the book at specified location in library.
				inventory[target].decnumcopies();
				inventory[target].inccopiessold();
				cash += inventory[target].getprice();
				cout<<"One copy of \"" << targettitle << "\" has been sold.\n";
				cout<<"The register now holds $" << getcash() << "." << endl;
			}
		}
}

void Bookstore::buyBook() // this code is addnewBook() with a small change that updates the cash field.
{
	cout<<"What is the title of the book?"<<endl;
	string title;
	
	getline(cin, title);

	cout<<"Who is the author?"<<endl;
	string author;
	
	getline(cin, author);

	/* Test for bad input. Same happens for price*/
	int index = 0;
	
	cout<<"What is the index number?"<<endl;
	if (!(cin >> index)) 
	{
		cout << "Please enter an number!\n";
		while (!(cin >> index)) 
		{
		//cout << "Please enter an number!\n";
		cin.clear();   // prepare cin
		cin.ignore();  // ignore the bad character
		}
	} 
	cin.get();


	double price;
	
	cout<<"What is the book's price?"<<endl;

	if (!(cin>>price)) 
	{
		cout << "Please enter an numerical value for price!\n";
		while (!(cin>>price) )
		{
		//cout << "please enter an number!\n";
		cin.clear();   // prepare cin
		cin.ignore();  // ignore the bad character
		}
	} 
	cin.get();


	Book newbook = Book(price,index,author,title);

	bool gooddata = verify(newbook);
	if( gooddata)
	{	
	/* Update cash. Add more if needed. */
	if ((cash - price) < 0) 
	{
		cout<< "Uh-oh! We don't have enough money to buy that book! It costs $" << price << " but we only have $" << cash << "!\n";
		cout<< "Lucky for you, I'm a nice guy so I'll give you $"<< price-cash <<". We have the book now, but the register is empty!\n";
		cash = 0;
	}
	/* Continue with addnewBook() method */

	bool alreadyHaveCopy = add_duplicatebook(newbook);//Increments quantity counter if the book is already in the library. Returns false if book not found.

	if(!alreadyHaveCopy)//If a copy doesn't already exisit in the library, add a new one.
		{
		int i = 0;
		bool found = false;
	
		if(bookcount==0 && !inventory[0].getdeletestatus()) //then put the put in the first position, so long as a deleted book isn't there.
			{
				inventory[0] = newbook;
				found = true;
			}

		while (!found && i <100) //search inventory until an insertion point is found
			{	
				int index = inventory[i].getindex();

				if (index == -1) 
				{
					inventory[i] = newbook;
					found = true;
				}
				i++;
			}
		if (!found)//only way this is possible is if we have gone through the entire array and not found a position
			{
				cout<<"Maximum library size reached. Please sell some books!\n";
			}
		}
	} else
	{
		cout << "That book cannot be added to the store. It shares some but not all of its identifier information with another book already on the shelves.\n"
				"Did you enter all the information correctly?\n";
		
		/*These values are increm'd when the bad book is created. Decrement them*/
		bookcount--;
		bookcountwcopies--;
		lifetimebookcount--;
	}
}

void Bookstore::refundBook(string title) 
{
	bool flag = false;

	for (int i = 0; i<lifetimebookcount; i++)
	{
		string titlecheck = inventory[i].gettitle();
		int copiessold = inventory[i].getcopiessold();
		

		if (title == titlecheck && copiessold>0) 
		{
			inventory[i].setdeletestatus(false);
			/* Update cash. Add more if needed. */
			cash -= inventory[i].getprice();
			if (cash < 0) 
			{
				cout<< "Uh-oh! We don't have enough money to refund that book! It costs $" << inventory[i].getprice() << " but we only have $" << cash+inventory[i].getprice() << "!\n";
				cash += inventory[i].getprice();
				cout<< "Lucky for you, I'm a nice guy so I'll give you $"<< inventory[i].getprice() <<". Total cash in the register is now $" << cash << ".\n\n";
				flag = true;
			} else
			{
				cout <<"Refund completed. The register now holds $" << cash << "." << endl;
				flag = true;
			}
			inventory[i].deccopiessold();
			inventory[i].incnumcopies();

			if (inventory[i].getnumcopies() > 1)
			{
				bookcountwcopies++;//new copy of previously existing type
			} else
			{
				bookcount++;//new type of book in the library
			}

		} 
	}
	if (!flag)	
		{
		cout << "We never sold that book." <<endl;
		}
}



void Bookstore::refundBook(int bookindex) //searches for the deleted book, undeletes it and updates cash. very similar to getbook(int).
{
	bool flag = false;


	for (int i = 0; i<lifetimebookcount; i++) //search the array for the potential refund. If found, update inventory and cash accordingly.
	{
		int copiessold = inventory[i].getcopiessold();//in order to refund, we must have sold this book at least once.

		if (inventory[i].getindex() == bookindex && copiessold > 0) 
			{
					inventory[i].setdeletestatus(false);
					/* Update cash. Add more if needed. */
					cash -= inventory[i].getprice();
					if (cash < 0) 
					{
						cout<< "Uh-oh! We don't have enough money to refund that book! It costs $" << inventory[i].getprice() << " but we only have $" << cash+inventory[i].getprice() << "!\n";
						cash += inventory[i].getprice();
						cout<< "Lucky for you, I'm a nice guy so I'll give you $"<< inventory[i].getprice() <<". Total cash in the register is now $" << cash << ".\n\n";
						flag = true;
					} else
					{
						cout <<"Refund completed. The register now holds $" << cash << "." << endl;
						flag = true;
					}

			inventory[i].deccopiessold();
			inventory[i].incnumcopies();

			if (inventory[i].getnumcopies() > 1)
			{
				bookcountwcopies++;//new copy of previously existing type
			} else
			{
				bookcount++;//new type of book in the library
			}

		} 
	}
	if (!flag)
			{
				cout << "We never sold that book." <<endl;
			}
}

void Bookstore::removeBook(int targetindex)
{
	int target = getbook(targetindex);
	
	int numcopies = 0; 

	bool removeduplicate = false;
	
	if( target != -1) //if book exists
	{
	numcopies = inventory[target].getnumcopies();//first check if duplicate exists.
	}

	if (numcopies > 1)
	{
	int targetindex = inventory[target].getindex();
	removeduplicate = remove_duplicatebook(targetindex); //If it does, this function deals with the removal. If not it returns false.
	}

	if (!removeduplicate)
		{
		if (target == -1) 
			{
				cout<<"We don't have a copy of that book!\n";
		} else 
			{
				bookcount--;
				inventory[target] = Book(-1,-1,"-1","-1"); //this is removed, not deleted. we overwrite it so the space is available again
				bookcount--;//decrement for the fake book just added
				cout<<"One copy of index \"" << targetindex << "\" has been removed from the store.\n";
			}
		}
}

void Bookstore::removeBook(string targettitle) //same as sell book, but doesn't update cash
{
	int target = getbook(targettitle);
	
	bool removeduplicate = false;

	int numcopies = 0;

	if (target != -1)
	{
		numcopies = inventory[target].getnumcopies();//first check if duplicate exists.
	}

	if (numcopies > 1)
	{
	removeduplicate = remove_duplicatebook(targettitle); //If it does, this function deals with the removal. If not it returns false.
	}

	if (!removeduplicate)
	{ 
		if (target == -1) 
			{
				cout<<"We don't own a copy of that book!\n";
		} else 
			{
				bookcount--;
				inventory[target] = Book(-1,-1,"-1","-1"); //this is removed, not deleted. we overwrite it so the space is available again
				bookcount--;//decrement for the fake book just added
				cout<<"One copy of \"" << targettitle << "\" has been removed.\n";
			}
		}
}


void Bookstore::listBooks() 
{
	if (bookcount!=0)
		{
		int printedcount = 0;
		for (int i=0; printedcount < bookcount; i++) 
			{
				if (!inventory[i].getdeletestatus() && inventory[i].getindex()!=-1)//if the current node is not deleted or empty, print it
				{
						cout << setfill('-') << setw(80) << "-";
						inventory[i].printtitle();
						inventory[i].printauthor();
						inventory[i].printindex();
						inventory[i].printprice();
						inventory[i].printnumcopies();
						printedcount++;
						cout << setfill('-') << setw(80) << "-";
				}		
			}
		cout << "In total there are " << bookcountwcopies << " book(s) in the store." <<endl;
		} else 
			{
				cout<<"The store is empty!"<<endl;
			}
}

double Bookstore::getcash()
{
	return cash;
}

/* Private Methods */

void Bookstore::initialize() 
{
	for (int i=0 ; i<100 ; i++) 
	{
	inventory[i] = Book(-1,-1,"-1","-1");
	}
	cash = 0;
	lifetimebookcount=0;
	bookcount=0;
	bookcountwcopies=0;//these are unintentionally incremented by the array init. Since the array isn't filled with real books bookcount shouldn't increase.
}

bool Bookstore::verify(Book current) //protects library from adding a book with the same index as an existing book but with different fields.
{
	int currindex = current.getindex(); // this is the book id index, not the array posn
	int inlibraryposn = getbook(currindex);//returns the array index of the copy already in the store
	if (inlibraryposn!=-1)
	{
		if(inventory[inlibraryposn].gettitle() == current.gettitle() && inventory[inlibraryposn].getauthor() == current.getauthor()
			&& inventory[inlibraryposn].getprice() == current.getprice())
		{
		return true;
		} else 
		{
			return false;
		}
	}
	return true;
}

bool Bookstore::add_duplicatebook(Book current) 
{
	int currindex = current.getindex(); // this is the book id index, not the array posn
	int inlibraryposn = getbook(currindex);//returns the array index of the copy already in the store

	if (inlibraryposn == -1)
	{
		return false; //there are no duplicate books to worry about

	} else 
	{
		inventory[inlibraryposn].incnumcopies();
		lifetimebookcount--;
		bookcount--;//this number tracks how many KINDS of books there are, not total number. so we must decrement to get rid of the extra book added when the copy was created.
		return true;
	}
}

bool Bookstore::remove_duplicatebook(string title)
{
	
	int inlibraryposn = getbook(title);

	if (inlibraryposn == -1)
	{
		return false; //there are no duplicate books to worry about
	} else 
	{
		inventory[inlibraryposn].decnumcopies();
		bookcountwcopies--;
		cout<<"One copy of \"" << title << "\" has been removed from the store.\n";
		return true;
	}
}

bool Bookstore::sell_duplicatebook(string title)
{
	
	int inlibraryposn = getbook(title);

	if (inlibraryposn == -1)
	{
		return false; //there are no duplicate books to worry about
	} else 
	{
		inventory[inlibraryposn].decnumcopies();
		inventory[inlibraryposn].inccopiessold();
		bookcountwcopies--;
		cout<<"One copy of \"" << title << "\" has been sold.\n";
		return true;
	}
}



bool Bookstore::remove_duplicatebook(int bookindex) 
{
	
	int inlibraryposn = getbook(bookindex);//gets array index for the book

	if (inlibraryposn == -1)
	{
		return false; //there are no duplicate books to worry about
	} else 
	{
		inventory[inlibraryposn].decnumcopies();
		bookcountwcopies--;
		cout<<"One copy of index \"" << bookindex << "\" has been removed from the store.\n";
		return true;
	}
}

bool Bookstore::sell_duplicatebook(int bookindex) 
{
	
	int inlibraryposn = getbook(bookindex);//gets array index for the book

	if (inlibraryposn == -1)
	{
		return false; //there are no duplicate books to worry about
	} else 
	{
		inventory[inlibraryposn].decnumcopies();
		inventory[inlibraryposn].inccopiessold();
		bookcountwcopies--;
		cout<<"One copy of index \"" << bookindex << "\" has been sold.\n";
		return true;
	}
}


bool Bookstore::exit()
{
	return true;
}