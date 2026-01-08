#include "game.hpp" 
#include "texture_manager.hpp"
#include "game_object.hpp"

GameObject* player;
GameObject* enemy[10];

Game::Game()
: isRunning(false), window(nullptr), renderer(nullptr)
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
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    player = new GameObject("assets/character/idle/tile000.png", renderer, 0, 0);

    for (int i = 0; i < 10; i++) 
    {
        std::string asset {"assets/character/idle/tile00" + std::to_string(i) + ".png"};
        enemy[i] = new GameObject(asset.c_str(), renderer, i*15, i*15);
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::update()
{ 
    // update game objects here -> all game related update functions like player update, enemy update, etc.
    player->Update();
    for (int i = 0; i < 10; i++) 
    {
        enemy[i]->Update();
    }
}

void Game::render()
{
    SDL_RenderClear(this->renderer); // clear the window to the renderer color
    // add stuff to render here: what ever paints first is in the back and everything goes on top.  
    player->Render(this->renderer);
    for (int i = 0; i < 10; i++) {
        enemy[i]->Render(this->renderer);
    }; 
    
    SDL_RenderPresent(this->renderer); // present the updated renderer to the window
}

void Game::clean()
{ 
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    std::cout << "Game Cleaned..." << std::endl;
}  