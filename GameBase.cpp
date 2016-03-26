// GameBase.cpp
// Author : Zheng Luo
// Modified by Zheng Luo on 03/24/14.

#include "OtherFunctions.h"
#include "GameBase.h"
#include "CheckersGame.h"
#include "ChessGame.h"
#include "NineAlmondsGame.h"
#include "MagicSquareGame.h"
#include "ReversiGame.h"
#include "TicTacToeGame.h"

#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <memory>
#include <list>
#include <fstream>

// initalize the static virable
GameBase * GameBase::instance_ = 0;

// constructor of the GameBase class
GameBase::GameBase(unsigned int h,unsigned int v,piece_color color,
				   string name,string symbol)
:horizontal_dimension(h),vertical_dimension(v),color(color),
 name(name), symbol(symbol),longest_string_length(symbol.length()){}

//retun the value of horizontal_dimension
unsigned int GameBase::get_horizontal_dimension() const
{
	return horizontal_dimension;
}

//retun the value of vertical_dimension
unsigned int GameBase::get_vertical_dimension() const
{
	return vertical_dimension;
}

// check the argument and creat the object
void GameBase::check_create(int argc , char * argv[])
{
	char * game_name=argv[1];
	// check whether the instance exist
	if(instance_ == 0)
	{
		if(argc == 4 &&
		   strcmp (game_name,"Checkers") == 0)
		{
			int checkersGame_dim = 8;
			char * first_player  = argv[2];
			char * second_player = argv[3];
			instance_ = new CheckersGame(checkersGame_dim, checkersGame_dim,
										 black_or_white, "checker", "C",
										 first_player, second_player);
		}
		else if(argc == 4 &&
				strcmp (game_name,"Chess") == 0)
		{
			int chessGame_dim = 8;
			char * first_player  = argv[2];
			char * second_player = argv[3];
			instance_ = new ChessGame(chessGame_dim, chessGame_dim,
									  black_or_white, "chess", "C",
									  first_player, second_player);
		}
		else if(argc == 2 &&
				strcmp (game_name,"NineAlmonds") == 0)
		{
			int nineAlmondsGame_dim = 5;
			instance_ = new NineAlmondsGame(nineAlmondsGame_dim,
											nineAlmondsGame_dim, brown,
											"almond", "A");
		}
		else if(argc == 2 &&
				strcmp (game_name,"MagicSquare") == 0)
		{
			int magicSquareGame_dim = 3;
			instance_ = new MagicSquareGame(magicSquareGame_dim,
											magicSquareGame_dim, brown,
											"square", "S");
		}
		else if(argc == 4 &&
				strcmp (game_name,"Reversi") == 0)
		{
			int reversiGame_dim = 8;
			char * first_player  = argv[2];
			char * second_player = argv[3];
			instance_ = new ReversiGame(reversiGame_dim,reversiGame_dim,
										black_or_white, "reversi","R",
										first_player, second_player);
		}
		else if(argc == 2 &&
				strcmp (game_name,"TicTacToe") == 0)
		{
			int ticTacToe_dim = 3;
			bool computer_first = true;
			bool play_with_computer = true;
			string mode = "hard";

			// Get the ticTacToe_dim from the commandline
			string s; // Temp virable to read command line data
			// Get the play_with_computer from the commandline
			cout << "Do you want to play with computer?\n"
					"Please type yes or no. Default option is yes. \n";
			getline(cin, s);
			play_with_computer = (s == "no") ? false : true;

			// Get the mode from the commandline
			if (play_with_computer)
			{
				cout << "Do you want to play easy or hard or impossible mode?\n"
						"Please type easy or hard or impossible. "
						"Default option is hard. \n";
				getline(cin, s);
				if (s == "easy")
					mode = "easy";
				else if (s == "impossible")
					mode = "impossible";
				else 
					mode = "hard";

				cout << "Do you want the computer to play first or second?\n"
						"Please type first or second. "
						"Default option is computer first. \n";
				getline(cin, s);
				computer_first = (s == "second") ? false : true;
			} 
			else
			{
				cout << "Please enter the dimenstion for the board.\n"
						"Default is 3.\n";
				getline(cin, s);
				stringstream strStream(s);
				strStream >> ticTacToe_dim;
				if (ticTacToe_dim < 2) 
				{
					cout << "Input dimenstion invalid, set to default 3\n";
					ticTacToe_dim = 3;
				}
			}
			instance_ = new TicTacToeGame(ticTacToe_dim, ticTacToe_dim,
										  black_or_white, "tictactoe",
										  "T", 'X', 'O', computer_first,
										  play_with_computer, mode);
		}
	}
	// if the instance already exist
	else
		throw instance_exist;
}

// instance method
GameBase * GameBase ::instance()
{
	if (instance_ != 0)
		return instance_;
	else
		throw instance_not_exist;
}

