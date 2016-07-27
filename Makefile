#
# Makefile for Games
# Modified by Zheng Luo on 03/25/14.

##############################################################
# Compiler and flags to use
##############################################################

CXX       = g++
CXXFLAGS  = -g -Wall -Werror -std=c++11 

##############################################################
# You shouldn't have to change anything below this line.
##############################################################

GAMES_EXE  = Games
GAMES_OBJS = Games.o GameBase.o \
			 CheckersGame.o ChessGame.o ChessDesign.o \
			 NineAlmondsGame.o MagicSquareGame.o ReversiGame.o \
			 TicTacToeBase.o TicTacToeGame.o TicTacToeState.o \
			 OtherFunctions.o

###

$(GAMES_EXE): $(GAMES_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(GAMES_OBJS)

clean:
	rm -f $(GAMES_EXE) $(GAMES_OBJS)


###

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

###		
			
CheckersGame.o: CheckersGame.cpp CheckersGame.h \
				OtherFunctions.cpp OtherFunctions.h \
				GameBase.cpp GameBase.h 

ChessGame.o: ChessGame.cpp ChessGame.h \
			 ChessDesign.cpp ChessDesign.h \
			 OtherFunctions.cpp OtherFunctions.h \
			 GameBase.cpp  GameBase.h

NineAlmondsGame.o: NineAlmondsGame.cpp NineAlmondsGame.h \
			 	   OtherFunctions.cpp OtherFunctions.h \
			       GameBase.cpp  GameBase.h

MagicSquareGame.o: MagicSquareGame.cpp MagicSquareGame.h \
				   OtherFunctions.cpp OtherFunctions.h \
				   GameBase.cpp GameBase.h 

ReversiGame.o: ReversiGame.cpp ReversiGame.h \
			   OtherFunctions.cpp OtherFunctions.h \
			   GameBase.cpp GameBase.h

TicTacToeBase.o: TicTacToeBase.cpp TicTacToeBase.h

TicTacToeGame.o: TicTacToeBase.cpp TicTacToeBase.h \
				 TicTacToeState.cpp TicTacToeState.h \
				 TicTacToeGame.cpp TicTacToeGame.h \
				 OtherFunctions.cpp OtherFunctions.h \
				 GameBase.cpp GameBase.h

TicTacToeState.o: TicTacToeState.cpp TicTacToeState.h

OtherFunctions.o: OtherFunctions.cpp OtherFunctions.h

GameBase.o: GameBase.cpp GameBase.h \
			OtherFunctions.cpp OtherFunctions.h \
			CheckersGame.cpp CheckersGame.h \
			ChessGame.cpp ChessDesign.cpp ChessGame.h ChessDesign.h \
			NineAlmondsGame.cpp NineAlmondsGame.h \
			MagicSquareGame.cpp MagicSquareGame.h \
			ReversiGame.cpp ReversiGame.h \
			TicTacToeGame.cpp TicTacToeBase.cpp TicTacToeState.cpp \
			TicTacToeGame.h TicTacToeBase.h TicTacToeState.h

Games.o: Games.cpp \
		 GameBase.cpp GameBase.h \
		 OtherFunctions.cpp OtherFunctions.h \
		 CheckersGame.cpp CheckersGame.h \
		 ChessGame.cpp ChessDesign.cpp ChessGame.h ChessDesign.h \
		 NineAlmondsGame.cpp NineAlmondsGame.h \
		 MagicSquareGame.cpp MagicSquareGame.h \
		 ReversiGame.cpp ReversiGame.h \
		 TicTacToeGame.cpp TicTacToeBase.cpp TicTacToeState.cpp \
		 TicTacToeGame.h TicTacToeBase.h TicTacToeState.h
