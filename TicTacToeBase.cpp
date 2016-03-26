// TicTacToeBase.cpp
// This class abstracts common elemnts
// Author : Zheng Luo
// Created by Zheng Luo on 04/14/14.

#include "OtherFunctions.h"
#include "TicTacToeBase.h"

#include <iostream>

TicTacToeBase::TicTacToeBase(unsigned int h,unsigned int v, 
                             char first, char second,
                             bool turn_of_com, bool play_with_com, 
                             string lev, unsigned int t_count)
: board_rows(h),board_cols(v),N(h),init_char(' '),
  p1_symbol(first),p2_symbol(second),
  player(second),turn_of_computer(turn_of_com),
  play_with_computer(play_with_com),mode(lev),turn_count(t_count)
{
    new_board_and_state(game_board, state);
}

TicTacToeBase:: ~TicTacToeBase()
{
    delete_board_and_state(game_board, state);
}

bool TicTacToeBase::done()
{   
    for (int i = 0; i < 2; i++)
    {
        int p_number = i;
    
        if (state[p_number][current_move_row]     == N ||
            state[p_number][N+current_move_col]   == N ||
            state[p_number][2*N]                  == N ||
            state[p_number][2*N+1]                == N ||
            turn_count                            == N * N)
            return true;
    }
    
    return false;
}

char TicTacToeBase::winner()
{       
    for (int i = 0; i < 2; i++)
    {
        int p_number = i;

        if (state[p_number][current_move_row]   == N ||
            state[p_number][N+current_move_col] == N ||
            state[p_number][2*N]                == N ||
            state[p_number][2*N+1]              == N) 
            return p_number == 0?  p1_symbol : p2_symbol;
    }

    // N means no winner
    return 'N';
}

void TicTacToeBase::print()
{
    for (unsigned int row = 0; row < board_rows; row++)
    {
        if (row == 0)
        {
            cout << "  ";
            for (unsigned int i = 0; i < board_cols; i++)
                cout << " " << i+1 << "  ";
            cout << "\n\n";
        }

        for (unsigned int col = 0; col < board_cols; col++)
        {
            if (col == 0)
                cout << row+1 << " ";
            cout << " " << game_board[row][col] << " ";
            if (col < board_cols-1)
                cout << "|";
        }

        cout << "\n";

        if (row < board_rows-1)
        {
            for(unsigned int i = 0; i< board_cols-1; i++)
            {
                if(i == 0)
                    cout << "  ----";
                else
                    cout << "----";
            }
            cout << "---\n";
        }
    }
}

void TicTacToeBase::print_state_array()
{
    // Used for print state array
    for (unsigned int i = 0; i < 2; i++)
        for (unsigned int j = 0; j < 2*N+2; j++)
            cout << "state[" << i << "]" << "[" << j 
                 << "]" << state[i][j] << endl;
}

void TicTacToeBase::increase_state_array(unsigned int &c_row, 
                                         unsigned int &c_col,
                                         unsigned int **state)
{
    int p_number;

    if (player == p1_symbol)               
        p_number = 0;
    else
        p_number = 1;

    // Increment the row state
    state[p_number][c_row]++;

    // Increment the column state
    state[p_number][N+c_col]++;

    // Increment the diagonal state
    if (c_row == c_col)
        state[p_number][2*N]++;

    // Increment the diagonal state 
    if (c_row + c_col == N-1)
        state[p_number][2*N+1]++;
}

void TicTacToeBase::new_board_and_state(char** &game_board, 
                                        unsigned int** &state)
{
    // Allocate memory for the game_board
    game_board = new char* [N];
    for (unsigned int i = 0; i < N; i++)
        game_board[i] = new char [N];

    // Allocate memory for the state
    state = new unsigned int*[2];
    for (unsigned int i = 0; i < 2; i++)
        state[i] = new unsigned int [2*N+2];
}

void TicTacToeBase::copy_board_and_state(char **game_board,
                                         char **board,
                                         unsigned int **state,
                                         unsigned int **s_array)
{
    // Copy the game_board from the Game
    for (unsigned int i = 0; i < N; i++)
        for (unsigned int j = 0; j < N; j++)
            game_board[i][j] = board[i][j];
    
    // Copy the state_array
    for (unsigned int i = 0; i < 2; i++)
        for (unsigned int j = 0; j < 2*N+2; j++)
            state[i][j] = s_array[i][j];
}

// delete board and state array
void TicTacToeBase::delete_board_and_state(char** &game_board, 
                                           unsigned int** &state)
{
    for (unsigned int i = 0; i < N; i++)
        delete [] game_board[i];
    delete [] game_board;

    for (unsigned int i = 0; i < 2; i++)
        delete [] state[i];
    delete [] state;  
}