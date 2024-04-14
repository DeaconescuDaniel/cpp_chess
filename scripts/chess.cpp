#include "chess.h"
#include <SDL2/SDL.h>


Square::Square(SQUARE_COLOR color, SQUARE_STATUS status, PIECE piece, const SDL_Rect &drawRect) : color(color),
                                                                                                  status(status),
                                                                                                  piece(piece),
                                                                                                  drawRect(drawRect),
                                                                                                  initialized(true){}


const char *piecePath(PIECE piece) {
    switch (piece) {
        case W_PAWN:
            return W_PAWN_PATH;
        case W_BISHOP:
            return W_BISHOP_PATH;
        case W_KNIGHT:
            return W_KNIGHT_PATH;
        case W_ROOK:
            return W_ROOK_PATH;
        case W_QUEEN:
            return W_QUEEN_PATH;
        case W_KING:
            return W_KING_PATH;
        case B_PAWN:
            return B_PAWN_PATH;
        case B_BISHOP:
            return B_BISHOP_PATH;
        case B_KNIGHT:
            return B_KNIGHT_PATH;
        case B_ROOK:
            return B_ROOK_PATH;
        case B_QUEEN:
            return B_QUEEN_PATH;
        case B_KING:
            return B_KING_PATH;
        default:
            return "";
    }
}

void initializeBoard(Square (&board)[8][8]) {
    SQUARE_COLOR color;
    PIECE piece;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                color = BLACK;
            } else {
                color = WHITE;
            }
            SDL_Rect rect = {100 * j, 100 * i, 100, 100};
            switch (i) {
                case 0:
                    switch (j) {
                        case 0:
                        case 7:
                            piece = B_ROOK;
                            break;
                        case 1:
                        case 6:
                            piece = B_KNIGHT;
                            break;
                        case 2:
                        case 5:
                            piece = B_BISHOP;
                            break;
                        case 3:
                            piece = B_QUEEN;
                            break;
                        case 4:
                            piece = B_KING;
                            break;
                        default:
                            piece = NONE;
                    }
                    break;
                case 1:
                    piece = B_PAWN;
                    break;
                case 6:
                    piece = W_PAWN;
                    break;
                case 7:
                    switch (j) {
                        case 0:
                        case 7:
                            piece = W_ROOK;
                            break;
                        case 1:
                        case 6:
                            piece = W_KNIGHT;
                            break;
                        case 2:
                        case 5:
                            piece = W_BISHOP;
                            break;
                        case 3:
                            piece = W_QUEEN;
                            break;
                        case 4:
                            piece = W_KING;
                            break;
                        default:
                            piece = NONE;
                    }
                    break;
                default:
                    piece = NONE;
            }
            board[i][j] = Square(color, CLEAR, piece, rect);

        }
    }

}


bool hasWhitePiece(const Square& square) {
    switch (square.piece) {
        case W_PAWN:
        case W_BISHOP:
        case W_KNIGHT:
        case W_ROOK:
        case W_QUEEN:
        case W_KING:
            return true;
        default:
            return false;
    }
}

bool hasBlackPiece(const Square& square) {
    switch (square.piece) {
        case B_PAWN:
        case B_BISHOP:
        case B_KNIGHT:
        case B_ROOK:
        case B_QUEEN:
        case B_KING:
            return true;
        default:
            return false;
    }
}