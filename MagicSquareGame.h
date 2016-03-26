// MagicSquareGame.h
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#ifndef MAGIC_SQUAREGAME_H
#define MAGIC_SQUAREGAME_H

class MagicSquareGame : public GameBase {

	friend ostream &operator<<(ostream &out, const MagicSquareGame &m);

public:
	MagicSquareGame(unsigned int h, unsigned int v, piece_color color,
					string name, string symbol, int lowest_piece_val_ =1)
	:GameBase(h, v, color, name, symbol),
	lowest_piece_val(lowest_piece_val_){};
	
	virtual ~MagicSquareGame() {};
	//set function
	virtual void initialize_game(); 
	virtual void initialize_game_from_start(); 
	//set function
 	virtual void push_v (numbered_game_piece ngp);
	//set function
	virtual void set_v (unsigned int x,unsigned int ,
		                numbered_game_piece ngp);
	// check whether the game is done
	virtual bool done();
	// prompt the user to input the value
	virtual int  prompt(unsigned int &a, unsigned int &b, int &c);
	// check and make a valid move in the game
	virtual void turn();
	// the play method
	virtual int  play();
	// the print method
	virtual void print();
	// set function
	virtual void push_avp (numbered_game_piece ngp);
	// Update longest_string_length
	virtual void find_display_length(int);
	// check whether the user finished inputing, 
	// return ture if there is empty sapce for input
	virtual bool check_is_empty();
	// save the current state
	virtual void save_current_state();
	// abort the current state
	virtual void abort_current_state();

protected:
	// hold the game pieces, it represents the gameboard, 
	// the index corresponds to the position of the board
	vector<numbered_game_piece> v;
	// store the vector of the available piece list
	vector<numbered_game_piece> avp;
	int lowest_piece_val;
};

#endif