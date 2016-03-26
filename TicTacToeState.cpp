// TicTacToeState.cpp
// This class mainly deals with minimax search
// Author : Zheng Luo
// Created by Zheng Luo on 04/14/14.
// http://www.neverstopbuilding.com/minimax

#include "TicTacToeBase.h"
#include "TicTacToeState.h"

#include <cstdlib>     // srand, rand
#include <ctime>       // time
#include <string>
#include <iostream>
#include <vector>

TicTacToeState::TicTacToeState(unsigned int h,unsigned int v,
							   char first, char second,
							   bool turn_of_com, bool play_with_com,
							   string lev, char **board, 
                               unsigned int **s_array, 
                               unsigned int c_row, unsigned int c_col, unsigned int t_count)
:TicTacToeBase(h, v, first, second, turn_of_com, play_with_com, lev, t_count)
{
    new_board_and_state(temp_board, temp_state);

    // Copy the information
    copy_board_and_state(game_board, board, state, s_array);

    // Store the number of possible action
    for (unsigned int i = 0; i < N; i++)
        for (unsigned int j = 0; j < N; j++)
        	if (game_board[i][j] == init_char)
        		actions.push_back(position(i,j));

    // Set the currentmove for state array use
    current_move_row = c_row;
    current_move_col = c_col;
}

TicTacToeState::~TicTacToeState()
{
    delete_board_and_state(temp_board, temp_state);
}

int TicTacToeState::utility(unsigned int depth)
{
    // Only support X is human, 
    // O is computer now
    if (winner() == p1_symbol) 
        return 10 - (int)depth;
    else if (winner() == p2_symbol)
        return (int)depth - 10;
    // If it is a tie
	return 0;
}

TicTacToeState TicTacToeState::result(position p)
{
    // Copy the information
    copy_board_and_state(temp_board, game_board, temp_state, state);

    // Increase temp_state
    increase_state_array(p.row, p.col, temp_state);

    // Set p2_or p1 symbol on the board
    if (player == p2_symbol)
        temp_board[p.row][p.col] = p2_symbol;  
    else
        temp_board[p.row][p.col] = p1_symbol;

    // Construct a new object for return
    TicTacToeState result_state(board_rows, board_cols, p1_symbol,
                                p2_symbol, turn_of_computer,
                                play_with_computer, mode, temp_board,
                                temp_state, p.row, p.col,
                                turn_count + 1);

    return result_state;
}

int TicTacToeState::max_value(unsigned int depth)
{
    if (done())
        return utility(depth);

    depth++; // Increase depth by one
    int v = -10; // Smaller than possible utility return
    for (unsigned int i = 0; i < actions.size(); i++)
    {
        player = p1_symbol; // p1 gets the max value

        TicTacToeState next_state = result(actions[i]); 
        int temp = next_state.min_value(depth);
        // For debuging purpose
        //if (depth == 2)
        //    print_debug_info(next_state, depth, temp);
        // Get the max from mins
        if (v < temp)
        {
            v = temp;
            index = i;
        }
    }
    return v;
}

int TicTacToeState::min_value(unsigned int depth)
{
    if (done())
        return utility(depth);

    depth++; // Increase depth by one
    int v = 10; // larger than possible utility return
    for (unsigned int i = 0; i < actions.size(); i++)
    {
        player = p2_symbol; // p2 gets the min value

        TicTacToeState next_state = result(actions[i]);
        int temp = next_state.max_value(depth);
        // For debuging purpose
        //if (depth == 1)
        //    print_debug_info(next_state, depth, temp);
        // Get the min from maxs
        if (v > temp)
        {
            v = temp;
            index = i;
        }
    }
    return v;
}

position* TicTacToeState::get_move()
{
    position* p = NULL;
    // Initialize random seed
    srand (time(NULL));
    // Get a random number for a move
    int r = rand() % 10;

    // esay mode will have 70% random moves
    // hard mode will have 50% random moves
    // impossivle mode will no random moves
    if ((mode == "easy" && r >= 3) ||
        (mode == "hard" && r >= 5) )
        index = rand() % actions.size(); 
    else 
    {
        unsigned int depth = 0;
        // 'O' always tries to minimize the value
        // 'X' always tries to maximize the value
        if (player == p2_symbol)
            min_value(depth);
        else 
            max_value(depth);
    }

    p = &actions[index];
	return p;
}

void TicTacToeState::print_debug_info(TicTacToeState &next_state, 
                                      int depth, int temp)
{
    cout << "--------------------------------------" << endl;
    cout << "depth = " << depth << ", "
         << "next_state_move:" << next_state.current_move_row + 1
         << "," << next_state.current_move_col + 1 << ", " << endl
         << "winner = " << next_state.winner() << ", "
         << "state value = " << temp << endl;
    next_state.print_state_array();
    next_state.print();
    cout << "--------------------------------------" << endl;
    cout << endl;
}