#include <SDL2/SDL.h>
#ifndef CHESS_CPP_CHESS_H
#define CHESS_CPP_CHESS_H

#endif
#define CHESSBOARD_WHITE 0xeeeed2
#define CHESSBOARD_GREEN 0x769656
#define CHESSBOARD_SELECTED 0xbaca44
#define CHESSBOARD_MOVE 0xaaff00
#define CHESSBOARD_TAKE 0xff809b
#define SPLIT_COLOR(color) (Uint8) (color >> 16), (Uint8) (color >> 8), (Uint8) color
#define W_PAWN_PATH R"(..\resources\Chess_plt60.png)"
#define B_PAWN_PATH R"(..\resources\Chess_pdt60.png)"
#define W_BISHOP_PATH R"(..\resources\Chess_blt60.png)"
#define B_BISHOP_PATH R"(..\resources\Chess_bdt60.png)"
#define W_KNIGHT_PATH R"(..\resources\Chess_nlt60.png)"
#define B_KNIGHT_PATH R"(..\resources\Chess_ndt60.png)"
#define W_ROOK_PATH R"(..\resources\Chess_rlt60.png)"
#define B_ROOK_PATH R"(..\resources\Chess_rdt60.png)"
#define W_QUEEN_PATH R"(..\resources\Chess_qlt60.png)"
#define B_QUEEN_PATH R"(..\resources\Chess_qdt60.png)"
#define W_KING_PATH R"(..\resources\Chess_klt60.png)"
#define B_KING_PATH R"(..\resources\Chess_kdt60.png)"

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
    SDL_Rect drawRect;
    Square(SQUARE_COLOR color, SQUARE_STATUS status, PIECE piece, const SDL_Rect &drawRect);
    Square() : initialized(false) {}
    bool isInitialized() const {
        return initialized;
    }
    Square(const Square& other)
            : color(other.color),
              status(other.status),
              piece(other.piece),
              drawRect(other.drawRect),
              initialized(other.initialized)
    {}

    Square& operator=(const Square& other) {
        if (!initialized) {
            color = other.color;
            status = other.status;
            piece = other.piece;
            drawRect = other.drawRect;
            initialized = true;
        } else {
            color = other.color;
            status = other.status;
            piece = other.piece;
            drawRect = other.drawRect;
        }
        return *this;
    }
    void uninitialize() {
        initialized = false;
    }
private:
    bool initialized;

};

void initializeBoard(Square (&board)[8][8]);
const char* piecePath(PIECE piece);
bool hasBlackPiece(const Square& square);
bool hasWhitePiece(const Square& square);