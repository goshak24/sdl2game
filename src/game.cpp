#include "game.hpp" 
#include "texture_manager.hpp"
#include "game_object.hpp"
#include "Map.hpp" 
#include "player.hpp"
#include "enemy.hpp" 
#include <iostream> 
#include "bullet.hpp"

Player* player; 
SDL_Renderer* Game::renderer = nullptr;
Map* map; 
Enemy* enemy;  
const Uint8 *keystate = SDL_GetKeyboardState(NULL); 

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
    Map::loadMap(1);  // Load level 1 once during initialization
    enemy = new Enemy("assets/character/idle/tile010.png", 200, 20, 25);
    enemy->setPlayer(player);
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
                player->handleKeyboardPress(keystate); 
            default:
                break;
        } 
    }
}

void Game::update()
{  
    player->Update(); 
    player->updateIdle(); 
    player->updateBullets(); 
    player->renderBullets(); 
    
    enemy->moveEnemy(player); 
    enemy->shootAtPlayer(player);
    enemy->updateBullets();
    enemy->Update(); 
    
    bool enemyHit = true;
    enemy->updateEnemyHealth(enemyHit);  
}

void Game::render()
{
    SDL_RenderClear(this->renderer);

    map->drawMap(); 
    map->switchMap(int(map->getCurrentLevel()) + 1); 
    
    player->Render(); 
    player->renderBullets(); 
    enemy->Render(); 
    enemy->renderBullets();
    
    SDL_RenderPresent(this->renderer);
}

void Game::clean()
{ 
    delete map;
    delete player;
    delete enemy; 

    map = nullptr;
    player = nullptr;
    enemy = nullptr; 

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit(); 
    std::cout << "Game Cleaned..." << std::endl;
}