#include <string>

using namespace std;

class Bank {

public:
    Bank();
	~Bank();	
    void OpenForBusiness(Bank our_bank);      

  private:
	  void PrintAccntInfo(int accntnum, Bank our_bank);
	  static int const t = 9;
	  void DeleteList(Bank *our_bank);
	  
	  struct transaction_node {		//This is used to record one transaction on an account. Transactions are linked together in each account's transaction_history linked list.
		  transaction_node(): next(nullptr) {}
		  string transaction;
		  transaction_node *next;		
	  };
	  

	  struct account {		//Stores balance and transaction history for a bank account.
			account(): head(nullptr), balance(1000) {}
			double balance;	
			transaction_node *head;
	  };

	  account accounts[21];		//21 so that we can start storage at 1. This way account 1 is stored in accounts[1]	

	   class Worker
            {
                public:
					Worker();
					~Worker();
					bool ReadFromFile(Bank *our_bank);
					void PrinttoFile(Bank *our_bank);
                    void GetTransaction(Bank bank_name, int *responses);
					bool ProcessTransaction(int user_responses[], Bank *bank_name);	//Returns false if the user wants to stop entering transations, true otherwise.

					void UpdateTransactionHistory(int account_number, string transaction, Bank *our_bank);
					
					/*Following three functions are used to get input from user and to test it for correctness*/
					int GetAccountNum();
					int GetChoiceNum();
					double GetAmount();
					char * GetDateandTime();
            };
			
};