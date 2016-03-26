// NineAlmondsGame.cpp
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#include "OtherFunctions.h"
#include "GameBase.h"
#include "NineAlmondsGame.h"

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
// store the continues move in file
vector <game_piece> trace_store_file;
// store the value of turn time
int turn_times = 0;
// tracing flag , indicate whether to initialize the tracing vector
int tracing_flag = 0;
// store the value reading from file
vector <game_piece> trace_read_from_file;
// flag out whehter to return the last state
extern int last_state; // 0 means not to return

//constructor of NineAlmondsGame
NineAlmondsGame::NineAlmondsGame(unsigned int h,unsigned int v,
	                          	 piece_color color,string name,
	                          	 string symbol)
	:GameBase( h, v, color, name, symbol) {}

// Define the initial state of the piece on the board for initialize_game() 
// function. x_empty,y_empty is defined in other_functions.h
game_piece empty(x_empty,y_empty);


//Initialize the board
void NineAlmondsGame::initialize_game()
{
	string first_line; // store the first line
	string board_line; // store the one line in the file
	string current_piece; // store the current piece
	string turn_s; // store the value of turn_times
	string x_s,y_s; //store the value of coordinate
	unsigned int x_,y_; //store the value of coordinate
	string check_trace_1; // store the flag of the trace
	string check_trace_2; // store the flag of the trace
	//=1 if it is needed to initialize game from start because 
	// the file is edited without permission.Otherwise =0.
	int flag_initialize_game_from_start=0;
	string game_name = argv_globle[1];
	string file_name = game_name + ".txt";
	// first try to read from file
	ifstream ifs (file_name.c_str());
	if (ifs.is_open ())
	{
		ifs>>first_line;
	}
	//1.initialize the piece on the NineAlmondsGame
	for(unsigned int i = get_vertical_dimension()-1; i +1 != 0; --i )
	{
		for(unsigned int j = 0; j < get_horizontal_dimension(); ++j)
		{
			push_v(empty);
		}
	}
	// initialize the board with saved value from the file
	if(first_line == game_name)
	{

		// iterate through the board
		for(unsigned int i = get_vertical_dimension()-1; i+1!= 0; --i )
		{
			// read the board information
			// iterate through each piece on the line
			for(unsigned int j = 0; j < get_horizontal_dimension(); ++j)
			{
				// extract the value from each pieces
				ifs >> current_piece;
				// check if the state is valid (check if the symbol 
				// has been edited without permission)
				if(current_piece != "A" && current_piece != "E"  )
				{
					cout<<"The saved file has been edited without permission." << endl;
					cout<<"So, a new game will be initialized." << endl;
					initialize_game_from_start();
					flag_initialize_game_from_start=1;
					break;
				}
				// check if there is a piece there
				if(current_piece == "A" && flag_initialize_game_from_start==0)
				{
					// set the current location with pieces
					set_v(j,i,game_piece(j,i));
				}
			}
		}

		//2. initialize the turn_times;
		if (flag_initialize_game_from_start==0)
		{
			ifs>> turn_times;
			//3. initialize the trace vector
			ifs>>check_trace_1;
			ifs>>check_trace_2;
			string check_trace = check_trace_1+check_trace_2;
			// set the flag
			if(check_trace!= "NO TRACE")
			//if(strcmp (check_trace_1,"NO") != 0 && 
			//strcmp (check_trace_2,"TRACE") != 0)
			{
				// set the flag to 1, in order to read in the turn()
				tracing_flag = 1;
				while(ifs.good())
				{
					ifs >> x_s ;// store the value of coordinate
					ifs	>> y_s;
					if( x_s == "END" && y_s== "TRACE")
					{
						break;
					}

					// store the game_piece to the file
					istringstream(x_s)>>x_;
					istringstream(y_s)>>y_;
					trace_read_from_file.push_back(game_piece(x_,y_));
				}
			}
			// set the last_state to 1 in order to change the print in main()
			last_state = 1;
		}

	}
	// do not read from file, initialize the board by default
	else
	{
		initialize_game_from_start();
	}
	// close the file stream
	ifs.close();
}

void NineAlmondsGame::initialize_game_from_start()
{
	// clear the board
	for(unsigned int i = get_vertical_dimension()-1; i+1!= 0; --i )
	{
		for(unsigned int j = 0; j < get_horizontal_dimension(); ++j)
		{
			set_v(j,i,empty);
		}
	}
	// initiallize the pieces on the board
	set_v(1,1,game_piece(1,1));
	set_v(2,1,game_piece(2,1));
	set_v(3,1,game_piece(3,1));
	set_v(1,2,game_piece(1,2));
	set_v(2,2,game_piece(2,2));
	set_v(3,2,game_piece(3,2));
	set_v(1,3,game_piece(1,3));
	set_v(2,3,game_piece(2,3));
	set_v(3,3,game_piece(3,3));
}

//set function
void NineAlmondsGame::push_v (game_piece gp)
{
	v.push_back(gp);
}

//set function
void NineAlmondsGame::set_v (unsigned int x,unsigned int y ,game_piece gp)
{
	v[horizontal_dimension*y+x] = gp;
}

// check whether the game is done
bool NineAlmondsGame::done()
{
	int count_empty = 0;
	int status = 0; // The status flag, 0 means not true
	int size = horizontal_dimension * vertical_dimension;
	for (int i = 0; i< size ; ++i)
    {
		// check if there is a piece on the board not in the middle
		if(i != 12 && v[i] == empty)
        {
			++count_empty;
        }
		// check if there is a piece on the board in the middle
		if(i == 12 && v[i] != empty)
        {
			status = 1;
        }
    }
	if(status == 1 && count_empty == 24)
    {
		return true;
    }
	else
    {
		return false;
    }
}

// check and make a valid move in the game
void NineAlmondsGame::turn()
{
	unsigned int d = horizontal_dimension;// the dimenstion of the board
	unsigned int current_position_x = 0;// the position of the current selected almond
	unsigned int current_position_y = 0;// the position of the current selected almond
	unsigned int move_to_x = 0;// the position where the user wants to move
	unsigned int move_to_y = 0;// the position where the user wants to move
	int input_valid = 1; // 0 means valid, 1 means invalid
	int distance_square = 0; // calculate distance between two points
	int middle_point_x = 0; // calculate middle point two points
	int middle_point_y = 0; // calculate middle point two points
	int module_x = 0; // check the module value
	int module_y = 0; // check the module value
	int move_times = 0; // record the time of move
	vector <game_piece> trace;
	string quit = "quit";
	string whether_to_conitue = "continue"; 
	// the flag used to indicate whether to continue, 0 means false, 1 means true
	// print the trace_read_from_file vector which is used to store the value 
	// and restore the trace vector
	if(tracing_flag == 1)
	{
		// set the move_times to 0
		move_times = 1;
		//print out of the record of the moving
		for(vector<struct game_piece>::iterator iter = trace_read_from_file.begin();
		    iter != trace_read_from_file.end(); ++iter)
		{
			if(iter != trace_read_from_file.end()-1)
			{
				//print the move
				cout << iter->x <<","<<iter->y<<" to ";
			}
			else
			{
				//print the move
				cout << iter->x <<","<<iter->y<< endl;
				// assign the value to the positions
				current_position_x = iter->x;
				current_position_y = iter->y;
			}
		}
		//store the value and restore the trace vector
		trace = trace_read_from_file;
		// assign value of trace to the trace_store_file
		trace_store_file = trace;
		// if the tracing_flag is 0, means the turn does not need to continue
	}
	else
	{
		cout <<"Please select an almond by specifying its "
		       "coordinate position or quit. " << endl;
		// prompt the user to input the value
		input_valid = prompt(current_position_x,current_position_y);
		// check whether the current posisiton is empty and check whether the input is valid
		while((input_valid != success) || 
			  (v[d*current_position_y+current_position_x] == empty) )
		{
			// check whether the input is valid
			if(input_valid != success)
			{
				cout<<"Bad command line, please select a almond by specifying "
				      "its coordinate position, for example: \"0,0\" or "
				      "input \"quit\" to quit the game." << endl;
				input_valid = prompt(current_position_x,current_position_y);
			}
			else // check whether the input is empty
			{
				cout<<"The current position is EMPTY, please re-select a "
				      "almond by specifying its coordinate position." << endl;
				input_valid = prompt(current_position_x,current_position_y);
			}
		}
	}
	// check whether_to_continue
	while (whether_to_conitue != "end")
	{
		if(tracing_flag == 0)
		{
			// prompt the user to input the destination
			cout << "Please select a destination by specifying "
			        "its coordinate position." << endl;
			input_valid = prompt(move_to_x,move_to_y);
			//check whether the input is quit_turn
			if (input_valid == quit_turn)
			{
				break;
			}
			// check whether the current posisiton is empty and 
			// check whether the input is valid
			while((input_valid != success) || (v[d*move_to_y+move_to_x] != empty) )
			{
				// check whether the input is valid
				if(input_valid != success)
				{
					cout<<"Bad command line, please select a destination by specifying "
					      "its coordinate position, for example: \"0,0\" or input \"quit\" to "
					      "quit the game or \"quit_turn\" to quit the turn\"." << endl;
					input_valid = prompt(move_to_x,move_to_y);
					//check whether the input is quit_turn
					if (input_valid == quit_turn)
					{
						break;
					}
				}
				else // check whether the input is not empty
				{
					cout << "The destination position is NOT empty, "
					       "please re-select a destination "
					       "by specifying its coordinate position." << endl;
					input_valid = prompt(move_to_x,move_to_y);
					//check whether the input is quit_turn
					if (input_valid == quit_turn)
					{
						break;
					}
				}
			}
				//check whether the input is quit_turn
			if (input_valid == quit_turn)
			{
				break;
			}
			// calculate the distance square
			distance_square = (current_position_x - move_to_x) * 
							  (current_position_x - move_to_x) +
			                  (current_position_y - move_to_y) * 
			                  (current_position_y - move_to_y);
			//calculate the module
			module_x = (current_position_x + move_to_x) % 2;
			module_y = (current_position_y + move_to_y) % 2;
			//calculate the middle point
			middle_point_x = (current_position_x + move_to_x) / 2;
			middle_point_y = (current_position_y + move_to_y) / 2;
			// check whether this is a valid move
			if((distance_square <= 8) &&
				(module_x == 0) &&
				(module_y == 0) &&
				(v[d*middle_point_y+middle_point_x] != empty))
			{
				// delete the almond been jumped
				v[d*middle_point_y+middle_point_x] = empty;
				// delete the almond where it jumped from
				v[d*current_position_y+current_position_x] = empty;
				// move a almond to the new destination
				v[d*move_to_y+move_to_x] = game_piece(move_to_x,move_to_y);
				// record the input value
				if (move_times == 0)
				{
					trace.push_back(game_piece(current_position_x,
						                       current_position_y));
				}
				trace.push_back(game_piece(move_to_x,move_to_y));
				// assign value of trace to the trace_store_file
				if(tracing_flag == 0)
				{
					trace_store_file = trace;
				}
				// set the position to the current almond
				current_position_x = move_to_x;
				current_position_y = move_to_y;
				// set the flag of move times
				move_times = 1;
			}
			else
			{
				cout <<"This is not valid move." << endl;
			}
			// print out the gameboard and each piece on the
			//  board by calling print() function
			print();
			//print out of the record of the moving
			for(vector<struct game_piece>::iterator iter = trace.begin(); 
				iter != trace.end(); ++iter)
			{
				if(iter != trace.end()-1)
				{
					//print the move
					cout << iter->x <<","<<iter->y<<" to ";
				}
				else
				{
					//print the move
					cout << iter->x <<","<<iter->y<< endl;
				}
			}
		}
		// check if the game can not continue or it has finished
		if(done()!= true && no_valid_move(v) == false)
		{
			cout << endl << "Enter \"continue\" to continue to make "
			                "additional valid jumps "
			                "with the same almond during this turn and "
			                "enter \"end\" to quit this turn"<<
						     " or \"quit\" to quit the game." << endl;
			// get the value of whether_to_conitue
			getline(cin,whether_to_conitue);
			// check the value of whether_to_conitue is valid
			while((whether_to_conitue != "continue") && 
				  (whether_to_conitue !="end") && 
				  (whether_to_conitue !="quit"))
			{
				cout << "Input is invalid, enter \"continue\" to continue to make "
						"additional valid jumps with the same almond during "
						"this turn and enter \"end\""
					    " to quit this turn or \"quit\" to quit the game." << endl;
				getline(cin,whether_to_conitue);
			}
			// print the last jumped almomd, because we can only continue to move 
			// the last moved almond
			if(whether_to_conitue == "continue")
			{
				cout << "The current position of last jumped almond is (" 
					 << current_position_x<<","
					 << current_position_y<<")." << endl;
			}
			else if(whether_to_conitue == "quit")
			{
				// check whehter need to save the game
				cout << "Do you want to save the game? Enter \"yes\" to "
				        "save the game and quit, "
				        "enter \"no\" to quit with saving." << endl;
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
						cout <<"Input not correct, please input the command again."
						       "Enter \"yes\" to save the game and quit, enter \"no\" to "
						       "quit with saving. " << endl;
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
		}
		else
		{
			break;
		}
		// set the flag to 0
		tracing_flag = 0;
	}
	// if it is end of the turn, clear trace_store_file
	trace_store_file.clear();
}

// Overloading the operator << for NineAlmonds Game
ostream &operator<< (ostream &out,  const NineAlmondsGame &n)
{
	//define the empty piece
	int piece_existing = 0;
	// store the value of the dimension
	unsigned int d = n.horizontal_dimension;
	for(unsigned int i = n.vertical_dimension-1; i+1!= 0; --i )
	{
		// Draw the Y coordinate
		out<< i<<" ";
		// Print the board
		for(unsigned int j = 0; j < n.horizontal_dimension; ++j)
		{
			//check whether it is empty
			if (n.v[d*i+j] != empty)
			{
				// print out the symbol
				out << setiosflags(ios_base::left)
				    << setw(n.longest_string_length+1) << n.symbol;
				piece_existing = 1;
			}
		// If there is no piece there, print out the space
		if(piece_existing == 0)
		{
			cout << setiosflags(ios_base::left)
			     << setw(n.longest_string_length+1) << " ";
		}
		piece_existing = 0;
			//change the line
			if(j == n.horizontal_dimension-1)
			{
				out<< endl;
			}
		}
	}
	// Draw the X coordinate
	out<<"X"<<" ";
	for(unsigned int j = 0; j < n.horizontal_dimension; ++j)
	{
		// Draw the X coordinate with the space between them
		out<< setiosflags(ios_base::left)
		   << setw(n.longest_string_length+1) << j;
	}
	return out;
}

// print method
void NineAlmondsGame::print()
{
	cout << endl <<*this<< endl<< endl;
}

// play the game by calling turn()
int NineAlmondsGame::play()
{
	int no_move = 0;
	while(done()!= true)
	{
		// check if there is valid move
		if(no_valid_move(v))
		{
			no_move = 1;
			break;
		}
		// call the function turn()
		turn();

		// increment the turn_times
		++turn_times;
	}
	if(no_move == 0)
	{
		cout << "Congratulations! You finish the game. It takes "
			 << turn_times <<" turns to complete the game." << endl;
		// overwrite the game's file to let the game start from the 
		// beginning next time.
		abort_current_state();
		return success;
	}
	else
	{
		cout<<"Sorry, the game is failed, because "
		      "there are no more valid moves." << endl;
		// overwrite the game's file to let the game start from the 
		// beginning next time.
		abort_current_state();
		return no_more_valid_move;
	}
}

// check if there will be valid move of the pieces
bool NineAlmondsGame::no_valid_move(vector<game_piece> board_state)
{
	unsigned int d = horizontal_dimension;
	// iterate the board to find pieces
	for(unsigned int i = vertical_dimension-1; i+1!= 0; --i )
	{
		for(unsigned int j = 0; j < horizontal_dimension; ++j)
		{
			//check whether it is empty
			if (board_state[d*i+j] != empty)
			{
				// a move may have 8 directions
				//case #1
				if(	i<=2 && j>=2)
				{
					if(board_state[d*(i+2)+(j-2)] == empty &&
					   board_state[d*(i+1)+(j-1)] != empty
						)
					{
						return false;
					}
				}

				// a move may have 8 directions
				//case #2
				if(i<=2)
				{
					if(board_state[d*(i+2)+j] == empty &&
					   board_state[d*(i+1)+j] != empty
					  )
					{
						return false;
					}
				}

				// a move may have 8 directions
				//case #3
				if((i<=2) && (j<=2))
				{
					if(board_state[d*(i+2)+(j+2)] == empty &&
					   board_state[d*(i+1)+(j+1)] != empty
					  )
					{
						return false;
					}
				}

				// a move may have 8 directions
				//case #4
				if(j>=2)
				{
					if(board_state[d*i+(j-2)] == empty &&
					   board_state[d*i+(j-1)] != empty
					  )
					{
						return false;
					}
				}

				// a move may have 8 directions
				//case #d
				if(j<=2)
				{
					if(board_state[d*i+(j+2)] == empty &&
					   board_state[d*i+(j+1)] != empty
					  )
					{
						return false;
					}
				}

				// a move may have 8 directions
				//case #6
				if(j>=2 && i>=2 )
				{
					if(board_state[d*(i-2)+(j-2)] == empty &&
					   board_state[d*(i-1)+(j-1)] != empty
					  )
					{
						return false;
					}
				}

				// a move may have 8 directions
				//case #7
				if(i>=2)
				{
					if(board_state[d*(i-2)+j] == empty &&
					   board_state[d*(i-1)+j] != empty
					  )
					{
						return false;
					}
				}

				// a move may have 8 directions
				//case #8
				if(i>=2 && j<=2)
				{
					if(board_state[d*(i-2)+(j+2)] == empty &&
					   board_state[d*(i-1)+(j+2)] != empty
					  )
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

// prompt function
int NineAlmondsGame::prompt(unsigned int &a, unsigned int &b)
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
					cout <<"Input not correct, please input the command again."
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
		else if(command_line == "quit_turn")
		{
			return quit_turn;
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

// Save the board state
void NineAlmondsGame::save_current_state()
{
	// make the file name
	string game_name = argv_globle[1];
	string file_name = game_name + ".txt";
	// write to the files
	ofstream ofs (file_name.c_str());
	if (ofs.is_open ())
	{
		ofs << game_name << endl;
		// 1. store the board state
		// flag whether the piece exists
		int piece_existing = 0;
		for(unsigned int i = vertical_dimension-1; i+1 != 0; --i )
		{
			// Print the board
			for(unsigned int j = 0; j < horizontal_dimension; ++j)
			{
				//check whether it is empty
				if (v[horizontal_dimension*i+j] != empty)
				{
					// print out the symbol
					ofs << symbol <<" ";
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
		// 2. store the number of turns
		ofs<< turn_times << endl;
		// 3. store the continue move state
		// if the vector is empty
		if(trace_store_file.empty())
		{
			ofs << "NO TRACE";
		}
		// if the vector is not empty
		else
		{
			// set the flag
			ofs << "START TRACE" << endl;
			for(vector<struct game_piece>::iterator iter = trace_store_file.begin(); 
				iter != trace_store_file.end(); ++iter)
			{
				ofs << iter->x <<" "<<iter->y<< endl;
			}
			// set the flag
			ofs << "END TRACE" << endl;
		}
	}
	// close the file
	ofs.close();
}

// abort the current state
void NineAlmondsGame::abort_current_state()
{
	// make the file name
	string information = "NO DATA";
	string game_name = argv_globle[1];
	string file_name = game_name + ".txt";
	// write to the files
	ofstream ofs (file_name.c_str());
	if (ofs.is_open ())
	{
		ofs << information << endl;
	}
	// close the file
	ofs.close();
}
