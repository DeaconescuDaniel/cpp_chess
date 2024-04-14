#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "chess.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;


SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Surface *windowSurface = nullptr;
SDL_Event currentEvent;
Square boardMatrix[8][8];

bool quit = false;
bool whiteTurn = true;
int mouseX, mouseY;
Square selectedSquare = Square();


void drawSquare(Square square) {
    Uint32 color;
    switch (square.status) {
        case CLEAR:
            switch (square.color) {
                case WHITE:
                    color = CHESSBOARD_WHITE;
                    break;
                default:
                    color = CHESSBOARD_GREEN;
                    break;
            }
            break;
        case SELECTED:
            color = CHESSBOARD_SELECTED;
            break;
        case POTENTIAL_MOVE:
            color = CHESSBOARD_MOVE;
            break;
        case POTENTIAL_TAKE:
            color = CHESSBOARD_TAKE;
            break;
        default:
            break;
    }

    SDL_Surface *surf = IMG_Load(piecePath(square.piece));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, SPLIT_COLOR(color), 0);
    SDL_RenderDrawRect(renderer, &square.drawRect);
    SDL_RenderFillRect(renderer, &square.drawRect);
    SDL_RenderCopy(renderer, texture, nullptr, &square.drawRect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(surf);
}

void selectSquare(int mouseX, int mouseY) {
    int i = mouseY / 100, j = mouseX / 100;
    if (!selectedSquare.isInitialized()) {
        if (hasWhitePiece( boardMatrix[i][j]) && whiteTurn) {
            selectedSquare = boardMatrix[i][j];
            selectedSquare.status = SELECTED;
            drawSquare(selectedSquare);
        } else if (hasBlackPiece( boardMatrix[i][j]) && !whiteTurn) {
            selectedSquare = boardMatrix[i][j];
            selectedSquare.status = SELECTED;
            drawSquare(selectedSquare);
        }
    } else {
        if (whiteTurn && (hasBlackPiece(boardMatrix[i][j]) || boardMatrix[i][j].piece == NONE) && boardMatrix[i][j].status!=SELECTED) {
            PIECE piece = selectedSquare.piece;
            selectedSquare.status = CLEAR;
            selectedSquare.piece = NONE;
            drawSquare(selectedSquare);
            boardMatrix[i][j] = boardMatrix[i][j];
            boardMatrix[i][j].piece = piece;
            drawSquare(boardMatrix[i][j]);
            selectedSquare.uninitialize();
            whiteTurn = !whiteTurn;
        } else if (!whiteTurn && (hasWhitePiece(boardMatrix[i][j]) || boardMatrix[i][j].piece == NONE) && boardMatrix[i][j].status!=SELECTED) {
            PIECE piece = selectedSquare.piece;
            selectedSquare.status = CLEAR;
            selectedSquare.piece = NONE;
            drawSquare(selectedSquare);
            selectedSquare = boardMatrix[i][j];
            boardMatrix[i][j].status = CLEAR;
            boardMatrix[i][j].piece = piece;
            drawSquare(boardMatrix[i][j]);
            selectedSquare.uninitialize();
            whiteTurn = !whiteTurn;
        }
        return;
    }
}


void drawBoard() {
    initializeBoard(boardMatrix);
    for (auto &i: boardMatrix) {
        for (const auto &j: i) {
            drawSquare(j);
        }
    }
}

bool initWindow() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL initialization failed" << std::endl;
        success = false;
    } else {
        window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        if (window == nullptr) {
            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;
        } else {
            windowSurface = SDL_GetWindowSurface(window);

            if (windowSurface == nullptr) {
                std::cout << "Failed to get the window surface: " << SDL_GetError() << std::endl;
                success = false;
            } else {
                SDL_FillRect(windowSurface, nullptr, SDL_MapRGB(windowSurface->format, 255, 255, 255));

                SDL_UpdateWindowSurface(window);
            }

        }
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << '\n';
        success = false;
    }
    return success;
}

void destroyWindow() {
    //Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    //Quit SDL
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (!initWindow()) {
        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }
    drawBoard();

    while (!quit) {
        if (SDL_WaitEvent(&currentEvent) != 0) {
            if (currentEvent.type == SDL_QUIT) {
                quit = true;
            }

            if (currentEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (currentEvent.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                    selectSquare(mouseX, mouseY);
                }
            }

            if (currentEvent.type == SDL_MOUSEMOTION) {
                if (currentEvent.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }

            }
        }
    }

    destroyWindow();
    return 0;
}