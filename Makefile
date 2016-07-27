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
                OtherFunctions.cpp OtherFunctions.h GameBase.h

ChessGame.o: ChessGame.cpp ChessGame.h \
             ChessDesign.h OtherFunctions.h GameBase.h

NineAlmondsGame.o: NineAlmondsGame.cpp NineAlmondsGame.h \
                   OtherFunctions.h GameBase.h

MagicSquareGame.o: MagicSquareGame.cpp MagicSquareGame.h \
                   OtherFunctions.h GameBase.h

ReversiGame.o: ReversiGame.cpp ReversiGame.h \
               OtherFunctions.h GameBase.h

TicTacToeBase.o: TicTacToeBase.cpp TicTacToeBase.h

TicTacToeGame.o: TicTacToeBase.cpp TicTacToeBase.h \
                 TicTacToeState.h TicTacToeGame.h OtherFunctions.h GameBase.h

TicTacToeState.o: TicTacToeState.cpp TicTacToeState.h

OtherFunctions.o: OtherFunctions.cpp OtherFunctions.h

GameBase.o: GameBase.cpp GameBase.h \
            OtherFunctions.h CheckersGame.h ChessGame.h NineAlmondsGame.h MagicSquareGame.h ReversiGame.h TicTacToeGame.h

Games.o: Games.cpp GameBase.h
