#include "player.hpp"
#include "texture_manager.hpp" 

Player::Player(const char* textureSheet, int x, int y)
    : GameObject(textureSheet, x, y)
{
    lastMoveTime = std::chrono::steady_clock::now();

    // Load idle textures ONCE - cached during the initialisation 
    idle0 = TextureManager::LoadTexture("assets/character/idle/tile000.png");
    idle1 = TextureManager::LoadTexture("assets/character/idle/tile003.png");
    idle2 = TextureManager::LoadTexture("assets/character/idle/tile002.png");

    walk_down0 = TextureManager::LoadTexture("assets/character/moving/walk/tile000.png");
    walk_down1 = TextureManager::LoadTexture("assets/character/moving/walk/tile001.png");
    walk_down2 = TextureManager::LoadTexture("assets/character/moving/walk/tile002.png");
    walk_down3 = TextureManager::LoadTexture("assets/character/moving/walk/tile003.png");

    walk_up0 = TextureManager::LoadTexture("assets/character/moving/walk/tile018.png");
    walk_up1 = TextureManager::LoadTexture("assets/character/moving/walk/tile019.png");
    walk_up2 = TextureManager::LoadTexture("assets/character/moving/walk/tile020.png");
    walk_up3 = TextureManager::LoadTexture("assets/character/moving/walk/tile021.png");

    walkDown = {
        walk_down0,
        walk_down1,
        walk_down2,
        walk_down3
    };

    walkUp = {
        walk_up0,
        walk_up1,
        walk_up2,
        walk_up3
    };
}    

void Player::handleKeyboardPress(const Uint8* keystate) 
{
    bool moved = false;

    if (keystate[SDL_SCANCODE_W]) {
        setY(getY() - 10);
        updateMove(walkUp);
        moved = true;
    }

    if (keystate[SDL_SCANCODE_S]) {
        setY(getY() + 10);
        updateMove(walkDown);
        moved = true;
    }

    if (keystate[SDL_SCANCODE_A]) {
        setX(getX() - 10);
        moved = true;
    }

    if (keystate[SDL_SCANCODE_D]) {
        setX(getX() + 10);
        moved = true;
    }

    if (moved) 
    { 
        // reset idle animation when moving
        idleFrame = 0;
    }
}

void Player::updateIdle() 
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::seconds>(now - lastMoveTime);

    if (elapsed.count() >= 0.05) 
    {   
        setTex(idle0);
    }

    // after 2 seconds → idle frame 1
    if (elapsed.count() >= 4 && idleFrame == 0) 
    {
        idleFrame = 1;
        setTex(idle1);
    }

    // after 4 seconds → idle frame 2
    else if (elapsed.count() >= 6 && idleFrame == 1) 
    {
        idleFrame = 2;
        setTex(idle2);
    }
} 

void Player::updateMove(std::vector<SDL_Texture*>& textures)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime);

    if (elapsed.count() > 150)
    {
        walkFrame = (walkFrame + 1) % textures.size(); // keeps frames less than texture size 
        setTex(textures[walkFrame]);
        lastMoveTime = now;
    }
} 