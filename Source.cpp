#include "SBDL.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>

#define BOMB '*'
#define WONGAME_RATIO 100.0
#define NOBOOMB_RATIO 10.0

const int FPS = 100;
const int delay = 1000 / FPS;
//initializing of some variable that are used across several functions

int const width = 640, height = 704;
int game_state = 0;//0 in main menu -  1 in play and so on...
int user_pos_x, user_pos_y;//mouse positon
int current_save_slot, all_slots;//the core of saving and loading algorithm
int const element_size = 32;//size of board elements
int input;//for load_menu --- it is the slot number
bool load_board = false;//when a board is deleted shifts to true to prevent from building a new board
int x[3],  i;//used for keypressing in custom menu

//used for keypressing in change_user and change_name menus
char temp_username[50] = "@";
int k=1;
bool hint = true;//used in change_user menu

SDL_Rect** rects;//for the board

//the definition of almost all of the textures and their corresponding rects
Texture background;
SDL_Rect background_R = { 0 , 0 ,672, 672 };

Texture new_game;
SDL_Rect new_game_R = { 245 , 0 , 150, 50 };

Texture load;
SDL_Rect load_R = { 245 , 50 , 150, 50 };

Texture change_name;
SDL_Rect change_name_R = { 245 , 150 , 150, 50 };

Texture leaderboard;
SDL_Rect leaderboard_R = { 245,250,150, 50 };

Texture end_game;
SDL_Rect end_game_R = { 245 , 100 , 150, 50 };

Texture change_user;
SDL_Rect change_user_R = { 245 , 200 , 150, 50 };

Texture difficulty;
SDL_Rect difficulty_R = { 0 , 0 , 150 , 50 };

Texture beginner;
SDL_Rect beginner_R = { 150 , 0 , 150 , 50 };

Texture intermediate;
SDL_Rect intermediate_R = { 150 , 50 , 150 , 50 };

Texture expert;
SDL_Rect expert_R = { 150 , 100 , 150 , 50 };

Texture custom;
SDL_Rect custom_R = { 0 , 150, 150 , 50 };

Texture back;
SDL_Rect back_newgame_menu_R = { 0 , 200, 150 , 50 };
SDL_Rect back_ingame_R = { 414 , 640, 150 , 64 };
SDL_Rect back_custom_menu_R = { 0,200 , 150, 50 };
SDL_Rect back_leaderboard_menu_R = { 255 ,500 ,150 ,50 };

Texture remaining_flags;
SDL_Rect remaining_flags_R = { 285 , 645 ,32 ,44 };
SDL_Rect flag_icon_R = { 325 , 650 , 32 , 32 };

//custom part
Texture rows;
SDL_Rect rows_R = { 0 , 0 , 150, 50 };

Texture columns;
SDL_Rect columns_R = { 0 , 50 ,150 , 50 };

Texture mines;
SDL_Rect mines_R = { 0 , 100, 150 ,50 };

Texture custom_0;//row
Texture custom_1;//col
Texture custom_2;//mine

SDL_Rect input_row_R = { 160 , 0 , 32 , 44 };
SDL_Rect input_columns_R = { 160 , 50 , 32 , 44 };
SDL_Rect input_mines_R = { 160 , 100 , 32 , 44 };
// 

Texture play_again;
SDL_Rect play_again_R = { 444 , 640 ,150 , 64 };

Texture score;
SDL_Rect score_R = { 30,  640 , 150 ,64 };

Texture score_number;
SDL_Rect score_number_R = { 180 , 645 , 32 ,44 };

Texture menu;
SDL_Rect menu_aftergame_R = { 240, 640 , 150 ,64 };

//load menu
Texture save_slot1;
Texture save_slot2;
SDL_Rect save_slot1_R = { 130 , 0 , 225 , 75 };
SDL_Rect save_slot2_R = { 355 , 0 , 150 , 75 };

Texture input_slot;
SDL_Rect input_slot_R = { 300, 75 , 32 ,44 };

SDL_Rect back_load_menu_R = { 255 ,400 ,150 ,50 };
//
Texture save_game;
SDL_Rect save_game_R = { 245, 100, 150 ,50 };

Texture quit_game;
SDL_Rect quit_game_R = { 245 , 150 , 150 , 50 };

Texture board_number;
SDL_Rect board_number_R = { 60 , 640 ,150 ,64 };
Texture number;
SDL_Rect number_R = { 210 , 645 , 32 , 44 };


Texture username_menu_background;
SDL_Rect username_menu_background_R = { 0 , 0 ,640 , 704 };

Texture username_input;
SDL_Rect  username_input_R = { 120 , 570 ,400, 100 };

Texture type_username;
SDL_Rect type_username_R = { 170, 620 , 300 , 40 };


Texture display_username;
SDL_Rect display_username_R = { 170 , 620 , 300 , 70 };

Texture changename_menu_input;
SDL_Rect changename_menu_input_R = { 170 , 0 , 300 , 50 };

SDL_Rect changename_menu_type_R = { 170 , 150, 300 , 70 };

//leaderboard
SDL_Rect rank_1_R = { 130 , 5 , 40 , 50 };
SDL_Rect rank_2_R = { 130 , 55 , 40 , 50 };
SDL_Rect rank_3_R = { 130 , 105 , 40 , 50 };
SDL_Rect rank_4_R = { 130 , 155 , 40 , 50 };
SDL_Rect rank_5_R = { 130 , 205 , 40 , 50 };
SDL_Rect first_R = { 170 , 0 , 250 , 50 };
SDL_Rect second_R = { 170 , 50 , 250 , 50 };
SDL_Rect third_R = { 170 , 100 , 250 , 50 };
SDL_Rect fourth_R = { 170 , 150 , 250 , 50 };
SDL_Rect fifth_R = { 170 , 200 , 250 , 50 };
SDL_Rect first_score_R = { 420 , 0 ,100 , 50 };
SDL_Rect second_score_R = { 420 , 50 , 100 , 50 };
SDL_Rect third_score_R = { 420 , 100 , 100 , 50 };
SDL_Rect fourth_score_R = { 420 , 150 , 100 , 50 };
SDL_Rect fifth_score_R = { 420 , 200 , 100 ,50 };
//

//definition of ingame pictures
Texture bomb;
Texture one;
Texture two;
Texture three;
Texture four;
Texture five;
Texture six;
Texture seven;
Texture eight;
Texture zero;
Texture uncovered;
Texture flag;
Texture wrong_flag;
Texture pressed_bomb;

//definition of sounds
Sound* error;
Sound* explosion;
Sound* victory;
Sound* switch_user;
Sound* change_name_done;
Sound* save_button;

//definition of fonts
Font* font;
Font* font_small;
Font* font_big;

struct board
{
	int  row;
	int  col;
	int  bomb;
	int save_slot;//finding the board in list with this number
	char** element;//the actual positining of bombs
	int** is_clicked;//0 not clicked --- 1 is clicked (show the real value) --- 2 is clicked show flag --- 3 is wrong flag --- 4 is pressed bomb
	int flag_counter;
	bool deleted;//when this is true the board can be used for initializng a new game 
	double board_ratio;//for calculating scores
	board* next_board;
};
board* head_board;//for implementing the linked list


struct user
{
	char user_name[50];
	double score;
	board* user_headboard;//each user finds it's path to their particular head_board with this pointer.
	//this pointer stores the address to that head_board  -main core of saving the users board-
	int headboard_tag;//for headboard

	int user_current_save_slot;//the following 3 variables are for saving the game state when a another user is made
	int user_all_slots;
	bool user_load_board = false;

	user* next_user;
};
user* head_user;//for implementing linked list
user* current_user;//used for changing name and applying score and... the program which user is currently logged in with this variable



//particulary for loading assets
void load_assets()
{
	//background = SBDL::loadTexture("pics/Minesweeper.png");
	username_menu_background = SBDL::loadTexture("assets/pics/defuser.png");
	username_input = SBDL::loadTexture("assets/pics/input.png");
	new_game = SBDL::loadTexture("assets/pics/newgame.png");
	load = SBDL::loadTexture("assets/pics/loadgame.png");
	leaderboard = SBDL::loadTexture("assets/pics/leaderboard.png");
	change_name = SBDL::loadTexture("assets/pics/changename.png");
	end_game = SBDL::loadTexture("assets/pics/exitgame.png");
	save_slot1 = SBDL::loadTexture("assets/pics/entersaveslot.png");
	save_slot2 = SBDL::loadTexture("assets/pics/number.png");
	difficulty = SBDL::loadTexture("assets/pics/choosedifficulty.png");
	beginner = SBDL::loadTexture("assets/pics/beginner.png");
	intermediate = SBDL::loadTexture("assets/pics/intermediate.png");
	expert = SBDL::loadTexture("assets/pics/expert.png");
	custom = SBDL::loadTexture("assets/pics/custom.png");
	back = SBDL::loadTexture("assets/pics/back.png");
	rows = SBDL::loadTexture("assets/pics/rows.png");
	columns = SBDL::loadTexture("assets/pics/columns.png");
	mines = SBDL::loadTexture("assets/pics/mines.png");

	bomb = SBDL::loadTexture("assets/pics/ingame/bomb.png");
	one = SBDL::loadTexture("assets/pics/ingame/one.png");
	two = SBDL::loadTexture("assets/pics/ingame/two.png");
	three = SBDL::loadTexture("assets/pics/ingame/three.png");
	four = SBDL::loadTexture("assets/pics/ingame/four.png");
	five = SBDL::loadTexture("assets/pics/ingame/five.png");
	six = SBDL::loadTexture("assets/pics/ingame/six.png");
	seven = SBDL::loadTexture("assets/pics/ingame/seven.png");
	eight = SBDL::loadTexture("assets/pics/ingame/eight.png");
	zero = SBDL::loadTexture("assets/pics/ingame/zero.png");
	uncovered = SBDL::loadTexture("assets/pics/ingame/uncovered.png");
	flag = SBDL::loadTexture("assets/pics/ingame/flag.png");
	wrong_flag = SBDL::loadTexture("assets/pics/ingame/wrongflag.png");
	pressed_bomb = SBDL::loadTexture("assets/pics/ingame/pressedbomb.png");

	play_again = SBDL::loadTexture("assets/pics/playagain.png");
	score = SBDL::loadTexture("assets/pics/score.png");
	save_game = SBDL::loadTexture("assets/pics/save.png");
	quit_game = SBDL::loadTexture("assets/pics/quit.png");
	board_number = SBDL::loadTexture("assets/pics/board.png");
	menu = SBDL::loadTexture("assets/pics/menu.png");
	change_user = SBDL::loadTexture("assets/pics/changeuser.png");


	error = SBDL::loadSound("assets/music/error.wav");
	explosion = SBDL::loadSound("assets/music/explosion.wav");
	victory = SBDL::loadSound("assets/music/victory.wav");
	switch_user = SBDL::loadSound("assets/music/switch.wav");
	change_name_done = SBDL::loadSound("assets/music/changename.wav");
	save_button = SBDL::loadSound("assets/music/savebutton.wav");

	font = SBDL::loadFont("assets/music/Roboto-Medium.ttf", 25);
	font_small = SBDL::loadFont("assets/music/times.ttf", 300);
	font_big = SBDL::loadFont("assets/music/changenamefont.ttf", 300);

	changename_menu_input = SBDL::createFontTexture(font_big, "ENTER NEW NAME", 0, 0, 0);
}

board** headboards;//is used to make an VLA array for storing address to headboards
void add_headboard(user* x)//a VLA array of pointers to headboard(which are board* themseleves)
{//x is the new made user
	if (x->headboard_tag == 1)
	{
		headboards = new board* [x->headboard_tag];//is 1 for the frist time
		x->user_headboard = headboards[x->headboard_tag - 1];
		x->user_headboard = NULL;//the headboard of first user is now NULL
		return;
	}
	board** new_headboards = new board * [x->headboard_tag];//added 
	for (int i = 0; i < x->headboard_tag - 1; i++)
	{
		new_headboards[i] = headboards[i];
	}
	x->user_headboard = new_headboards[x->headboard_tag - 1];//assigned
	x->user_headboard = NULL;

	headboards = new_headboards;//new_headboards variable is used as a transporter
	delete[] new_headboards;//preventing memory leak
}

user* last_user_finder()
{
	int tag = 0;
	user* last = head_user;
	while (last->next_user != NULL)
		last = last->next_user;
	return last;
}

void add_user()//adding a new user to our linked list
{
	user** ptr_head = &head_user;
	user* new_user = new user;
	new_user->user_current_save_slot = 0;
	new_user->user_all_slots = 0;
	new_user->user_load_board = false;
	new_user->score = 0.0;
	new_user->next_user = NULL;

	if (*ptr_head == NULL)//the first user
	{
		new_user->headboard_tag = 1;
		add_headboard(new_user);
		*ptr_head = new_user;
	}
	else
	{
		user* last = last_user_finder();
		new_user->headboard_tag = (last->headboard_tag) + 1;
		add_headboard(new_user);
		last->next_user = new_user;
	}
}

int lentgh(char str[])
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return i;
}

bool compare(char a[], char b[])//compare function considering @ character
{
	for (int i = 1; a[i] != '\0'; i++)
	{
		if (a[i] != b[i - 1])
			return false;
	}
	return true;
}

bool is_already_taken(char x[], int size)
{
	user* temp = head_user;
	while (temp != NULL)
	{
		if (lentgh(x) != lentgh(temp->user_name) + 1)
		{
			temp = temp->next_user;
			continue;
		}
		if (compare(x, temp->user_name))
		{
			current_user = temp;
			return true;
		}
		temp = temp->next_user;
	}
	return false;
}


void user_name_menu()
{
	game_state = 5;
	if (hint)
		type_username = SBDL::createFontTexture(font_small, "ex:pouria82", 0, 0, 0);
	else
		type_username = SBDL::createFontTexture(font_small, temp_username, 0, 0, 0);


	SBDL::showTexture(username_menu_background, username_menu_background_R);
	SBDL::showTexture(username_input, username_input_R);
	SBDL::showTexture(type_username, type_username_R);
	
	if (SBDL::keyPressed(SDL_SCANCODE_A)) {
		temp_username[k] = 'a'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_B)) {
		temp_username[k] = 'b'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_C)) {
		temp_username[k] = 'c'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_D)) {
		temp_username[k] = 'd'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_E)) {
		temp_username[k] = 'e'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_F)) {
		temp_username[k] = 'f'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_G)) {
		temp_username[k] = 'g'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_H)) {
		temp_username[k] = 'h'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_I)) {
		temp_username[k] = 'i'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_J)) {
		temp_username[k] = 'j'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_K)) {
		temp_username[k] = 'k'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_L)) {
		temp_username[k] = 'l'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_M)) {
		temp_username[k] = 'm'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_N)) {
		temp_username[k] = 'n'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_O)) {
		temp_username[k] = 'o'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_P)) {
		temp_username[k] = 'p'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_Q)) {
		temp_username[k] = 'q'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_R)) {
		temp_username[k] = 'r'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_S)) {
		temp_username[k] = 's'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_T)) {
		temp_username[k] = 't'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_U)) {
		temp_username[k] = 'u'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_V)) {
		temp_username[k] = 'v'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_W)) {
		temp_username[k] = 'w'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_X)) {
		temp_username[k] = 'x'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_Y)) {
		temp_username[k] = 'y'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_Z)) {
		temp_username[k] = 'z'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_0)) {
		temp_username[k] = '0'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_1)) {
		temp_username[k] = '1'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_2)) {
		temp_username[k] = '2'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_3)) {
		temp_username[k] = '3'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_4)) {
		temp_username[k] = '4'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_5)) {
		temp_username[k] = '5'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_6)) {
		temp_username[k] = '6'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_7)) {
		temp_username[k] = '7'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_8)) {
		temp_username[k] = '8'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_9)) {
		temp_username[k] = '9'; k++; hint = false;
	}else if (SBDL::keyPressed(SDL_SCANCODE_BACKSPACE)) {
		if (lentgh(temp_username) == 1)
			return;
		k--; temp_username[k] = '\0';
	}

	if (SBDL::keyPressed(SDL_SCANCODE_RETURN))
	{
		if (is_already_taken(temp_username, k))//switch to this user
		{
			SBDL::playSound(switch_user, 1);
			current_save_slot = current_user->user_current_save_slot;//saving game state...
			all_slots = current_user->user_all_slots;
			load_board = current_user->user_load_board;

			for (int i = 1; i < k; i++)
			{
				temp_username[i] = '\0';
			}
			temp_username[0] = '@';//reinitializing temp_username for next times
			k = 1;
			game_state = 0;
			return;
		}
		//if we reached here  we are definitly making a new user
		add_user();
		user* x = last_user_finder();//automatically will return the new user which was made in previous line
		for (int i = 1; i < k; i++) {
			x->user_name[i - 1] = temp_username[i];
		}
		for (int i = 1; i < k; i++)
		{
			temp_username[i] = '\0';
		}
		temp_username[0] = '@';//reinitializing temp_username for next times
		x->user_name[k-1] = '\0';
		game_state = 0;
		k = 1;
		current_user = x;
	}
	SBDL::freeTexture(type_username);
}



void change_name_menu()
{
	game_state = 15;


	type_username = SBDL::createFontTexture(font_small, temp_username, 0, 0, 0);

	SBDL::showTexture(changename_menu_input, changename_menu_input_R);
	SBDL::showTexture(back, back_leaderboard_menu_R);
	SBDL::showTexture(type_username, changename_menu_type_R);

	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, back_leaderboard_menu_R))
		game_state = 0;

	if (SBDL::keyPressed(SDL_SCANCODE_A)) {
		temp_username[k] = 'a'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_B)) {
		temp_username[k] = 'b'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_C)) {
		temp_username[k] = 'c'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_D)) {
		temp_username[k] = 'd'; k++;
	}else if (SBDL::keyPressed(SDL_SCANCODE_E)) {
		temp_username[k] = 'e'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_F)) {
		temp_username[k] = 'f'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_G)) {
		temp_username[k] = 'g'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_H)) {
		temp_username[k] = 'h'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_I)) {
		temp_username[k] = 'i'; k++;
	}else if (SBDL::keyPressed(SDL_SCANCODE_J)) {
		temp_username[k] = 'j'; k++;
	}else if (SBDL::keyPressed(SDL_SCANCODE_K)) {
		temp_username[k] = 'k'; k++;
	}else if (SBDL::keyPressed(SDL_SCANCODE_L)) {
		temp_username[k] = 'l'; k++;
	}else if (SBDL::keyPressed(SDL_SCANCODE_M)) {
		temp_username[k] = 'm'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_N)) {
		temp_username[k] = 'n'; k++;
	}else if (SBDL::keyPressed(SDL_SCANCODE_O)) {
		temp_username[k] = 'o'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_P)) {
		temp_username[k] = 'p'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_Q)) {
		temp_username[k] = 'q'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_R)) {
		temp_username[k] = 'r'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_S)) {
		temp_username[k] = 's'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_T)) {
		temp_username[k] = 't'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_U)) {
		temp_username[k] = 'u'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_V)) {
		temp_username[k] = 'v'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_W)) {
		temp_username[k] = 'w'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_X)) {
		temp_username[k] = 'x'; k++;
	}else if (SBDL::keyPressed(SDL_SCANCODE_Y)) {
		temp_username[k] = 'y'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_Z)) {
		temp_username[k] = 'z'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_0)) {
		temp_username[k] = '0'; k++;
	}else if (SBDL::keyPressed(SDL_SCANCODE_1)) {
		temp_username[k] = '1'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_2)) {
		temp_username[k] = '2'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_3)) {
		temp_username[k] = '3'; k++;
	}else if (SBDL::keyPressed(SDL_SCANCODE_4)) {
		temp_username[k] = '4'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_5)) {
		temp_username[k] = '5'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_6)) {
		temp_username[k] = '6'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_7)) {
		temp_username[k] = '7'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_8)) {
		temp_username[k] = '8'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_9)) {
		temp_username[k] = '9'; k++; 
	}else if (SBDL::keyPressed(SDL_SCANCODE_BACKSPACE)) {
		if (lentgh(temp_username) == 1)
			return;
		k--; temp_username[k] = '\0';
	}

	if (SBDL::keyPressed(SDL_SCANCODE_RETURN))
	{
		if (is_already_taken(temp_username, k))
		{
			SBDL::playSound(error, 1);
			for (int i = 1; i < k; i++)
			{
				temp_username[i] = '\0';
			}
			temp_username[0] = '@';
			k = 1;
			return;
		}
		else
		{
			for (int i = 1; i < k; i++) {
				current_user->user_name[i - 1] = temp_username[i];
			}
			for (int i = 1; i < k; i++)
			{
				temp_username[i] = '\0';
			}
			temp_username[0] = '@';
			current_user->user_name[k - 1] = '\0';
			game_state = 0;
			k = 1;
			SBDL::playSound(change_name_done, 1);
		}
	}
	SBDL::freeTexture(type_username);
}

//in this function we will count all the users first then a VLA is made and all the useres are stored in it
//after we will sort it by score and put the top five in our refrenced array 
void leaderboard_calc(user* top_five[],int size,int &number_of_users)
{
	user* temp = head_user;
	while (temp != NULL)
	{
		number_of_users++;
		temp = temp->next_user;
	}

	int idx = 0;
	user** ranking = new user * [number_of_users];
	ranking[idx] = head_user;
	for (int i = 1; i < number_of_users; i++)
	{
		ranking[i] = ranking[i - 1]->next_user;
	}
	//now we'll sort it
	for (int i = 0; i < number_of_users - 1; i++)
		for (int j = 0; j < number_of_users - 1 - i; j++)
			if (ranking[j + 1]->score > ranking[j]->score)
				std::swap(ranking[j + 1], ranking[j]);

	for (int j = 0; j < size; j++)
	{
		top_five[j] = ranking[j];
		if (j == number_of_users - 1)
			break;
	}

	delete[] ranking;
}


void leaderboard_menu()
{
	int number_of_users = 0;
	Texture top_five_username[5];
	Texture top_five_score[5];
	for (int i = 0; i < 5; i++)
		top_five_username[i] = SBDL::createFontTexture(font_small,"@username",0,0,0);

	for (int i = 0; i < 5; i++)
		top_five_score[i] = SBDL::createFontTexture(font_small, "#score", 0, 0, 0);

	user* top_five[5]{};
	leaderboard_calc(top_five,5,number_of_users);

	for (int i = 0; i < number_of_users; i++)
		SBDL::freeTexture(top_five_username[i]);

	for (int i = 0; i < number_of_users; i++)
		SBDL::freeTexture(top_five_score[i]);
	
	for (int i = 0; i < 5; i++)
	{
		top_five_username[i] = SBDL::createFontTexture(font_small, top_five[i]->user_name, 0, 0, 0);
		top_five_score[i] = SBDL::createFontTexture(font_small,"#" + std::to_string((int)round(top_five[i]->score)), 7, 73,117);
		if (i == number_of_users - 1)
			break;
	}
	
	Texture rank_1 = SBDL::createFontTexture(font, "1", 207, 158, 0);
	Texture rank_2 = SBDL::createFontTexture(font, "2", 176, 176, 176);
	Texture rank_3 = SBDL::createFontTexture(font, "3",176 ,141 ,87);
	Texture rank_4 = SBDL::createFontTexture(font, "4", 0, 0, 0);
	Texture rank_5 = SBDL::createFontTexture(font, "5", 0, 0, 0);


	SBDL::showTexture(rank_1, rank_1_R);
	SBDL::showTexture(rank_2, rank_2_R);
	SBDL::showTexture(rank_3, rank_3_R);
	SBDL::showTexture(rank_4, rank_4_R);
	SBDL::showTexture(rank_5, rank_5_R);
	SBDL::showTexture(top_five_username[0], first_R);
	SBDL::showTexture(top_five_username[1], second_R);
	SBDL::showTexture(top_five_username[2], third_R);
	SBDL::showTexture(top_five_username[3], fourth_R);
	SBDL::showTexture(top_five_username[4], fifth_R);
	SBDL::showTexture(top_five_score[0], first_score_R);
	SBDL::showTexture(top_five_score[1], second_score_R);
	SBDL::showTexture(top_five_score[2], third_score_R);
	SBDL::showTexture(top_five_score[3], fourth_score_R);
	SBDL::showTexture(top_five_score[4], fifth_score_R);
	SBDL::showTexture(back, back_leaderboard_menu_R);

	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, back_leaderboard_menu_R))
		game_state = 0;
	

	SBDL::freeTexture(rank_1);
	SBDL::freeTexture(rank_2);
	SBDL::freeTexture(rank_3);
	SBDL::freeTexture(rank_4);
	SBDL::freeTexture(rank_5);
	for (int i = 0; i < 5; i++)
		SBDL::freeTexture(top_five_username[i]);

	for (int i = 0; i < 5; i++)
		SBDL::freeTexture(top_five_score[i]);

	number_of_users = 0;
}



board* slot_finder(int slot)//recives a slot number and will find the corrsponding board
{
	board* result = current_user->user_headboard;
	while (result != NULL)
	{
		if (slot == result->save_slot)
			return result;
		result = result->next_board;
	}
}


void show_main_menu()
{
	display_username = SBDL::createFontTexture(font_small, current_user->user_name, 0, 0, 0);

	SBDL::showTexture(new_game, new_game_R);
	SBDL::showTexture(load,load_R);
	SBDL::showTexture(end_game, end_game_R);
	SBDL::showTexture(change_name, change_name_R);
	SBDL::showTexture(leaderboard,leaderboard_R);
	SBDL::showTexture(change_user, change_user_R);
	SBDL::showTexture(display_username, display_username_R);
	//SBDL::showTexture(seven, background_1_R);

	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, new_game_R))
	{
		game_state = 11;
	}
	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, load_R))
	{
		if (all_slots == 0)//no current board is loaded
			SBDL::playSound(error, 1);
		else
		game_state = 13;
	}
	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, end_game_R))
	{
		game_state = 14;
	}
	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, change_name_R))
	{
		game_state = 15;
	}
	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, leaderboard_R))
	{
		game_state = 16;
	}
	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, change_user_R))
	{
		//if we type a username which is not already taken a new user will be made otherwise if it's already taken, the program will 
		//switch between these two users
		current_user->user_current_save_slot = current_save_slot;//saving the game state
		current_user->user_all_slots = all_slots;
		current_user->user_load_board = load_board;
		current_save_slot = 0;
		all_slots = 0;
		load_board = false;
		game_state = 5;
	}

	SBDL::freeTexture(display_username);

}

bool is_in_board(int i, int j,int row,int col)
{
	if (i >= 0 && i < row && j >= 0 && j < col)
		return true;
	else
		return false;
}


int adjacent_bombs(int i, int j,int row,int col,char** board_)
{
	int bomb_num = 0;
	for (int k = i - 1; k <= i + 1; k++)
		for (int l = j - 1; l <= j + 1; l++)
			if (is_in_board(k, l,row,col) && board_[k][l] == BOMB)
				bomb_num++;
	return bomb_num;
}



void init_board(board* new_board)
{
	int row = new_board->row;
	int col = new_board->col;
	int bomb = new_board->bomb;
	new_board->deleted = false;


	new_board->element = new char*[row];
	new_board->is_clicked = new int* [row];
	for (int i = 0; i < row; i++)//will be deleted deleted in delete_game function
	{
		new_board->element[i] = new char[col];
		new_board->is_clicked[i] = new int[col];

	}


	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			new_board->element[i][j] = '0';//initialize with 0 for the moment
			new_board->is_clicked[i][j] = false;
		}
	}


	//placing bombs
	bool** is_bomb = new bool* [row];
	for (int i = 0; i < row; i++)
		is_bomb [i] = new bool[col];
	int B_row = 0, B_col = 0;
	int i = 0;
	while(i < bomb)
	{
		B_row = (rand() % row), B_col = (rand() % col);
		if (new_board->element[B_row][B_col]!= BOMB)
		{
			new_board->element[B_row][B_col] = BOMB;
			i++;
		}
		else
			continue;
	}
	//setting the number of adjacent bombs in none-bomb positions
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (new_board->element[i][j] != BOMB)
				new_board->element[i][j] = adjacent_bombs(i, j,row,col,new_board->element) + '0';//setting the number

	for (int i = 0; i < row; i++)
		delete[] is_bomb[i];
	delete[] is_bomb;
}

board* last_board_finder()//returns the adress of the last board in list
{
	board* last = current_user->user_headboard;

	while (last->next_board != NULL)
		last = last->next_board;

	return last;
}

//in the following function we already know the board's saveslot number
void add_game(int difficulty_level,int save_slot)//receives a number to generate a new board with a particular difficulty
{
	board** ptr_head;
	board* new_board;
	if (!load_board)//should we build a new board or not?
	{//here we should 

		 ptr_head = &current_user->user_headboard;
		 new_board = new board;
		 new_board->next_board = NULL;

		if (*ptr_head == NULL)//list is empty
		{
			*ptr_head = new_board;
		}
		else
		{
			board* last = last_board_finder();
			last->next_board = new_board;
		}
	}
	else
	{
		new_board = slot_finder(current_save_slot);
		load_board = false;
	}


	switch (difficulty_level)
	{
	case 1:
		new_board->row = 5;
		new_board->col = 5;
		new_board->bomb = 4;
		new_board->flag_counter = 0;
		new_board->save_slot = save_slot;
		new_board->board_ratio =  4.0 / (5.0 * 5.0);
		break;
	case 2:
		new_board->row = 12;
		new_board->col = 12;
		new_board->bomb = 28;
		new_board->flag_counter = 0;
		new_board->save_slot = save_slot;
		new_board->board_ratio = 28.0 / (12.0 * 12.0);
		break;
	case 3:
		new_board->row = 20;
		new_board->col = 20;
		new_board->flag_counter = 0;
		new_board->bomb = 96;
		new_board->save_slot = save_slot;
		new_board->board_ratio = 96.0 / (20.0 * 20.0);
		break;
	case 4:
		new_board->row = x[0];
		new_board->col = x[1];
		new_board->flag_counter = 0;
		new_board->bomb = x[2];
		new_board->save_slot = save_slot;
		new_board->board_ratio = (double)x[2] / (x[0] * x[1]);//explicit type conversion(by assignment)
		x[0] = 0;
		x[1] = 0;
		x[2] = 0;
		i = 0;
	}
	std::cout << new_board->board_ratio<<std::endl;
	init_board(new_board);

	game_state = 1;//show time!
}
//once a board is deleted every thing in it is deleted EXEPCT the address of the board itself --- 
// new boards will be built when we have no empty boards in our list otherwise the new board adress will be the FIRST EMPTY board that had been created 

int empty_board_finder()//finds if between CURRENT boards we have an empty one with the help of deleted function if not returns -1
{
	board* temp = current_user->user_headboard;
	int check = 0;
	while (temp != NULL)
	{
		if (temp->deleted)//empty board found(could be the last board)
		{
			return temp->save_slot;//temp->deleted value will shift to false in init_board
		}
		temp = temp->next_board;
	}
	return -1;//we have to make a new board

}


void new_game_menu()
{

	SBDL::showTexture(difficulty, difficulty_R);
	SBDL::showTexture(beginner, beginner_R);
	SBDL::showTexture(intermediate, intermediate_R);
	SBDL::showTexture(expert, expert_R);
	SBDL::showTexture(custom, custom_R);
	SBDL::showTexture(back, back_newgame_menu_R);

	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, back_newgame_menu_R))
	{
		game_state = 0;
	}
	else if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, beginner_R))
	{
		if (all_slots == 0)//first board of the game
		{
			current_save_slot = 1;
			all_slots++;
		}
		else
		{
			all_slots++;
			int x = empty_board_finder();
			if (x != -1)
			{
				current_save_slot = x;
				load_board = true;//tells add_game not to build a new board but to load the first empty board

			}
			else
			{
				current_save_slot = last_board_finder()->save_slot + 1;
			}
		}

		add_game(1,current_save_slot);//first board corresponds to saveslot 1
	}
	else if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, intermediate_R))
	{
		if (current_save_slot == 0)
		{
			current_save_slot = 1;
			all_slots++;
		}
		else
		{
			all_slots++;
			int x = empty_board_finder();
			if (x != -1)
			{
				current_save_slot = x;
				load_board = true;//tells add_game not to build a new board but to load the first empty board
			}
			else
			{
				current_save_slot = last_board_finder()->save_slot + 1;
			}
		}

		add_game(2,current_save_slot);
	}
	else if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, expert_R))
	{
		if (current_save_slot == 0)
		{
			current_save_slot = 1;
			all_slots++;
		}
		else
		{
			all_slots++;
			int x = empty_board_finder();
			if (x != -1)
			{
				current_save_slot = x;
				load_board = true;//tells add_game not to build a new board but to load the first empty board
			}
			else
			{
				current_save_slot = last_board_finder()->save_slot + 1;
			}
		}
		add_game(3,current_save_slot);
	}
	else if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, custom_R))
	{
		game_state = 12;
	}
}

void custom_menu()
{
	SBDL::showTexture(rows, rows_R);
	SBDL::showTexture(columns, columns_R);
	SBDL::showTexture(mines, mines_R);
	SBDL::showTexture(back, back_custom_menu_R);

	custom_0 = SBDL::createFontTexture(font, std::to_string(x[0]), 0, 0, 0);
	SBDL::showTexture(custom_0, input_row_R);
	custom_1 = SBDL::createFontTexture(font, std::to_string(x[1]), 0, 0, 0);
	SBDL::showTexture(custom_1, input_columns_R);
	custom_2 = SBDL::createFontTexture(font, std::to_string(x[2]), 0, 0, 0);
	SBDL::showTexture(custom_2, input_mines_R);



	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, back_custom_menu_R))
	{
		if (i == 0)
			game_state = 11;
		else
			i--;
	}

	if (SBDL::keyPressed(SDL_SCANCODE_0))
	{
		x[i] *= 10;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_1))
	{
		x[i] = (10 * x[i]) + 1;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_2))
	{
		x[i] = (10 * x[i]) + 2;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_3))
	{
		x[i] = (10 * x[i]) + 3;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_4))
	{
		x[i] = (10 * x[i]) + 4;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_5))
	{
		x[i] = (10 * x[i]) + 5;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_6))
	{
		x[i] = (10 * x[i]) + 6;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_7))
	{
		x[i] = (10 * x[i]) + 7;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_8))
	{
		x[i] = (10 * x[i]) + 8;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_9))
	{
		x[i] = (10 * x[i]) + 9;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_BACKSPACE))
	{
		x[i] = (x[i] - (x[i] % 10)) / 10;
	}
	if (SBDL::keyPressed(SDL_SCANCODE_RETURN))
	{
		if (x[2] >= (x[0] * x[1]) && (x[1] != 0 || x[2] != 0))//the bombs are more than tiles ro equal
		{
			SBDL::playSound(error, 1);
			x[2] = 0;
			return;
		}
		//error handling
		if (x[0] > 20)
		{
			SBDL::playSound(error, 1);
			x[0] = 0;
			return;
		}
		if (x[1] > 20)
		{
			SBDL::playSound(error, 1);
			x[1] = 0;
			return;
		}
		i++;
	}
	if (i == 3)
	{
		if (all_slots == 0)//first board of the game
		{
			current_save_slot = 1;
			all_slots++;
		}
		else
		{
			all_slots++;
			int x = empty_board_finder();
			if (x != -1)
			{
				current_save_slot = x;
				load_board = true;//tells add_game not to build a new board but to load the first empty board
			}
			else
			{
				current_save_slot = last_board_finder()->save_slot + 1;
			}
		}
		add_game(4, current_save_slot);

	}
	SBDL::freeTexture(custom_0);
	SBDL::freeTexture(custom_1);
	SBDL::freeTexture(custom_2);
}

Texture uncover(char x,int row,int col)//updates the board when tile is presed//not used for displaying a flag
{
		if (x == BOMB)
			return bomb;
		else if (x == '1')
			return one;
		else if (x == '2')
			return two;
		else if (x == '3')	
			return three;
		else if (x == '4')
			return four;
		else if (x == '5')
			return five;
		else if (x == '6')
			return six;
		else if (x == '7')
			return seven;
		else if (x == '8')
			return eight;
		else if (x == '0')
			return zero;
}


void auto_uncover(int i, int j,board* x)//recursive implementation
{
	int row = x->row;
	int col = x->col;

	if (x->is_clicked[i][j] == 1 || x->is_clicked[i][j] == 2)//if not considered will go in endless loop also here the flag tile is not uncovered
		return;
	current_user->score += x->board_ratio * NOBOOMB_RATIO;
	std::cout << current_user->score << std::endl;

	x->is_clicked[i][j] = 1;//set the statud to clicked
	if (x->element[i][j] == '0')
	{
		for (int k = i - 1; k <= i + 1; k++)
			for (int l = j - 1; l <= j + 1; l++)
				if (is_in_board(k, l, row, col) && !(k == i && l == j))
					auto_uncover(k, l, x);
	}	
}
void loose_game(board* x)//adjust the board for the user to see at the end of the game
{
	SBDL::playSound(explosion, 1);


	int row = x->row;
	int col = x->col;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (x->is_clicked[i][j] == 0)//has not been clicked at all
			{
				x->is_clicked[i][j] = 1;//should print the value for user
			}
			else if (x->is_clicked[i][j] == 2)//is a flag
			{
				if (x->element[i][j] != BOMB)//wrong flag
					x->is_clicked[i][j] = 3;
				//otherwise is a correct flag so flag should be represented
			}
			//last else corresponds to the 1 value witch is already pressed
		}
	}
	game_state = -1;
}

void delete_game()
{
	board* x = slot_finder(current_save_slot);//find the target board with slot number

	for (int i = 0; i < x->row; i++)
	{
		delete[] x->element[i];
		delete[] x->is_clicked[i];
	}
	delete[] x->element;
	delete[] x->is_clicked;

	x->deleted = true;
	x->flag_counter = 0;

	if (all_slots == 0)//fixes the bug when deleting the only board in th game and then want to build a new one
		load_board = true;
}


void gameover_menu()
{
	score_number = SBDL::createFontTexture(font, std::to_string((int)round(current_user->score)), 237,0, 0);


	board* x = slot_finder(current_save_slot);
	int check{};

	for (int i = 0; i < x->row; i++)//just printing the board
	{
		for (int j = 0; j < x->col; j++)
		{
			check = x->is_clicked[i][j];//status of the tile
			if (check == 1)
				SBDL::showTexture(uncover(x->element[i][j], x->row, x->col), rects[i][j]);

			else if (check == 2)
				SBDL::showTexture(flag, rects[i][j]);

			else if (check == 3)
				SBDL::showTexture(wrong_flag, rects[i][j]);

			else if (check == 4)
				SBDL::showTexture(pressed_bomb, rects[i][j]);

			else//0
				SBDL::showTexture(uncovered, rects[i][j]);
		}
	}
	SBDL::showTexture(play_again, play_again_R);
	SBDL::showTexture(score, score_R);
	SBDL::showTexture(menu, menu_aftergame_R);
	SBDL::showTexture(score_number, score_number_R);


	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, menu_aftergame_R))
	{
		delete_game();
		game_state = 0;
	}
	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, play_again_R))
	{
		delete_game();
		init_board(x);
		game_state = 1;
	}

	SBDL::freeTexture(score_number);
}

bool winning_process(board* x)
{
	int result = 0;
	for (int i = 0; i < x->row; i++)
	{
		for (int j = 0; j < x->col; j++)
		{
			if (x->is_clicked[i][j] == 1)
				result++;
		}
	}
	int check = (x->row * x->col) - x->bomb;
	if (result == check)
		return true;
	else
		return false;
}



void game_won(board* x)// represent unflaged positions as flags when won and change the gamestate also adds the score
{
	SBDL::playSound(victory, 1);
	for (int i = 0; i < x->row; i++)
	{
		for (int j = 0; j < x->col; j++)
		{
			if (x->is_clicked[i][j] == 0 && x->element[i][j] == BOMB)
				x->is_clicked[i][j] = 2;
		}
	}
	current_user->score += x->board_ratio * WONGAME_RATIO;
	game_state = 2;
}

void wongame_menu()
{
	score_number = SBDL::createFontTexture(font, std::to_string((int)round(current_user->score)), 0, 219, 11);

	board* x = slot_finder(current_save_slot);
	int check{};
	for (int i = 0; i < x->row; i++)
	{
		for (int j = 0; j < x->col; j++)
		{
			check = x->is_clicked[i][j];
			if (check == 1)
				SBDL::showTexture(uncover(x->element[i][j], x->row, x->col), rects[i][j]);
			else if (check == 2)//possible bug  --> forgot why i wrote this:)
				SBDL::showTexture(flag, rects[i][j]);
		}
	}
	SBDL::showTexture(play_again, play_again_R);
	SBDL::showTexture(score, score_R);
	SBDL::showTexture(menu, menu_aftergame_R);
	SBDL::showTexture(score_number, score_number_R);

	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, menu_aftergame_R))
	{
		delete_game();
		game_state = 0;
	}
	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, play_again_R))
	{
		delete_game();
		init_board(x);
		game_state = 1;
	}

	SBDL::freeTexture(score_number);
}

void back_ingame_menu()
{
	SBDL::showTexture(save_game, save_game_R);
	SBDL::showTexture(quit_game, quit_game_R);

	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, quit_game_R))
	{
		delete_game();
		game_state = 0;
	}
	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, save_game_R))
	{
		//do nothing
		SBDL::playSound(save_button, 1);
		game_state = 0;
	}

}

void init_recs(int row, int col)
{
	rects = new SDL_Rect * [row];
	for (int i = 0; i < row; i++)
	{
		rects[i] = new SDL_Rect[col];
	}
	for (int j = 0; j < col; j++)
	{
		for (int i = 0; i < row; i++)//defining the board tiles in vertical order
		{
			rects[i][j].x = j * element_size;
			rects[i][j].y = i * element_size;
			rects[i][j].h = element_size;
			rects[i][j].w = element_size;
		}
	}
}
void play_game()
{	
	board* playing_board = slot_finder(current_save_slot);//possible error --> have not seen any yet

	int row = playing_board->row;
	int col = playing_board->col;

	init_recs(row, col);

	remaining_flags = SBDL::createFontTexture(font, std::to_string(playing_board->bomb - playing_board->flag_counter), 153, 0, 0);
	number = SBDL::createFontTexture(font, std::to_string(current_save_slot), 0, 0, 0);


	char element{};
	for (int i = 0; i < row; i++)//adjusting is_clicked variable value(the state of each tile)
	{
		for (int j = 0; j < col; j++)
		{
			element = playing_board->element[i][j];
			if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, rects[i][j]))
			{
				if (element != BOMB && element != '0' && playing_board->is_clicked[i][j] != 2)
				{
					if (playing_board->is_clicked[i][j] == 1)//already clicked
						SBDL::playSound(error, 1);
					else
						current_user->score += playing_board->board_ratio * NOBOOMB_RATIO;//every nobom position click has score
					playing_board->is_clicked[i][j] = 1;
					std::cout << current_user->score<<std::endl;
				}
				else if (element == '0')
				{
					auto_uncover(i, j, playing_board);
				}
				else if (playing_board->is_clicked[i][j] == 2)
				{
					SBDL::playSound(error, 1);

				}
				else if (element == BOMB)
				{
					playing_board->is_clicked[i][j] = 4;//red bomb picture
					loose_game(playing_board);
					return;//this return will prevent play_game() to delete rects**
					//so the user can see the board after losing
				}

			}
			else if (SBDL::Mouse.clicked(SDL_BUTTON_RIGHT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, rects[i][j]))//set a flag
			{
				if (playing_board->is_clicked[i][j] == 0)//is not clicked at all
				{
					if (playing_board->flag_counter < playing_board->bomb)
					{
						playing_board->is_clicked[i][j] = 2;//sets the satus to flag
						playing_board->flag_counter++;
					}
					else
						SBDL::playSound(error, 1);
				}

				else if (playing_board->is_clicked[i][j] == 1)//has been clicked
					SBDL::playSound(error, 1);

				else//is already flag
				{
					playing_board->is_clicked[i][j] = 0;
					playing_board->flag_counter--;
				}
			}

			//printing part

			if (playing_board->is_clicked[i][j] == 1)
				SBDL::showTexture(uncover(element, row, col), rects[i][j]);

			else if (playing_board->is_clicked[i][j] == 2)
				SBDL::showTexture(flag, rects[i][j]);

			else if (playing_board->is_clicked[i][j] == 3)
				SBDL::showTexture(wrong_flag, rects[i][j]);

			else if (playing_board->is_clicked[i][j] == 4)
				SBDL::showTexture(pressed_bomb, rects[i][j]);

			else//0
				SBDL::showTexture(uncovered, rects[i][j]);
		}
		if (winning_process(playing_board))
		{
			game_won(playing_board);
			return;//this return will prevent play_game() to delete rects**
			//so the user can see the board after winning the game
		}
	}
	
	SBDL::showTexture(remaining_flags, remaining_flags_R);
	SBDL::showTexture(flag, flag_icon_R);
	SBDL::showTexture(board_number, board_number_R);
	SBDL::showTexture(number, number_R);
	SBDL::showTexture(back, back_ingame_R);
	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, back_ingame_R))
		game_state = 3;

	for (int i = 0; i < playing_board->row; i++)
	{
		delete[] rects[i];
	}
	delete[] rects;

	SBDL::freeTexture(remaining_flags);
	SBDL::freeTexture(number);

}


void load_menu()//just changes the currentsaveslot variable
{
	input_slot = SBDL::createFontTexture(font, std::to_string(input), 0, 0, 0);

	SBDL::showTexture(save_slot1, save_slot1_R);
	SBDL::showTexture(save_slot2, save_slot2_R);
	SBDL::showTexture(input_slot, input_slot_R);
	SBDL::showTexture(back, back_load_menu_R);

	if (SBDL::Mouse.clicked(SDL_BUTTON_LEFT, 1, SDL_RELEASED) && SBDL::pointInRect(user_pos_x, user_pos_y, back_load_menu_R))
	{
		game_state = 0;
	}

	if (SBDL::keyPressed(SDL_SCANCODE_0))
	{
		input *= 10;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_1))
	{
		input = (10 * input) + 1;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_2))
	{
		input = (10 * input) + 2;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_3))
	{
	    input = (10 * input) + 3;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_4))
	{
		input = (10 * input) + 4;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_5))
	{
		input = (10 * input) + 5;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_6))
	{
		input = (10 * input) + 6;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_7))
	{
		input = (10 * input) + 7;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_8))
	{
		input = (10 * input) + 8;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_9))
	{
		input = (10 * input) + 9;
	}
	else if (SBDL::keyPressed(SDL_SCANCODE_BACKSPACE))
	{
		input = (input - (input % 10)) / 10;
	}
	if (SBDL::keyPressed(SDL_SCANCODE_RETURN))
	{
		if (input > all_slots || input == 0)
		{
			SBDL::playSound(error, 1);
			input = 0;
			return;
		}
		if (slot_finder(input)->deleted)
		{
			SBDL::playSound(error, 1);
			input = 0;
			return;
		}
		current_save_slot = input;
		game_state = 1;
		input = 0;
	}
	SBDL::freeTexture(input_slot);
}



int main()
{
	srand(time(0));
	

	SBDL::InitEngine("MINESWEEPER", width, height);
	load_assets();
	game_state = 5;

	while (SBDL::isRunning())
	{
		int start_loop = SBDL::getTime();
		SBDL::updateEvents();
		SBDL::clearRenderScreen();



		switch (game_state)
		{
		case 5:user_name_menu(); break;
		case 0: show_main_menu(); break;
		case 11:new_game_menu(); break;
		case 12:custom_menu(); break;
		case 13:load_menu(); break;
		case 14:exit(0); break;
		case 15:change_name_menu(); break;
		case 16:leaderboard_menu(); break;
		case 1:play_game(); break;
		case -1:gameover_menu(); break;
		case 2:wongame_menu(); break;
		case 3:back_ingame_menu();
		}

		user_pos_x = SBDL::Mouse.x;
		user_pos_y = SBDL::Mouse.y;


		SBDL::updateRenderScreen();
		int end_loop = SBDL::getTime() - start_loop;
		if (end_loop < delay)
			SBDL::delay(delay - end_loop);
	}
	return 0;
}