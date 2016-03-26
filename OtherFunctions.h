// OtherFunctions.h
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#ifndef OTHER_FUNCTION_H
#define OTHER_FUNCTION_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <list>

using namespace std;

// The empty represents there is no piece there,  
// if the x == 10 and y == 10, it means there is no piece there
const unsigned int x_empty = 10;
const unsigned int y_empty = 10;

// The color of the pieces
typedef enum piece_color { 
	brown, black_or_white, black, white 
} Color;

// The enumtype of return value
enum return_value { 
	success, bad_command_line, bad_memory_allocation, 
	quit_turn, quit_game, failure, no_more_valid_move,
	other_exceptions, instance_not_exist, instance_exist,
	invalid_file_state 
};

// Call usage function when the input is not correct
return_value call_usage_function();

// The move type of the chess piece
enum MoveType {
	ILLEGAL, NORMAL, CASTLE, DOUBLESTEP, 
	ENPASSANT, ESCAPE, PROMOTION
};

// The definition of each piece
typedef struct game_piece {
	// default constructor with no arguments
	game_piece();
	// default constructor with arguments
	game_piece(unsigned int m, unsigned int n);
	bool operator!= (const game_piece & gp) const;
	bool operator== (const game_piece & gp) const;
	unsigned int x, row; // x means the row
	unsigned int y, col; // y means the column
} Point, position;

// The definition of the numbered_game_piece
struct numbered_game_piece : public game_piece {
	numbered_game_piece(unsigned int m, unsigned int n,
						unsigned int v);
	int value;
};

// The definition of the reversi_game_piece
typedef struct reversi_game_piece : public game_piece {
	reversi_game_piece(unsigned int m, unsigned int n,
					   piece_color c, string s);
	piece_color color;
	string symbol;
} checkers_game_piece, chess_game_piece;

#endif