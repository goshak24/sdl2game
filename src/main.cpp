#include "SDL.h"
#include "game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[])
{
    const int FPS = 60; 
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime; 

    game = new Game();
    game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        printf("IMG_Init failed: %s\n", IMG_GetError());
    } else {
        printf("SDL_image initialized: %d\n", IMG_Init(0)); // shows supported flags
    } 
    
    while (game->running()) {
        frameStart = SDL_GetTicks();

        frameTime = SDL_GetTicks() - frameStart; // time per frame in milliseconds 
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    delete game;
    return 0;
} 