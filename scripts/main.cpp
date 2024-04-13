#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "chess.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *windowSurface = NULL;
SDL_Event currentEvent;
Square boardMatrix[8][8];

bool quit = false;

int mouseX, mouseY;

void drawSquare(Square square) {
    Uint32 color;
    if(square.color==WHITE){
        color=0xeeeed2;
    }else{
        color=0x769656;
    }
    SDL_Surface *surf = IMG_Load(piecePath(square.piece));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer,(Uint8)(color>>16),(Uint8)(color>>8),(Uint8)color,0);
    SDL_RenderDrawRect(renderer,&square.drawRect);
    SDL_RenderFillRect(renderer,&square.drawRect);
    SDL_RenderCopy(renderer, texture, nullptr, &square.drawRect);
    SDL_RenderPresent(renderer);
}

void drawBoard() {
    initializeBoard(boardMatrix);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            drawSquare(boardMatrix[i][j]);
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
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        if (window == NULL) {
            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;
        } else {
            windowSurface = SDL_GetWindowSurface(window);

            if (windowSurface == NULL) {
                std::cout << "Failed to get the window surface: " << SDL_GetError() << std::endl;
                success = false;
            } else {
                SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));

                SDL_UpdateWindowSurface(window);
            }

        }
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout<<"SDL_image could not initialize! SDL_image Error: " << IMG_GetError()<<'\n';
        success = false;
    }
    return success;
}

void destroyWindow() {
    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

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
                }
            }

            if (currentEvent.type == SDL_MOUSEMOTION) {
                if (currentEvent.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }

            }
 //           SDL_RenderClear(renderer);
//            SDL_UpdateWindowSurface(window);
//            SDL_RenderPresent(renderer);
        }
    }

    destroyWindow();
    return 0;
}