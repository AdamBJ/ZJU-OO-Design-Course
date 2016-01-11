#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Bank.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>

using std::cout;
using std::cin;


Bank::Bank() {

}

Bank::~Bank() {

}

/* The key function for the program. All course of the program is controlled by this function*/
void Bank::OpenForBusiness(Bank our_bank) {
	
	Worker Bob = Worker();
	bool readin = Bob.ReadFromFile(&our_bank); //returns true if items were read in from the file.

	if (readin) {
		cout <<"Welcome back to our bank!" << endl;
	} else {
		cout <<"Wow, a new customer! Welcome to our bank!" << endl;
	}
	restart:
	cout <<"What would you like to do?\n";
	cout <<"	1.Perform a transaction.\n";
	cout <<"	2.Access account records.\n";
	cout <<"	3.Exit.\n";
	
	string choice;
	
	cin >> choice;

	/*PERFORM TRANSACTION*/
	if (choice == "1") {
		bool more_trans = true;

		while (more_trans)	{
			int user_response[2];	//updated in the function via pointers
			Bob.GetTransaction(our_bank, user_response);

			more_trans = Bob.ProcessTransaction(user_response, &our_bank); // returns false if the user is done entering transactions, true otherwise.
		}
		goto restart;
		/*ACCESS ACCOUNT RECORDS*/
	}else if (choice == "2") {
		
		bool more_prints = true;
		while (more_prints)	{
			cout << "Would you like to view an account's transaction history?Y/N\n";
			string resp;
	
			bool badinputchk = true;
	
			while (badinputchk) { //false if we have good input.
			cin >> resp;
				if (resp == "Y") {
					

					string resp2;
					cout << "Which account would you like to view (1,2,3...)? Enter 'all' to view all of them.\n";
					cin.clear();
					cin >> resp2;
				
					tryagain:	//return here if we don't get a valid input

					if (resp2 == "all")	{
						for (int i=1;i<21;i++)	//print all the account transactions					
							PrintAccntInfo(i,our_bank);
							badinputchk = false;
					} else if (atoi(resp2.c_str())) { // if a single account is entered
						int resp_int = stoi(resp2);
						PrintAccntInfo(resp_int,our_bank);
						badinputchk = false;
					
					} else { //if resp is not a valid int
						cout << "Please enter a valid account number (1-20).\n";
						cin.clear();
						cin >> resp2;
						goto tryagain;
					}

				} else if (resp == "N") {
					more_prints = false;
					goto restart;
				} else {
					cin.clear();
					cout << "Please enter either 'Y' or 'N'.\n";
				}
			} //end badinputchk while
		} goto restart;
	/*EXIT*/
	} else if ( choice == "3" ) {
		cout << "Press enter to exit.\n";
		cin.get();
		cin.get();
	}
	/*BAD INPUT*/
	else {
		cout << "Please choose a valid option.\n";
		cin.clear();
		goto restart;
	}
	//end big choice if else
	Bob.PrinttoFile(&our_bank);
    DeleteList(&our_bank);	//free the linked lists attached to each account to prevent memory leaks.
}

void Bank::PrintAccntInfo(int accntnum, Bank bank_name) {
	int transactions = 0;
	transaction_node *temp;
	temp = bank_name.accounts[accntnum].head;
	
	cout << setfill('-') << setw(40) << "-" <<endl;
	cout << "Transaction history for account " << accntnum << ":\n";
	cout << setfill('-') << setw(40) << "-" <<endl;

	while (temp) {
		
		cout << temp->transaction; 
		transactions ++;
		if (temp->next)
			temp = temp->next;
		else
			temp =nullptr;
	} 

	//truncate the extra 0's
	string balance = to_string(bank_name.accounts[accntnum].balance);
	size_t dotIndex0 = balance.find(".");
    string final_balance = balance.substr(0, dotIndex0 + 3);

	cout << "There have been a total of " << transactions << " transaction(s). The final balance is $" + final_balance + ".\n";
}

void Bank::DeleteList(Bank *our_bank) {		//Free the list before the program closes.
	transaction_node *item;
	transaction_node *old;

	for (int i = 1; i<21; i++) {
		item = our_bank->accounts[i].head;
		while (item)
		{
			old = item;
			item = item->next;
			delete old;
		}
	}
}


Bank::Worker::Worker() {

}

Bank::Worker::~Worker() {

}

bool Bank::Worker::ReadFromFile(Bank *our_bank) {
	
	ifstream accounts_txt("accounts.txt");
	int accntnum = 0;
	bool gotbalance = false;
	bool gotdate = false;
	string temp;

	if (accounts_txt) {
	  // The file exists, and is open for input. Read in our transactions
		for( std::string line; getline( accounts_txt, line ); ) {

			if (line != "") { //ignore empty lines

				if (atoi(line.c_str()) && !gotbalance) { //This is an account number, signifies a new account in the text file.
					accntnum = atoi(line.c_str());
					gotbalance = true;
				
				} else if (atof(line.c_str())) { //get balance
					our_bank->accounts[accntnum].balance = atof(line.c_str());
					gotbalance = false;
				} else {
					if (!gotdate) {
						temp += line;
						temp += "\n";
						gotdate = true;
					} else {
						temp += line;
						temp += "\n";
						gotdate = false;
						UpdateTransactionHistory(accntnum, temp, our_bank);
						temp = "";
					}
				}	
			}//end first if
		}
		return true;
	} else { // No file exists 
		return false;
	}
	//accounts_txt.close(); isn't neccesary. Auto closes when it hits the closing brace.
}

void Bank::Worker::PrinttoFile(Bank *our_bank) {

	ofstream accounts_txt ("accounts.txt");
	transaction_node *temp;
	
	if (accounts_txt.is_open()) {
	for (int i = 1; i<21; i++) {
		
		temp = our_bank->accounts[i].head;
		accounts_txt << i <<endl; 
		accounts_txt << our_bank->accounts[i].balance <<endl;

		while (temp) {
		
			accounts_txt << temp->transaction << endl; 

			if (temp->next)
				temp = temp->next;
			else
				temp =nullptr;
		} 
	} //end for
	accounts_txt.close();
	}
}

void Bank::Worker::GetTransaction(Bank bank_name, int *responses) {

	cout << "What account would you like to access?\n";
	*responses = GetAccountNum();

	//truncate the extra 0's
		string balance = to_string(bank_name.accounts[*responses].balance);
		size_t dotIndex0 = balance.find(".");
        string final_balance = balance.substr(0, dotIndex0 + 3);

	cout << "Account opened. Current balance is $" << final_balance << ". What would you like to do?\n"
			"		1. Make a deposit.\n"
			"		2. Make a withdrawal.\n"		
			"		3. Transfer money to another user's account.\n";
	*(responses+1) = GetChoiceNum();
 //Since this funciton is void, everything that isn't a point is will be "out of scope" aka destroyed after function returns!
}

//*ProcessTransaction first navigates to the appropriate account, then prompts the user for the rest of the transaction info and modifies the account(s) accordingly. */
bool Bank::Worker::ProcessTransaction(int user_responses[], Bank *bank_name)	{

	int user_account_number = user_responses[0] , user_choice = user_responses[1];

	switch (user_choice) {
	case 1: 
		{
		cout << "Please enter the deposit amount:";
		
		double deposit = GetAmount();

		bank_name->accounts[user_account_number].balance += deposit;	//update the balance
		
		char * date_time = GetDateandTime();
		string dt(date_time);
		
		//truncate the extra 0's
		string sbalance = to_string(bank_name->accounts[user_account_number].balance);
		size_t dotIndex0 = sbalance.find(".");
        string final_sbalance = sbalance.substr(0, dotIndex0 + 3);

		string sdeposit = to_string(deposit);
		size_t dotIndex9 = sdeposit.find(".");
        string final_sdeposit = sdeposit.substr(0, dotIndex9 + 3);

		string transaction = dt + "	Deposited $" + final_sdeposit +". Balance = $" + final_sbalance + ".\n";	//prepare the transaction history
		const string& ctransaction = transaction;
		cout << "Balance updated. Your new balance is $" + final_sbalance +".\n";

		UpdateTransactionHistory(user_account_number, ctransaction, bank_name);
		
		break;
		}
	case 2:
		/* Virtually the same as the deposit block above, except that we are taking money away instead of adding it.*/

		{cout << "Please enter the withdrawal amount:";
		
		double withdrawal = GetAmount();

		if (bank_name->accounts[user_account_number].balance - withdrawal >= 0) {
		bank_name->accounts[user_account_number].balance -= withdrawal;	//update the balance
		
		char *date_time = GetDateandTime();
		string dt(date_time);

		string sbalance = to_string(bank_name->accounts[user_account_number].balance);
		size_t dotIndex1 = sbalance.find(".");
        string final_sbalance = sbalance.substr(0, dotIndex1 + 3);

		string swithdrawal = to_string(withdrawal);
		size_t dotIndex8 = swithdrawal.find(".");
        string final_swithdrawal = swithdrawal.substr(0, dotIndex8 + 3);

		string transaction = dt + "	Withdrew $" + final_swithdrawal +". Balance = $" + final_sbalance + ".\n";	//prepare the transaction history
		const string& ctransaction = transaction;
		cout << "Balance updated. Your new balance is $" + final_sbalance +".\n";

		UpdateTransactionHistory(user_account_number, ctransaction, bank_name);
		} else {
			cout << "There is not enough money in the account to do that.\n";
		}

		break;
		}
	case 3:
		/*Transfer combines the functionalites of Widthdraw and Deposit, it updates two accounts.*/
		{
		cout << "How much do you want to trasfer?\n";
		double transfer = GetAmount();
		
		if (bank_name->accounts[user_account_number].balance - transfer >= 0) {
		cout << "Which account (1-20) do you want to transfer funds to?\n";
		int transferee;
		transferee = GetAccountNum();

		bank_name->accounts[user_account_number].balance -= transfer;	//update the balance
		bank_name->accounts[transferee].balance += transfer;

		char *date_time = GetDateandTime();
		string dt(date_time);

		string sbalance = to_string(bank_name->accounts[user_account_number].balance);
		size_t dotIndex = sbalance.find(".");
        string final_sbalance = sbalance.substr(0, dotIndex + 3);

		string stransfer = to_string(transfer);
		size_t dotIndex7 = stransfer.find(".");
        string final_stransfer = stransfer.substr(0, dotIndex7 + 3);


		/* Update the transaction history for the accout that transfered the funds.*/
		string transaction1 = dt + "	Transfered $" + final_stransfer + " to account " + to_string(transferee) +". Your updated balance: $" + final_sbalance + ".\n";	//prepare the transaction history
		const string& ctransaction = transaction1;
		cout << "Transaction completed. Your new balance is $" + final_sbalance +".\n";

		UpdateTransactionHistory(user_account_number, ctransaction, bank_name);

		/* Update the transaction history for the accout that received the funds.*/
		string tbalance = to_string(bank_name->accounts[transferee].balance);
		size_t dotIndex2 = tbalance.find(".");
        string final_tbalance = tbalance.substr(0, dotIndex2 + 3);


		string transaction2 = dt + "	Received transfer of $" + final_stransfer + " from account " + to_string(user_account_number) +". Your updated balance: $" + final_tbalance + ".\n";	//prepare the transaction history
		const string& cttransaction = transaction2;

		UpdateTransactionHistory(transferee, cttransaction, bank_name);

		} else {
			cout << "There is not enough money in the account to do that.\n";
		}
		break;
		}			
	} //end switch block
	cout << "Would you like to process another transaction?Y/N\n";
			string resp;
	
			bool badinputchk = true;
	
			while (badinputchk) {
			cin >> resp;
				if (resp == "Y") {
					return true;
				} else if (resp == "N") {
					return false;
				} else {
					cin.clear();
					cout << "Please enter either 'Y' or 'N'.\n";
				}
			} //end while
}

/*Adds the transaction to the head of the linked list attached to the account.*/
void Bank::Worker::UpdateTransactionHistory(int account_number, string transaction, Bank *our_bank_ptr) {
	
	transaction_node *new_trans = new transaction_node; //If this is a node it is destroyed at end of function. As pointer, pointer is destoryed, but NOT the info it points to!
	
	new_trans->transaction = transaction;

	if (our_bank_ptr->accounts[account_number].head == nullptr) {	//If this is the first transaction
		our_bank_ptr->accounts[account_number].head = new_trans;

	} else {	//If this isn't the first transaction, disconnect the account from its current transaction list, connect the new transaction to the account and then connect the old list to the new transaction.
		transaction_node *temp;
		temp = our_bank_ptr->accounts[account_number].head;

		while (our_bank_ptr->accounts[account_number].head->next) {
			our_bank_ptr->accounts[account_number].head = our_bank_ptr->accounts[account_number].head->next;
		}
		our_bank_ptr->accounts[account_number].head->next = new_trans;
		our_bank_ptr->accounts[account_number].head = temp;
	}
}


int Bank::Worker::GetAccountNum() {		//Rejects input if it is not a valid account number (an integer between 1 and 20 inclusive).
	int account_number;
	if (!(cin >> account_number) || account_number < 1 || account_number > 20) {
		cout << "Please enter an number between 1 and 20!\n";

		while (!(cin >> account_number) || account_number < 1 || account_number > 20) {
		cin.clear();	// Clear the input buffer
		cin.ignore();	// Ignore the bad character
		}
	} 
	cin.get();		//Get the newline char left in the input buffer
	
	return account_number;
}

int Bank::Worker::GetChoiceNum() {		//Rejects input if it is not a valid choice (an integer between 1 and 3 inclusive).
	int choice_number;
	if (!(cin >> choice_number) || choice_number < 1 || choice_number > 3) {
		cout << "Please enter 1, 2, or 3!\n";

		while (!(cin >> choice_number) || choice_number < 1 || choice_number > 3) {
		cin.clear();	// Clear the input buffer
		cin.ignore();	// Ignore the bad character
		}
	} 
	cin.get();		//Get the newline char left in the input buffer
	
	return choice_number;
}

double Bank::Worker::GetAmount() {		//Rejects input if it is not a valid choice (an integer between 1 and 3 inclusive).
	
	double amount;

	if (!(cin >> amount) || amount < 1) {
		cout << "Please enter an amount greater than 0.\n";

		while (!(cin >> amount) || amount < 1) {
		cin.clear();	// Clear the input buffer
		cin.ignore();	// Ignore the bad character
		}
	} 
	cin.get();		//Get the newline char left in the input buffer

	return amount;
}

char * Bank::Worker::GetDateandTime() {
	 // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

   return dt;
}
