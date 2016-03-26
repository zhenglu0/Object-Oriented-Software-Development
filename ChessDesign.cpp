// ChessBoardPiece.cpp
// Author : Zheng Luo
// Modified by Zheng Luo on 04/29/14.
// http://inst.eecs.berkeley.edu/~cs162/sp07/Nachos/chess.shtml

#include "OtherFunctions.h"
#include "GameBase.h"
#include "ChessDesign.h"

#include <cmath>
#include <iostream>
#include <string>

// Implementation of the History class
History::History(Point f, Point t, Board* b, History *p)
{
    board = b;
    from = f;
    to = t;
    killed_piece = NULL;
    prev = next = NULL;
}

// Implementation of the Board class
Board::Board()
:en_passant(Point(x_empty,y_empty)),can_en_passant(false),N(8)
{
    first_history = last_history = NULL;

    // Allocate memory for the chess_board
    chess_board = new Piece** [N];
    for (unsigned int i = 0; i < N; i++)
        chess_board[i] = new Piece* [N];

    // Initialize chess_board piece to NULL
    for (unsigned int i = 0; i < N; i++)
        for (unsigned int j = 0; j < N; j++)
            chess_board[i][j] = NULL;
    
    // Initialize chess board with pieces
    chess_board[0][0] = new Rook  (Point(0,0), black, this, "R");
    chess_board[0][1] = new Knight(Point(0,1), black, this, "N");
    chess_board[0][2] = new Bishop(Point(0,2), black, this, "B");
    chess_board[0][3] = new Queen (Point(0,3), black, this, "Q");
    chess_board[0][4] = new King  (Point(0,4), black, this, "K");
    chess_board[0][5] = new Bishop(Point(0,5), black, this, "B");
    chess_board[0][6] = new Knight(Point(0,6), black, this, "N");
    chess_board[0][7] = new Rook  (Point(0,7), black, this, "R");

    for (unsigned int i = 0; i < N; i++)
        chess_board[1][i] = new Pawn(Point(1,i), black, this, 1, "P");

    chess_board[7][0] = new Rook  (Point(7,0), white, this, "r");
    chess_board[7][1] = new Knight(Point(7,1), white, this, "n");
    chess_board[7][2] = new Bishop(Point(7,2), white, this, "b");
    chess_board[7][3] = new Queen (Point(7,3), white, this, "q");
    chess_board[7][4] = new King  (Point(7,4), white, this, "k");
    chess_board[7][5] = new Bishop(Point(7,5), white, this, "b");
    chess_board[7][6] = new Knight(Point(7,6), white, this, "n");
    chess_board[7][7] = new Rook  (Point(7,7), white, this, "r");

    for (unsigned int i = 0; i < N; i++)
        chess_board[6][i] = new Pawn(Point(6,i), white, this, -1, "p");
}

Board::~Board()
{
    for (unsigned int i = 0; i < N; i++)
        delete [] chess_board[i];
    delete [] chess_board;
}

Piece* Board::PieceAt(Point p)
{
    return chess_board[p.x][p.y];
}

 // Set the Piece
void Board::PlacePieceAt(Piece* piece, Point p)
{
    chess_board[p.x][p.y] = piece;
}

void Board::Move(Point p1, Point p2)
{
    Move(p1, p2, Point());
}

// This method moves the piece occupying p1 to p2,
// without any check as to whether the move is legal
void Board::Move(Point p1, Point p2, Point ep)
{
    //add the move from p1 to p2 to the history;
    //en_passant = ep;
    //if there is a piece at p2
    if (chess_board[p2.x][p2.y] != NULL)
        delete chess_board[p2.x][p2.y];

    //set location p2 on the board to point to the piece that is at p1 now;
    chess_board[p2.x][p2.y] = chess_board[p1.x][p1.y];
    chess_board[p2.x][p2.y]->SetLocation(p2);

    //set location p1 to NULL
    chess_board[p1.x][p1.y] = NULL;
}

void Board::TryToMove(Point p1, Point p2)
{
    // If you don't move this ENPASSANT turn 
    // We can not move it next time
    if (PieceAt(p1) != NULL &&
        PieceAt(p1)->CanMove(p2) != ESCAPE)
    {
        PieceAt(p1)->TryToMove(p2);
        can_en_passant = false;  
    }
    else
    {
        PieceAt(p1)->TryToMove(p2);
    }
}

bool Board::CanMove(Point p1, Point p2)
{
    if (PieceAt(p1) != NULL &&
        PieceAt(p1)->CanMove(p2) != ILLEGAL)
        return true;

    return false;
}

Point Board::GetEnPassant()
{
    return en_passant;
}

void Board::SetEnPassant(Point p)
{
    en_passant = p;
}

bool Board::GetCanEnPassant()
{
    return can_en_passant;
}

void Board::SetCanEnPassant(bool flag)
{
    can_en_passant = flag;
}

unsigned int Board::GetDimenstion()
{
    return N;
}

// Implementation of the Piece class
Piece::Piece(Point p, Color c, Board *b, string s)
:chess_game_piece(p.x,p.y,c,s),board(b){}

Point Piece::GetLocation()
{
    return Point(x,y);
}

Color Piece::GetColor()
{
    return color;
}

string Piece::GetSymbol()
{
    return symbol;
}

void Piece::SetLocation(Point p)
{
    x = p.x;
    y = p.y;
}

void Piece::TryToMove(Point p)
{
    // get the current location
    int current_x = GetLocation().x;
    int current_y = GetLocation().y;

    board->Move(Point(current_x,current_y), p);
}

// returns ILLEGAL for illegal moves, ENPASSANT
// when the move kills a pawn by the en passant rule
MoveType Piece::CanMove(Point p)
{
    // p is on the board
    if (p.x < board->GetDimenstion() && 
        p.y < board->GetDimenstion())
    {
        // there is no piece at p
        if (board->PieceAt(p) == NULL)
            return NORMAL;
        if (board->GetEnPassant() == p)
            return ENPASSANT;
        // the color of the piece at point p is different
        if (board->PieceAt(p)->GetColor() != GetColor())
            return NORMAL;
    }
    return ILLEGAL;
}

// Implementation of the Pawn class
// redefine CanMove according the rules of pawn movement
Pawn::Pawn(Point p, Color c, Board * b, int d, string s)
:Piece(p,c,b,s),direction(d),can_double_step(true) {}

// moves the piece to p only if the move is legal
// kills the en passant pawn if necessary
void Pawn::TryToMove(Point p)
{
    if (CanMove(p) != ILLEGAL) 
    {
        // get the current location
        int current_x = GetLocation().x;
        int current_y = GetLocation().y;

        // get the difference
        int dx = p.x - current_x;
        int dy = p.y - current_y;

        // get the direction
        int direction_x = (dx == 0) ? 0 : abs(dx) / dx; 

        if (CanMove(p) == ENPASSANT)
        {
            // kill pawn
            if (dy < 0)
            {
                delete board->PieceAt(Point(current_x,current_y-1));
                board->PlacePieceAt(NULL,Point(current_x,current_y-1));
            }
            else
            {
                delete board->PieceAt(Point(current_x,current_y+1));
                board->PlacePieceAt(NULL,Point(current_x,current_y+1));                
            }
        }

        if (CanMove(p) == ESCAPE)
        {
            board->SetEnPassant(Point(p.x-direction_x,p.y));
            board->SetCanEnPassant(true);
        }   

        if (CanMove(p) == PROMOTION)
        {
            GetPromotion(Point(current_x,current_y));
        }  
        can_double_step = false;
        board->Move(Point(current_x,current_y), p);
    }
}

MoveType Pawn::CanMove(Point p)
{
    if(Piece::CanMove(p) == ILLEGAL)
        return ILLEGAL;

    // get the current location
    int current_x = GetLocation().x;
    int current_y = GetLocation().y;

    // get the difference
    int dx = p.x - current_x;
    int dy = p.y - current_y;

    if(dx == direction) 
    { 
        // if we're killing diagonally or 
        // we move one space forward
        if ( (abs(dy) == 1 && 
              board->PieceAt(p) != NULL &&
              GetColor() != board->PieceAt(p)->GetColor() ) ||
              (dy == 0 && 
               board->PieceAt(p) == NULL) )
        {
            if ((dx > 0 && p.x == board->GetDimenstion() - 1) ||
                (dx < 0 && p.x == 0))
                return PROMOTION;                
            else 
                return NORMAL;
        }
        
        // if the enpassant happens
        if ( abs(dy) == 1 && 
             board->GetEnPassant() == p &&
             board->GetCanEnPassant() )
            return ENPASSANT;
    }

    // the double step move
    if (can_double_step &&
        dx == 2 * direction && 
        dy == 0 && 
        board->PieceAt(p) == NULL &&
        board->PieceAt(Point(current_x + direction, current_y)) == NULL)
    {
        // check the probably enpassant position see if there are 
        // pawns of different color are next to this piece
        if ( ( p.y > 0 && board->PieceAt(Point(p.x,p.y-1)) != NULL &&
               ( board->PieceAt(Point(p.x,p.y-1))->GetSymbol() == "P" ||
               board->PieceAt(Point(p.x,p.y-1))->GetSymbol() == "p") &&
               board->PieceAt(Point(p.x,p.y-1))->GetColor() != GetColor() ) ||
             ( p.y < board->GetDimenstion() -1 && 
                board->PieceAt(Point(p.x,p.y+1)) != NULL &&
               ( board->PieceAt(Point(p.x,p.y+1))->GetSymbol() == "P" ||
               board->PieceAt(Point(p.x,p.y+1))->GetSymbol() == "p") &&
               board->PieceAt(Point(p.x,p.y+1))->GetColor() != GetColor() ) )
            return ESCAPE;

        return DOUBLESTEP;
    }
    
    return ILLEGAL;
}

void Pawn::GetPromotion(Point p)
{
    while (true) 
    {
        cout << "Please type the which piece you want the pawn "
                "be promoted to Q means Queen, N mean Knight, "
                "B mean Bishop, R means Rook.\n";
        
        string s; // Temp virable to read command line data
        getline(cin, s);
        char select = s[0];
        Piece *piece = NULL;
        Color c = board->PieceAt(p)->GetColor();
        // check the option
        switch (select) 
        {
            case 'Q':
                cout << "Promoted to Queen !!!\n";
                s = (c == black) ? "Q" : "q";
                piece = new Queen(p, c, board, s);
                delete board->PieceAt(p);
                board->PlacePieceAt(piece,p);
                return;
            case 'N':
                cout << "Promoted to Knight !!!\n";
                s = (c == black) ? "N" : "n";
                piece = new Knight(p, c, board, s);
                delete board->PieceAt(p);
                board->PlacePieceAt(piece,p);
                return;
            case 'B':
                cout << "Promoted to Bishop !!!\n";
                s = (c == black) ? "B" : "b";
                piece = new Bishop(p, c, board, s);
                delete board->PieceAt(p);
                board->PlacePieceAt(piece,p);
                return;
            case 'R':
                cout << "Promoted to Rook !!!\n";
                s = (c == black) ? "R" : "r";
                piece = new Rook(p, c, board, s);
                delete board->PieceAt(p);
                board->PlacePieceAt(piece,p);
                return;            
            default:
                break;
          }

        cout << "Invalid input, please try again" << endl;
    }    
}

// Implementation of the Bishop class
Bishop::Bishop(Point p, Color c, Board * b, string s)
:Piece(p,c,b,s) {}

void Bishop::TryToMove(Point p)
{
    if (CanMove(p) != ILLEGAL) 
        board->Move(Point(GetLocation().x,GetLocation().y), p);
}

MoveType Bishop::CanMove(Point p)
{
    if(Piece::CanMove(p) == ILLEGAL)
        return ILLEGAL;

    // get the current location
    int current_x = GetLocation().x;
    int current_y = GetLocation().y;

    // get the difference
    int dx = p.x - current_x;
    int dy = p.y - current_y;

    // get the direction
    int direction_x = abs(dx) / dx;
    int direction_y = abs(dy) / dy;

    // same distance in x and y dirs
    if (abs(dx) == abs(dy)) 
    {
        // no pieces between location and p
        while (Point(current_x + direction_x,
                     current_y + direction_y) != p) 
        {
            if (board->PieceAt(Point(current_x + direction_x,
                                     current_y + direction_y)) != NULL)
                return ILLEGAL;

            // update the current x and y
            current_x += direction_x;
            current_y += direction_y;
        }

        return NORMAL;
    }

    return ILLEGAL;
}

// Implementation of the Rook class
Rook::Rook(Point p, Color c, Board * b, string s)
:Piece(p,c,b,s), can_castling(true) {}

void Rook::TryToMove(Point p)
{
    if (CanMove(p) != ILLEGAL) 
    {
        can_castling = false;
        board->Move(Point(GetLocation().x,GetLocation().y), p);
    }
}

MoveType Rook::CanMove(Point p)
{
    if(Piece::CanMove(p) == ILLEGAL)
        return ILLEGAL;

    // get the current location
    int current_x = GetLocation().x;
    int current_y = GetLocation().y;

    // get the difference
    int dx = p.x - current_x;
    int dy = p.y - current_y;

    // get the direction
    int direction_x = (dx == 0) ? 0 : abs(dx) / dx; 
    int direction_y = (dy == 0) ? 0 : abs(dy) / dy;

    // only moves in x or y direction
    if (dx == 0 || dy == 0) 
    {
        // no pieces between location and p
        while (Point(current_x + direction_x,
                     current_y + direction_y) != p) 
        {
            if (board->PieceAt(Point(current_x + direction_x,
                                     current_y + direction_y)) != NULL)
                return ILLEGAL;

            // update the current x and y
            current_x += direction_x;
            current_y += direction_y;
        }
        
        return NORMAL;
    }

    return ILLEGAL;
}

bool Rook::GetCanCastling()
{
    return can_castling;
}

// Implementation of the Knight class
Knight::Knight(Point p, Color c, Board * b, string s)
:Piece(p,c,b,s) {}

void Knight::TryToMove(Point p)
{
    if (CanMove(p) != ILLEGAL) 
        board->Move(Point(GetLocation().x,GetLocation().y), p); 
}

MoveType Knight::CanMove(Point p)
{
    if(Piece::CanMove(p) == ILLEGAL)
        return ILLEGAL;

    // get the difference
    int dx = p.x - GetLocation().x;
    int dy = p.y - GetLocation().y;

    // move one step, L shape or 
    // killing a piece of different color
    if ( (abs(dx) == 2 && abs(dy) == 1) || 
         (abs(dx) == 1 && abs(dy) == 2) )
        return NORMAL;
    
    return ILLEGAL;
}

// Implementation of the King class
King::King(Point p, Color c, Board * b, string s)
:Piece(p,c,b,s), can_castling(true) {}

void King::TryToMove(Point p)
{
    if (CanMove(p) != ILLEGAL) 
    {
        // get the current location
        int current_x = GetLocation().x;
        int current_y = GetLocation().y;

        if (CanMove(p) == CASTLE)
        {
            int dy = p.y - GetLocation().y;
            int direction_y = (dy == 0) ? 0 : abs(dy) / dy;

            if (direction_y > 0)
                board->Move(Point(current_x,7), Point(current_x,5));
            else
                board->Move(Point(current_x,0), Point(current_x,3));
        }   

        can_castling = false;
        board->Move(Point(current_x,current_y), p);
    }
}

MoveType King::CanMove(Point p)
{
    if(Piece::CanMove(p) == ILLEGAL)
        return ILLEGAL;

    // get the current location
    int current_x = GetLocation().x;
    int current_y = GetLocation().y;

    int dx = p.x - current_x;
    int dy = p.y - current_y;

    //int direction_x = (dx == 0) ? 0 : abs(dx) / dx;
    int direction_y = (dy == 0) ? 0 : abs(dy) / dy;

    // move one step, L or 
    // killing a piece of different color
    if ( (abs(dx) == 0 && abs(dy) == 1) || 
         (abs(dx) == 1 && abs(dy) == 0) ||
         (abs(dx) == 1 && abs(dy) == 1) )
        return NORMAL;
    // check if the move is the castling
    if (can_castling && 
        (abs(dx) == 0 && abs(dy) == 2))
    {
        // if the king moves right
        if (direction_y > 0)
            if (dynamic_cast<Rook*>(board->PieceAt(Point(current_x,7)))
                                    ->GetCanCastling()     &&
                board->PieceAt(Point(current_x,6)) == NULL &&
                board->PieceAt(Point(current_x,5)) == NULL)
                return CASTLE;
        
        // if the king moves left
        if (direction_y < 0)
            if (dynamic_cast<Rook*>(board->PieceAt(Point(current_x,0)))
                                    ->GetCanCastling()     &&
                board->PieceAt(Point(current_x,1)) == NULL &&
                board->PieceAt(Point(current_x,2)) == NULL &&
                board->PieceAt(Point(current_x,3)) == NULL)
                return CASTLE;
    }
    
    return ILLEGAL;
}

// Implementation of the Queen class
Queen::Queen(Point p, Color c, Board * b, string s)
:Piece(p,c,b,s) {}

void Queen::TryToMove(Point p)
{
    if (CanMove(p) != ILLEGAL) 
        board->Move(Point(GetLocation().x,GetLocation().y), p);
}

MoveType Queen::CanMove(Point p)
{
    if(Piece::CanMove(p) == ILLEGAL)
        return ILLEGAL;

    // get the current location
    int current_x = GetLocation().x;
    int current_y = GetLocation().y;

    // get the difference
    int dx = p.x - current_x;
    int dy = p.y - current_y;

    // get the direction
    int direction_x = (dx == 0) ? 0 : abs(dx) / dx; 
    int direction_y = (dy == 0) ? 0 : abs(dy) / dy;

    // only moves in x or y direction
    // same distance in x and y dirs
    if (dx == 0 || dy == 0 ||
        abs(dx) == abs(dy))
    {
        // no pieces between location and p
        while (Point(current_x + direction_x,
                     current_y + direction_y) != p) 
        {
            if (board->PieceAt(Point(current_x + direction_x,
                                     current_y + direction_y)) != NULL)
                return ILLEGAL;

            // update the current x and y
            current_x += direction_x;
            current_y += direction_y;
        }
        
        return NORMAL;
    }

    return ILLEGAL;
}

