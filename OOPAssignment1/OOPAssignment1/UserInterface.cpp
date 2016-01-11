#include "UserInterface.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
/*Public Methods*/

UserInterface::UserInterface()
{
			cout << setfill('-') << setw(80) << "-" <<endl;
			cout << "Welcome to Bookstore-O-Matic v 1.0!" << endl << endl;
			SFU.initialize();//initialize the bookstore
			quit = false;
}

void UserInterface::prompt()
{
	cout << setfill('-') << setw(80) << "-"<< endl;
	cout << "Please choose from the following options:\n" << endl;
			cout <<		"1. To exit, enter \"quit\".\n\n"
						 "2. To add a book to the bookstore, enter \"add\".\n\n"
						 "3. To remove a book from the bookstore, enter \"remove <book's index>\" or \"remove <book's title>\".\n\n"
						 "4. To list all the book in the store, enter \"list\".\n\n"
						 "5. To search the store for a book, enter \"find <book's index>\" or \"find <book's title>\".\n\n"
						 "6. To sell a book from store the store, enter \"sell <book's index>\" or \"sell <book's title>\".\n\n"
						 "7. To buy a book for the bookstore, enter \"buy\".\n\n"
						 "8. To refund a book purchased from the bookstore, enter \"refund\".\n\n"
						 "9. To check the amount of cash in the register, enter \"check register\".\n\n";
}

string UserInterface::getinput()
{
	string input;
	getline(cin, input);
	return input;

}


bool UserInterface::processinput( string input)
{
	
	bool keepgoing = true;// changed to false if quit input == quit
	tryagain:// return here if input is bad. Prevents 
	

	if(input == "add")
	{
		SFU.addnewBook();

	} else if(input.substr(0,6) == "remove") //check if first part of input correct
	{
		string index = input.substr(7);

		if (is_number(index)) //check if index is valid
		{
			SFU.removeBook(atoi(index.c_str()));
		} else 
		{
			SFU.removeBook(index);
		}

	} else if(input == "list")
	{
		SFU.listBooks();

	} else if(input.substr(0,4) == "find") //check if first part of input correct
	{
		string index = input.substr(5);

		if (is_number(index)) //check if index is valid
		{
			SFU.findBook(atoi(index.c_str()));
		} else 
		{
			SFU.findBook(index);
		}
			
	} else if(input.substr(0,4) == "sell") //check if first part of input correct
	{
		
		string index = input.substr(5);
		
		if (is_number(index)) //check if index is valid
		{
			SFU.sellBook(atoi(index.c_str()));
		} else 
		{
			SFU.sellBook(index);
		}
	} else if(input == "buy")
	{
		SFU.buyBook();

	} else if(input.substr(0,6) == "refund")
	{
		string index = input.substr(7);

		if (is_number(index)) //check if index is valid
		{
			SFU.refundBook(atoi(index.c_str()));
		} else 
		{
			SFU.refundBook(index);
		}
	} else if(input == "check register")
	{
		cout << "The register holds $" << SFU.getcash() << ".";

	} else if(input == "quit")
	{
		keepgoing = false;
	}

	else
	{	cout << "That is not a valid input, please try again.\n";
		getline(cin, input);
		goto tryagain;
	}

	if (keepgoing)
	{	cout << "\nPress enter to continue." << endl;
	cin.get();
	
	}
	return keepgoing;
}


bool UserInterface::is_number(const string& s)
{
	string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it))
		++it;
    return !s.empty() && it == s.end();
}

