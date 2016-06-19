**************************************************************************
## Object-Oriented-Software-Developmen Labs

Zheng Luo Yan Liu Yue Yuan
**************************************************************************

************************************************
Explanations on how we format the file. 
We will explain by giving examples and comments.
************************************************
1.For the NineAlmonds game:
<NineAlmonds.txt>:
NineAlmonds	  //The name of the game 
E A E E E 	  //The board (the axis is omitted). "E" stands for no piece at that position, "A" is the symbol of the piece. 
E E A A E 
E E A A E 
E A A A E 
E E E E E 
0                 //The number of turns
START TRACE
1 2		  //The trace of last turn
1 4
END TRACE

2.For the MagicSquare game:
<MagicSquare.txt>:
MagicSquare   //The name of the game 
E E E         //The board (the axis is omitted). "E" stands for no piece at that position
E 3 E 
E E 1 
AVP START //Below stores the available piece list
2
4
5
6
7
8
9
AVP END //Available piece list ends

3.For the MagicSquare game:
<Reversi_Alice_Bob.txt>
Reversi                 //The name of the game 
Alice                   //The name of the first player
Bob                     //The name of the second player
E E E E E E E E         //The board (the axis is omitted). "E" stands for no piece at that position. "X" is the symbol of the first player, "O" is the symbol
E E E E E E E E         //of the second player.
E E E X E E E E 
E E E X X E E E 
E E E X O E E E 
E E E E E E E E 
E E E E E E E E 
E E E E E E E E 
1			//The number of turns for the first player
0			//The number of turns for the second player
Bob			//The name of the current turn

4.For the Checkers game:
<Checkers_Alice_Bob.txt>
Checkers                //The name of the game 
Alice			//The name of the first player
Bob			//The name of the second player
E X E X E X E X 	//The board (the axis is omitted). "E" stands for no piece at that position. "X" is the symbol of the first player, "O" is the symbol
X E X E X E X E 	//of the second player.
E E E X E X E X 
E E X E E E E E 
E E E E E E E E 
O E O E O E O E 
E O E O E O E O 
O E O E O E O E 
1			//The number of turns for the first player
0			//The number of turns for the second player
Bob			//The name of the current turn


***************************************
Test cases for the three games.
***************************************
***************************************
1. Test cases for the NineAlmonds game:
***************************************

After the input "lab5.exe NineAlmonds," we see the following:

The initial state is:

4
3   A A A
2   A A A
1   A A A
0
X 0 1 2 3 4

Please select an almond by specifying its coordinate position or quit.


---------------
case 1:
---------------
check if the input is out of boundary
input: 7,7
output: The input is out of boundary x <=4 y<=4. 
Bad command line, please select an almond by specifying its coordinate position, for example: "0,0" or input "quit" to quit the game.


---------------
case 2:
---------------
input: \n
output: Bad command line, please select an almond by specifying its coordinate position, for example: "0,0" or input "quit" to quit the game.


---------------
case 3:
---------------
input: 2,2,3
output: Bad command line, please select an almond by specifying its coordinate position, for example: "0,0" or input "quit" to quit the game.


---------------
case 4:
---------------
check for invalid movement, if I try to jump from 3,3 to 0,0
Please select a destination by specifying its coordinate position.
input:3,3
Please select a destination by specifying its coordinate position.
input:0,0
This is not valid move

4
3   A A A
2   A A A
1   A A A
0
X 0 1 2 3 4

Enter "continue" to continue to make additional valid jumps with the same almond during this turn and enter "end" to quit this turn or "quit" to quit the game.


---------------
case 5:
---------------
check the valid movement
Please select a almond by specifying its coordinate position or quit.
input : 2,2
Please select a destination by specifying its coordinate position.
input : 2,0

4
3   A A A
2   A   A
1   A   A
0     A
X 0 1 2 3 4

2,2 to 2,0

Enter "continue" to continue to make additional valid jumps with the same almond during this turn and enter "end" to quit this turn or "quit" to quit the game.


---------------
case 6:
---------------
check if the game saves correctly
following the output lines of case 5 we input: quit
output: Do you want to save the game? Enter "yes" to save the game and quit, enter "no" to quit without saving.
input: yes
output: The game has been saved, and the game quit.

Now we open up the game Nine Almonds again and see the following:

The last state before quitting is:

4
3   A A A
2   A   A
1   A   A
0     A
X 0 1 2 3 4

2,2 to 2,0

Enter "continue" to continue to make additional valid jumps with the same almond during this turn and enter "end" to quit this turn or "quit" to quit the game.


---------------
case 7:
---------------
input : continue
output: The current position of last jumped almond is (2,0).
Please select a destination by specifying its coordinate position.
input : 4,2

4
3   A A A
2   A   A A
1   A    
0
X 0 1 2 3 4

2,2 to 2,0 to 4,2

Enter "continue" to continue to make additional valid jumps with the same almond during this turn and enter "end" to quit this turn or "quit" to quit the game.


---------------
case 8:
---------------
input : continue
output :The current position of last jumped almond is (4,2).
Please select a destination by specifying its coordinate position.
input : 2,4

4    A
3   A A
2   A   A
1   A 
0
X 0 1 2 3 4

2,2 to 2,0 to 4,2 to 2,4

Enter "continue" to continue to make additional valid jumps with the same almond during this turn and enter "end" to quit this turn or "quit" to quit the game.


---------------
case 9:
---------------
input: continue
ouput :The current position of last jumped almond is (2,4).
Please select a destination by specifying its coordinate position.
input:0,2

output :
4
3     A
2 A A   A
1   A
0
X 0 1 2 3 4

2,2 to 2,0 to 4,2 to 2,4 to 0,2

Enter "continue" to continue to make additional valid jumps with the same almond during this turn and enter "end" to quit this turn or "quit" to quit the game.


---------------
case 10:
---------------
input: end
Please select a almond by specifying its coordinate position or quit.
1,1
Please select a destination by specifying its coordinate position.
1,3

4
3   A A
2 A     A
1
0
X 0 1 2 3 4

1,1 to 1,3

Enter "continue" to continue to make additional valid jumps with the same almond during this turn and enter "end" to quit this turn or "quit" to quit the game.


---------------
case 11:
---------------
input: end
Please select a almond by specifying its coordinate position or quit.
3,2
Please select a destination by specifying its coordinate position.
1,4

4   A
3   A 
2 A     
1
0
X 0 1 2 3 4

3,2 to 1,4

Enter "continue" to continue to make additional valid jumps with the same almond during this turn and enter "end" to quit this turn or "quit" to quit the game.


---------------
case 12:
---------------
input: continue
ouput :The current position of last jumped almond is (1,4).
Please select a destination by specifying its coordinate position.
input:1,2

output :

4
3
2 A A
1
0
X 0 1 2 3 4

3,2 to 1,4 to 1,2

Enter "continue" to continue to make additional valid jumps with the same almond during this turn and enter "end" to quit this turn or "quit" to quit the game.


---------------
case 13:
---------------
input: end
Please select a almond by specifying its coordinate position or quit.
0,2
Please select a destination by specifying its coordinate position.
2,2

4
3
2      A
1
0
X 0 1 2 3 4

0,2 to 2,2

Congratulations! You finish the game. It takes 5 turns to complete the game.


-----------------------------------------------------------------------------------------------
Check if the file contains valid state of a previously saved version of that particular game.
case 14:
-----------------------------------------------------------------------------------------------
Our program can deal with bad formatting. Below gives a saved file in which there is a blank between the data and there are additional spaces between symbols:
<NineAlmonds.txt>:
NineAlmonds


E A E E E 

E E   A A E 
E E A A E 
E A A A E 
E E E E E 
0
START TRACE
1 2
1 4
END TRACE

Our program can still read the data and gives following output:

The last state before quitting is:

4   A
3     A A
2     A A
1   A A A
0
X 0 1 2 3 4

1,2 to 1,4

Enter "continue" to continue to make additional valid jumps with the same almond during this turn and enter "end" to quit this turn or "quit" to quit the game.


Our approach: We can deal with this because we use istringstream instead of getline to read data.

-----------------------------------------------------------------------------------------------
Check if the file contains valid state of a previously saved version of that particular game.
case 15:
-----------------------------------------------------------------------------------------------
If the saved file has been edited without permission to something like:

<NineAlmonds.txt>:
dfkdfdkf

Our program will initialized the game from beginning, and the output would be:

The initial state is:

4
3   A A A
2   A A A
1   A A A
0
X 0 1 2 3 4

Please select an almond by specifying its coordinate position or quit.

Our approach: We have several check points when reading data. If the first word is not our game name, we will know the file has been edited without permission, and will initialize the game from start.


-----------------------------------------------------------------------------------------------
Check if the file contains valid state of a previously saved version of that particular game.
case 16:
-----------------------------------------------------------------------------------------------
If the saved file has been edited without permission. For example (see below a changed saved file), the symbol of the game piece is changed from "A" to "B" 

<NineAlmonds.txt>:
NineAlmonds
E A E B E 
E E A A E 
E E A A E 
E A A A E 
E E E E E 
0
START TRACE
1 2
1 4
END TRACE

Our program will initialized the game from beginning, and the output would be:

The saved file has been edited without permission.
So, a new game will be initialized.
The initial state is:

4
3   A A A
2   A A A
1   A A A
0
X 0 1 2 3 4

Please select an almond by specifying its coordinate position or quit.

Our approach: We check if the symbol on the board is "A" when reading data.




-----------------------------------------------------------------------------------------------
case 17:
-----------------------------------------------------------------------------------------------
If the game was quit without saving, next time when the program is run, the output would be: 

The initial state is:

4
3   A A A
2   A A A
1   A A A
0
X 0 1 2 3 4

Please select an almond by specifying its coordinate position or quit.

Our approach: We write "NO DATA" in the file if the game is quit without saving. When reading the file,  if the first word is not our game name, we will initialize the game from start.

***************************************
2. Test cases for the MagicSquare game:
***************************************

After the input "lab5.exe MagicSquare," we see the following:

The initial state is:

2
1
0
X 0 1 2

Available pieces: 1 2 3 4 5 6 7 8 9

Please input the coordinate position and the value of the availale piece. For example, "1,1 3" or input "quit" to quit the game.


---------------
case 1:
---------------
After putting several almonds onto the board as instructed, we get the following:

2
1 9
0 4 3 8
X 0 1 2

Available pieces: 1 2 5 6 7

Please input the coordinate position and the value of the availale piece. For example, "1,1 3" or input "quit" to quit the game.


---------------
case 2:
---------------
Now we test if the game can be saved correctly.

input: quit
Do you want to save the game? Enter "yes" to save the game and quit, enter "no" to quit without saving
input: yes
The game has been saved, and the game quit.


---------------
case 3:
---------------
test completion of the game.
We first reload the game and see the following:

The last state before quitting is:

2
1 9
0 4 3 8
X 0 1 2

Available pieces: 1 2 5 6 7

Please input the coordinate position and the value of the availale piece. For example, "1,1 3" or input "quit" to quit the game.

After putting all the remaining almonds onto the board as instructed, we get the following:

2 2 7 6
1 9 5 1
0 4 3 8
X 0 1 2

Available pieces: 

Congratulations! You finish the game. It takes 9 turns to complete the game.

-----------------------------------------------------------------------------------------------
Check if the file contains valid state of a previously saved version of that particular game.
case 4:
-----------------------------------------------------------------------------------------------
Our program can deal with bad formatting. Below gives a saved file in which there is a blank between the data and there are additional spaces between symbols:
<MagicSquare.txt>:
MagicSquare
E E E 

E   2 E 
E E E 
AVP START
1
3
4
5
6
7
8
9
AVP END

Our program can still read the data and gives following output:

The last state before quitting is:

2
1
0
X 0 1 2

Available pieces:

Please input the coordinate position and the value of the available piece. For example: "1,1 3" or input "quit" to quit the game.

Our approach: We can deal with this because we use istringstream instead of getline to read data.


-----------------------------------------------------------------------------------------------
Check if the file contains valid state of a previously saved version of that particular game.
case 5:
-----------------------------------------------------------------------------------------------
If the piece_number on the board in the saved file is changed to some number that is out of range 1 ~ dimension^2, the state is invalid, and our program will initial the game from start.

For example, if the saved file is changed to the following 
<MagicSquare.txt>:
MagicSquare
E E E 
E 20 E 
E E E 
AVP START
1
3
4
5
6
7
8
9
AVP END

Our program will output:

The saved file has been edited without permission.
So, a new game will be initialized.
The initial state is:

2
1
0
X 0 1 2

Available pieces: 1 2 3 4 5 6 7 8 9

Please input the coordinate position and the value of the available piece. For example: "1,1 3" or input "quit" to quit the game.

-----------------------------------------------------------------------------------------------
Check if the file contains valid state of a previously saved version of that particular game.
case 6:
-----------------------------------------------------------------------------------------------
If the piece_number on the board in the saved file is changed to something that is out of range 1 ~ dimension^2, for example, a letter. The state is invalid, and our program will initialize the game from start.

For example, if the saved file is changed to the following 
<MagicSquare.txt>:
MagicSquare
E E E 
E bb E 
E E E 
AVP START
1
3
4
5
6
7
8
9
AVP END

Our program will output:

The saved file has been edited without permission.
So, a new game will be initialized.
The initial state is:

2
1
0
X 0 1 2

Available pieces: 1 2 3 4 5 6 7 8 9

Please input the coordinate position and the value of the available piece. For example: "1,1 3" or input "quit" to quit the game.


***************************************
3. Test cases for the Reversi game:
***************************************

After the input "lab5.exe Reversi Alice Bob," we see the following:

The initial state is:

7
6
5
4       O X
3       X O
2
1
0
X 0 1 2 3 4 5 6 7

Total number of X = 2
Total number of O = 2

Alice's turn, the symbol is X. Please put your game piece by specifying its coordinate position or quit.


---------------
case 1:
---------------
test that a well-formed input makes the program behave correctly.
after the initial screen, input: 4,2
output:

7
6
5
4       O X
3       X X
2         X
1
0
X 0 1 2 3 4 5 6 7

Total number of X = 4
Total number of O = 1

Bob's turn, the symbol is O. Please put your game piece by specifying its coordinate position or quit.


---------------
case 2:
---------------
test that if a position is not valid for putting the gamepiece, then it prompts an error message.
after the case 1 screen, input: 7,7
output: The position is NOT a valid put position, please re-put your game piece by specifying its coordinate position.


---------------
case 3:
---------------
test to make sure that the program captures the bad command line
after the case 2 screen, input: 5,
output: Bad command line, please put your game piece by specifying its coordinate position, for example: "0,0" or input "quit" to quit the game.


---------------
case 4:
---------------
test whether the game can be saved properly.
after the case 3 screen, input: quit
output: Do you want to save the game? Enter "yes" to save the game and quit, enter "no" to quit without saving.
input: yes
output: The game has been saved, and the game quit.

Reload the game. We get the following screen:

The last state before quitting is:

7
6
5
4       O X
3       X X
2         X
1
0
X 0 1 2 3 4 5 6 7

Total number of X = 4
Total number of O = 1

Bob's turn, the symbol is O. Please put your game piece by specifying its coordinate position or quit.


---------------
case 5:
---------------
quit the game and test how the program handles badly formed command lines.
if we input "lab5.exe Reversi" (thus omitting the name of the players), then,

output: Command line error!
Please input "lab5.exe NineAlmonds" or "lab5.exe MagicSquare" or "lab5.exe Reversi Alice Bob."
where Alice is the person in Reversi Game who moves first, and Bob is the person who moves second.


---------------
case 6:
---------------
we reload the game again, and test how the program handles successful completion of the game.

for example, after keep playing the game, one possible scenario of successful completion is the following:

Bob's turn, the symbol is 0. Please put your game piece by specifying its coordinate position or quit.
input: 7,0

7 O O O O O O O O
6 O O X O O O O O
5 O X O X X O O O
4 X X O O X O X O
3 X X O X O X X O  
2 X X O O O O O O
1 X X O O O O O O
0 X X X X X X X O
X 0 1 2 3 4 5 6 7

Total number of X = 27
Total number of O = 37

Bob is the WINNER! Congratulations! Bob took 30 turns to finish the game.


---------------
case 7:
---------------
we also want to check another successful completion case. in this case the game will stop without filling 
the entire board because the board will only have game pieces from one single player.

We will let the players make the following moves:

X - 3,5
O - 2,5
X - 1,5
O - 4,5
X - 5,5
O - 5,4
X - 5,3
O - 5,2
X - 6,1

The final screen will look like:

7 
6 
5   X X X X X
4       X X X
3       X X X  
2           X
1             X
0 
X 0 1 2 3 4 5 6 7

Total number of X = 13
Total number of O = 0

Bob's turn SKIPPED, because there is no valid square to put.

Alice is the WINNER! Congratulations! Alice took 5 turns to finish the game.

** Note that the test shows that the program is able to make skips when no valid move exists.
The program will also stop when the board consists of game pieces of only one player, even if it is not filled.


-----------------------------------------------------------------------------------------------
Check if the file contains valid state of a previously saved version of that particular game.
case 8:
-----------------------------------------------------------------------------------------------
Our program can deal with bad formatting. Below gives a saved file in which there is a blank between the data and there are additional spaces between symbols:
<Reversi_A_B.txt>:

Reversi
A
B
E E E E E E E E 
E E E E E E E E 
E E E X E E E E 

E E E  X X E E E 
E E E X O E E E 
E E E E E E E E 
E E E E E E E E 
E E E E E E E E 
1
0
B


Our program can still read the data and gives following output:

The last state before quitting is:

7
6
5       X
4       X X
3       X O
2
1
0
X 0 1 2 3 4 5 6 7

Total number of X = 4
Total number of O = 1

B's turn, the symbol is O. Please put your game piece by specifying its coordinate position or quit.
Our approach: We can deal with this because we use istringstream instead of getline to read data.


-----------------------------------------------------------------------------------------------
Check if the file contains valid state of a previously saved version of that particular game.
case 9:
-----------------------------------------------------------------------------------------------
If the saved file has been edited without permission. For example (see below a changed saved file), the board shows a symbol other than "O","X" and "E", such as "C". 

<Reversi_A_B.txt>:
Reversi
A
B
E E E E E C E E 
E E E E E E E E 
E E E X E E E E 
E E E X X E E E 
E E E X O E E E 
E E E E E E E E 
E E E E E E E E 
E E E E E E E E 
1
0
B

Our program will initialized the game from beginning, and the output would be:

The saved file has been edited without permission.
So, a new game will be initialized.
The last state before quitting is:

7
6
5
4       O X
3       X O
2
1
0
X 0 1 2 3 4 5 6 7

Total number of X = 2
Total number of O = 2

A's turn, the symbol is X. Please put your game piece by specifying its coordinate position or quit.

Our approach: We check if the symbol on the board is "A" when reading data.


******************************************************************************
******************************************************************************
Extra Credit
******************************************************************************
******************************************************************************

Summarize approach: 
-------------------
Most of the design of the Checkers game is very like the Reversi Game. We used a vector to hold the Checkers game piece. The following functions are very similar with the functions used in the Reversi game. 
virtual bool done();
virtual int prompt(unsigned int &a, unsigned int &b);
virtual void turn();
virtual void print();
virtual int play();
virtual void save_current_state();
virtual void abort_current_state();


Some functions are different.
We wrote the following two functions for checking if the position is valid for putting a valid piece.
virtual bool valid_put_position_black(unsigned int i, unsigned int j, unsigned int m, unsigned int n) 
virtual bool valid_put_position_white(unsigned int i, unsigned int j, unsigned int m, unsigned int n)

We wrote the following two functions for completing the play's turn and change the board according to the rules.
virtual void complete_black_turn(unsigned int i, unsigned int j, unsigned int m, unsigned int n) 
virtual void complete_white_turn(unsigned int i, unsigned int j, unsigned int m, unsigned int n) 

We wrote the following two functions for checking if there is a putting position for white piece.
virtual bool check_available_move_black();
virtual bool check_available_move_white();

We wrote the following two functions for deciding whether the piece on the board should be changed into the King.
virtual void whether_change_into_king(); 

We wrote the following two functions for checking if the current piece can move continuously.
virtual bool check_continuous_move_current_black(unsigned int i, unsigned int j);
virtual bool check_continuous_move_current_white(unsigned int i, unsigned int j);

Please read the comments in the source files to know the details of the implementation.


*********************************
Test cases for the Checkers game:
*********************************
-----------------------------------------------------------------------------
case 1: show the output produced by our program for one run with two players 
-----------------------------------------------------------------------------
We test one complete run of two players:

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
1,5
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
2,4

7   X   X   X   X
6 X   X   X   X
5       X   X   X
4     X
3
2 O   O   O   O
1   O   O   O   O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 12
Total number of White Pieces = 12

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
4,2
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
3,3

7   X   X   X   X
6 X   X   X   X
5       X   X   X
4     X
3       O
2 O   O       O
1   O   O   O   O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 12
Total number of White Pieces = 12

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
2,4
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
4,2

7   X   X   X   X
6 X   X   X   X
5       X   X   X
4     
3       
2 O   O   X   O
1   O   O   O   O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 12
Total number of White Pieces = 11

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
5,1
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
3,3

7   X   X   X   X
6 X   X   X   X
5       X   X   X
4     
3       O    
2 O   O       O
1   O   O       O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 11
Total number of White Pieces = 11

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
3,5
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
2,4

7   X   X   X   X
6 X   X   X   X
5           X   X
4     X
3       O    
2 O   O       O
1   O   O       O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 11
Total number of White Pieces = 11

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
3,3
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
1,5

7   X   X   X   X
6 X   X   X   X
5   O       X   X
4     
3           
2 O   O       O
1   O   O       O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 10
Total number of White Pieces = 11

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
0,6
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
2,4

7   X   X   X   X
6     X   X   X
5           X   X
4     X  
3           
2 O   O       O
1   O   O       O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 10
Total number of White Pieces = 10

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
2,2
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
3,3

7   X   X   X   X
6     X   X   X
5           X   X
4     X  
3       O    
2 O           O
1   O   O       O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 10
Total number of White Pieces = 10

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
2,4
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
4,2

7   X   X   X   X
6     X   X   X
5           X   X
4       
3           
2 O       X   O
1   O   O       O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 10
Total number of White Pieces = 9

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
3,1
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
5,3

7   X   X   X   X
6     X   X   X
5           X   X
4       
3           O
2 O           O
1   O           O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 9
Total number of White Pieces = 9

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
5,5
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
4,4

7   X   X   X   X
6     X   X   X
5               X
4         X
3           O
2 O           O
1   O           O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 9
Total number of White Pieces = 9

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
5,3
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
3,5

7   X   X   X   X
6     X   X   X
5       O       X
4         
3           
2 O           O
1   O           O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 9

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
2,6
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
4,4

7   X   X   X   X
6         X   X
5               X
4         X  
3           
2 O           O
1   O           O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 8

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
0,2
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
1,3

7   X   X   X   X
6         X   X
5               X
4         X  
3   O        
2             O
1   O           O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 8

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
4,6
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
3,5

7   X   X   X   X
6             X
5       X       X
4         X  
3   O        
2             O
1   O           O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 8

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
1,3
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
2,4

7   X   X   X   X
6             X
5       X       X
4     O   X  
3           
2             O
1   O           O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 8

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
3,5
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
1,3

7   X   X   X   X
6             X
5               X
4         X  
3   X        
2             O
1   O           O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 7

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
1,1
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
2,2

7   X   X   X   X
6             X
5               X
4         X  
3   X        
2     O       O
1               O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 7

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
1,3
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
3,1

7   X   X   X   X
6             X
5               X
4         X  
3           
2             O
1       X       O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 6

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
0,0
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
1,1

7   X   X   X   X
6             X
5               X
4         X  
3           
2             O
1   O   X       O
0     O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 6

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
4,4
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
3,3

7   X   X   X   X
6             X
5               X
4           
3       X    
2             O
1   O   X       O
0     O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 6

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
1,1
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
2,2

7   X   X   X   X
6             X
5               X
4           
3       X    
2     O       O
1       X       O
0     O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 6

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
3,3
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
1,1

7   X   X   X   X
6             X
5               X
4           
3           
2             O
1   X   X       O
0     O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 5

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
6,2
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
5,3

7   X   X   X   X
6             X
5               X
4           
3           O
2             
1   X   X       O
0     O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 5

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
1,1
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
0,0

7   X   X   X   X
6             X
5               X
4           
3           O
2             
1       X       O
0 B   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 5

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
2,0
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
1,1

7   X   X   X   X
6             X
5               X
4           
3           O
2             
1   O   X       O
0 B       O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 5

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
0,0
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
2,2

7   X   X   X   X
6             X
5               X
4           
3           O
2     B        
1       X       O
0         O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 4

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
5,3
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
6,4

7   X   X   X   X
6             X
5               X
4             O
3            
2     B        
1       X       O
0         O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 4

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
7,5
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
5,3

7   X   X   X   X
6             X
5               
4             
3           X 
2     B        
1       X       O
0         O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 3

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
7,1
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
6,2

7   X   X   X   X
6             X
5               
4             
3           X 
2     B       O  
1       X       
0         O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 3

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
5,3
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
7,1

7   X   X   X   X
6             X
5               
4             
3           
2     B         
1       X       X
0         O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 2

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
6,0
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
5,1

7   X   X   X   X
6             X
5               
4             
3           
2     B         
1       X   O   X
0         O   
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 2

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
7,1
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
6,0

7   X   X   X   X
6             X
5               
4             
3           
2     B         
1       X   O   
0         O   B
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 2

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
5,1
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
6,2

7   X   X   X   X
6             X
5               
4             
3           
2     B       O   
1       X      
0         O   B
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 2

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
3,1
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
2,0

7   X   X   X   X
6             X
5               
4             
3           
2     B       O   
1             
0     B   O   B
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 2

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
4,0
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
5,1

7   X   X   X   X
6             X
5               
4             
3           
2     B       O   
1           O  
0     B       B
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 2

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
6,0
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
4,2

7   X   X   X   X
6             X
5               
4             
3           
2     B   B   O   
1             
0     B       
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 1

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
6,2
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
5,1

7   X   X   X   X
6             X
5               
4             
3           
2     B   B      
1           O 
0     B       
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 1

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
4,2
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
6,0

7   X   X   X   X
6             X
5               
4             
3           
2     B         
1            
0     B       B
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 8
Total number of White Pieces = 0

Alice is the WINNER! Congratulations! Bob took 20 turns to finish the game.



---------------
case 2:
---------------
test that if a position is not valid for putting the game piece, then it prompts an error message.
after the case 1 screen, input: 0.3
output: The current position is NOT white checker, please re-select a Source by specifying its coordinate position.


---------------
case 3:
---------------
test to make sure that the program captures the bad command line
after the case 2 screen, input: 5,
output: Bad command line, please select a check by specifying its Source position, for example: "0,0" or input "quit" to quit the game.


---------------
case 4:
---------------
test whether the game can be saved properly.
after the case 3 screen, input: quit
output: Do you want to save the game? Enter "yes" to save the game and quit, enter "no" to quit without saving.
input: yes
output: The game has been saved, and the game quit.

Reload the game. We get the following screen:

The last state before quitting is:

7   X   X   X   X
6 X   X   X   X
5       X   X   X
4     X
3
2 O   O   O   O
1   O   O   O   O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 12
Total number of White Pieces = 12

Alice's turn SKIPPED, because there is no valid move.

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.


---------------
case 5:
---------------
quit the game and test how the program handles badly formed command lines.
if we input "lab5.exe Checkers Alice" (thus omitting the name of the players), then,

output: Command line error!
Please input "lab5.exe NineAlmonds" or "lab5.exe MagicSquare" or "lab5.exe Reversi Alice Bob."
where Alice is the person in Reversi Game who moves first, and Bob is the person who moves second.


---------------
case 6:
---------------
we reload the game again, and test whether the program successfully converts "man" to "king".

for example, after keep playing the game, one possible scenario is the following:

7   X   X   X   X
6 X   X   X   X
5       X      
4         X   X
3       O
2 X   O   O   O
1   O   O   O   O
0 O       O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 12
Total number of White Pieces = 11

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
input: 0,2

7   X   X   X   X
6 X   X   X   X
5       X      
4         X   X
3       O
2     O   O   O
1       O   O   O
0 O   B   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 12
Total number of White Pieces = 10

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.

** We can  see that the "X" is converted into "B", therefore the program handles convertion of "man" into "king" properly.

---------------
case 7:
---------------
test whether the program handles successful completion of the game properly.

for example, after keep playing the game, one possible scenario is the following:

7       W
6         W      
5           B
4  
3   
2       
1  
0    
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 1
Total number of White Pieces = 2

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.
input: 4,6
Bob's turn, the symbol is O (white man) or W (white king). Please select a Destination by specifying its coordinate position.
input: 6,4

7       W
6               
5           
4             W
3   
2       
1  
0    
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 0
Total number of White Pieces = 2

Bob is the WINNER! Congratulations! Bob took 36 turns to finish the game.

---------
case 8: 
--------
Our program can deal with bad formatting with the saved file. Below gives a saved file in which there is a blank between the data and there are additional spaces between symbols:

<Checkers_Alicce_Bob.txt>:
Checkers
Alice
Bob
E X E X E X E X 
X E X E X E X E 
E E E X E X E X 

E E X E   E E E E 
E E E E E O E E 
O E O E O E E E 
E O E O E O E O 
O E O E O E O E 
1
1
Alice

Our program can still read the data and gives following output:

The last state before quitting is:

7   X   X   X   X
6 X   X   X   X
5       X   X   X
4     X
3           O
2 O   O   O
1   O   O   O   O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 12
Total number of White Pieces = 12

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source positi

Our approach: We can deal with this because we use istringstream instead of getline to read data.

---------------
case 9:
---------------
Test double jump when circumstances permit.

We first make several moves that ensure double jump is allowable in subsequent moves. 
One of the scenarios is the following:

7   X   X   X   X
6 X   X   X   
5       X   X   X
4     X       O
3   O           O
2     O   O    
1   O       O   O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 11
Total number of White Pieces = 12

Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
input: 7,5
Alice's turn, the symbol is X (black man) or B (black king). Please select a Destination by specifying its coordinate position.
input: 5,3

Then the screen will prompt the following:

7   X   X   X   X
6 X   X   X   
5       X   X   
4     X       
3   O       X   O
2     O   O    
1   O       O   O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 11
Total number of White Pieces = 11

Alice can move the same piece continuously, enter "yes" to move it continuously, enter "no" to quit the 
current turn or enter "quit" to quit the game.
input: yes
output: The current black piece you select is (5,3)
Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.
input: 3,1

output screen:

7   X   X   X   X
6 X   X   X   
5       X   X   
4     X       
3   O           O
2     O       
1   O   X   O   O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Total number of Black Pieces = 11
Total number of White Pieces = 10

Bob's turn, the symbol is O (white man) or W (white king). Please select a checker by specifying its Source position or quit.

** Therefore, we show that the program can now implement double jump successfully.

---------------
case 10:
---------------
Check that the double jump only allows the double-jumpable game piece to move.

For example, in the following screen (from Case 8), we notice that both X's at positions (2,4) and (5,3) can move to eat out a white man,
but only (5,3) can make a double jump.

7   X   X   X   X
6 X   X   X   
5       X   X   
4     X       
3   O       X   O
2     O   O    
1   O       O   O
0 O   O   O   O
X 0 1 2 3 4 5 6 7

Alice can move the same piece continuously, enter "yes" to move it continuously, enter "no" to quit the 
current turn or enter "quit" to quit the game.
input: yes
output: The current black piece you select is (5,3)
Alice's turn, the symbol is X (black man) or B (black king). Please select a checker by specifying its Source position or quit.

If we want to make (2,4) move, we may input: 0,2

The output: This is not valid move. Please re-select a Destination by specifying its coordinate position.

** Therefore, the test shows that the program ensures only the game piece that can double jump is moved in the second jump.





