// ReversiGame.cpp
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#include "OtherFunctions.h"
#include "GameBase.h"
#include "ReversiGame.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <memory>
#include <list>
#include <fstream>

// globe value of argv[]
extern char ** argv_globle;
// flag out whehter to return the last state
extern int last_state; // 0 means not to return
//Define the initial state of the piece on the board for initialize_game() 
// function. x_empty,y_empty is defined in other_functions.h
reversi_game_piece empty_rgp(x_empty,y_empty,black_or_white,"E");
// symbol for the black peice
string X = "X";
// symbol for the white peice
string O = "O";
// store the value of turn time
int first_person_turn_times = 0;
// store the value of turn time
int second_person_turn_times = 0;
// store the whose turn
string whose_turn;

//constructor of ReversiGame
ReversiGame::ReversiGame(unsigned int h,unsigned int v,piece_color color,
	                    string name,string symbol, string first, string second)
:GameBase( h, v, color, name, symbol),
first_person(first),second_person(second) {}

//set function
void ReversiGame::push_v (reversi_game_piece rgp)
{
	v.push_back(rgp);
}

//set function
void ReversiGame::set_v (unsigned int x,unsigned int y ,reversi_game_piece rgp)
{
	v[horizontal_dimension*y+x] = rgp;
}

// print method
void ReversiGame::print()
{
	cout << endl << *this << endl << endl;
	// print the number of pieces
	cout << "Total number of X = "<< count_black_pieces()<< endl;
	cout << "Total number of O = "<< count_white_pieces()<< endl;
	cout << endl;
}

// Overloading the operator << for NineAlmonds Game
ostream &operator<< (ostream &out,  const ReversiGame &r)
{
	//define the empty piece
	int piece_existing = 0;
	// store the value of the dimension
	unsigned int d = r.horizontal_dimension;
	for(unsigned int i = r.vertical_dimension-1; i+1!= 0; --i )
	{
		// Draw the Y coordinate
		out<< i<<" ";
		// Print the board
		for(unsigned int j = 0; j < r.horizontal_dimension; ++j)
		{
			//check whether it is empty
			if (r.v[d*i+j] != empty_rgp)
			{
				// print out the symbol
				out << setiosflags(ios_base::left)
				    << setw(r.longest_string_length+1) 
				    << r.v[d*i+j].symbol;
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
				out<< endl;
			}
		}
	}
	// Draw the X coordinate
	out<<"X"<<" ";
	for(unsigned int j = 0; j < r.horizontal_dimension; ++j)
	{
		// Draw the X coordinate with the space between them
		out << setiosflags(ios_base::left)
		    << setw(r.longest_string_length+1) << j;
	}
	return out;
}

//Initialize the board
void ReversiGame::initialize_game()
{
	string first_line; // store the first line
	string first_person_file; // store the first person
	string second_person_file; // store the first person
	string board_line; // store the one line in the file
	string current_piece; // store the current piece
	string turn_s; // store the value of turn_times
	string game_name = argv_globle[1];
	//=1 if it is needed to initialize game from start because 
	// the file is edited without permission.Otherwise =0.
	int flag_initialize_game_from_start=0;
	string first_person_program = argv_globle[2];
	string second_perosn_program = argv_globle[3];
	string file_name = game_name +"_"+ first_person_program +"_"+ 
	                   second_perosn_program + ".txt";
	// first try to read from file
	ifstream ifs (file_name.c_str());
	if (ifs.is_open ())
	{
		ifs>>first_line;
		ifs>>first_person_file;
		ifs>>second_person_file;
	}
	//1.initialize the piece on the NineAlmondsGame
	for(unsigned int i = get_vertical_dimension()-1; i+1 != 0; --i )
	{
		for(unsigned int j = 0; j < get_horizontal_dimension(); ++j)
		{
			push_v(empty_rgp);
		}
	}
	// initialize the board with saved value from the file
	if(	first_line == game_name &&
		first_person_file == first_person_program &&
		second_person_file == second_perosn_program)
	{

		// iterate through the board
		for(unsigned int i = get_vertical_dimension()-1; i+1 != 0; --i )
		{
			// read the board information
			// iterate through each piece on the line
			for(unsigned int j = 0; j < get_horizontal_dimension(); ++j)
			{
				// extract the value from each pieces
				ifs >> current_piece;
				// check if there is a piece there
				if (current_piece != X && 
				    current_piece != O && 
				    current_piece != "E")
				{
					cout<<"The saved file has been edited without permission."
					<< endl <<"So, a new game will be initialized." << endl;
					initialize_game_from_start();
					flag_initialize_game_from_start=1;
					break;
				}

				if(current_piece == X && flag_initialize_game_from_start==0)
				{
					// set the current location with pieces
					set_v(j,i,reversi_game_piece(j,i,black,X));
				}
				else if(current_piece == O && flag_initialize_game_from_start==0)
				{
					// set the current location with pieces
					set_v(j,i,reversi_game_piece(j,i,white,O));
				}
			}
		}
		// 2. initialize the turn_times;
		ifs >> first_person_turn_times;
		ifs >> second_person_turn_times;
		// 3.specify the turn
		ifs >> whose_turn;
		// set the last_state to 1 in order to change the print in main()
		last_state = 1;
	}
	// do not read from file, initialize the board by default
	else
	{
		initialize_game_from_start();
	}
	ifs.close();
}

void ReversiGame::initialize_game_from_start()
{
// clear the board
	for(unsigned int i = get_vertical_dimension()-1; i+1 != 0; --i )
	{
		for(unsigned int j = 0; j < get_horizontal_dimension(); ++j)
		{
			set_v(j,i,empty_rgp);
		}
	}
		// initiallize the pieces on the board
		set_v(3,3,reversi_game_piece(3,3,black,X));
		set_v(4,4,reversi_game_piece(4,4,black,X));
		set_v(3,4,reversi_game_piece(3,4,white,O));
		set_v(4,3,reversi_game_piece(4,3,white,O));
		// specify the turn
		whose_turn = argv_globle[2];
}

// check whether the game is done
bool ReversiGame::done()
{
	//1. if all the square are filled
	if(count_black_pieces() + count_white_pieces() == 
	   horizontal_dimension * vertical_dimension)
	{
		return true;
	}
	// 2, if all the pieces on the board is the same color
	else if(count_black_pieces() == 0 || count_white_pieces() == 0)
	{
		return true;
	}
	else if( check_available_square_black() == false &&
		     check_available_square_white() == false)
	{
		return true;
	}
	// if not finished
	return false;
}

// prompt the user to input the value
int ReversiGame::prompt(unsigned int &a, unsigned int &b)
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
			cout << "Do you want to save the game? Enter \"yes\" to save the "
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
			// Check how many comma there are and replace comma with white space
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
					     << vertical_dimension-1<< endl;
				}
			}
		}
	}
	return bad_command_line;
}

// check and make a valid move in the game
void ReversiGame::turn()
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	unsigned int first_person_x = 0;// the position of the first_person selected piece
	unsigned int first_person_y = 0;// the position of the first_person selected piece
	unsigned int second_person_x = 0;// the position of the second_person selected piece
	unsigned int second_person_y = 0;// the position of the second_person selected piece
	int input_valid = 1; // 0 means valid, 1 means invalid
	// if it is the first person's (X) turn
	if(whose_turn == argv_globle[2])
	{
		// check if there is valid square for the first person
		if(check_available_square_black() == true)
		{
			cout << first_person << "'s turn, the symbol is " << X 
			     << ". Please put your game piece by specifying its "
			        "coordinate position or quit. " << endl;
			// prompt the user to input the value
			input_valid = prompt(first_person_x,first_person_y);
			// check whether the current posisiton is empty and 
			// check whether the input is valid
			while((input_valid != success) || 
				  (v[d*first_person_y+first_person_x] != empty_rgp) || 
				   valid_put_position_black(first_person_x,first_person_y) != true )
			{
				// check whether the input is valid
				if(input_valid != success)
				{
					cout << "Bad command line, please put your game piece by "
					        "specifying its coordinate position, for "
					        "example: \"0,0\" or input \"quit\" to quit "
					        "the game." << endl;
					input_valid = prompt(first_person_x,first_person_y);
				}
				// check whether the input is empty
				else if(v[d*first_person_y+first_person_x] != empty_rgp)
				{
					cout << "The current position is NOT EMPTY, please re_put your "
					        "game piece by specifying its coordinate position." << endl;
					input_valid = prompt(first_person_x,first_person_y);
				}
				// check if this is a valid put
				else
				{
					cout << "The position is NOT a valid put position, please re_put"
					       " your game piece by specifying its coordinate position." << endl;
					input_valid = prompt(first_person_x,first_person_y);
				}
			}
			// the player play his own turn
			complete_black_turn(first_person_x,first_person_y);
			// increament the each person's turn times
			++first_person_turn_times;
			print();
			// change the turn
			whose_turn =  argv_globle[3];
		}
		// skip this turn for the first player
		else
		{
			// change the turn
			whose_turn =  argv_globle[3];
			cout << first_person << "'s turn SKIPPED, because there is no "
			        "valid square to put." << endl<< endl;
		}
	}
	// if it is the second person's (O) turn
	if(whose_turn == argv_globle[3])
	{
		// check if there is valid square for the second person
		if(check_available_square_white() == true)
		{
			cout << second_person << "'s turn, the symbol is " << O 
			     <<". Please put your game piece by specifying its "
			       "coordinate position or quit. " << endl;
			// prompt the user to input the value
			input_valid = prompt(second_person_x,second_person_y);
			// check whether the current posisiton is empty and check whether the input is valid
			while((input_valid != success) || 
				 (v[d*second_person_y+second_person_x] != empty_rgp) || 
				 valid_put_position_white(second_person_x,second_person_y) != true)
			{
				// check whether the input is valid
				if(input_valid != success)
				{
					cout << "Bad command line, please put your game piece by specifying"
					        " its coordinate position, for "
					        "example: \"0,0\" or input \"quit\" to quit the game." << endl;
					input_valid = prompt(second_person_x,second_person_y);
				}
				// check whether the input is empty
				else if(v[d*second_person_y+second_person_x] != empty_rgp)
				{
					cout << "The current position is NOT EMPTY, please re_put your "
					        " game piece by specifying its coordinate position." << endl;
					input_valid = prompt(second_person_x,second_person_y);
				}
				else
				{
					cout << "The position is NOT a valid put position, please re_put "
					        "your game piece by specifying its coordinate position." << endl;
					input_valid = prompt(second_person_x,second_person_y);
				}
			}
			// the player play his own turn
			complete_white_turn(second_person_x,second_person_y);
			// increament the each person's turn times
			++second_person_turn_times;
			print();
			// change the turn
			whose_turn =  argv_globle[2];
		}
		// skip this turn for the second player
		else
		{
			// change the turn
			whose_turn =  argv_globle[2];
			cout << second_person << "'s turn SKIPPED, because there is"
			  						  "no valid square to put." << endl<< endl;
		}
	}
}

// play the game by calling turn()
int ReversiGame::play()
{
	while(done()!= true)
	{
		// call the function turn()
		turn();
	}
	// check who is the winner
	// if first person is the winner
	if(count_black_pieces() > count_white_pieces())
	{
		cout << first_person << " is the WINNER! Congratulation! " <<
			first_person <<" took "<< first_person_turn_times
			<< " turns to finish the game." << endl;
	}
	// if second person is the winner
	else if(count_black_pieces() < count_white_pieces())
	{
		cout << second_person << " is the WINNER! Congratulation! " <<
			second_person <<" took "<< second_person_turn_times
			<< " turns to finish the game." << endl;
	}
	// if it is a tie
	else
	{
		cout <<"This is a TIE." << endl;
	}
	// the next time the game should start from the beginning
	abort_current_state();
	return success;
}

// save the current state
void ReversiGame::save_current_state()
{
	// make the file name
	string game_name = argv_globle[1];
	string first_person = argv_globle[2];
	string second_perosn = argv_globle[3];
	string file_name = game_name +"_"+ first_person +
	                   "_"+ second_person + ".txt";
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
				if (v[horizontal_dimension*i+j] != empty_rgp)
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
	ofs<< whose_turn;
	// close the file
	ofs.close();
	}
}

// abort the current state
void ReversiGame::abort_current_state()
{
	// make the file name
	string information = "NO DATA";
	string game_name = argv_globle[1];
	string first_person = argv_globle[2];
	string second_perosn = argv_globle[3];
	string file_name = game_name +"_"+ first_person +"_"+ 
	                   second_person + ".txt";
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
bool ReversiGame::valid_put_position_black(unsigned int i, unsigned int j)
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	int x = 0; // hold the value of i
	int y = 0; // hold the value of j
	// when you put your piece on the borad,for example in the middle, 
	// there should be eight position to be checked

	// case 1 , direction 11 o'clock
	if(i>=1 && j<= 6)
	{
		x = i-1;
		y = j+1;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			--x;
			++y;
			while(x>=0 && y<=7)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
				++y;
			}
		}
	}

	// case 2 , direction 12 o'clock
	if(j<= 6)
	{
		x = i;
		y = j+1;
		// if the piece is  white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			++y;
			while(y<=7)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++y;
			}
		}
	}

	// case 3 , direction 1  o'clock
	if(i<=6 && j<= 6)
	{
		x = i+1;
		y = j+1;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			++x;
			++y;
			while(x<=7 && y<=7)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
				++y;
			}
		}
	}

	// case 4 , direction 3  o'clock
	if(i<=6)
	{
		x = i+1;
		y = j;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			++x;
			while(x<=7)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
			}
		}
	}

	// case 5 , direction 5  o'clock
	if(i<=6 && j>=1)
	{
		x = i+1;
		y = j-1;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			++x;
			--y;
			while(x<=7 && y>=0)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
				--y;
			}
		}
	}

	// case 6 , direction 6  o'clock
	if(j>=1)
	{
		x = i;
		y = j-1;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			--y;
			while(y>=0)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--y;
			}
		}
	}

	// case 7 , direction 7  o'clock
	if(i>=1 && j>= 1)
	{
		x = i-1;
		y = j-1;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			--x;
			--y;
			while(x>=0 && y>=0)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
				--y;
			}
		}
	}

	// case 8 , direction 9  o'clock
	if(i>=1)
	{
		x = i-1;
		y = j;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			--x;
			while(x>=0)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
			}
		}
	}
	// after all the checking, if there is no true case, return false
	return false;
}

// checks if this puting position is valid
bool ReversiGame::valid_put_position_white(unsigned int i, unsigned int j)
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	int x = 0; // hold the value of i
	int y = 0; // hold the value of j
	// when you put your piece on the borad,for example in the middle, 
	// there should be eight position to be checked

	// case 1 , direction 11 o'clock
	if(i>=1 && j<= 6)
	{
		x = i-1;
		y = j+1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			--x;
			++y;
			while(x>=0 && y<=7)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
				++y;
			}
		}
	}

	// case 2 , direction 12 o'clock
	if(j<= 6)
	{
		x = i;
		y = j+1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			++y;
			while(y<=7)
			{
				// whtie piece found
				if(v[d*y+x].symbol == O)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++y;
			}
		}
	}

	// case 3 , direction 1  o'clock
	if(i<=6 && j<= 6)
	{
		x = i+1;
		y = j+1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			++x;
			++y;
			while(x<=7 && y<=7)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
				++y;
			}
		}
	}

	// case 4 , direction 3  o'clock
	if(i<=6)
	{
		x = i+1;
		y = j;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			++x;
			while(x<=7)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
			}
		}
	}

	// case 5 , direction 5  o'clock
	if(i<=6 && j>=1)
	{
		x = i+1;
		y = j-1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			++x;
			--y;
			while(x<=7 && y>=0)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
				--y;
			}
		}
	}

	// case 6 , direction 6  o'clock
	if(j>=1)
	{
		x = i;
		y = j-1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			--y;
			while(y>=0)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--y;
			}
		}
	}

	// case 7 , direction 7  o'clock
	if(i>=1 && j>= 1)
	{
		x = i-1;
		y = j-1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			--x;
			--y;
			while(x>=0 && y>=0)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
				--y;
			}
		}
	}

	// case 8 , direction 9  o'clock
	if(i>=1)
	{
		x = i-1;
		y = j;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			--x;
			while(x>=0)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					return true;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
			}
		}
	}
	// after all the checking, if there is no true case, return false
	return false;
}

// complete the play's turn and change the board according to the rules
void ReversiGame::complete_black_turn(unsigned int i, unsigned int j)
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	int x = 0; // hold the value of i
	int y = 0; // hold the value of j
	int n = 0; // record the number of O between the X
	// put the piece on the borad
	v[d*j+i] = reversi_game_piece(i,j,black,X);
	// when you put your piece on the borad,for example in the middle, 
	// there should be eight position to be checked

	// case 1 , direction 11 o'clock
	if(i>=1 && j<= 6)
	{
		x = i-1;
		y = j+1;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			--x;
			++y;
			while(x>=0 && y<=7)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					// calculate the number of white pieces
					n = y-j-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y-1)+(x+1)] = reversi_game_piece(x+1,y-1,black,X);
						--y;
						++x;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
				++y;
			}
		}
	}

	// case 2 , direction 12 o'clock
	if(j<= 6)
	{
		x = i;
		y = j+1;
		// if the piece is  white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			++y;
			while(y<=7)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					// calculate the number of white pieces
					n = y-j-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y-1)+x] = reversi_game_piece(x,y-1,black,X);
						--y;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++y;
			}
		}
	}

	// case 3 , direction 1  o'clock
	if(i<=6 && j<= 6)
	{
		x = i+1;
		y = j+1;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			++x;
			++y;
			while(x<=7 && y<=7)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					// calculate the number of white pieces
					n = y-j-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y-1)+(x-1)] = reversi_game_piece(x-1,y-1,black,X);
						--y;
						--x;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
				++y;
			}
		}
	}

	// case 4 , direction 3  o'clock
	if(i<=6)
	{
		x = i+1;
		y = j;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			++x;
			while(x<=7)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					// calculate the number of white pieces
					n = x-i-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*y+(x-1)] = reversi_game_piece(x-1,y,black,X);
						--x;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
			}
		}
	}

	// case 5 , direction 5  o'clock
	if(i<=6 && j>=1)
	{
		x = i+1;
		y = j-1;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			++x;
			--y;
			while(x<=7 && y>=0)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					// calculate the number of white pieces
					n = x-i-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y+1)+(x-1)] = reversi_game_piece(x-1,y+1,black,X);
						--x;
						++y;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
				--y;
			}
		}
	}

	// case 6 , direction 6  o'clock
	if(j>=1)
	{
		x = i;
		y = j-1;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			--y;
			while(y>=0)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					// calculate the number of white pieces
					n = j-y-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y+1)+x] = reversi_game_piece(x,y+1,black,X);
						++y;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--y;
			}
		}
	}

	// case 7 , direction 7  o'clock
	if(i>=1 && j>= 1)
	{
		x = i-1;
		y = j-1;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			--x;
			--y;
			while(x>=0 && y>=0)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					// calculate the number of white pieces
					n = j-y-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y+1)+(x+1)] = reversi_game_piece(x+1,y+1,black,X);
						++x;
						++y;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
				--y;
			}
		}
	}

	// case 8 , direction 9  o'clock
	if(i>=1)
	{
		x = i-1;
		y = j;
		// if the piece is white piece
		if(v[d*y+x].symbol == O)
		{
			//continue searching
			--x;
			while(x>=0)
			{
				// black piece found
				if(v[d*y+x].symbol == X)
				{
					// calculate the number of white pieces
					n = i-x-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*y+(x+1)] = reversi_game_piece(x+1,y,black,X);
						++x;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
			}
		}
	}
}

// complete the play's turn and change the board according to the rules
void ReversiGame::complete_white_turn(unsigned int i, unsigned int j)
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	int x = 0; // hold the value of i
	int y = 0; // hold the value of j
	int n = 0; // record the number of O between the X
	// put the piece on the borad
	v[d*j+i] = reversi_game_piece(i,j,white,O);

	// when you put your piece on the borad,for example in the middle, 
	// there should be eight position to be checked

	// case 1 , direction 11 o'clock
	if(i>=1 && j<= 6)
	{
		x = i-1;
		y = j+1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			--x;
			++y;
			while(x>=0 && y<=7)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					// calculate the number of white pieces
					n = y-j-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y-1)+(x+1)] = reversi_game_piece(x+1,y-1,white,O);
						--y;
						++x;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
				++y;
			}
		}
	}

	// case 2 , direction 12 o'clock
	if(j<= 6)
	{
		x = i;
		y = j+1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			++y;
			while(y<=7)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					// calculate the number of white pieces
					n = y-j-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y-1)+x] = reversi_game_piece(x,y-1,white,O);
						--y;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++y;
			}
		}
	}

	// case 3 , direction 1  o'clock
	if(i<=6 && j<= 6)
	{
		x = i+1;
		y = j+1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			++x;
			++y;
			while(x<=7 && y<=7)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					// calculate the number of white pieces
					n = y-j-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y-1)+(x-1)] = reversi_game_piece(x-1,y-1,white,O);
						--y;
						--x;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
				++y;
			}
		}
	}

	// case 4 , direction 3  o'clock
	if(i<=6)
	{
		x = i+1;
		y = j;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			++x;
			while(x<=7)
			{
				// whtie piece found
				if(v[d*y+x].symbol == O)
				{
					// calculate the number of white pieces
					n = x-i-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*y+(x-1)] = reversi_game_piece(x-1,y,white,O);
						--x;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
			}
		}
	}

	// case 5 , direction 5  o'clock
	if(i<=6 && j>=1)
	{
		x = i+1;
		y = j-1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			++x;
			--y;
			while(x<=7 && y>=0)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					// calculate the number of white pieces
					n = x-i-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y+1)+(x-1)] = reversi_game_piece(x-1,y+1,white,O);
						--x;
						++y;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				++x;
				--y;
			}
		}
	}

	// case 6 , direction 6  o'clock
	if(j>=1)
	{
		x = i;
		y = j-1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			--y;
			while(y>=0)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					// calculate the number of white pieces
					n = j-y-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y+1)+x] = reversi_game_piece(x,y+1,white,O);
						++y;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--y;
			}
		}
	}

	// case 7 , direction 7  o'clock
	if(i>=1 && j>= 1)
	{
		x = i-1;
		y = j-1;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			--x;
			--y;
			while(x>=0 && y>=0)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					// calculate the number of white pieces
					n = j-y-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*(y+1)+(x+1)] = reversi_game_piece(x+1,y+1,white,O);
						++x;
						++y;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
				--y;
			}
		}
	}

	// case 8 , direction 9  o'clock
	if(i>=1)
	{
		x = i-1;
		y = j;
		// if the piece is black piece
		if(v[d*y+x].symbol == X)
		{
			//continue searching
			--x;
			while(x>=0)
			{
				// white piece found
				if(v[d*y+x].symbol == O)
				{
					// calculate the number of white pieces
					n = i-x-1;
					for(int k = 0; k < n; ++k)
					{
						// change the color of the pieces
						v[d*y+(x+1)] = reversi_game_piece(x+1,y,white,O);
						++x;
					}
					break;
				}
				// if empty piece is found
				else if (v[d*y+x] == empty_rgp)
				{
					break;
				}
				// if the piece is white continue searching
				--x;
			}
		}
	}
}

// count the number of plack pieces
unsigned int ReversiGame::count_black_pieces()
{
	unsigned total_number_of_black_pieces = 0;
	// store the value of the dimension
	unsigned int d = horizontal_dimension;
	for(unsigned int i = vertical_dimension-1; i+1 != 0; --i )
	{
		for(unsigned int j = 0; j < horizontal_dimension; ++j)
		{
			//check whether it is empty
			if (v[d*i+j] != empty_rgp)
			{
				// count the black pieces
				if(v[d*i+j].symbol == X)
				{
					++total_number_of_black_pieces;
				}
			}
		}
	}
	return total_number_of_black_pieces;
}

// count the number of white piece
unsigned int ReversiGame::count_white_pieces()
{
	unsigned total_number_of_white_pieces = 0;
	// store the value of the dimension
	unsigned int d = horizontal_dimension;
	for(unsigned int i = vertical_dimension-1; i+1 != 0; --i )
	{
		for(unsigned int j = 0; j < horizontal_dimension; ++j)
		{
			//check whether it is empty
			if (v[d*i+j] != empty_rgp)
			{
				//cout the white pieces
				if(v[d*i+j].symbol == O)
				{
					++total_number_of_white_pieces;
				}
			}
		}
	}
	return total_number_of_white_pieces;
}

// check if there is a put position for black piece
bool ReversiGame::check_available_square_black()
{
	// store the value of the dimension
	unsigned int d = horizontal_dimension;
	for(unsigned int i = vertical_dimension-1; i+1 != 0; --i )
	{
		for(unsigned int j = 0; j < horizontal_dimension; ++j)
		{
			//check whether it is empty
			if (v[d*i+j] == empty_rgp)
			{
				// check position
				if(valid_put_position_black(j,i) == true)
				{
					return true;
				}
			}
		}
	}
	return false;
}

// check if there is a put position for white piece
bool ReversiGame::check_available_square_white()
{
	// store the value of the dimension
	unsigned int d = horizontal_dimension;
	for(unsigned int i = vertical_dimension-1; i+1 != 0; --i )
	{
		for(unsigned int j = 0; j < horizontal_dimension; ++j)
		{
			//check whether it is empty
			if (v[d*i+j] == empty_rgp)
			{
				// check position
				if(valid_put_position_white(j,i) == true)
				{
					return true;
				}
			}
		}
	}
	return false;
}
