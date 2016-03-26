// Games.cpp
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#include "OtherFunctions.h"
#include "GameBase.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <list>

// used to store the argv[] globely
char ** argv_globle;
// flag out whehter to return the last state
int last_state = 0; // 0 means not to return

int main(int argc, char * argv[])
{	
	// indicating the condition of the game
	int play_condition = failure; 
	argv_globle = argv;
	// creat objects according to users input
	GameBase * ptr = 0;
	try
	{
		GameBase::check_create(argc, argv);
		ptr = GameBase::instance();
	}
	// check if the memory allocation is successful.
	catch(bad_alloc & ba)
	{
		cout << "Caught" << ba.what() << "exception" << endl;
		return bad_memory_allocation;
	}
	// check if the input value is valid
	catch(return_value & rv)
	{
		if (rv == instance_not_exist)
		{
			return call_usage_function();//return bad_command_line
		}
		else
		{
			return rv; // return instance_exist
		}
			
	}
	// use a smart pointer to point to the object, 
	// it will delete automatically so we don't need to 
	// delete it explicitly.
    shared_ptr<GameBase> g_ptr(ptr);
	// if an object of NineAlmondsGame or MagicSquareGame 
	// or ReversiGame class is created,
	// the value of the pointer must not be zero and the object 
	// which the pointer points to must be the instance.
	if	(g_ptr.get() != 0)
	{	
		//initialize the board
		try
		{
			g_ptr->initialize_game();
		}
		catch(string s)
		{
			cout << s << endl;//cout the error
			cout << "The game is quit!" << endl;
			return invalid_file_state;
		}
		catch (...) 
		{
		    // Catch everything else
			cout << "Other exceptions are caught. " << endl;
			return other_exceptions;
		}
		
		// check whether a previous game is saved or not
		if(last_state == 0)
		{
			cout << "The initial state is: " << endl;
		}
		else
		{
			cout << "The last state before quitting is: " << endl;
		}
		
		// print the board just after initialization
		g_ptr->print();
		try
		{
			// call the play function to play the game
			play_condition = g_ptr->play();
			cout << endl;
		}
		
		// catches the quit exception
		catch(string &)
		{
			cout << "and the game quits." << endl;
			return quit_game;
		}
		catch (...) // Catch everything else
		{
			cout << "Other exceptions are caught. " << endl;
			return other_exceptions;
		}
	}
	return play_condition;
}
	
