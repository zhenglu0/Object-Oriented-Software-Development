// MagicSquareGame.cpp
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#include "OtherFunctions.h"
#include "GameBase.h"
#include "MagicSquareGame.h"

#include <math.h>
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

// push function
void MagicSquareGame::push_v (numbered_game_piece ngp)
{
	v.push_back(ngp);
}

//set function
void MagicSquareGame::set_v (unsigned int x,unsigned int y ,
							 numbered_game_piece ngp)
{
	v[horizontal_dimension*y+x] = ngp;
}

// Define the initial state of the piece on the board 
// for initialize_game() function. 
// x_empty,y_empty is defined in other_functions.h
numbered_game_piece empty_ngp(x_empty,y_empty,0);

//Initialize the board
void MagicSquareGame::initialize_game()
{
	string first_line; // store the first line
	string board_line; // store the one line in the file
	string current_piece; // store the current piece
	int current_piece_value;// store the current piece value
	//=1 if it is needed to initialize game from start because the 
	// file is edited without permission.Otherwise =0.
	string turn_s; // store the value of turn_times
	int flag_initialize_game_from_start=0;
	unsigned int avp_value; //store the value of avp_piece
	string check_avp; // store the flag of the trace
	string game_name = argv_globle[1];
	string file_name = game_name + ".txt";
	// first try to read from file
	ifstream infile (file_name.c_str());
	if (infile.is_open ())
	{
		infile >> first_line;
	}
	//1.initialize the piece on the MagicSquare set them all empty
	for(unsigned int i = get_vertical_dimension()-1; i+1 != 0; --i )
	{
		for(unsigned int j = 0; j <get_horizontal_dimension(); ++j)
		{
			push_v(empty_ngp);
		}
	}
	// initialize the board with saved value from the file
	if(first_line == game_name)
	{
		// iterate through the board
		for(unsigned int i = get_vertical_dimension()-1; i+1 != 0; --i )
		{
			// read the board information
			// iterate through each piece on the line
			for(unsigned int j = 0; j < get_horizontal_dimension(); ++j)
			{
				// extract the value from each pieces
				infile >> current_piece;
				// check if there is a piece there
				if(current_piece != "E")
				{
					//change a string to an integer
					istringstream ( current_piece ) >> current_piece_value ;
					if (current_piece_value > 
						int(horizontal_dimension*horizontal_dimension) || 
						current_piece_value <1 )
					{
						cout<<"The saved file has been edited without permission." << endl;
						cout<<"So, a new game will be initialized." << endl;
						initialize_game_from_start();
						flag_initialize_game_from_start=1;
						break;
					}

					// set the current location with pieces
					set_v(j,i,numbered_game_piece(j,i,current_piece_value));

				}
			}
		}
		//2. initialize the trace vector
		if (flag_initialize_game_from_start==0)
		{
			infile>>check_avp;
			// set the flag
			if(check_avp == "AVP_START")
			{
				while(infile.good())
				{
					string piece_value; // store the value of coordinate
					//getline(ifs,piece_value);
					infile>>piece_value;
					if(piece_value == "AVP_END")
					{
						break;
					}
					istringstream coordinate_ss(piece_value);
					coordinate_ss >> avp_value;
					// store the game_piece to the file
					push_avp(numbered_game_piece(x_empty,y_empty,avp_value));
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
	infile.close();
}

void MagicSquareGame::initialize_game_from_start()
{
	// initialize the avp
	for (int i=lowest_piece_val; 
		 i<=int(get_horizontal_dimension()*get_horizontal_dimension())
		    -(1-lowest_piece_val);++i)
	{
		push_avp(numbered_game_piece(x_empty,y_empty,i));
	}
}


// Overloading the operator << for MagicSquare Game
ostream &operator<< (ostream &out,  const MagicSquareGame &m)
{
	int piece_existing = 0;
	// store the value of the dimension
	unsigned int d = m.horizontal_dimension;
	for(unsigned int i = m.vertical_dimension-1; i +1 != 0; --i )
	{
		// Draw the Y coordinate
		out<< i <<" ";
		// Print the board
		for(unsigned int j = 0; j < m.horizontal_dimension; ++j)
		{
			//check whether it is empty
			if (m.v[d*i+j] != empty_ngp)
			{
				// print out the symbol
				out<< setiosflags(ios_base::left)
				   << setw(m.longest_string_length+1) << m.v[d*i+j].value;
				piece_existing = 1;
			}
			// If there is no piece there, print out the space
			if(piece_existing == 0)
			{
				cout << setiosflags(ios_base::left)
				     << setw(m.longest_string_length+1) << " ";
			}
			piece_existing = 0;
			//change the line
			if(j == m.horizontal_dimension-1)
			{
				out<< endl;
			}
		}
	}
	// Draw the X coordinate
	out<<"X"<<" ";
	for(unsigned int j = 0; j < m.horizontal_dimension; ++j)
	{
		// Draw the X coordinate with the space between them
		out<< setiosflags(ios_base::left)
		   << setw(m.longest_string_length+1) << j;
	}
	out << endl<< endl<< "Available pieces: ";
	// iterate through the available pieces
	vector <numbered_game_piece> ::const_iterator iter;
	for(iter = m.avp.begin(); iter != m.avp.end(); iter++ )
	{
		out << iter->value << " ";
	}
	return out;
}

// print method
void MagicSquareGame::print()
{
	cout << endl <<*this<< endl<< endl;
}

//set function
void MagicSquareGame::push_avp (numbered_game_piece ngp)
{
	avp.push_back(ngp);
}

// check whether the game is done
bool MagicSquareGame::done()
{
	//int count_empty = 0;
	//int status = 0; // The status flag, 0 means not true
	int size = horizontal_dimension * vertical_dimension;
	for (int i = 0; i< size ; ++i)
	{
		// check if there is an empty piece
		if(v[i] == empty_ngp)
		{
			return false;
		}
	}

	//Compute magicNumber. If the lowest_piece_value=1,magicNumber=n(n^2+1)/2, where n 
	// is the order of the magic number (from Wiki).
	//When the lowest_piece_value=i, the value of each piece is (1-i) smaller than 1. 
	// So the magicNumber should be n(n^2+1)/2-(1-i)*n=(n^3-n+2n*i)/2.
	int magicNumber=(int(powf(double(horizontal_dimension),3.0))-
					horizontal_dimension+2*horizontal_dimension*lowest_piece_val)/2;

	// Compute the sum of each row, column and diagnoal.
	int * s_row=new int[vertical_dimension](); //s_row[i] is the sum of the i-th row
	int * s_column=new int[horizontal_dimension](); //s_column[i] is the sum of the i-th column
	int s_diagonal_LtR=0; //sum of the piece on the diagonal from top left to bottom right
	int s_diagonal_RtL=0; //sum of the piece on the diagonal from top right to bottom left

	//Compute s_row[]
	for (unsigned int j=0;j<vertical_dimension;++j)
	{
		for (unsigned int i=0;i<horizontal_dimension;++i)
		{
			s_row[j]=s_row[j]+v[j*horizontal_dimension+i].value;
		}
	}

	//Compute s_column[]
	for (unsigned int i=0;i<horizontal_dimension;++i)
	{
		for (unsigned int j=0;j<vertical_dimension;++j)
		{
			s_column[i]=s_column[i]+v[i*vertical_dimension+j].value;
		}
	}

	//Compute s_diagonal_LtR
	for (unsigned int j=0;j<vertical_dimension;++j)
	{
		s_diagonal_LtR=s_diagonal_LtR+v[j*horizontal_dimension+j].value;
	}

	//Compute s_diagonal_RtL
	for (unsigned int j=0;j<vertical_dimension;++j)
	{
		s_diagonal_RtL=s_diagonal_RtL+
			v[j*horizontal_dimension+horizontal_dimension-j-1].value;
	}

	bool temp=1;
	//Check if sum of each row and column equals the magicNumber
	for (unsigned int i=0; i<horizontal_dimension;++i)
	{
		temp=temp && (s_row[i]==magicNumber)&&
			 (s_column[i]==magicNumber);
	}

	delete [] s_row;
	delete [] s_column;

	//Check if sum of the diagonal equals the magicNumber
	temp=temp && (s_diagonal_LtR==magicNumber) && 
			  (s_diagonal_RtL==magicNumber);

	//The sum of each row, column and diagnoal equals to magicNumber
	if (temp==1) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

// play the game by calling turn()
int MagicSquareGame::play()
{
	int whether_success = 0; // 0 means not success
	while(check_is_empty() == true)
	{
		// call the function turn()
		turn();
	}
	// if the game finished
	if(done() == true)
	{
		whether_success = 1;
	}
	// if the game finished
	if(whether_success == 1)
	{
		cout << "Congratulations! You finish the game. It takes "
		     << get_horizontal_dimension()*get_horizontal_dimension() 
		     <<" turns to complete the game." << endl;
		// overwrite the game's file to let the game start 
		// from the beginning next time.
		abort_current_state();
		return success;
	}
	else
	{
		cout << "Sorry, the game is failed, because the sum of every "
		        "line and diagonal is not equal." << endl;
		// overwrite the game's file to let the game start 
		// from the beginning next time.
		abort_current_state();
		return failure;
	}
}

// prompt the user to input the value
int MagicSquareGame::prompt(unsigned int &a, unsigned int &b, int &c)
{
	int count_string = 0;
	int count_comma = 0;
	int command_valid = 1;
	string quit = "quit";
	// define string virables
	string command_line;
	string command_original;
	string coordinate;
	string temp;
	unsigned int m; // temporarily storing the integer value of commandline
	unsigned int n; // temporarily storing the integer value of commandline
	int p; // temporarily storing the integer value of commandline
	// get the input from the input stream
	getline(cin,command_line);
	command_original = command_line;
	istringstream counts (command_original);
	// count the input string
	while(counts>>temp)
	{
		count_string ++;
	}
	// check whether the input command line is valid and if the input is quit
	if(count_string == 1 && command_line == quit)
	{
		// check whether need to save the game
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
		throw quit;
		return quit_game;
		}
	}
	// if the input is not quit
	else if(count_string == 2)
	{
		// convert command_line into istringstream
		istringstream cmd(command_line);
		cmd >> coordinate;
		// Check if there is comma in the begining or in the end
		if(coordinate[0] == ',' || coordinate[coordinate.length()-1] == ',')
		{
			command_valid = 0;
		}
		// Check how many comma there are and replace comma with white space
		for (unsigned int i = 0; i < coordinate.length(); ++i)
		{
			if (coordinate[i] == ',')
			{
				++count_comma;
				coordinate[i] = ' ';
			}
		}
		//define iss as istringstream
		istringstream iss (coordinate);
		// check the input format and if it is correct, 
		// assign the value to int &a, int &b, int &c
		if(count_comma == 1 &&
			command_valid ==1 &&
			iss >> m && iss >>n && cmd >> p)
		{
			//check the boundary
			if( m <= horizontal_dimension-1 &&
				n<= vertical_dimension -1 &&
				p<= int(horizontal_dimension * vertical_dimension)
			  )
			{
				//set value to those arguments.
				a = m;
				b = n;
				c = p;
				return success;
			}
			else
			{
				cout << "Error: The input coordinate is out of the "
				        "boundary or the input value is out of range." << endl;
				cout <<" The coordinate x should <= "<< horizontal_dimension-1 
				     << " and y should <= "<<vertical_dimension-1<<"!" << endl;
				cout <<" Also, the value of pieces should z <= "
				     << int(horizontal_dimension*horizontal_dimension -
				     	(1-lowest_piece_val))
				     << "." << endl;
			}
		}
	}
	return bad_command_line;
}

// check and make a valid move in the game
void MagicSquareGame::turn()
{
	unsigned int position_x = 0; // the position being selected
	unsigned int position_y = 0; // the position being selected
	int piece_value = 0; // the value of the piece in the available list
	int piece_found = 0; // whether found the value of the piece in the available list
	int input_valid = 1; // 0 means valid, 1 means invalid
	cout << "Please input the coordinate position and the value of the available"
			" piece. For example: \"1,1 3\" or input \"quit\" to quit the game." << endl;
	// call the prompt function to get the input value
	input_valid = prompt(position_x,position_y,piece_value);
	// iterate through the available pieces
	for( vector <numbered_game_piece> ::iterator iter = avp.begin(); 
		 iter != avp.end(); iter++ )
	{
		if(iter->value == piece_value)
		{
			// set the flag to one, if piece is found
			piece_found = 1;
		}
	}
	// check the format and get the input value
	while(	(input_valid != success) ||
			piece_found == 0 ||
			(v[horizontal_dimension*position_y+position_x] != empty_ngp) )
	{
		// check whether the input is valid
		if(input_valid != success)
		{
			cout << "Bad command line, Please input the coordinate position and the "
				    "value of the available piece. For example: \"1,1 3\" or"
				    " input \"quit\" to quit the game." << endl;
			input_valid = prompt(position_x,position_y,piece_value);
			// check whether there is the piece whose value is piece_value
			for(vector <numbered_game_piece> ::iterator iter = avp.begin(); 
				iter != avp.end(); iter++ )
			{
				if(iter->value == piece_value)
				{
					// set the flag to one
					piece_found = 1;
				}
			}
		}
		// check whether the position on the board is empty
		else if(v[horizontal_dimension*position_y+position_x] != empty_ngp)
		{
			cout << "The current position is not EMPTY. Please input the coordinate "
					"position and the value of the available piece. "
					"For example: \"1,1 3\" or input \"quit\" to quit the game." << endl;
			input_valid = prompt(position_x,position_y,piece_value);
			// check whether there is the piece whose value is piece_value
			for(vector <numbered_game_piece> ::iterator iter = avp.begin(); 
				iter != avp.end(); iter++ )
			{
				if(iter->value == piece_value)
				{
					// set the flag to one
					piece_found = 1;
				}
			}
		}
		else // check whether there is the piece whose value is piece_value
		{
			cout << "There is NO piece which value is "<< piece_value 
			     << " in the available piece list. ""Please input the coordinate"
			        " position and the value of the available piece. For "
			         "example: \"1,1 3\" or input \"quit\" to quit the game." << endl;
			input_valid = prompt(position_x,position_y,piece_value);
			// check whether there is the piece whose value is piece_value
			for(vector <numbered_game_piece> ::iterator iter = avp.begin(); 
				iter != avp.end(); iter++ )
			{
				if(iter->value == piece_value)
				{
					// set the flag to one
					piece_found = 1;
				}
			}
		}
	}
	// update the board
	v[horizontal_dimension*position_y+position_x].x = position_x;
	v[horizontal_dimension*position_y+position_x].y = position_y;
	v[horizontal_dimension*position_y+position_x].value = piece_value;
	find_display_length(piece_value);
	// delete the vector in the available piece list
	int i = 0;
	for(vector <numbered_game_piece> ::iterator iter = avp.begin(); 
		iter != avp.end(); iter++ )
	{
		if(iter->value == piece_value)
		{
			break;
		}
		++i;
	}
	// delete the vector in the available piece list
	avp.erase(avp.begin()+i);
	// print out the gameboard and each piece on the board 
	// by calling print() function
	print();
}

// Update longest_string_length
void MagicSquareGame::find_display_length(int piece_value)
{
		string piece_value_str;
		stringstream iss;
		iss << piece_value;
		piece_value_str = iss.str();
		unsigned int piece_value_length = piece_value_str.length();
		if (piece_value_length>longest_string_length)
		{
			longest_string_length = piece_value_length;
		}
}

// check whether the user finished inputing, 
// return ture if there is empty sapce for input
bool MagicSquareGame::check_is_empty()
{
	int size = horizontal_dimension * vertical_dimension;
	for (int i = 0; i< size ; ++i)
	{
		// check if there is an empty piece
		if(v[i] == empty_ngp)
		{
			return true;
		}
	}
	return false;
}

// save the current state
void MagicSquareGame::save_current_state()
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
		int piece_existing = 0;
		// store the value of the dimension
		unsigned int d = horizontal_dimension;
		for(unsigned int i = vertical_dimension-1; i+1 != 0; --i )
		{
			// Print the board
			for(unsigned int j = 0; j < horizontal_dimension; ++j)
			{
				//check whether it is empty
				if (v[d*i+j] != empty_ngp)
				{
					// print out the symbol
					ofs << setiosflags(ios_base::left)
						<< setw(longest_string_length+1) << v[d*i+j].value;
					piece_existing = 1;
				}
				// If there is no piece there, print out the the symbol E
				if(piece_existing == 0)
				{
					ofs << setiosflags(ios_base::left)
					    << setw(longest_string_length+1) << "E";
				}
				piece_existing = 0;
				//change the line
				if(j == horizontal_dimension-1)
				{
					ofs<< endl;
				}
			}
		}
		// insert the symbol in the file
		ofs << "AVP_START" << endl;
		// iterate through the available pieces
		for(vector <numbered_game_piece> ::const_iterator iter = avp.begin(); 
			iter != avp.end(); iter++ )
		{
			ofs << iter->value << endl ;
		}
		// insert the symbol in the file
		ofs  << "AVP_END" << endl;
	}
	// close the file
	ofs.close();
}

// abort the current state
void MagicSquareGame ::abort_current_state()
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
