// ChessDesign.h
// Author : Zheng Luo
// Modified by Zheng Luo on 04/29/14.
// http://inst.eecs.berkeley.edu/~cs162/sp07/Nachos/chess.shtml

#ifndef CHESS_DESIGN_H
#define CHESS_DESIGN_H
 
class Piece; // just declaration for compiler
class Board; // just declaration for compiler

// Declaration of the History class
class History {
public:
    History(Point f, Point t, Board* b, History *p);
    void SetNext(History *n){};
    void UndoLastMove(){};
    void RedoUndoneMove(){};
private:
    Board *board;
    // the point a piece was moved from
    Point from;
    // the point a piece was moved to
    Point to;
    // remembers what piece was killed
    Piece *killed_piece;
    // history on this move.
    History *next;
    History *prev;
};

// Declaration of the Board class
class Board {
public:
    // creates board with pieces in initial configuration
    Board();
    // delete the piece on the board
    ~Board();
    // return the piece at location p
    Piece* PieceAt(Point p);
    // Set the Piece
    void PlacePieceAt(Piece* piece, Point p);
    // move piece at p1 to p2
    void Move(Point p1, Point p2);
    // move piece at p1 to p2, remembering
    void Move(Point p1, Point p2, Point ep);
    // check to move piece at p1 to p2
    void TryToMove(Point p1, Point p2);
    // check whether can move
    bool CanMove(Point p1, Point p2);
    // get Enpassant
    Point GetEnPassant();
    // set Enpassant
    void SetEnPassant(Point p);
    // get whether can enpassant
    bool GetCanEnPassant();
    // set cab_enpassant
    void SetCanEnPassant(bool flag);
    // get the dimenstion
    unsigned int GetDimenstion();
private:
    Piece*** chess_board;
    History* first_history;
    History* last_history;
    Point en_passant;
    bool can_en_passant;
    unsigned int N;  // board dimension
};

// Declaration of the Piece class
// Here we use the PRIVATE inheritance
// The definition of the chess game_piece
class Piece : private chess_game_piece {
public:
    Piece(Point p, Color c, Board *b, string s);
    virtual ~Piece(){};
    Point GetLocation();
    Color GetColor();
    string GetSymbol();
    void SetLocation(Point p);
    virtual void TryToMove(Point p);
    virtual MoveType CanMove(Point p);
protected:
    Board* board;
};

// THe specific piece of the Pawn piece
class Pawn : public Piece {
public:
    Pawn(Point p, Color c, Board * b, int d, string s);
    virtual void TryToMove(Point p);
    virtual MoveType CanMove(Point p);
private:
    void GetPromotion(Point p);
    int direction;  // 1 for up, -1 for down
    bool can_double_step;
};

// THe specific piece of the Bishop piece
class Bishop : public Piece {
public:
    Bishop(Point p, Color c, Board * b, string s);
    virtual void TryToMove(Point p);
    virtual MoveType CanMove(Point p);
};

// THe specific piece of the Rook piece
class Rook : public Piece {
public:
    Rook(Point p, Color c, Board * b, string s);
    virtual void TryToMove(Point p);
    virtual MoveType CanMove(Point p);
    bool GetCanCastling();
private:
    bool can_castling;
};

// THe specific piece of the Knight piece
class Knight : public Piece {
public:
    Knight(Point p, Color c, Board * b, string s);
    virtual void TryToMove(Point p);
    virtual MoveType CanMove(Point p);
};

// THe specific piece of the King piece
class King : public Piece {
public:
    King(Point p, Color c, Board * b, string s);
    virtual void TryToMove(Point p);
    virtual MoveType CanMove(Point p);
    bool can_castling;
};

// THe specific piece of the Queen piece
class Queen : public Piece {
public:
    Queen(Point p, Color c, Board * b, string s);
    virtual void TryToMove(Point p);
    MoveType CanMove(Point p);
};

#endif