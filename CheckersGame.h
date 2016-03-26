// Checkers.h
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#ifndef CHECKER_H
#define CHECKER_H

class CheckersGame : public GameBase {

	friend ostream &operator<<(ostream &out, const CheckersGame &n);

public:
	CheckersGame(unsigned int h, unsigned int v, piece_color color, 
				 string name, string symbol, string first, string second);
	virtual ~CheckersGame(){};
	//set function
	virtual void initialize_game();
	virtual void initialize_game_from_start(){}; 
	//set function
	virtual void push_v (checkers_game_piece cgp); 
	//set function
	virtual void set_v (unsigned int x,unsigned int y ,
					    checkers_game_piece cgp); 
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
	virtual bool valid_put_position_black(unsigned int i, unsigned int j, 
										  unsigned int m, unsigned int n);
	// checks if this puting position is valid 
	virtual bool valid_put_position_white(unsigned int i, unsigned int j, 
										  unsigned int m, unsigned int n);
	// complete the play's turn and change the board according to the rules
	virtual void complete_black_turn(unsigned int i, unsigned int j, 
									 unsigned int m, unsigned int n);
	// complete the play's turn and change the board according to the rules
	virtual void complete_white_turn(unsigned int i, unsigned int j, 
									 unsigned int m, unsigned int n);
	// count the number of plack pieces
	virtual unsigned int count_black_pieces();
	// count the number of white piece
	virtual unsigned int count_white_pieces();
	// check if there is a put position for black piece
	virtual bool check_available_move_black();
	// check if there is a put position for white piece
	virtual bool check_available_move_white();
	// decide whether the piece on the board should be change into the King
	virtual void whether_change_into_king();
	// check if the continuous move is valid
	virtual bool check_continuous_move_current_black(unsigned int i, 
													 unsigned int j);
	// check if the continuous move is valid
	virtual bool check_continuous_move_current_white(unsigned int i, 
													 unsigned int j);

protected:
	// hold the game pieces, it represents the gameboard, 
	// the index correspond to the position of the board
	vector<checkers_game_piece> v;
	// store the name of the player who moves first
	string first_person;
	// store the name of the player who moves second
	string second_person;

};

#endif