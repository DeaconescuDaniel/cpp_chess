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

bool quit = false;

int mouseX, mouseY;

void drawBoard() {

    Uint32 color;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                color = SDL_MapRGB(windowSurface->format, 238, 238, 210);
            } else {
                color = SDL_MapRGB(windowSurface->format, 118, 150, 86);
            }
            SDL_Rect rect = {100 * j, 100 * i, 100, 100};
            SDL_FillRect(windowSurface, &rect, color);
            SDL_Surface *surf = IMG_Load(
                    B_BISHOP_PATH);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_RenderPresent(renderer);
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
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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
            SDL_RenderClear(renderer);
//            SDL_UpdateWindowSurface(window);
//            SDL_RenderPresent(renderer);
        }
    }

    destroyWindow();
    return 0;
}