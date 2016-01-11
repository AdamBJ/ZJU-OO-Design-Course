
#include "Bookstore.h"
#include "GlobalVariables.h"
#include "UserInterface.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

bool quit = false;
string input;

int main()
{
	UserInterface SFU = UserInterface();
	bool keepgoing = true;

	while (keepgoing)
	{
	SFU.prompt();
	input = SFU.getinput();
	keepgoing = SFU.processinput(input);//if quit is entered this returns false
	}
}



