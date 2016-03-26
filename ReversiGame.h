// ReversiGame.h
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H

class ReversiGame : public GameBase {

	friend ostream &operator<<(ostream &out, const ReversiGame &n);

public:
	ReversiGame(unsigned int h, unsigned int v, piece_color color, 
		        string name, string symbol, string first, string second);
	virtual ~ReversiGame() {};
	//set function
	virtual void initialize_game(); 
	//set function
	virtual void initialize_game_from_start();
	//set function
	virtual void push_v (reversi_game_piece rgp); 
	//set function
	virtual void set_v (unsigned int x,unsigned int y ,
		                reversi_game_piece rgp); 
	// check whether the game is done
	virtual bool done();
	// prompt the user to input the value
	virtual int  prompt(unsigned int &a, unsigned int &b);
	// check and make a valid move in the game
	virtual void turn();
	// the print method
	virtual void print();
	// play the game by calling turn()
	virtual int  play();
	// save the current state
	virtual void save_current_state();
	// abort the current state
	virtual void abort_current_state();
	// checks if this puting position is valid 
	virtual bool valid_put_position_black(unsigned int i, unsigned int j);
	// checks if this puting position is valid 
	virtual bool valid_put_position_white(unsigned int i, unsigned int j);
	// complete the play's turn and change the board according to the rules
	virtual void complete_black_turn(unsigned int i, unsigned int j);
	// complete the play's turn and change the board according to the rules
	virtual void complete_white_turn(unsigned int i, unsigned int j);
	// count the number of plack pieces
	virtual unsigned int count_black_pieces();
	// count the number of white piece
	virtual unsigned int count_white_pieces();
	// check if there is a put position for black piece
	virtual bool check_available_square_black();
	// check if there is a put position for white piece
	virtual bool check_available_square_white();

protected:
	// hold the game pieces, it represents the gameboard, 
	// the index correspond to the position of the board
	vector<reversi_game_piece> v;
	// store the name of the player who moves first
	string first_person;
	// store the name of the player who moves second
	string second_person;

};

#endif
