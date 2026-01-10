#include "game.hpp" 
#include "texture_manager.hpp"
#include "game_object.hpp"
#include "Map.hpp"
#include "player.hpp" 

Player* player; 
SDL_Renderer* Game::renderer = nullptr;
Map* map; 

Game::Game()
: isRunning(false), window(nullptr)
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0; 

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    } 

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialised!..." << std::endl;

        window = SDL_CreateWindow(
            title,
            xpos,
            ypos,
            width,
            height,
            flags
        );

        if (window) {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer) {
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    player = new Player("assets/character/idle/tile000.png", 0, 0);
    map = new Map(); 
}

void Game::handleEvents()
{
    SDL_Event event; 
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN: 
                player->handleKeyboardPress(event.key.keysym.scancode);  
            default:
                break;
        }
    }
}

void Game::update()
{ 
    // update game objects here -> all game related update functions like player update, enemy update, etc.
    player->Update(); 
}

void Game::render()
{
    SDL_RenderClear(this->renderer); // clear the window to the renderer color

    // add stuff to render here: what ever paints first is in the back and everything goes on top. 
    map->drawMap(); 
    player->Render(); 
    
    SDL_RenderPresent(this->renderer); // present the updated renderer to the window
}

void Game::clean()
{ 
    delete map;
    delete player;

    map = nullptr;
    player = nullptr;

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit(); 
    std::cout << "Game Cleaned..." << std::endl;
}  