#include <string>

using namespace std;

class Game {

public:
	Game();
	~Game();
	void Play();
	void InitializeMap();
	void InitMonsters();
	void InitBosses(int num_qs, int time_limit, string boss_desc, int posn);
	void ReInitMonsters();
	int TakeTurn(int player_loc);

private:	
	class Monster {
	public:
		Monster();
		~Monster();
		virtual int Interact ();
		string CountDown(int time_limit);
		string qs[3]; // 1 question for normal monsters, 2 for mini-boss, 3 for boss
		string as[3];
		string description;
		int time_limit;
	};

	class MiniBoss: public Monster {
	public:
		MiniBoss();
		~MiniBoss();
		int Interact ();//overloaded, called if the monster is the MiniBoss
	};

	class BigBoss: public Monster {
	public:
		BigBoss();
		~BigBoss();
		int Interact ();//overloaded, called if the monster is the MiniBoss
	};

	class Room {
	public:
		Room();
		~Room();
		void PrintDesc(Room &current);
		void SetDirection(int array_index, Room &current);

		Monster *occupant;
		string description;
		int adjacent[4];//stores the array indices of adjacent rooms.
		string direction[5];//stores the directions the player can go from this room.
		string direction_resp[4];
	};

	//arrays storing all questions and descriptions
	static const string music_questions[5];
	static const string movie_questions[5];
	static const string book_questions[5];
	static const string math_questions[5];
	static const string history_questions[5];
	static const string anatomy_questions[5];

	static const string music_answers[5];
	static const string movie_answers[5];
	static const string book_answers[5];
	static const string math_answers[5];
	static const string history_answers[5];
	static const string anatomy_answers[5];

	static const string monst_desc[7];

	static const string room_desc[7];
	//array for storing the map (rooms) and for the monsters associated with each room (monsters)
	static Room game_map[12];
	//array for storing death thoughts
	static const string death_thoughts[5];
	static const string gameover[5];
	static const string congrats[7];
	static const string intro;
	static const string title[3];
	static const string mini_b_desc;
	static const string mini_b_desc2;
	static const string boss_desc[2];
	static const string entrdesc;
	static const string entrdesc2;
	static const string entrdesc3;
};
