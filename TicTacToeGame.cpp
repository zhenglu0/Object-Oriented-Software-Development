// TicTacToeGame.cpp
// This class is a implementation of TicTacToe Game 
// Author : Zheng Luo
// Modified by Zheng Luo on 04/14/14.

#include "OtherFunctions.h"
#include "GameBase.h"
#include "TicTacToeBase.h"
#include "TicTacToeGame.h"
#include "TicTacToeState.h"

#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>

// Use the MULTIPLE inheritance here
// Derived from two base classes
TicTacToeGame::TicTacToeGame(unsigned int h, unsigned int v,
                             piece_color color, string name, string symbol, 
                             char first, char second, bool turn_of_com, 
                             bool play_with_com, string lev)
:GameBase( h, v, color, name, symbol),
 TicTacToeBase(h, v, first, second, turn_of_com, play_with_com, lev, 0) {}

void TicTacToeGame::initialize_game()
{
    for (unsigned int row = 0; row < board_rows; row++)
        for (unsigned int col = 0; col < board_cols; col++)
            game_board[row][col] = init_char;
    
    for (unsigned int i = 0; i < 2; i++)
        for (unsigned int j = 0; j < 2*N+2; j++)
            state[i][j] = 0;
}

int TicTacToeGame::play()
{   
    // Initialize the board and state array
    initialize_game();

    while (true)
    {
        // Flip the symbol each turn
        if (player == p2_symbol) 
            player = p1_symbol;
        else 
            player = p2_symbol;

        cout << "\n\n\n\n\n";
        // The turn may be either a computer or human
        if (turn_of_computer &&
            play_with_computer) 
        {
            cout << "Computer " << player << "'s Turn NOW!" << endl;
            turn_computer();
            turn_of_computer = false;
        } 
        else 
        {
            cout << "Player " << player << "'s Turn NOW!" << endl;
            turn();
            turn_of_computer = true;
        }

        cout << "\n";
        print();
        turn_count++;

        // Use the Base class method
        if (done())
        {
            if (winner() != 'N')
            {
                cout << "\n\n\n\n\nCongratulations Player " << winner()
                     << ", you've won with " << N << " in a row!\n\n";
                break;
            }
            // The board is full and the game is over
            else
            {
                cout << "\n\nGame Over!\n\nThere is no Winner :-(\n";
                break;
            }
        }
    }
    return success;
}

void TicTacToeGame::turn()
{
    unsigned int row = 0, col = 0;
    
    // Read the position from the command line
    read_position(row, col);

    // Store information for state array
    increase_state_array(row, col, state);

    // Finally, we store the correct mark into the given location
    game_board[row][col] = player;
}

void TicTacToeGame::turn_computer()
{
    cout << "\n\n";
    if (turn_count != 0)
    {
        // Use the MinMax Search to find optimal solution
        TicTacToeState game_state(board_rows, board_cols, p1_symbol, 
                                  p2_symbol, turn_of_computer,
                                  play_with_computer, mode, game_board,
                                  state, current_move_row,
                                  current_move_col, turn_count);
        
        // Get the optimal move position
        position *p = game_state.get_move();

        // Store information for state array
        increase_state_array(p->row, p->col, state);
        
        // Set the current mvoe
        current_move_row = p->row;
        current_move_col = p->col;

        // Finally, we store the correct mark into the given location
        game_board[p->row][p->col] = player;
    }
    else
    {
        // Place the 'X' piece on the center of the board
        unsigned int row = 1, col = 1;
        increase_state_array(row, col, state);
        game_board[1][1] = player;
    }
}

void TicTacToeGame::read_position(unsigned int &row, unsigned int &col)
{
    while (true) 
    {
        cout << "\n\n\nPlayer " << player
             << ", please enter the row column of your move.\n"
                "For example 1,1 meaning (1,1), "
                "the input range should be less or equal to " 
            << N << endl;
        string s; // Temp virable to read command line data
        getline(cin, s);
        // Replace comma with space
        replace(s.begin(), s.end(), ',', ' ');
        // This code converts from string to number safely.
        stringstream strStream(s);
        if (strStream >> row && row <= N &&
            strStream >> col && col <= N &&
            game_board[row-1][col-1] == init_char)
            break;
        cout << "Invalid number, please try again" << endl;
    }
    row--; // Translate the user's board_rows and columns numbering
    col--; // (starting with 1) to the computer's (starting with 0)
    // Set the current mvoe
    current_move_row = row;
    current_move_col = col;
}