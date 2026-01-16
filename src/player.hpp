#pragma once
#include "game_object.hpp"
#include <chrono>
#include <vector>

class Player : public GameObject 
{
public:
    Player(const char* textureSheet, int x, int y);

    void handleKeyboardPress(const Uint8* keystate);
    void updateIdle();

    void updateMove(std::vector<SDL_Texture*>& textures); 

private:
    std::chrono::steady_clock::time_point lastMoveTime;

    // idle animation state
    int idleFrame = 0;
    int walkFrame = 0; 

    std::vector<SDL_Texture*> walkDown;
    std::vector<SDL_Texture*> walkUp;

    // cached textures (loaded once)
    SDL_Texture* idle0;
    SDL_Texture* idle1;
    SDL_Texture* idle2;

    SDL_Texture* walk_down0;
    SDL_Texture* walk_down1;
    SDL_Texture* walk_down2;
    SDL_Texture* walk_down3;

    SDL_Texture* walk_up0;
    SDL_Texture* walk_up1;
    SDL_Texture* walk_up2;
    SDL_Texture* walk_up3;
};