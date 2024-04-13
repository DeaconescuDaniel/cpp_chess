#include <SDL2/SDL.h>
#ifndef CHESS_CPP_CHESS_H
#define CHESS_CPP_CHESS_H

#endif

#define W_PAWN_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_plt60.png)"
#define B_PAWN_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_pdt60.png)"
#define W_BISHOP_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_blt60.png)"
#define B_BISHOP_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_bdt60.png)"
#define W_KNIGHT_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_nlt60.png)"
#define B_KNIGHT_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_ndt60.png)"
#define W_ROOK_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_rlt60.png)"
#define B_ROOK_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_rdt60.png)"
#define W_QUEEN_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_qlt60.png)"
#define B_QUEEN_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_qdt60.png)"
#define W_KING_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_klt60.png)"
#define B_KING_PATH R"(C:\Users\bests\OneDrive\Desktop\Extra\chess_cpp\resources\Chess_kdt60.png)"

typedef enum{
    WHITE,
    BLACK
}SQUARE_COLOR;

typedef enum{
    CLEAR,
    SELECTED,
    POTENTIAL_MOVE,
    POTENTIAL_TAKE,
}SQUARE_STATUS;

typedef enum{
    NONE,
    W_PAWN,
    W_BISHOP,
    W_KNIGHT,
    W_ROOK,
    W_QUEEN,
    W_KING,
    B_PAWN,
    B_BISHOP,
    B_KNIGHT,
    B_ROOK,
    B_QUEEN,
    B_KING
}PIECE;


class Square{
public:
    SQUARE_COLOR color;
    SQUARE_STATUS  status;
    PIECE piece;
    int drawx;
    int drawy;

    void drawSquare(Square square);

};

void drawPiece(PIECE piece);
