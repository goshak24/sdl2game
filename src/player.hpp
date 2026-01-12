#pragma once
#include "game_object.hpp"
#include <chrono>

class Player : public GameObject 
{
public:
    Player(const char* textureSheet, int x, int y);

    void handleKeyboardPress(Uint8 event);
    void updateIdle();

private:
    std::chrono::steady_clock::time_point lastMoveTime;

    // idle animation state
    int idleFrame = 0;

    // cached textures (loaded once)
    SDL_Texture* idle0;
    SDL_Texture* idle1;
    SDL_Texture* idle2;
};