// OtherFunctions.cpp
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#include "OtherFunctions.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <memory>
#include <list>

using namespace std;

return_value call_usage_function()
{
	cout << "Command line error! Please input:\n"
			"\"Games Checkers Alice Bob\"    OR \n"
			"\"Games Chess Alice Bob\"       OR \n"
		    "\"Games NineAlmonds\"           OR \n"
		    "\"Games MagicSquare\"           OR \n"
		    "\"Games Reversi Alice Bob\"     OR \n"
		    "\"Games TicTacToe\"             AND\n"
		    "WHERE Alice is the person in Reversi Game (or Checkers) "
	        "who moves first,\nand Bob is the person who moves second.\n";

	return bad_command_line;
}

//constructor of game_piece with no arguments
game_piece::game_piece () {}

//constructor of game_piece with arguments
game_piece::game_piece (unsigned int m, unsigned int n)
: x(m), row(m), y(n), col(n) {}

// overload the != operator
bool game_piece::operator!= (const game_piece & gp) const
{
	return (x != gp.x || y != gp.y);
}

// overload the == operator
bool game_piece::operator== (const game_piece & gp) const
{
	return (x == gp.x && y == gp.y);
}

// constructor of numbered_game_piece
numbered_game_piece::numbered_game_piece (unsigned int m, 
	                                      unsigned int n, unsigned int v)
: game_piece(m,n), value(v) {}

// constructor of reversi_game_piece
reversi_game_piece::reversi_game_piece (unsigned int m, unsigned int n,
									    piece_color c, string s)
: game_piece(m,n), color(c), symbol(s) {}
