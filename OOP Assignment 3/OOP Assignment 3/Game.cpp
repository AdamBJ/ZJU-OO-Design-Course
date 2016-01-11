#include "Game.h"
#include <iostream>
#include <time.h>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <mmsystem.h>
#include <iomanip>
#pragma comment(lib, "winmm.lib")


using std::cout;
using std::cin;

/*Public members*/
Game::Game(){}
Game::~Game(){}



int Game::TakeTurn(int player_loc) {
	int rslt; //0 if player is dead otherwise we continue



	if (player_loc != 666) {
		cout << game_map[player_loc].description << endl;
	}
	string ignore;
	getline(cin,ignore);

	if (player_loc == 666) {
		rslt = game_map[player_loc].occupant->Interact();//boss fight

	} else if (game_map[player_loc].occupant->time_limit != -1) {
		if (game_map[player_loc].occupant->time_limit == 30) {//boss preamble
			
			game_map[player_loc].description = "You arrive back at the entrance. The silence here coupled with the sight of the yawning darkness of the final door is unnerving.";
			game_map[player_loc].occupant->time_limit=-1;
			
		} else if (game_map[player_loc].occupant->time_limit == 40) { //miniboss
			rslt = game_map[player_loc].occupant->Interact();
			ReInitMonsters();
			if (rslt == 0) return -1; //player is dead
		} else {
			cout << "There's someone in here!!" <<endl;
			getline(cin,ignore);
			rslt = game_map[player_loc].occupant->Interact();
			if (rslt == 0) return -1; //player is dead
		}
		
	} else {
		cout <<"There's no one here."<<endl;
		getline(cin,ignore);
	}
	
	string plyr_resp;
	string directions = "";
	cout << "There are a total of " << game_map[player_loc].direction[4] << " doors leading from this room.\n";
	for (int p=0; p < 4; p++) {
			if (game_map[player_loc].direction[p]!="-1") {
				directions += game_map[player_loc].direction[p];
			}
	}
	cout << directions << endl;
	
	getline(cin, plyr_resp);


	while (true) {
		for (int i=0; i<4; i++) {//check if its a valid choice
			if (plyr_resp == game_map[player_loc].direction_resp[i]) {
				if (plyr_resp == "final") {//if its final, initiate the boss fight
					cout << endl;
					int final_rslt= game_map[4].occupant->Interact(); //fight the boss
					if (final_rslt) return -2;//player victory
					else return -1;//player dead
				}
				cout << endl;
				if (plyr_resp == "upwards") cout <<"You ascend the staircase and open the door at the top."<<endl;
				else if (plyr_resp == "down") cout <<"You descend the staircase and open the door at the bottom."<<endl;
				else cout << "You open the " << plyr_resp << "ern door." << endl;
				getline(cin, plyr_resp);
				return game_map[player_loc].adjacent[i];
			} 
		}	
			
		string prompt = "(";
		for (int p=0; p<4; p++) {
			if (game_map[player_loc].direction_resp[p]!= "-1") {
				prompt+= " "+game_map[player_loc].direction_resp[p];
			}
		}
		prompt += " )";
		cout << prompt << endl;
		getline(cin, plyr_resp);
	}
	//need to resturn someonthign?
}

/*Private members*/
unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

void Game::Play() {
	string ignore;

	PlaySound(TEXT("02-town.wav"), NULL, SND_FILENAME | SND_ASYNC);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
	cout << endl <<endl<<endl<<endl<<endl<<endl<<endl<<endl;

	for (int i=0; i<3; i++) {
		cout <<title[i]<<endl;
		}
	cout << endl;

	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

	
	cout << endl <<endl<<endl<<endl<<endl<<endl<<endl<< endl <<endl<<endl<<endl;
	cout << "Press enter to begin!" << endl;
	
	
	getline (cin, ignore);

	string scrolldown = "";


	cout << scrolldown <<endl;
	cout << scrolldown <<endl;
	cout << scrolldown <<endl;
	cout << scrolldown <<endl;
	cout << scrolldown <<endl;
	cout << scrolldown <<endl;


	PlaySound(NULL, 0, 0);
	
	cout << setfill('-') << setw(80) << "-" <<endl;
	cout << "INSTRUCTIONS:\n\n"
		"Welcome! As you are playing, please keep the following two rules in mind:\n\n"
		"1. When answering a monster's question, make sure you enter your response exactly as it appears in the question statement. For example,"
		" if the question is \"Is Canada or China the larger country?\" you must enter Canada in order for your response to be "
		"accepted as correct. *If you enter canada or CAnada or anything else of that nature it will count as an incorrect response!*\n\n"
		"2. If you don't know the answer to the question, there is usually just enough time to google it before the question's timelimit is reached!\n\n"
		"3. At any point, press enter to advance to the next screen.\n\n"
		"Have fun!\n\n";
	cout << setw(80) << "-";
	
	cout << scrolldown <<endl;
	cout << scrolldown <<endl;
	cout << scrolldown <<endl;
	cout << scrolldown <<endl;
	cout << scrolldown <<endl;
	cout << scrolldown <<endl;
	cout << scrolldown <<endl;

	getline (cin, ignore);
	
	cout << intro<<endl<<endl;
	

	                                                  
     
  cout << scrolldown <<endl;
	cout << "                      _( )_          () ()          _( )_" <<endl;
   cout << "   _( )_              |_|_|      /\\/\\|| ||/\\/\\      |_|_|              _( )_" <<endl;
	cout << "   |___|/\\/\\/\\/\\/\\/\\/\\|___|/\\/\\/\\/\\/\\|| ||/\\/\\/\\/\\/\\|___|/\\/\\/\\/\\/\\/\\/\\|___| " <<endl;
	cout << "   |_|_|\\/\\/\\/\\/\\/\\/\\/|_|_|\\/\\/\\/\\/\\/|| ||\\/\\/\\/\\/\\/|_|_|\\/\\/\\/\\/\\/\\/\\/|_|_| " <<endl;
	cout << "   |___|/\\/\\/\\/\\/\\/\\/\\|___|/\\/\\/\\/\\/\\|| ||/\\/\\/\\/\\/\\|___|/\\/\\/\\/\\/\\/\\/\\|___| " <<endl;
	cout << "   |_|_|\\/\\/\\/\\/\\/\\/\\/|_|_|\\/\\/\\/\\/\\/|| ||\\/\\/\\/\\/\\/|_|_|\\/\\/\\/\\/\\/\\/\\/|_| | " <<endl;
	cout << "  [_____]            [_____]                       [_____]            [_____]" <<endl;
	
	cout << scrolldown <<endl;
	
	getline (cin, ignore);

	cout << entrdesc <<endl;

	getline (cin, ignore);

	cout << entrdesc2 <<endl;

	getline (cin, ignore);

	cout << entrdesc3 <<endl;

	getline (cin, ignore);

	unsigned long seed = mix(clock(), time(0), GetTickCount());
	srand(seed);
	InitializeMap();
	int player_loc = 4;
	
	while (player_loc != -1 && player_loc != -2) {
		player_loc = TakeTurn(player_loc);
	}

	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
	if (player_loc == -1) {
		cout << gameover[0] <<endl;
		cout << gameover[1] <<endl;
		cout << gameover[2] <<endl;
		cout << gameover[3] <<endl;
		cout << gameover[4] <<endl;
	} else {
			SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
		cout << "As you answer the last question correctly the orb's green glow fades, and is quickly replaced by a brilliant orange light that makes you think of an unfathomably hot furnace. You know that you must disrupt the Core somehow, but with no weapon or tool of any kind in the room you take the only course of action you can think of; you pluck your former interrogator from the air, and pitch it headlong into the hot glow of the Core as if it were a bloodthirsty baseball.\n\nThe reaction is immediate and unmistakeable. The glow of the Core dims, and the Pillar begins to shake violently. You quickly exit the building to observe the destruction from a more comfortable distance, feeling at peace and satisfied for the first time in decades.\n\nCongratulations!" << endl;
		
		getline (cin, ignore);
		
		for (int i=0; i<7; i++) {
		cout <<congrats[i]<<endl;
		}

		for (int i=0; i<12; i++) {
			delete game_map[i].occupant; //free memory
		}
	}
	//delete the two bosses
	getline (cin, ignore);
}

void Game::InitializeMap() {
	
	for (int i=0; i < 12; i++) {
		game_map[i].SetDirection(i,game_map[i]); //initializes the proper doors in each room
		game_map[i].description=room_desc[rand()%5]; //randomly inserts a description
		//inserts a random monster, some rooms will be full others will be left empty.	
		if (i%2 == 0) {
			InitMonsters();//puts a random monster in a random room
		}
	}
	/*Place the mini-boss on level 2 and the ladder to go from level 1 to level 2*/
	InitBosses(2,40,monst_desc[5],rand()%6+6);
	
	int ladder_posn = rand()%6;//place the ladder in a random level 1 room
	if (ladder_posn == 4) // don't place it at the entrance
		ladder_posn = 0;
	int ladder_posn_top = rand()%6+6;
	game_map[ladder_posn].direction[3] = " There's also a staircase leading upwards!";
	game_map[ladder_posn].adjacent[3] = ladder_posn_top; // ladder leads to random room on 2nd level
	game_map[ladder_posn].direction_resp[3] = "upwards";

	game_map[ladder_posn_top].direction[3] = " There's also a staircase leading back down to the first level.";
	game_map[ladder_posn_top].adjacent[3] = ladder_posn;
	game_map[ladder_posn_top].direction_resp[3] = "down";

	/*Initialize the entrace description*/
	game_map[4].description = room_desc[5];
}

void Game::InitBosses(int num_qs, int time_limit, string boss_desc, int posn) {
	

	if (num_qs ==3) {
		BigBoss *big = new BigBoss();
	
		game_map[posn].occupant = big; //must be deleted at the end
	}
	else {
		MiniBoss *mini = new MiniBoss();
	
		game_map[posn].occupant = mini;
	}

	num_qs--;
	//int posn = rand()%6+6; //put it in a random room
	while (num_qs >= 0) {
		int rand_q = rand()%5;
		int monst_type = rand()%5; //type of question the boss will ask

		switch (monst_type) {
		case 0://Music
			game_map[posn].occupant->description = boss_desc; //make it a random monster type
			game_map[posn].occupant->qs[num_qs] = music_questions[rand_q]; //make it a random question for the given MT
			game_map[posn].occupant->as[num_qs] = music_answers[rand_q]; //store the correct answer
			game_map[posn].occupant->time_limit = time_limit;
			break;
		case 1://Books
			game_map[posn].occupant->description = boss_desc; //make it a random monster type
			game_map[posn].occupant->qs[num_qs] = book_questions[rand_q]; //make it a random question for the given MT
			game_map[posn].occupant->as[num_qs] = book_answers[rand_q]; //store the correct answer
			game_map[posn].occupant->time_limit = time_limit;
			break;
		case 2://Math
			game_map[posn].occupant->description = boss_desc; //make it a random monster type
			game_map[posn].occupant->qs[num_qs] = math_questions[rand_q]; //make it a random question for the given MT
			game_map[posn].occupant->as[num_qs] = math_answers[rand_q]; //store the correct answer
			game_map[posn].occupant->time_limit = time_limit;
			break;
		case 3://Books
			game_map[posn].occupant->description = boss_desc; //make it a random monster type
			game_map[posn].occupant->qs[num_qs] = history_questions[rand_q]; //make it a random question for the given MT
			game_map[posn].occupant->as[num_qs] = history_answers[rand_q]; //store the correct answer
			game_map[posn].occupant->time_limit = time_limit;
			break;
		case 4://Anatomy
			game_map[posn].occupant->description = boss_desc; //make it a random monster type
			game_map[posn].occupant->qs[num_qs] = anatomy_questions[rand_q]; //make it a random question for the given MT
			game_map[posn].occupant->as[num_qs] = anatomy_answers[rand_q]; //store the correct answer
			game_map[posn].occupant->time_limit = time_limit;
			break;
		}
	num_qs--;
	}
}


void Game::InitMonsters() {
	
	int rand_q = rand()%5;
	int rand_pos = rand()%12; //put it in a random room
	int monst_type = rand()%5;

	while (game_map[rand_pos].occupant->time_limit != -1 || rand_pos == 4) {
		if (rand_pos<11)
					rand_pos++;
				else 
					rand_pos=0;
	}

	switch (monst_type) {
	case 0://Music
		game_map[rand_pos].occupant->description =monst_desc[0]; //make it a random monster type
		game_map[rand_pos].occupant->qs[0] = music_questions[rand_q]; //make it a random question for the given MT
		game_map[rand_pos].occupant->as[0] = music_answers[rand_q]; //store the correct answer
		game_map[rand_pos].occupant->time_limit =45;
		break;
	case 1://Books
		game_map[rand_pos].occupant->description =monst_desc[1]; //make it a random monster type
		game_map[rand_pos].occupant->qs[0] = book_questions[rand_q]; //make it a random question for the given MT
		game_map[rand_pos].occupant->as[0] = book_answers[rand_q]; //store the correct answer
		game_map[rand_pos].occupant->time_limit =45;
		break;
	case 2://Math
		game_map[rand_pos].occupant->description =monst_desc[2]; //make it a random monster type
		game_map[rand_pos].occupant->qs[0] = math_questions[rand_q]; //make it a random question for the given MT
		game_map[rand_pos].occupant->as[0] = math_answers[rand_q]; //store the correct answer
		game_map[rand_pos].occupant->time_limit =45;
		break;
	case 3://Books
		game_map[rand_pos].occupant->description =monst_desc[3]; //make it a random monster type
		game_map[rand_pos].occupant->qs[0] = history_questions[rand_q]; //make it a random question for the given MT
		game_map[rand_pos].occupant->as[0] = history_answers[rand_q]; //store the correct answer
		game_map[rand_pos].occupant->time_limit =45;
		break;
	case 4://Anatomy
		game_map[rand_pos].occupant->description =monst_desc[4]; //make it a random monster type
		game_map[rand_pos].occupant->qs[0] = anatomy_questions[rand_q]; //make it a random question for the given MT
		game_map[rand_pos].occupant->as[0] = anatomy_answers[rand_q]; //store the correct answer
		game_map[rand_pos].occupant->time_limit =45;
		break;
	}
}


void Game::ReInitMonsters() { //Repopulates each room with random monsters, changes the entrance description for boss fight.


	for (int i=0; i < 12; i++) {
		//set all rooms to empty
		delete game_map[i].occupant;
		game_map[i].occupant = new Monster();
		game_map[i].occupant->time_limit = -1;
		//inserts a random monster, some rooms will be full others will be left empty.
		}
	
	for (int i=0; i <12; i++) {
		if (i%2 == 0) InitMonsters();//puts a random monster in a random room
	}


			

	//set boss
	game_map[4].description = room_desc[6];
	game_map[4].direction[4] = "4";
	game_map[4].direction[2] += " You're not sure where the final door leads, but you know your \"guide\" will be waiting for you on the other side of it.\n";
	game_map[4].direction_resp[3] = "final";
	InitBosses(3,30,monst_desc[6],4);
	
}

/*Room*/



Game::Room::Room() {

	occupant = new Monster();

	memset(adjacent, -1, 4 * sizeof(int));
	
	for (int i=0; i<4; i++) {
		direction[i]="-1";
		direction_resp[i] = "-1";
	} 
	direction[4] = "-1";
}

Game::Room::~Room() {}

void Game::Room::PrintDesc(Room &curr) {
	cout << curr.description <<endl;
}

void Game::Room::SetDirection(int index, Room &curr) {
	if (index <= 5) { // 1st floor
		switch (index) {
		case 0:
			adjacent[0] = 1;
			adjacent[1] = 3;
			direction[0] = "One leads to the east ";
			direction[1] = "and one leads to the south.";
			direction[4] = "2";//keep track of the number of doors leading from this room
			
			//acceptable user responses to "where do you want to go?"
			direction_resp[0] = "east";
			direction_resp[1] = "south";
			break;
		case 1:
			adjacent[0] = 0;
			adjacent[1] = 4;
			adjacent[2] = 2;
			direction[0] = "One leads to the west";
			direction[1] = ", one leads to the south";
			direction[2] = " and one leads to the east.";
			direction[4] = "3";

			direction_resp[0] = "west";
			direction_resp[1] = "south";
			direction_resp[2] = "east";
			break;
		case 2:
			adjacent[0] = 1;
			adjacent[1] = 5;
			direction[0] = "One leads to the west";
			direction[1] = " and one leads to the south.";
			direction[4] = "2";

			direction_resp[0] = "west";
			direction_resp[1] = "south";
			break;
		case 3:
			adjacent[0] = 0;
			adjacent[1] = 4;
			direction[0] = "One leads to the north";
			direction[1] = " and one leads east.";
			direction[4] = "2";

			direction_resp[0] = "north";
			direction_resp[1] = "east";
			break;
		case 4:
			adjacent[0] = 1;
			adjacent[1] = 5;
			adjacent[2] = 3;
			direction[0] = "One leads to the north";
			direction[1] = ", one leads to the east and";
			direction[2] = " one leads west.";
			direction[4] = "3";

			direction_resp[0] = "north";
			direction_resp[1] = "east";
			direction_resp[2] = "west";
			break;
		case 5:
			adjacent[0] = 2;
			adjacent[1] = 4;
			direction[0] = "One leads to the north";
			direction[1] = " and one leads west.";
			direction[4] = "2";

			direction_resp[0] = "north";
			direction_resp[1] = "west";
			break;
		}

	} else { //second floor
		switch (index) {
		case 6:
			adjacent[0] = 7;
			adjacent[1] = 9;
			direction[0] = "One leads to the east";
			direction[1] = " and one leads to the south.";
			direction[4] = "2";

			direction_resp[0] = "east";
			direction_resp[1] = "south";
			break;
		case 7:
			adjacent[0] = 6;
			adjacent[1] = 10;
			adjacent[2] = 8;
			direction[0] = "One leads to the west";
			direction[1] = ", one leads to the south";
			direction[2] = " and one leads to the east.";
			direction[4] = "3";

			direction_resp[0] = "west";
			direction_resp[1] = "south";
			direction_resp[2] = "east";
			break;
		case 8:
			adjacent[0] = 7;
			adjacent[1] = 11;
			direction[0] = "One leads to the west";
			direction[1] = " and one leads to the south.";
			direction[4] = "2";

			direction_resp[0] = "west";
			direction_resp[1] = "south";
			break;
		case 9:
			adjacent[0] = 6;
			adjacent[1] = 10;
			direction[0] = "One leads to the north";
			direction[1] = " and one leads east.";
			direction[4] = "2";

			direction_resp[0] = "north";
			direction_resp[1] = "east";
			break;
		case 10:
			adjacent[0] = 7;
			adjacent[1] = 11;
			adjacent[2] = 9;
			direction[0] = "One leads to the north";
			direction[1] = ", one leads to the east and";
			direction[2] = " one leads west.";
			direction[4] = "3";

			direction_resp[0] = "north";
			direction_resp[1] = "east";
			direction_resp[2] = "west";
			break;
		case 11:
			adjacent[0] = 8;
			adjacent[1] = 10;
			direction[0] = "One leads to the north";
			direction[1] = " and one leads west.";
			direction[4] = "2";

			direction_resp[0] = "north";
			direction_resp[1] = "west";
			break;
		}
	}
}

/* Monster */

Game::Monster::Monster() {//initializes an "empty room". When we populate the rooms, some rooms will be filled, others will be left empty.
	time_limit = -1;
}


Game::Monster::~Monster() {

}

/* Credit for the basis of this countdown function goes to http://en.allexperts.com/q/C-1040/2010/5/set-amount-time-user.htm */
string Game::Monster::CountDown(int time_limit) {

       // expire in time_limit seconds
       time_t expiry = time(NULL) + time_limit;

       string input;
       while(true)
       {
           if (time(NULL) > expiry)
           {
               cout << "You were too slow! Brood beetles begin to flood the room. Your final thought is of " << death_thoughts[rand()%3] <<endl; //%10 because there are 10 entries. return sa value from 0 to 9.
			   return "DEAD";
           }

           if (_kbhit())
           {
               char ch = (char)_getch();
			   if (ch == '\b') {
				   cout << "\b \b";
				   input = input.substr(0,input.size()-1);
			   } else {
				   cout << ch; // echo character back to the screen
			  
				   if (ch == '\n' || ch == '\r') break;
				   else input.insert(input.end(), 1, ch);
			   }
           }
           else
           {
               Sleep(1); 
           }
       }

	   cout << "\"" << input << "!\"" << ", you say.\n\n";	   
	   return input;
   }

int Game::Monster::Interact() { //Returns -1 if player dies.
	cout << description << endl;
	
	string ignore;
	getline(cin,ignore);

	cout << "The thing in front of you looks like it's getting ready to ask something. Judging from the look on its face, you think you'll have about " << time_limit <<" seconds to respond before it loses its patience.\n ***Get ready!***\n";
	
	getline(cin,ignore);
	
	cout << qs[0] << endl;

	string resp = CountDown(time_limit);

	if (resp == "DEAD")//didn't answer in time
		return 0;
	else if (resp != as[0]) { //answered incorrectly
		cout << "The creature in front of you turns back to what it was doing, suddenly uninterested. Clearly that was not the answer it was looking for.";
			getline(cin,ignore);
			cout << "\nYour ears detect a faint sound, seeming to come from everywhere at once. It sounds almost like... skittering...\n";
			getline(cin,ignore);
		return 0;
	}else 
		time_limit = -1;//set monster as "dead"
		cout << "The thing in front of you seems satisfied by your answer and turns back to what it was doing. You'd better move along before it changes it's mind.\n";
		getline(cin,ignore);
		return 1;
}

Game::MiniBoss::MiniBoss(): Monster()
{
}

Game::MiniBoss::~MiniBoss() {}

int Game::MiniBoss::Interact() {
	string ignore;
	
	cout << description;
	getline(cin,ignore);

	cout << mini_b_desc;
	getline(cin,ignore);

	cout << mini_b_desc2;
	getline(cin,ignore);

	for (int i=0; i<2; i++) {
	if (i==0)cout << "You look for a moment into the creature's gleaming eyes. You don't think it would be a good idea to keep it waiting.\n***Get ready!***\n";
	if (i==1)cout << "The creature blinks once. \"Stage one verification complete. Commencing stage two procedures.\" Get ready, its going to ask another question!\n";
	getline(cin,ignore);
	
	cout << qs[i] << endl;

	string resp = CountDown(time_limit);

	if (resp == "DEAD")//didn't answer in time
		return 0;
	else if (resp != as[i]) { //answered incorrectly
		cout << "A series of clicks and beeps is followed by eerie pause. Finally, the creature speaks: "
			"\"Knowledge vessel contains errors. Commencing bio-repurposing.\"";
		getline(cin,ignore);
		return 0;
	}else if (i == 1) {//if both questions correct
		cout <<"More gibberish noises flows from your interrogator before: "
		"\"Accepted. Extermination not currently required.\"\n";
		getline(cin,ignore);
		cout << "\"Knowledge vessel, you are hereby ordered to proceed to the first floor Core facility for indoctrination. Be prepared for further questioning by other vessels en route.\"\n";
		getline(cin,ignore);
		return 1;
	}
	}
}

Game::BigBoss::BigBoss(): Monster()
{
}

Game::BigBoss::~BigBoss() {}

int Game::BigBoss::Interact() {
	string ignore;

	cout << description;
	getline(cin,ignore);

	cout << boss_desc[0];
	getline(cin,ignore);

	cout << boss_desc[1];
	getline(cin,ignore);

	for (int i=0; i<=2; i++) {
	if (i==1){
		cout << "As you move closer to the core, your guide's chirps become higher pitched and more irregular. You're not sure, but you think its becoming agitated.\n";
		getline(cin,ignore);
		cout <<"When it asks its next question, you shouldn't keep it it waiting.";
		getline(cin,ignore);
	}
		if (i==2) {
			cout << "You look again at your guide's eyes and see that they're boring into you. Does it suspect something? You look away, but it's too late. The creatures voice once again crackles to life: \"The vessel will have 25 seconds to respond to the final test query!\".";
			getline(cin,ignore);
			cout << "\t\t\t\t***This is it! Get ready!***\n";
			getline(cin,ignore);
		}
	
	
	cout << qs[i] << endl;

	if (i==2) time_limit = 25;
	string resp = CountDown(time_limit);

	if (resp == "DEAD")//didn't answer in time
		return 0;
	else if (resp != as[i]) { //answered incorrectly
		cout << "The instant you answer, the door to the chamber slides shut silently behind you.";
		getline(cin,ignore);
		cout << "In the center of the room the core begins to glow menacingly. Your guide begins to chitter at you in a way that sounds almost satisfied.\n";
		getline(cin,ignore);
		return 0;
	}else if (i == 2 )
		return 1;
}

	

}

const string Game::music_questions[5] ={"\"Who composed Moonlight Sonata?\"\nYou're sure the answer is either Beethoven or Mozart.\n","\"Did Tom Petty and the Heartbreakers write Mary Jane's Last Dance?\"\nYou think it just wants a yes or no.\n","\"Did 2pac or Biggie write Thugz Mansion?\"\n","\"Who sings Party in the USA?\"\nThey played this song at your birthday... was it Katy Perry? Or Kelly Clarkson... or maybe Miley Cyrus?\n","\"Is Abbey Road Studios located in New York or London?\"\n"};
const string Game::book_questions[5] = {"\"Is the King James version of the Holy Bible in wider circulation than the English Standard Version?\"\nYou think he's looking for a yes or no here.","\"Is The Hobbit a prequel or sequel to the Lord of the Rings?\"\n","\"Which novel, published at the very end of the 19th century, produced the most-filmed horror character of the 20th century?\"\n You are commanded you to respond entirely in lowercase, whatever that means.\n","\"Was the first James Bond book Casino Royal or Goldfinger?\"\n","\"What author wrote about Willie Wonka and the Chocolate Factory?\"\nYou are commanded to respond entirely in lowercase, whatever that means.\n"};
const string Game::math_questions[5] = {"\"What is 36x5?\"\n","\"What is 121/11?\"\n","\"What is 2 to the power of 7?\"\n","\"What is 157-34?\"\n","\"What is the square root of 25?\""};
const string Game::history_questions[5] = {"\"What year did World War 2 end?\"","\"Was John A. Macdonald or Wilfrid Laurier the first prime minister of Canada?\"\n","\"Did America purchase Alaska from Russia, Canada or Great Britain?\"\n","The site of Cortez's first landing in the New World occured in what today is which country?\"\nYou're pretty sure its either Mexico or Peru.\n","\"Did a Chinese inventor or Korean inventor create the first compass?\"\n"};
const string Game::anatomy_questions[5] = {"\"What is the largest bone in the human body?\"\nYou're sure its either the femur or the humerus.\n","\"Is carpelum or ulna the name of a real bone in the human body?\"\n","\"Are there more than 100, more than 200, or more than 300 bones in your body?\"\n","\"Is your mandible found in your head or your wrist?\"\n","\"Are your wrists or your fingers affected by carpal tunnel syndrome?\"\n"};
const string Game::movie_questions[5] = {"\"Did Titanic or Avatar gross more at the box office?\"\n","\"Was Casablanca filmed in colour or in black and white?\"\n","What actor played Ned Stark in the HBO series Game of Thrones?\"\nThis is followed by a droning: \"respond entirely in lower-case\". You're not sure what that means.\n","As of November 18th 2013 what is the highest grossing movie of all time?\"\nThis is followed by a droning: \"respond entirely in lower-case\". You're not sure what that means.\n","\"Did Martin Sheen or Charlie Sheen star in Apocalypse Now?\"\n"};

const string Game::music_answers[5] = {"Beethoven","yes","2pac","Miley Cyrus","London"};
const string Game::book_answers[5] = {"yes","prequel","dracula","Casino Royal","roald dahl"};
const string Game::math_answers[] = {"180","11","128","123","5"};
const string Game::history_answers[] = {"1945","John A. Macdonald","Russia","Mexico","Chinese"};
const string Game::anatomy_answers[] = {"femur","ulna","more than 200","head","wrists"};
const string Game::movie_answers[] = {"Avatar","black and white","sean bean","avatar","Martin Sheen"};

//Music, Books, Math, History, Anatomy, Miniboss, Boss
const string Game::monst_desc[7]=  {"In the corner you see a scarred and shrivelled creature with a pair of ancient headphones clasped against its ears. You think this was once a person, but if it ever was it has forgotten what that meant long ago. Its eyes are pressed shut, and it rocks back and forth to the rhythm of a tune only it can hear. As the door closes behind you its eyes snap open, and it smiles at you.",
"The ancient man at the centre of the room is so hunched over that, at first glance, you think he must be a sickly child... until you see the book his eyes are greedily consuming. He seems to have been hunched over reading for so long that his back has been permanently warped. He twists his body to gaze up at you, seemingly annoyed at the interruption.",
"The woman who stands before you appears both slender and stern. The abacus she clutches is a blur of motion as her deft hands flick beads back and forth. She stares at you with a level, guarded gaze without stopping (or even slowing) her calculations on the abacus. You can just barely hear her mumbling to herself as she counts.",
"The blank, dead eyes of the man before you suggest a terrible weight rests on his shoulders. As you examine the contents of the room more closely you notice that the newspaper clippings scattered around are all of famous tragedies. The sheets of newspaper he had in his hand fall to the floor to join the others when he sees you, and you catch glimpses of headlines such as the sinking of the Titanic, and the explosion of the Hindenberg blimp.",
"The surgical gown of the room's only inhabitant is a crisp and clean as her hands are steady. The woman, (girl, really) is slight of build but holds herself in a cool, still manner. She is twirling a scalpel as you enter as though it were a baton in a parade, but she quickly and deftly catches it and places it back on its tray when she notices you.",
"An all too familiar buzzing start behind you. Whirling towards the noise, you see one of those merciless mechanized insects rise up out of a panel in the floor. It begins to drift sleepily towards you, seemingly without urgency.\n",
"Stepping through what was a solid door just seconds ago, you find yourself in a dark circular room, lit only by a glowing green orb in the center.\n"
};

const string Game::boss_desc[] ={"A tirade of noise from your guide (captor?) is followed by: \"Subject suitability 90% assured. Knowledge query required to confirm suitability, before the Core will be exposed for indoctrination procedures.\"\n","Two words jump out at you: \"Core...\" and \"exposed.\" You ready yourself for the Brood's questions.\n"};
const string Game::mini_b_desc= "You realize the door has sealed behind you, and you stand transfixed, sure you are about to die. Unbelievably, as the mechanoid nears you, it slows further and then stops completely.\n";
const string Game::mini_b_desc2= "It emits a series of clicks and beeps, followed by perfect, clipped English.\n\"Knowledge source detected. Core status, contained. Proceeding with interrogation.\"\n";
const string Game::entrdesc = "The massive gates at the base of the Pillar loom before you. To your surprise, they are ajar. The brood must truly be invincible for them to be so brazen.";
const string Game::entrdesc2 = "You're still not sure how you'll destroy the Brood, but the answer must be inside. You quickly step through the gates.";
const string Game::entrdesc3 ="Once inside the compound, you head for the giant archway in the distance that looks to you like the entrance. You are unnerved by the silence of your surroundings, and so make your way as quickly as possible. Once you arrive, you take a breath and step into the yawning darkness of the archway.";

const string Game::death_thoughts[5] = {"your dog Ralph.","meatballs. Weird.","how lonley Grandma's going to be without you.","the first time you rode a bike.","about all the cattle you'll be leaving behind."};

const string Game::room_desc[7] = {"You enter a room so dark you can barely see the far wall, but the unmistakable and nauseating scent of old blood hangs heavy in the air. You try not to think about what might be causing your feet to stick to the floor. Several sets of what look to be manacles line each wall.",
	"As you step through the doorway you are greeted by the overpowering reek of antiseptic. The surgical table in front of you looks to have been so thoroughly cleaned that you can nearly see your reflection in the metal backing.",
	"Your eyes are immediately drawn to the far wall, which appears to be a floor-to-ceiling bank of monitors. Each one is playing reruns of old news channels. (They must be reruns; nobody has been broadcasting anything for over ten years).",
	"As you step through the doorway, the roar of machinery causes you to wince. Pipes of all sizes run down from the ceiling into various machines that seem to be responsible for the unbelievable noise.",
	"The door opens on a long, featureless hallway of the same smooth stone you saw in the entrance to the Pillar. The corridor is brightly and evenly lit, despite there being no visible light sources.",
	"You find yourself in a tall, hexagonal room. The walls seem to be made of a solid stone, and are dotted with torches of green flame. The shadows cast by these torches seem... wrong, somehow.",
	"Finally you and your buzzing guide arrive back at the entrance to the Pillar. It is much as you remember it, but as you enter a single green torch flutters and goes out. The wall the torch was mounted on shimmers, then disappears. Your guide floats through the new opening, clearly expecting you to follow."
};
Game::Room Game::game_map[12];

const string Game::gameover[] = {" GGG   AA  M   M EEEE      OOO  V     V EEEE RRRR ","G     A  A MM MM E        O   O V     V E    R   R" ,"G  GG AAAA M M M EEE      O   O  V   V  EEE  RRRR ","G   G A  A M   M E        O   O   V V   E    R R  "," GGG  A  A M   M EEEE      OOO     V    EEEE R  RR"} ;
const string Game::congrats[] = {  

"#     #                                  ###",   
" #   #   ####  #    #    #    # # #    # ###", 
"  # #   #    # #    #    #    # # ##   # ###",
"   #    #    # #    #    #    # # # #  #  # ",
"   #    #    # #    #    # ## # # #  # #    ",
"   #    #    # #    #    ##  ## # #   ## ###",
 "   #     ####   ####     #    # # #    # ###"};

const string Game::intro = "Twenty years have passed. Twenty long, hard years, since the Brood arrived. Buzzing, thirsty, relentless... they were no bigger than your fist, but their hard metal skins made them nearly impossible for us to destroy.\n\nAt first, we resisted. We fought, and died, by the millions... but almost nobody fights any more. When the Brood pours out of the Pillar for its Harvest each year most people simply wait to see if it will be their turn to be herded away like so much cattle, never to be seen again. Nobody knows what happens to those taken, but everyone knows that any who resist will die quickly, and horribly.\n\nBut you are tired of waiting. You want a life, you want hope, you need to be rid of the damned Brood.\n\nYou must destroy the Pillar."; 
const string Game::title[] = 
{"    ___..............................._........__...........................",
 "    .|.|_.._....|/.._.._\\.../|.._.._|(_|._..../..._..|..|.._.._._|_._..__._.",
 "    .|.|.|(/_...|\\.|.|(_)\\^/.|.(/_(_|__|(/_...\\__(_).|..|.(/_(_..|_(_).|._>."};


 
 
 
                                                                                                        
                                                         
                                                                                                


                                                            
                                                            
                                                            
                    

