// TicTacToeState.h
// This class mainly deals with minimax search
// Author : Zheng Luo
// Created by Zheng Luo on 04/14/14.
// http://www.neverstopbuilding.com/minimax

#ifndef TIC_TAC_TOE_STATE_H
#define TIC_TAC_TOE_STATE_H

#include "OtherFunctions.h"
#include <string>
#include <vector>

using namespace std;

// Game state representing a state of the Tic-Tac-Toe-puzzle
class TicTacToeState : public TicTacToeBase {

public:
	TicTacToeState(unsigned int h, unsigned int v,
				   char first, char second, bool turn_of_com,
				   bool play_with_com, string lev, 
				   char **board, unsigned int **s_array,
				   unsigned int c_row, unsigned int c_col, unsigned int c_count);
	virtual ~TicTacToeState();
	// Get the optimal move position
	virtual position* get_move();

protected:
	// Store the set of legal moves in a state.  
	vector <position> actions;
	// Index of next action
	unsigned int index;
	// The transition model, which defines the result of a move.
	// After take a set of actions.
	TicTacToeState result(position);
	// A utility function (also called an objective function or 
	// payoff function), defines the final numeric value for a 
	// game that ends in terminal state s for a player p.
	int utility(unsigned int depth);
	// The min for max value returned for this state
	int max_value(unsigned int depth);
	int min_value(unsigned int depth);
	// Temp virables
	char **temp_board;
	unsigned int **temp_state;
	void print_debug_info(TicTacToeState &next_state, 
						  int depth, int temp);
};

#endif