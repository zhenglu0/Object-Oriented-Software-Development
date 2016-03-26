// ChessGame.h
// Author : Zheng Luo
// Created by Zheng Luo on 04/29/14.

#ifndef CHESS_H
#define CHESS_H

#include "ChessDesign.h"

class ChessGame : public GameBase {
	//  support insertion operator
	friend ostream &operator<<(ostream &out, const ChessGame &n);

public:
	ChessGame(unsigned int h, unsigned int v, piece_color color, 
			  string name, string symbol, string first, string second);
	virtual ~ChessGame();
	// set function, not implemented
	virtual void initialize_game(){};
	virtual void initialize_game_from_start(){}; 
	// check whether the game is done
	virtual bool done();
	// check and make a valid move in the game
	virtual void turn();
	// the print method
	virtual void print();
	// play the game by calling turn()
	virtual int  play();
	// save the current state, not implemented
	virtual void save_current_state(){};
	// abort the current state, not implemented
	virtual void abort_current_state(){};

protected:
	// read position from commandline
	void read_position(Point &from, Point &to);
	// change the player symbol
	void change_current_player();
	// A pointer for ChessBoard
	Board *chess_board;
	// store the name of the player who moves first
	string first_person;
	// store the name of the player who moves second
	string second_person;
	// store current player name
	string player;
	// store the current player color
	Color player_color;
	// chessboard dimension
	unsigned int N;
	// move a piece from point
	Point from;
	// move a piece to point
	Point to;
};

#endif