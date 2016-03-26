// ChessGame.cpp
// Author : Zheng Luo
// Created by Zheng Luo on 04/29/14.

#include "OtherFunctions.h"
#include "GameBase.h"
#include "ChessDesign.h"
#include "ChessGame.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

//constructor of ChessGame
ChessGame::ChessGame(unsigned int h, unsigned int v, piece_color color,
				     string name, string symbol, string first, string second)
:GameBase(h, v, color, name, symbol), // assume black go first
first_person(first),second_person(second),player(first),player_color(black),N(h)
{
	// initialize the baord
	chess_board = new Board();
}

ChessGame::~ChessGame()
{
	delete chess_board;
}

// check whether the game is done
bool ChessGame::done()
{
    for (unsigned int i = 0; i < N; i++)
        for (unsigned int j = 0; j < N; j++)
            if (chess_board->PieceAt(Point(i,j)) != NULL &&
                ( chess_board->PieceAt(Point(i,j))->GetSymbol() == "K" ||
            	  chess_board->PieceAt(Point(i,j))->GetSymbol() == "k" ) &&
            	chess_board->PieceAt(Point(i,j))->GetColor() != player_color)
            	return false;
    return true;
}

// check and make a valid move in the game
void ChessGame::turn()
{
	// move the piece
	chess_board->TryToMove(from,to);
}

// print method
void ChessGame::print()
{
	cout << endl << *this << endl << endl;
}

// play the game by calling turn()
int ChessGame::play()
{
	while (true)
	{
		// Read the where the player wants to place a piece
		read_position(from, to);
		// Make a turn
		turn();
		// Print the board
		print();
		// Check if there is a winner
		if (done())
			break;
		// Change a player
		change_current_player();
	}
	cout << "Congratulations to " << player
		 << "\nYou win the game." << endl;
    return success;
};

// read position from commandline
void ChessGame::read_position(Point &from, Point &to)
{
    while (true) 
    {
        cout << "\n\n\nPlayer " << player
             << ", please enter the from to of your move.\n"
                "For example 1,1 2,2 meaning from (1,1) to (2,2), "
                "and the input range should be less or equal to " 
            << N -1 << endl;
        string s; // Temp virable to read command line data
        getline(cin, s);
        // Replace comma with space
        replace(s.begin(), s.end(), ',', ' ');
        // This code converts from string to number safely.
        stringstream strStream(s);
        // Extrace the number and assign to point from and to
        if (strStream >> from.x && strStream >> from.y &&
            strStream >> to.x   && strStream >> to.y)
        	if(chess_board->CanMove(from, to))
        		break;

        cout << "Invalid select or move, please try again" << endl;
    }
}

void ChessGame::change_current_player()
{
	if (player_color == black)
	{
		player = second_person;
        player_color = white;
	}
    else
    { 
        player = first_person;
        player_color = black;
    }
}

// Overloading the operator << for Checkers Game
ostream &operator<< (ostream &out,  const ChessGame &r)
{
	// store the value of the dimension
	unsigned int d = r.horizontal_dimension;
	
	// Draw the X coordinate
	out << "X" << " ";
	for(unsigned int j = 0; j < d; ++j)
	{
		// Draw the X coordinate with the space between them
		out << setiosflags(ios_base::left)
			<< setw(r.longest_string_length+1) << j;
	}
	out << "X" << endl;

	for(unsigned int i = 0; i < d; ++i)
	{
		// Draw the Y coordinate
		out << i << " ";
		// Print the board
		for(unsigned int j = 0; j < d; ++j)
		{
			// check whether it is empty
			// If there is no piece there, print out the space
			if(r.chess_board->PieceAt(Point(i,j)) == NULL)
			{
				out << setiosflags(ios_base::left)
					 << setw(r.longest_string_length+1) << " ";
			}
			else
			{
				// print out the symbol
				out << setiosflags(ios_base::left)
					<< setw(r.longest_string_length+1) 
					<< r.chess_board->PieceAt(Point(i,j))->GetSymbol();
			}
			// Draw the Y coordinate and change the line
			if(j == d-1)
				out << i << endl;
		}
	}

	// Draw the X coordinate
	out << "X" << " ";
	for(unsigned int j = 0; j < d; ++j)
	{
		// Draw the X coordinate with the space between them
		out << setiosflags(ios_base::left)
			<< setw(r.longest_string_length+1) << j;
	}
	out << "X" << endl;

	return out;
}
