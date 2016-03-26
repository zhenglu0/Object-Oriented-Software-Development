// CheckersGame.cpp
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#include "OtherFunctions.h"
#include "GameBase.h"
#include "CheckersGame.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <memory>
#include <list>
#include <fstream>
#include <cmath>

// globe value of argv[]
extern char ** argv_globle;
// flag out whehter to return the last state
extern int last_state; // 0 means not to return
// Define the initial state of the piece on the board for initialize_game() 
// function. x_empty,y_empty is defined in other_functions.h
checkers_game_piece empty_cgp(x_empty,y_empty,black_or_white,"E");
// symbol for the black peice
extern string X;
// symbol for the white peice
extern string O;
// store the value of turn time
extern int first_person_turn_times;
// store the value of turn time
extern int second_person_turn_times;
// store the whose turn
extern string whose_turn;
// symbol for black King
string B = "B";
// symbol for white King
string W = "W";
// flag indicate whether it is in the continuous move
int whether_in_continuous_move = 0; // 0 means not in the continuous move
// store the position value
unsigned int file_x = 0;
unsigned int file_y = 0;
// stores the value of conitous move
int continuous_move_flag = 0;

//constructor of CheckersGame
CheckersGame::CheckersGame(unsigned int h,unsigned int v,piece_color color,
				    string name,string symbol, string first, string second)
:GameBase(h, v, color, name, symbol),
first_person(first),second_person(second) {}

//set function
void CheckersGame::push_v (checkers_game_piece cgp)
{
	v.push_back(cgp);
}

//set function
void CheckersGame::set_v (unsigned int x,unsigned int y ,
						  checkers_game_piece cgp)
{
	v[horizontal_dimension*y+x] = cgp;
}

// print method
void CheckersGame::print()
{
	cout << endl << *this << endl << endl;
	// print the number of pieces
	cout << "Total number of Black Pieces = " << count_black_pieces() << endl;
	cout << "Total number of White Pieces = " << count_white_pieces() << endl;
	cout << endl;
}

// Overloading the operator << for Checkers Game
ostream &operator<< (ostream &out,  const CheckersGame &r)
{
	//define the empty piece
	int piece_existing = 0;
	// store the value of the dimension
	unsigned int d = r.horizontal_dimension;
	for(unsigned int i = r.vertical_dimension-1; i+1 != 0; --i )
	{
		// Draw the Y coordinate
		out << i << " ";
		// Print the board
		for(unsigned int j = 0; j < r.horizontal_dimension; ++j)
		{
			//check whether it is empty
			if (r.v[d*i+j] != empty_cgp)
			{
				// print out the symbol
				out << setiosflags(ios_base::left)
					<< setw(r.longest_string_length+1) << r.v[d*i+j].symbol;
				piece_existing = 1;
			}
			// If there is no piece there, print out the space
			if(piece_existing == 0)
			{
				cout << setiosflags(ios_base::left)
					 << setw(r.longest_string_length+1) << " ";
			}
			piece_existing = 0;
			//change the line
			if(j == r.horizontal_dimension-1)
			{
				out << endl;
			}
		}
	}
	// Draw the X coordinate
	out << "X" << " ";
	for(unsigned int j = 0; j < r.horizontal_dimension; ++j)
	{
		// Draw the X coordinate with the space between them
		out << setiosflags(ios_base::left)
			<< setw(r.longest_string_length+1) << j;
	}
	return out;
}

//Initialize the board
void CheckersGame::initialize_game()
{
	string first_line; // store the first line
	string first_person_file; // store the first person
	string second_person_file; // store the first person
	string board_line; // store the one line in the file
	string current_piece; // store the current piece
	string turn_s; // store the value of turn_times
	string last_position; // store the value of the last position
	string game_name = argv_globle[1];
	string first_person_program = argv_globle[2];
	string second_perosn_program = argv_globle[3];
	string file_name = game_name +"_"+ first_person_program +
					   "_"+ second_perosn_program + ".txt";
	// first try to read from file
	ifstream ifs (file_name.c_str());
	if (ifs.is_open ())
	{
		getline(ifs,first_line);
		getline(ifs,first_person_file);
		getline(ifs,second_person_file);
	}
	//1.initialize the piece on the NineAlmondsGame
	for(unsigned int i = get_vertical_dimension()-1; i+1 != 0; --i )
	{
		for(unsigned int j = 0; j < get_horizontal_dimension(); ++j)
		{
			push_v(empty_cgp);
		}
	}
	// initialize the board with saved value from the file
	if(	first_line == game_name &&
		first_person_file == first_person_program &&
		second_person_file == second_perosn_program)
	{
		// set the last_state to 1 in order to change the print in main()
		last_state = 1;
		// iterate through the board
		for(unsigned int i = get_vertical_dimension()-1; i+1 != 0; --i )
		{
			// read the board information
			getline(ifs,board_line);
			//cout << board_line << endl;
			istringstream pieces(board_line);
			// iterate through each piece on the line
			for(unsigned int j = 0; j < get_horizontal_dimension(); ++j)
			{
				// extract the value from each pieces
				pieces >> current_piece;
				// check if there is a piece there
				if(current_piece == X)
				{
					// set the current location with pieces
					set_v(j,i,checkers_game_piece(j,i,black,X));
				}
				else if(current_piece == B)
				{
					// set the current location with pieces
					set_v(j,i,checkers_game_piece(j,i,black,B));
				}
				else if(current_piece == O)
				{
					// set the current location with pieces
					set_v(j,i,checkers_game_piece(j,i,white,O));
				}
				else if(current_piece == W)
				{
					// set the current location with pieces
					set_v(j,i,checkers_game_piece(j,i,white,W));
				}
			}
		}
		// 2. initialize the turn_times;
		getline(ifs,turn_s);
		istringstream turn_ss_first(turn_s);
		turn_ss_first >> first_person_turn_times;
		getline(ifs,turn_s);
		istringstream turn_ss_second(turn_s);
		turn_ss_second >> second_person_turn_times;
		// 3. specify the turn
		getline(ifs,turn_s);
		istringstream whose_turn_ss(turn_s);
		whose_turn_ss >> whose_turn;
		// 4. initialize last position
		getline(ifs,last_position);
		if(last_position == "SOURCE START")
		{
			// set the flag to 1, in order to read in the turn()
			continuous_move_flag = 1;
			while(ifs.good())
			{
				string coordinate; // store the value of coordinate
				getline(ifs,coordinate);
				if(coordinate == "SOURCE END")
				{
					break;
				}
				istringstream coordinate_ss(coordinate);
				coordinate_ss >> file_x >> file_y;
			}
		}
	}
	// do not read from file, initialize the board by default
	else
	{
		// initiallize the pieces of the first player on the board
		// y = 7
		set_v(1,7,checkers_game_piece(1,7,black,X));
		set_v(3,7,checkers_game_piece(3,7,black,X));
		set_v(5,7,checkers_game_piece(5,7,black,X));
		set_v(7,7,checkers_game_piece(7,7,black,X));
		// y = 6
		set_v(0,6,checkers_game_piece(0,6,black,X));
		set_v(2,6,checkers_game_piece(2,6,black,X));
		set_v(4,6,checkers_game_piece(4,6,black,X));
		set_v(6,6,checkers_game_piece(6,6,black,X));
		// y = 5
		set_v(1,5,checkers_game_piece(1,5,black,X));
		set_v(3,5,checkers_game_piece(3,5,black,X));
		set_v(5,5,checkers_game_piece(5,5,black,X));
		set_v(7,5,checkers_game_piece(7,5,black,X));

		// initiallize the pieces of the second player on the board
		//y = 2
		set_v(0,2,checkers_game_piece(0,2,white,O));
		set_v(2,2,checkers_game_piece(2,2,white,O));
		set_v(4,2,checkers_game_piece(4,2,white,O));
		set_v(6,2,checkers_game_piece(6,2,white,O));
		// y = 1
		set_v(1,1,checkers_game_piece(1,1,white,O));
		set_v(3,1,checkers_game_piece(3,1,white,O));
		set_v(5,1,checkers_game_piece(5,1,white,O));
		set_v(7,1,checkers_game_piece(7,1,white,O));
		// y = 0
		set_v(0,0,checkers_game_piece(0,0,white,O));
		set_v(2,0,checkers_game_piece(2,0,white,O));
		set_v(4,0,checkers_game_piece(4,0,white,O));
		set_v(6,0,checkers_game_piece(6,0,white,O));
		// specify the turn
		whose_turn = argv_globle[2];
	}
}

// check whether the game is done
bool CheckersGame::done()
{
	// 1, if all the pieces on the board is the same color
	if(count_black_pieces() == 0 || count_white_pieces() == 0)
	{
		return true;
	}
	// 2, if one person can not move
	else if( check_available_move_black() == false || 
			 check_available_move_white() == false)
	{
		return true;
	}
	// if not finished
	return false;
}

// prompt the user to input the value
int CheckersGame::prompt(unsigned int &a, unsigned int &b)
{
	int count_string = 0;
	int count_comma = 0;
	int command_valid = 1;
	string quit = "quit";
	string command_line;
	string command_original;
	string temp;
	unsigned int m; // temporarily storing the integer value of commandline
	unsigned int n; // temporarily storing the integer value of commandline
	// get the input from the input stream
	getline(cin,command_line);
	command_original = command_line;
	istringstream counts (command_original);
	// count the input string
	while(counts>>temp)
	{
		count_string ++;
	}
	// check whether the input command line is valid
	if(count_string == 1)
	{
		// if the input is quit
		if (command_line == quit)
		{
			// check whehter need to save the game
			cout <<"Do you want to save the game? Enter \"yes\" to save the "
				   "game and quit, enter \"no\" to quit without saving." << endl;
			// define viarbles
			string user_input;
			int user_input_valid = 0;
			int count_string_q = 0;
			string temp_q;
			// get the input from user
			// get the input from the input stream
			getline(cin,user_input);
			istringstream counts_q (user_input);
			// count the input string
			while(counts_q >> temp_q)
			{
				++count_string_q;
			}
			while(user_input_valid != 1 || count_string_q !=1 )
			{
				if (user_input == "yes" && count_string_q == 1)
				{
					// set user_input_valid to 1 to get out of the loop
					user_input_valid = 1;
					// save current state
					save_current_state();
					cout << "The game has been saved, ";
				}
				else if(user_input == "no" && count_string_q == 1 )
				{
					// set user_input_valid to 1 to get out of the loop
					user_input_valid = 1;
					// abort the current state
					abort_current_state();
					cout << "The game has NOT been saved, ";
				}
				else
				{
					cout << "Input not correct, please input the command again."
						    "Enter \"yes\" to save the game and quit, "
						    "enter \"no\" to quit with saving. " << endl;
					getline(cin,user_input);
					count_string_q = 0;
					istringstream counts_q (user_input);
					// count the input string
					while(counts_q>>temp_q)
					{
						++count_string_q;
					}
				}
			}

			throw quit;
			return quit_game;
		}
		// if the input is not quit
		else
		{
			// Check how many comma there are and 
			// replace comma with white space
			for (unsigned int i = 0; i < command_line.length(); ++i)
			{
				if (command_line[i] == ',')
				{
					++count_comma;
					command_line[i] = ' ';
				}
			}
			// Check if there is comma in the begining or in the end
			if(command_original[0] == ',' || 
			   command_original[command_line.length()-1] == ',')
			{
				command_valid = 0;
			}
			//define iss as istringstream
			istringstream iss (command_line);
			// check the input format and if it is correct, 
			// assign the value to int &a, int &b
			if(count_comma == 1 &&
				command_valid ==1 &&
				iss >> m && iss >>n)
			{
				//check the boundary
				if(m <= horizontal_dimension-1 &&
					n<= vertical_dimension -1)
				{
					//set value of those to arguments.
					a = m;
					b = n;
					return success;
				}
				else
				{
					cout << "The input is out of boundary x <="
					     << horizontal_dimension-1 << " y <="
					     << vertical_dimension-1 << endl;
				}
			}
		}
	}
	return bad_command_line;
}

// check and make a valid move in the game
void CheckersGame::turn()
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	unsigned int first_person_x_s = 0;// the sourse of the first_person selected piece
	unsigned int first_person_y_s = 0;// the sourse of the first_person selected piece
	unsigned int first_person_x_d = 0;// the destination of the first_person selected piece
	unsigned int first_person_y_d = 0;// the destination of the first_person selected piece
	unsigned int second_person_x_s = 0;// the sourse of the second_person selected piece
	unsigned int second_person_y_s = 0;// the sourse of the second_person selected piece
	unsigned int second_person_x_d = 0;// the destination of the second_person selected piece
	unsigned int second_person_y_d = 0;// the destination of the second_person selected piece
	int input_valid = 1; // 0 means valid, 1 means invalid
	int whether_continous_move_black = 1; // 0 means no continuous move, 1 means there is continuous move
	int whether_continous_move_white = 1; // 0 means no continuous move, 1 means there is continuous move
	int whether_print_for_black = 0; // 0 means no print
	int whether_print_for_white = 0; // 0 means no print
	int check_last_continue_black = 0; // 0 means no last continue
	int check_last_continue_white = 0; // 0 means no last continue
	// initialize some parameters
	if(continuous_move_flag == 1)
	{
		// check the turn
		if ( whose_turn == argv_globle[2] )
		{
			// assign the value
			first_person_x_s = file_x;
			first_person_y_s = file_y;
			// change the print flag
			++whether_print_for_black;
		}
		// check the turn
		else if ( whose_turn == argv_globle[3] )
		{
			// assign the value
			second_person_x_s = file_x;
			second_person_y_s = file_y;
			// change the print flag
			++whether_print_for_white;
		}

	}
	//1.
	// if it is the first person's (X) turn
	if ( whose_turn == argv_globle[2] )
	{
		// check if there is piece for black piece
		if( count_black_pieces() != 0)
		{
			// do not have continuous move
			if(continuous_move_flag == 0)
			{
				// prompt the user to input the source information
				cout << first_person << "'s turn, the symbol is " << X 
				     <<" (black man) or "<< B <<" (black king). Please select a checker"
				       " by specifying its Source position or quit. " << endl;
				// prompt the user to input the value
				input_valid = prompt(first_person_x_s,first_person_y_s);
				// check whether the current posisiton is empty 
				// and check whether the input is valid
				while((input_valid != success) ||
					(v[d*first_person_y_s+first_person_x_s].color != black))
				{
					// check whether the input is valid
					if(input_valid != success)
					{
						cout << "Bad command line, please select a chekcer by "
						        "specifying its Source position, "
						         "for example: \"0,0\" or input \"quit\" to "
						         "quit the game." << endl;
						input_valid = prompt(first_person_x_s,first_person_y_s);
					}
					// check whether the input is empty
					else if(v[d*first_person_y_s+first_person_x_s].color != black)
					{
						cout << "The current position is NOT black checker, "
						        "please re-select a Source by specifying its "
						         "coordinate position." << endl;
						input_valid = prompt(first_person_x_s,first_person_y_s);
					}
				}
			}
			// check whether the turn needs to continue, the default mode is the turn needs to be played once
			while(whether_continous_move_black != 0)
			{
				// if do not have continuous move
				if(continuous_move_flag == 0)
				{
					// print the last piece information
					if(whether_print_for_black != 0)
					{
						cout << "The current black piece you select is (" 
							  <<first_person_x_s << "," 
							  << first_person_y_s<<")" << endl;
					}
					// prompt the user to input the destination infomation
					cout << first_person << "'s turn, the symbol is " << X 
					     <<" (black man) or "<< B << " (black king). Please select a "
					       "Destination by specifying its coordinate position." << endl;
					// continuous move
					if(check_last_continue_black == 1)
					{
						// set the flag to 1
						whether_in_continuous_move = 1;
					}
					// prompt the user to input the value
					input_valid = prompt(first_person_x_d,first_person_y_d);
					// check whether the detination posisiton is black and check whether the input is valid
					while((input_valid != success) ||
							(v[d*first_person_y_d+first_person_x_d] != empty_cgp) ||
							valid_put_position_black(first_person_x_s,first_person_y_s,first_person_x_d,first_person_y_d) != true)
					{
						// check whether the input is valid
						if(input_valid != success)
						{
							cout << "Bad command line, please select a chekcer by specifying"
							      " its Destination position, for example: \"0,0\" or "
							      "input \"quit\" to quit the game." << endl;
							input_valid = prompt(first_person_x_d,first_person_y_d);
						}
						// check whether the input is empty
						else if(v[d*first_person_y_d+first_person_x_d] != empty_cgp)
						{
							cout << "The current position is NOT EMPTY, please re-select a "
							        "Destination position by specifying its coordinate position." << endl;
							input_valid = prompt(first_person_x_d,first_person_y_d);
						}
						else
						{
							cout << "This is not valid move. Please re-select a Destination "
							        "by specifying its coordinate position." << endl;
							input_valid = prompt(first_person_x_d,first_person_y_d);
						}
					}
					// the player play his own turn
					complete_black_turn(first_person_x_s,first_person_y_s,
										first_person_x_d,first_person_y_d);
					// decide whether the piece on the board should be change into the King
					whether_change_into_king();
				}
				// store the value of difference
				int black_difference_x = first_person_x_d - first_person_x_s;
				int black_difference_y = first_person_y_d - first_person_y_s;
				// check if the piece can make continuous move
				if( (check_continuous_move_current_black(first_person_x_d,first_person_y_d) == true &&
					abs(black_difference_x) == 2 &&
					abs(black_difference_y) == 2) ||
					continuous_move_flag == 1
					)
				{
					print();
					cout << argv_globle[2] <<" can move the same piece continuously, "
						 "enter \"yes\" to move it continuously, " <<
						 "enter \"no\" to quit the current turn or enter \"quit\" to quit the game." << endl;
					// get the input from user and test the input
					//int count_string = 0;
					//int command_valid = 1;
					string user_input;
					int user_input_valid = 0;
					int count_string_q = 0;
					string temp_q;
					// get the input from user
					// get the input from the input stream
					getline(cin,user_input);
					istringstream counts_q (user_input);
					// count the input string
					while(counts_q >> temp_q)
					{
						++count_string_q;
					}
					while(user_input_valid != 1 || count_string_q !=1 )
					{
						if (user_input == "yes" && count_string_q == 1)
						{
							// set user_input_valid to 1 to get out of the loop
							user_input_valid = 1;
							// set the flag to 1, make it continue
							whether_continous_move_black = 1;
							// set to 1 to indicate continous move
							check_last_continue_black = 1;
							if(continuous_move_flag == 1)
							{
								first_person_x_s = file_x;
								first_person_y_s = file_y;
							}
							else
							{
								// set the source position for the continuous piece
								first_person_x_s = first_person_x_d;
								first_person_y_s = first_person_y_d;
							}
							++whether_print_for_black;
							// set the flag to 0
							continuous_move_flag = 0;
						}
						else if(user_input == "no" && count_string_q == 1 )
						{
							// set user_input_valid to 1 to get out of the loop
							user_input_valid = 0;
							// increament the each person's turn times
							++first_person_turn_times;
							print();
							// change the turn
							whose_turn =  argv_globle[3];
							// break out of the loop
							whether_continous_move_black = 0;
							// get out of this while loop
							break;
						}
						else if(user_input == "quit" && count_string_q == 1)
						{
							string quit = "quit";
							// check whehter need to save the game
							cout << "Do you want to save the game? Enter \"yes\" to save "
							       "the game and quit, enter \"no\" to quit with saving." << endl;
							// define viarbles
							string user_input;
							int user_input_valid = 0;
							int count_string_q = 0;
							string temp_q;
							// get the input from user
							// get the input from the input stream
							getline(cin,user_input);
							istringstream counts_q (user_input);
							// count the input string
							while(counts_q >> temp_q)
							{
								++count_string_q;
							}
							while(user_input_valid != 1 || count_string_q !=1 )
							{
								if (user_input == "yes" && count_string_q == 1)
								{
									// set user_input_valid to 1 to get out of the loop
									user_input_valid = 1;
									// set the flag to 1
									whether_in_continuous_move = 1;
									// set to 1 to indicate continous move
									check_last_continue_black = 1;
									if(continuous_move_flag == 1)
									{
										first_person_x_d = file_x;
										first_person_y_d = file_y;
									}
									file_x = first_person_x_d;
									file_y = first_person_y_d;
									// save current state
									save_current_state();
									cout << "The game has been saved, ";
								}
								else if(user_input == "no" && count_string_q == 1 )
								{
									// set user_input_valid to 1 to get out of the loop
									user_input_valid = 1;
									// abort the current state
									abort_current_state();
									cout << "The game has NOT been saved, ";
								}
								else
								{
									cout << "Input not correct, please input the command "
									       "again.Enter \"yes\" to save the game and quit, "
									       "enter \"no\" to quit with saving. " << endl;
									getline(cin,user_input);
									count_string_q = 0;
									istringstream counts_q (user_input);
									// count the input string
									while(counts_q>>temp_q)
									{
										++count_string_q;
									}
								}
							}
							throw quit;
						}
						// if the input is not valid
						else
						{
							cout <<"Input not correct, You can move the same piece "
							       "continuously, enter \"yes\" to move it continuously,"
									" enter \"no\" to quit the current turn or "
									"enter \"quit\" to quit the game." << endl;
							getline(cin,user_input);
							count_string_q = 0;
							istringstream counts_q (user_input);
							// count the input string
							while(counts_q>>temp_q)
							{
								++count_string_q;
							}
						}
					}
				}
				// if the current person can not make continuous move
				else
				{
				// increament the each person's turn times
				++first_person_turn_times;
				print();
				// change the turn
				whose_turn =  argv_globle[3];
				// break out of the loop
				whether_continous_move_black = 0;
				// set the flag to 0, not to write the current position into the file
				whether_in_continuous_move = 0;
				// set to 0 to indicate no last continous move
				check_last_continue_black = 0;
				}
			}// end of while
		}
		// skip this turn for the first player
		else
		{
			// change the turn
			whose_turn =  argv_globle[3];
			cout << first_person << "'s turn SKIPPED, because "
					"there is no valid move." << endl<< endl;
		}
	}
	// 2.
	// if it is the second person's (O) turn
	if(whose_turn == argv_globle[3])
	{
		// check if the there is white pieces
		if (count_white_pieces() != 0)
		{
			// do not have continuous move
			if(continuous_move_flag == 0)
			{
				// prompt the user to input the source information
				cout << second_person << "'s turn, the symbol is " << O 
					 << " (white man) or "<< W <<" (white king). Please select a checker "
					    "by specifying its Source position or quit. " << endl;
				// prompt the user to input the value
				input_valid = prompt(second_person_x_s,second_person_y_s);
				// check whether the source posisiton is white and check whether the input is valid
				while((input_valid != success) ||
					(v[d*second_person_y_s+second_person_x_s].color != white))
				{
					// check whether the input is valid
					if(input_valid != success)
					{
						cout << "Bad command line, please select a chekcer by specifying "
							   "its Source position, for example: \"0,0\" or input \"quit\" to quit the game." << endl;
						input_valid = prompt(second_person_x_s,second_person_y_s);
					}
					// check whether the input is empty
					else if(v[d*second_person_y_s+second_person_x_s].color != white)
					{
						cout << "The current position is NOT white checker, please re-select a "
							   "Source by specifying its coordinate position." << endl;
						input_valid = prompt(second_person_x_s,second_person_y_s);
					}
				}
			}
			// check whether the turn needs to continue, the default mode is the turn needs to be played once
			while(whether_continous_move_white != 0)
			{
				// if do not have continuous move
				if(continuous_move_flag == 0)
				{
					// print the last piece information
					if(whether_print_for_white != 0)
					{
						cout << "The current black piece you select is (" 
							 << second_person_x_s << "," << second_person_y_s
							 <<")" << endl;
					}
					// prompt the user to input the destination infomation
					cout << second_person << "'s turn, the symbol is " << O <<" (white man) or "
					     << W << " (white king). Please select a Destination by "
					     "specifying its coordinate position." << endl;
					// continuous move
					if(check_last_continue_white == 1)
					{
						// set the flag to 1
						whether_in_continuous_move = 1;
					}
					// prompt the user to input the value
					input_valid = prompt(second_person_x_d,second_person_y_d);
					// check whether the current posisiton is empty and check whether the input is valid
					while((input_valid != success) ||
						(v[d*second_person_y_d+second_person_x_d] != empty_cgp) ||
						valid_put_position_white(second_person_x_s,second_person_y_s,
												 second_person_x_d,second_person_y_d) != true)
					{
						// check whether the input is valid
						if(input_valid != success)
						{
							cout<<"Bad command line, please select a chekcer by specifying "
								  "its Destination position, for example: \"0,0\" or input \"quit\" to quit the game." << endl;
							input_valid = prompt(second_person_x_d,second_person_y_d);
						}
						// check whether the input is empty
						else if(v[d*second_person_y_d+second_person_x_d] != empty_cgp)
						{
							cout << "The current position is NOT EMPTY, please re-select a "
							       "Destination by specifying its coordinate position." << endl;
							input_valid = prompt(second_person_x_d,second_person_y_d);
						}
						else
						{
							cout <<"This is not valid move. Please re-select a Destination"
								   " by specifying its coordinate position." << endl;
							input_valid = prompt(second_person_x_d,second_person_y_d);
						}
					}
					// the player play his own turn
					complete_white_turn(second_person_x_s,second_person_y_s,
										second_person_x_d,second_person_y_d);
					// decide whether the piece on the board should be change into the King
					whether_change_into_king();
				}
				// store the value of difference
				int white_difference_x = second_person_x_d - second_person_x_s;
				int white_difference_y = second_person_y_d - second_person_y_s;
				// check if the piece can make continuous move
				if((check_continuous_move_current_white(second_person_x_d,second_person_y_d) == true &&
					abs(white_difference_x) == 2 &&
					abs(white_difference_y) == 2 )||
					continuous_move_flag == 1
					)
				{
					print();
					cout << argv_globle[3] <<" can move the same piece continuously, "
						"enter \"yes\" to move it continuously, " <<
						"enter \"no\" to quit the current turn or enter \"quit\" to quit the game." << endl;
					// get the input from user and test the input
					//int count_string = 0;
					//int command_valid = 1;
					string user_input;
					int user_input_valid = 0;
					int count_string_q = 0;
					string temp_q;
					// get the input from user
					// get the input from the input stream
					getline(cin,user_input);
					istringstream counts_q (user_input);
					// count the input string
					while(counts_q >> temp_q)
					{
						++count_string_q;
					}
					while(user_input_valid != 1 || count_string_q !=1 )
					{
						if (user_input == "yes" && count_string_q == 1)
						{
							// set user_input_valid to 1 to get out of the loop
							user_input_valid = 1;
							// set the flag to 1, make it continue
							whether_continous_move_white = 1;
							// set to 1 to indicate continous move
							check_last_continue_white = 1;
							// set the source position for the continuous piece
							if(continuous_move_flag == 1)
							{
								second_person_x_s = file_x;
								second_person_y_s = file_y;
							}
							else
							{
								// set the source position for the continuous piece
								second_person_x_s = second_person_x_d;
								second_person_y_s = second_person_y_d;
							}
							++whether_print_for_white;
							// set the flag to 0
							continuous_move_flag = 0;
						}
						else if(user_input == "no" && count_string_q == 1 )
						{
							// set user_input_valid to 1 to get out of the loop
							user_input_valid = 0;
							// increament the each person's turn times
							++second_person_turn_times;
							print();
							// change the turn
							whose_turn =  argv_globle[2];
							// break out of the loop
							whether_continous_move_black = 0;
							// get out of this while loop
							break;
						}
						else if(user_input == "quit" && count_string_q == 1)
						{
							string quit = "quit";
							// check whehter need to save the game
							cout <<"Do you want to save the game? Enter \"yes\" to save"
							       " the game and quit, enter \"no\" to quit with saving." << endl;
							// define viarbles
							string user_input;
							int user_input_valid = 0;
							int count_string_q = 0;
							string temp_q;
							// get the input from user
							// get the input from the input stream
							getline(cin,user_input);
							istringstream counts_q (user_input);
							// count the input string
							while(counts_q >> temp_q)
							{
								++count_string_q;
							}
							while(user_input_valid != 1 || count_string_q !=1 )
							{
								if (user_input == "yes" && count_string_q == 1)
								{
									// set user_input_valid to 1 to get out of the loop
									user_input_valid = 1;
									// set the flag to 1
									whether_in_continuous_move = 1;
									// set to 1 to indicate continous move
									check_last_continue_white = 1;
									if(continuous_move_flag == 1)
									{
										second_person_x_d = file_x;
										second_person_y_d = file_y;
									}
									file_x = second_person_x_d;
									file_y = second_person_y_d;
									// save current state
									save_current_state();
									cout << "The game has been saved, ";
								}
								else if(user_input == "no" && count_string_q == 1 )
								{
									// set user_input_valid to 1 to get out of the loop
									user_input_valid = 1;
									// abort the current state
									abort_current_state();
									cout << "The game has NOT been saved, ";
								}
								else
								{
									cout << "Input not correct, please input the command "
									       "again.Enter \"yes\" to save the game and quit, "
									        "enter \"no\" to quit with saving. " << endl;
									getline(cin,user_input);
									count_string_q = 0;
									istringstream counts_q (user_input);
									// count the input string
									while(counts_q>>temp_q)
									{
										++count_string_q;
									}
								}
							}
							throw quit;
						}
						// if the user input is not valid
						else
						{
							cout <<"Input not correct, You can move the same "
							       "piece continuously, enter \"yes\" to"
							        " move it continuously," <<
									" enter \"no\" to quit the current turn or "
									"enter \"quit\" to quit the game." << endl;
							getline(cin,user_input);
							count_string_q = 0;
							istringstream counts_q (user_input);
							// count the input string
							while(counts_q>>temp_q)
							{
								++count_string_q;
							}
						}
					}
				}
				// if the current person can not make continuous move
				else
				{
					// increament the each person's turn times
					++second_person_turn_times;
					print();
					// change the turn
					whose_turn =  argv_globle[2];
					// break out of the loop
					whether_continous_move_white = 0;
					// set the flag to 0, not to write the current position into the file
					whether_in_continuous_move = 0;
					// set to 0 to indicate no last continous move
					check_last_continue_white = 0;
				}
			}
		}
		// skip this turn for the second player
		else
		{
			// change the turn
			whose_turn =  argv_globle[2];
			cout << second_person << "'s turn SKIPPED, "
			        "because there is no valid move." << endl << endl;
		}
	}
}

// play the game by calling turn()
int CheckersGame::play()
{
	while(done()!= true)
	{
		// call the function turn()
		turn();
	}
	// check who is the winner
	// if first person is the winner
	if(check_available_move_black() == true && check_available_move_white() == false)
	{
		cout << first_person << " is the WINNER! Congratulation! " 
		     << first_person <<" took "<< first_person_turn_times
			 << " turns to finish the game." << endl;
	}
	// if second person is the winner
	else if(check_available_move_black() == false && check_available_move_white() == true)
	{
		cout << second_person << " is the WINNER! Congratulation! " 
		     << second_person <<" took "<< second_person_turn_times
			 << " turns to finish the game." << endl;
	}
	// if it is a tie
	else
	{
		cout <<"This is a TIE." << endl;
	}
	// the next time the game should start from the beginning
	//abort_current_state();
	return success;
}

// save the current state
void CheckersGame::save_current_state()
{
	// make the file name
	string game_name = argv_globle[1];
	string first_person = argv_globle[2];
	string second_perosn = argv_globle[3];
	string file_name = game_name +"_"+ first_person +"_"+ second_person + ".txt";
	// write to the files
	ofstream ofs (file_name.c_str());
	if (ofs.is_open ())
	{
		// 1. store the name of the game and the name of the player
		ofs << game_name << endl;
		ofs << argv_globle[2] << endl;
		ofs << argv_globle[3] << endl;
		// 2. store the board state
		// flag whether the piece exists
		int piece_existing = 0;
		for(unsigned int i = vertical_dimension-1; i+1 != 0; --i )
		{
			// Print the board
			for(unsigned int j = 0; j < horizontal_dimension; ++j)
			{
				//check whether it is empty
				if (v[horizontal_dimension*i+j] != empty_cgp)
				{
					// print out the symbol
					ofs << v[horizontal_dimension*i+j].symbol <<" ";
					piece_existing = 1;
				}
				// If there is no piece there, print out the space
				if(piece_existing == 0)
				{
					ofs << "E" << " ";
				}
				piece_existing = 0;
				//change the line
				if(j == horizontal_dimension-1)
				{
					ofs<< endl;
				}
			}
		}
	// 3. store the number of turns
	ofs<< first_person_turn_times << endl;
	ofs<< second_person_turn_times << endl;
	// 4. store the current turn of the player
	ofs<< whose_turn << endl;
	// 5. save the continuous move
	if(whether_in_continuous_move == 1)
	{
		ofs << "SOURCE START" << endl;
		// store the last continuous position of the piece
		ofs << file_x << " " << file_y << endl ;
		ofs << "SOURCE END" << endl;
	}
	// close the file
	ofs.close();
	}
}

// abort the current state
void CheckersGame::abort_current_state()
{
	// make the file name
	string information = "NO DATA";
	string game_name = argv_globle[1];
	string first_person = argv_globle[2];
	string second_perosn = argv_globle[3];
	string file_name = game_name +"_"+ first_person +"_"+ second_person + ".txt";
	// write to the files
	ofstream ofs (file_name.c_str());
	if (ofs.is_open ())
	{
		ofs << information << endl;
	}
	// close the file
	ofs.close();
}

// checks if this puting position is valid
bool CheckersGame::valid_put_position_black(unsigned int i, unsigned int j, 
	                                        unsigned int m, unsigned int n)
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	// 1. if the black piece is a man or king
	// case 1 , direction 5  o'clock without white piece in the middle
	if( i+1 == m && j-1 == n &&
		i <=6 && j>=1 &&
		v[d*n+m] == empty_cgp)
	{
		return true;
	}
	// case 2 , direction 5  o'clock with white piece in the middle
	if( i+2 == m && j-2 == n &&
		i <=5 && j>=2 &&
		v[d*n+m] == empty_cgp)
	{
		if(v[d*(j-1)+(i+1)].color == white)
		{
			return true;
		}
	}
	// case 3 , direction 7  o'clock without white piece in the middle
	if( i-1 == m && j-1 == n &&
		i>=1 && j>=1 &&
		v[d*n+m] == empty_cgp)
	{
		return true;
	}
	// case 4 , direction 7  o'clock with white piece in the middle
	if( i-2 == m && j-2 == n &&
		i >=2 && j>=2 &&
		v[d*n+m] == empty_cgp)
	{
		if(v[d*(j-1)+(i-1)].color == white)
		{
			return true;
		}
	}
	// 2.  if the symbol is the black king, move backwards
	if(v[d*j+i].symbol == B)
	{
		// case 1 , direction 11  o'clock without black piece in the middle
		if( i-1 == m && j+1 == n &&
			i>=1 && j<=6 &&
			v[d*n+m] == empty_cgp)
		{
			return true;
		}
		// case 2 , direction 11  o'clock with black piece in the middle
		if( i-2 == m && j+2 == n &&
			i>=2 && j<=5  &&
			v[d*n+m] == empty_cgp)
		{
			if(v[d*(j+1)+(i-1)].color == white)
			{
				return true;
			}
		}
		// case 3 , direction 1  o'clock without black piece in the middle
		if( i+1 == m && j+1 == n &&
			i<=6 && j<=6 &&
			v[d*n+m] == empty_cgp)
		{
			return true;
		}
		// case 4 , direction 1  o'clock with black piece in the middle
		if( i+2 == m && j+2 == n &&
			i <=5 && j<=5 &&
			v[d*n+m] == empty_cgp)
		{
			if(v[d*(j+1)+(i+1)].color == white)
			{
				return true;
			}
		}
	}
	return false;
}

// checks if this puting position is valid
bool CheckersGame::valid_put_position_white(unsigned int i, unsigned int j, 
	                                        unsigned int m, unsigned int n)
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	// 1. if the white piece is a man or king
	// case 1 , direction 11  o'clock without black piece in the middle
	if( i-1 == m && j+1 == n &&
		i>=1 && j<=6 &&
		v[d*n+m] == empty_cgp)
	{
		return true;
	}
	// case 2 , direction 11  o'clock with black piece in the middle
	if( i-2 == m && j+2 == n &&
		i>=2 && j<=5 &&
		v[d*n+m] == empty_cgp)
	{
		if(v[d*(j+1)+(i-1)].color == black)
		{
			return true;
		}
	}
	// case 3 , direction 1  o'clock without black piece in the middle
	if( i+1 == m && j+1 == n &&
		i<=6 && j<=6 &&
		v[d*n+m] == empty_cgp)
	{
		return true;
	}
	// case 4 , direction 1  o'clock with black piece in the middle
	if( i+2 == m && j+2 == n &&
		i <=5 && j<=5 &&
		v[d*n+m] == empty_cgp)
	{
		if(v[d*(j+1)+(i+1)].color == black)
		{
			return true;
		}
	}
	// 2.  if the symbol is the white king, move backwards
	if(v[d*j+i].symbol == W)
	{
		// case 1 , direction 5  o'clock without white piece in the middle
		if( i+1 == m && j-1 == n &&
			i <=6 && j>=1 &&
			v[d*n+m] == empty_cgp)
		{
			return true;
		}
		// case 2 , direction 5  o'clock with white piece in the middle
		if( i+2 == m && j-2 == n &&
			i <=5 && j>=2 &&
			v[d*n+m] == empty_cgp)
		{
			if(v[d*(j-1)+(i+1)].color == black)
			{
				return true;
			}
		}
		// case 3 , direction 7  o'clock without white piece in the middle
		if( i-1 == m && j-1 == n &&
			i>=1 && j>=1&&
			v[d*n+m] == empty_cgp)
		{
			return true;
		}
		// case 4 , direction 7  o'clock with white piece in the middle
		if( i-2 == m && j-2 == n &&
			i >=2 && j>=2&&
			v[d*n+m] == empty_cgp)
		{
			if(v[d*(j-1)+(i-1)].color == black)
			{
				return true;
			}
		}
	}
	return false;
}

// complete the play's turn and change the board according to the rules
void CheckersGame::complete_black_turn(unsigned int i, unsigned int j, 
	                                   unsigned int m, unsigned int n)
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	// 1. if the black piece is a man
	if(v[d*j+i].symbol == X)
	{
		// case 1 , direction 5  o'clock without white piece in the middle
		if( i+1 == m && j-1 == n &&
			i <=6 && j>=1 )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j-1)+(i+1)] = checkers_game_piece(i+1,j-1,black,X);
		}
		// case 2 , direction 5  o'clock with white piece in the middle
		if( i+2 == m && j-2 == n &&
			i <=5 && j>=2 )
		{
			if(v[d*(j-1)+(i+1)].color == white)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j-1)+(i+1)] = empty_cgp;
				// destination position
				v[d*(j-2)+(i+2)] = checkers_game_piece(i+2,j-2,black,X);
			}
		}
		// case 3 , direction 7  o'clock without white piece in the middle
		if( i-1 == m && j-1 == n &&
			i>=1 && j>=1 )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j-1)+(i-1)] = checkers_game_piece(i-1,j-1,black,X);
		}
		// case 4 , direction 7  o'clock with white piece in the middle
		if( i-2 == m && j-2 == n &&
			i >=2 && j>=2 )
		{
			if(v[d*(j-1)+(i-1)].color == white)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j-1)+(i-1)] = empty_cgp;
				// destination position
				v[d*(j-2)+(i-2)] = checkers_game_piece(i-2,j-2,black,X);
			}
		}
	}
	// 2.  if the symbol is the black king
	else if(v[d*j+i].symbol == B)
	{
		// case 1 , direction 5  o'clock without white piece in the middle
		if( i+1 == m && j-1 == n &&
			i <=6 && j>=1 )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j-1)+(i+1)] = checkers_game_piece(i+1,j-1,black,B);
		}
		// case 2 , direction 5  o'clock with white piece in the middle
		if( i+2 == m && j-2 == n &&
			i <=5 && j>=2 )
		{
			if(v[d*(j-1)+(i+1)].color == white)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j-1)+(i+1)] = empty_cgp;
				// destination position
				v[d*(j-2)+(i+2)] = checkers_game_piece(i+2,j-2,black,B);
			}
		}
		// case 3 , direction 7  o'clock without white piece in the middle
		if( i-1 == m && j-1 == n &&
			i>=1 && j>=1 )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j-1)+(i-1)] = checkers_game_piece(i-1,j-1,black,B);
		}
		// case 4 , direction 7  o'clock with white piece in the middle
		if( i-2 == m && j-2 == n &&
			i >=2 && j>=2 )
		{
			if(v[d*(j-1)+(i-1)].color == white)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j-1)+(i-1)] = empty_cgp;
				// destination position
				v[d*(j-2)+(i-2)] = checkers_game_piece(i-2,j-2,black,B);
			}
		}
		// case 5 , direction 11  o'clock without black piece in the middle
		if( i-1 == m && j+1 == n &&
			i>=1 && j <=6  )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j+1)+(i-1)] = checkers_game_piece(i-1,j+1,black,B);
		}
		// case 6 , direction 11  o'clock with white piece in the middle
		if( i-2 == m && j+2 == n &&
			i>=2 && j<=5 )
		{
			if(v[d*(j+1)+(i-1)].color == white)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j+1)+(i-1)] = empty_cgp;
				// destination position
				v[d*(j+2)+(i-2)] = checkers_game_piece(i+2,j-2,black,B);
			}
		}
		// case 7 , direction 7  o'clock without white piece in the middle
		if( i+1 == m && j+1 == n &&
			i<=6 && i<=6 )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j+1)+(i+1)] = checkers_game_piece(i+1,j+1,black,B);
		}
		// case 8 , direction 7  o'clock with white piece in the middle
		if( i+2 == m && j+2 == n &&
			i <=6 && j<=6 )
		{
			if(v[d*(j+1)+(i+1)].color == white)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j+1)+(i+1)] = empty_cgp;
				// destination position
				v[d*(j+2)+(i+2)] = checkers_game_piece(i+2,j+2,black,B);
			}
		}
	}
}

// complete the play's turn and change the board according to the rules
void CheckersGame::complete_white_turn(unsigned int i, unsigned int j, unsigned int m, unsigned int n)
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	// 1. if the black piece is a man
	if(v[d*j+i].symbol == O)
	{
		// case 1 , direction 11  o'clock without black piece in the middle
		if( i-1 == m && j+1 == n &&
			i>=1 && j <=6  )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j+1)+(i-1)] = checkers_game_piece(i-1,j+1,white,O);
		}
		// case 2 , direction 11  o'clock with white piece in the middle
		if( i-2 == m && j+2 == n &&
			i>=2 && j<=5 )
		{
			if(v[d*(j+1)+(i-1)].color == black)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j+1)+(i-1)] = empty_cgp;
				// destination position
				v[d*(j+2)+(i-2)] = checkers_game_piece(i+2,j-2,white,O);
			}
		}
		// case 3 , direction 1  o'clock without white piece in the middle
		if( i+1 == m && j+1 == n &&
			i<=6 && i<=6 )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j+1)+(i+1)] = checkers_game_piece(i+1,j+1,white,O);
		}
		// case 4 , direction 1  o'clock with white piece in the middle
		if( i+2 == m && j+2 == n &&
			i <=6 && j<=6 )
		{
			if(v[d*(j+1)+(i+1)].color == black)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j+1)+(i+1)] = empty_cgp;
				// destination position
				v[d*(j+2)+(i+2)] = checkers_game_piece(i+2,j+2,white,O);
			}
		}
	}
	// 2.  if the symbol is the white king
	else if(v[d*j+i].symbol == W)
	{
		// case 1 , direction 11  o'clock without black piece in the middle
		if( i-1 == m && j+1 == n &&
			i>=1 && j <=6  )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j+1)+(i-1)] = checkers_game_piece(i-1,j+1,white,W);
		}
		// case 2 , direction 11  o'clock with white piece in the middle
		if( i-2 == m && j+2 == n &&
			i>=2 && j<=5 )
		{
			if(v[d*(j+1)+(i-1)].color == black)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j+1)+(i-1)] = empty_cgp;
				// destination position
				v[d*(j+2)+(i-2)] = checkers_game_piece(i+2,j-2,white,W);
			}
		}
		// case 3 , direction 1  o'clock without white piece in the middle
		if( i+1 == m && j+1 == n &&
			i<=6 && i<=6 )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j+1)+(i+1)] = checkers_game_piece(i+1,j+1,white,W);
		}
		// case 4 , direction 1  o'clock with white piece in the middle
		if( i+2 == m && j+2 == n &&
			i <=6 && j<=6 )
		{
			if(v[d*(j+1)+(i+1)].color == black)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j+1)+(i+1)] = empty_cgp;
				// destination position
				v[d*(j+2)+(i+2)] = checkers_game_piece(i+2,j+2,white,W);
			}
		}
		// case 5 , direction 5  o'clock without white piece in the middle
		if( i+1 == m && j-1 == n &&
			i <=6 && j>=1 )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j-1)+(i+1)] = checkers_game_piece(i+1,j-1,white,W);
		}
		// case 6 , direction 5  o'clock with white piece in the middle
		if( i+2 == m && j-2 == n &&
			i <=5 && j>=2 )
		{
			if(v[d*(j-1)+(i+1)].color == black)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j-1)+(i+1)] = empty_cgp;
				// destination position
				v[d*(j-2)+(i+2)] = checkers_game_piece(i+2,j-2,white,W);
			}
		}
		// case 7 , direction 7  o'clock without white piece in the middle
		if( i-1 == m && j-1 == n &&
			i>=1 && j>=1 )
		{
			// the source position empty
			v[d*j+i] = empty_cgp;
			// the destination position black pieces
			v[d*(j-1)+(i-1)] = checkers_game_piece(i-1,j-1,white,W);
		}
		// case 8 , direction 7  o'clock with white piece in the middle
		if( i-2 == m && j-2 == n &&
			i >=2 && j>=2 )
		{
			if(v[d*(j-1)+(i-1)].color == black)
			{
				// the source position empty
				v[d*j+i] = empty_cgp;
				// the middle position empty
				v[d*(j-1)+(i-1)] = empty_cgp;
				// destination position
				v[d*(j-2)+(i-2)] = checkers_game_piece(i-2,j-2,white,W);
			}
		}
	}
}

// count the number of plack pieces
unsigned int CheckersGame::count_black_pieces()
{
	unsigned total_number_of_black_pieces = 0;
	// store the value of the dimension
	unsigned int d = horizontal_dimension;
	for(unsigned int i = vertical_dimension-1; i+1 != 0; --i )
	{
		for(unsigned int j = 0; j < horizontal_dimension; ++j)
		{
			//check whether it is empty
			if (v[d*i+j] != empty_cgp)
			{
				// count the black pieces
				if(v[d*i+j].color == black)
				{
					++total_number_of_black_pieces;
				}
			}
		}
	}
	return total_number_of_black_pieces;
}

// count the number of white piece
unsigned int CheckersGame::count_white_pieces()
{
	unsigned total_number_of_white_pieces = 0;
	// store the value of the dimension
	unsigned int d = horizontal_dimension;
	for(unsigned int i = vertical_dimension-1; i+1 != 0; --i )
	{
		for(unsigned int j = 0; j < horizontal_dimension; ++j)
		{
			//check whether it is empty
			if (v[d*i+j] != empty_cgp)
			{
				//cout the white pieces
				if(v[d*i+j].color == white)
				{
					++total_number_of_white_pieces;
				}
			}
		}
	}
	return total_number_of_white_pieces;
}

// check if there is a available move for black piece
bool CheckersGame::check_available_move_black()
{
	// store the value of the dimension
	unsigned int d = horizontal_dimension;
	for(unsigned int j = vertical_dimension-1; j+1 != 0; --j )
	{
		for(unsigned int i = 0; i < horizontal_dimension; ++i)
		{
			//check whether it is black piece
			if (v[d*j+i].color == black)
			{
				// 1.  if the black piece is man or king
				// case 1 , direction 5  o'clock without white piece in the middle
				if(i<=6 && j>=1 && valid_put_position_black(i,j,i+1,j-1)== true)
				{
					return true;
				}
				// case 2 , direction 5  o'clock with white piece in the middle
				if(i<=5 && j>=2 && valid_put_position_black(i,j,i+2,j-2)== true)
				{
					return true;
				}
				// case 3 , direction 7  o'clock without white piece in the middle
				if(i>=1 && j>=1 && valid_put_position_black(i,j,i-1,j-1) == true)
				{
					return true;
				}
				// case 4 , direction 7  o'clock with white piece in the middle
				if(i>=2 && j>=2 && valid_put_position_black(i,j,i-2,j-2) == true)
				{
					return true;
				}
				// 2. if the black piece is king
				if(v[d*j+i].symbol == B)
				{
					// case 1 , direction 11  o'clock without white piece in the middle
					if(i>=1 && j<=6 && valid_put_position_black(i,j,i-1,j+1) == true)
					{
						return true;
					}
					// case 2 , direction 11  o'clock with white piece in the middle
					if(i>=2 && j<=5 && valid_put_position_black(i,j,i-2,j+2) == true)
					{
						return true;
					}
					// case 3 , direction 1  o'clock without white piece in the middle
					if(i<=6 && j<=6 && valid_put_position_black(i,j,i+1,j+1) == true)
					{
						return true;
					}
					// case 4 , direction 1  o'clock with white piece in the middle
					if(i<=5 && j<=5 && valid_put_position_black(i,j,i+2,j+2) == true)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

// check if there is a available move for white piece
bool CheckersGame::check_available_move_white()
{
	// store the value of the dimension
	unsigned int d = horizontal_dimension;
	for(unsigned int j = vertical_dimension-1; j+1 != 0; --j )
	{
		for(unsigned int i = 0; i < horizontal_dimension; ++i)
		{
			//check whether it is white piece
			if (v[d*j+i].color == white)
			{
				// 1.  if the black piece is man or king
				// case 1 , direction 11  o'clock without black piece in the middle
				if(i>=1 && j<=6 && valid_put_position_white(i,j,i-1,j+1)== true)
				{
					return true;
				}
				// case 2 , direction 11  o'clock with black piece in the middle
				if(i>=2 && j<=5 && valid_put_position_white(i,j,i-2,j+2)== true)
				{
					return true;
				}
				// case 3 , direction 1  o'clock without black piece in the middle
				if(i<=6 && j<=6 && valid_put_position_white(i,j,i+1,j+1) == true)
				{
					return true;
				}
				// case 4 , direction 1  o'clock with black piece in the middle
				if(i<=5 && j<=5 && valid_put_position_white(i,j,i+2,j+2) == true)
				{
					return true;
				}
				// 2. if the black piece is king
				if(v[d*j+i].symbol == W)
				{
					// case 1 , direction 5  o'clock without black piece in the middle
					if(i<=6 && j>=1 && valid_put_position_white(i,j,i+1,j-1)== true)
					{
						return true;
					}
					// case 2 , direction 5  o'clock with black piece in the middle
					if(i<=5 && j>=2 && valid_put_position_white(i,j,i+2,j-2)== true)
					{
						return true;
					}
					// case 3 , direction 7  o'clock without black piece in the middle
					if(i>=1 && j>=1 && valid_put_position_white(i,j,i-1,j-1) == true)
					{
						return true;
					}
					// case 4 , direction 7  o'clock with black piece in the middle
					if(i>=2 && j>=2 && valid_put_position_white(i,j,i-2,j-2) == true)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

// decide whether the piece on the board should be change into the King
void CheckersGame:: whether_change_into_king()
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	// for the black piece to be the King
	for(unsigned int i = 0; i < d; ++i)
	{
		if(v[i].color == black && v[i].symbol == X)
		{
			v[i] = checkers_game_piece(i,0,black,B);
		}
	}
	// for the white piece to be the King
	for(unsigned int i = 0; i < d; ++i)
	{
		if(v[d*7+i].color == white && v[d*7+i].symbol == O)
		{
			v[d*7+i] = checkers_game_piece(i,7,white,W);
		}
	}
}

// check if the continuous move is valid
bool CheckersGame:: check_continuous_move_current_black(unsigned int i, unsigned int j)
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	// 1.  if the black piece is man or king
	// case 1 , direction 5  o'clock with white piece in the middle
	if(i<=5 && j>=2 && valid_put_position_black(i,j,i+2,j-2)== true)
	{
		return true;
	}
	// case 2 , direction 7  o'clock with white piece in the middle
	if(i>=2 && j>=2 && valid_put_position_black(i,j,i-2,j-2) == true)
	{
		return true;
	}
	// 2. if the black piece is king
	if(v[d*j+i].symbol == B)
	{
		// case 1 , direction 11  o'clock with white piece in the middle
		if(i>=2 && j<=5 && valid_put_position_black(i,j,i-2,j+2) == true)
		{
			return true;
		}
		// case 2 , direction 1  o'clock with white piece in the middle
		if(i<=5 && j<=5 && valid_put_position_black(i,j,i+2,j+2) == true)
		{
			return true;
		}
	}
	return false;
}

// check if the continuous move is valid
bool CheckersGame:: check_continuous_move_current_white(unsigned int i, unsigned int j)
{
	// store the value of the dimension
	unsigned int d = horizontal_dimension;
	// 1.  if the black piece is man or king
	// case 1 , direction 11  o'clock with black piece in the middle
	if(i>=2 && j<=5 && valid_put_position_white(i,j,i-2,j+2)== true)
	{
		return true;
	}
	// case 2 , direction 1  o'clock with black piece in the middle
	if(i<=5 && j<=5 && valid_put_position_white(i,j,i+2,j+2) == true)
	{
		return true;
	}
	// 2. if the black piece is king
	if(v[d*j+i].symbol == W)
	{
		// case 1 , direction 5  o'clock with black piece in the middle
		if(i<=5 && j>=2 && valid_put_position_white(i,j,i+2,j-2)== true)
		{
			return true;
		}
		// case 2 , direction 7  o'clock with black piece in the middle
		if(i>=2 && j>=2 && valid_put_position_white(i,j,i-2,j-2) == true)
		{
			return true;
		}
	}
	return false;
}
