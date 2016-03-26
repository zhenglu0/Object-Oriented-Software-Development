// TicTacToeBase.h
// This class abstracts common elemnts
// Author : Zheng Luo
// Created by Zheng Luo on 04/14/14.

#ifndef TIC_TAC_TOE_BASE_H
#define TIC_TAC_TOE_BASE_H

#include "OtherFunctions.h"
#include <string>

using namespace std;

class TicTacToeBase {

public:
	TicTacToeBase(unsigned int h,unsigned int v,
				  char first, char second, bool turn_of_com,
				  bool play_with_com, string lev, unsigned int t_count);
	virtual ~TicTacToeBase();

protected:
	// print the value in the array
	virtual void print_state_array();
	// increase the current move in state array
	virtual void increase_state_array(unsigned int &c_row, 
									  unsigned int &c_col,
									  unsigned int **state);
	// check whether the game is done
	virtual bool done();	
	// return the winner of the game
	virtual char winner();
	// print board
	virtual void print();
	// new board and state array
	virtual void new_board_and_state(char** &game_board, 
									 unsigned int** &state);
	// copy board and state array
	virtual void copy_board_and_state(char **game_board, char **temp_board,
						   unsigned int **state, unsigned int **temp_state);
	
	// delete board and state array
	virtual void delete_board_and_state(char** &game_board, 
										unsigned int** &state);
	// virables
	unsigned int board_rows;
	unsigned int board_cols;
	unsigned int N; // number of contiguous marks a player to win
	char init_char;
	char p1_symbol;
	char p2_symbol;
	char **game_board;
	char player;
	unsigned int current_move_row;
	unsigned int current_move_col;
	unsigned int **state;
	bool turn_of_computer;
	bool play_with_computer;
	string mode;
	unsigned int turn_count;
};

#endif