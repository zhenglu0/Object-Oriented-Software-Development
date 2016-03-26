// TicTacToeGame.h
// This class is a implementation of TicTacToe Game 
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.
// Combied with Lab5, original url of the program 
// http://stackoverflow.com/questions/1056316/
// algorithm-for-determining-tic-tac-toe-game-over

#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

#include "TicTacToeBase.h"

// Use the MULTIPLE inheritance here
// Derived from two base classes
class TicTacToeGame : public GameBase , public TicTacToeBase {
	//  not support insertion operator
	friend ostream &operator<<(ostream &out, const TicTacToeGame &n);

public:
	TicTacToeGame(unsigned int h,unsigned int v, 
				  piece_color color, string name, string symbol, 
				  char first, char second, 
				  bool turn_of_com, bool play_with_com, string lev);
	virtual ~TicTacToeGame() {};
	// set function
	virtual void initialize_game();
	// not implemented
	virtual void initialize_game_from_start() {};
	// the done is implemented in the TicTacToeBase
	virtual bool done() { return TicTacToeBase::done(); };
	// check and make a valid move for human in the game
	virtual void turn();
	// check and make a valid move for computer in the game
	virtual void turn_computer();
	// the print method
	virtual void print() { TicTacToeBase::print(); };
	// play the game by calling turn()
	virtual int  play();
	// save the current state, not implemented
	virtual void save_current_state() {};
	// abort the current state, not implemented
	virtual void abort_current_state() {};

protected:
	// read position from commandline
	void read_position(unsigned int &row, unsigned int &col);
};

#endif