#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_
#include "Bookstore.h"

class UserInterface {
	public:
		UserInterface();
		void prompt ();
		string getinput();
		bool processinput(string input);
		
	private:
		bool is_number(const string& s);
		bool quit;
		Bookstore SFU;
};

#endif /* BOOKSTORE_H_ */