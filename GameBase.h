// GameBase.h
// Author : Zheng Luo
// Modified by Zheng Luo on 03/25/14.

#ifndef GAME_BASE_H
#define GAME_BASE_H

class GameBase {

public :
	GameBase(unsigned int h,unsigned int v,piece_color color,
			 string name,string symbol);
	virtual ~GameBase() {};
	virtual void print() = 0;
	// check whether the game is done
	virtual bool done() = 0;
	// prompt the user to input the value
	virtual void turn() = 0;
	// play the game by calling turn()
	virtual int  play() = 0;
	// check the argument and creat the object
	static void  check_create(int argc , char * argv[]);
	//retun the value of horizontal_dimension
	unsigned int get_horizontal_dimension() const;
	//retun the value of vertical_dimension
	unsigned int get_vertical_dimension() const;
	// initialize the board 
	virtual void initialize_game() = 0; 
	// initialize the board if the user doesn't save the previous game
	virtual void initialize_game_from_start() = 0; 
	// instance method
	static GameBase * instance(); 
	// save current state
	virtual void save_current_state() = 0;
	// abort the current state
	virtual void abort_current_state() = 0;

protected :
	unsigned int horizontal_dimension;
	unsigned int vertical_dimension;
	piece_color color; 
	string name;
	string symbol;
	unsigned int longest_string_length;
	static GameBase * instance_;

};

#endif