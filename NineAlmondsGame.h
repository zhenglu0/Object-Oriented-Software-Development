// NineAlmondsGame.h
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#ifndef NINE_ALMODS_GAME_H
#define NINE_ALMODS_GAME_H

class NineAlmondsGame : public GameBase {

	friend ostream &operator<<(ostream &out, const NineAlmondsGame &n);

public:
	NineAlmondsGame(unsigned int h, unsigned int v, 
					piece_color color, string name, string symbol);
	virtual ~NineAlmondsGame() {};
	//set function
	virtual void initialize_game(); 
	//set function
	virtual void initialize_game_from_start();
	//set function
 	virtual void push_v (game_piece gp);
	//set function
	virtual void set_v (unsigned int x,unsigned int ,game_piece gp);
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
	// checks if there is valid move
	bool no_valid_move(vector<game_piece> board_state);
	// save the current state
	virtual void save_current_state();
	// abort the current state
	virtual void abort_current_state();

protected:
	// hold the game pieces, it represents the gameboard, 
	// the index correspond to the position of the board
	vector<game_piece> v;

};

#endif