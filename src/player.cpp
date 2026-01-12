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
}

void Player::handleKeyboardPress(Uint8 event) 
{
    bool moved = false;

    switch (event) 
    {
        case SDL_SCANCODE_W:
            setY(getY() - 10);
            moved = true;
            break;
        case SDL_SCANCODE_S:
            setY(getY() + 10);
            moved = true;
            break;
        case SDL_SCANCODE_A:
            setX(getX() - 10);
            moved = true;
            break;
        case SDL_SCANCODE_D:
            setX(getX() + 10);
            moved = true;
            break;
        default:
            break;
    }

    if (moved) 
    {
        lastMoveTime = std::chrono::steady_clock::now();

        // reset idle animation when moving
        idleFrame = 0;
        setTex(idle0);
    }
}

void Player::updateIdle() 
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::seconds>(now - lastMoveTime);

    // after 2 seconds → idle frame 1
    if (elapsed.count() >= 2 && idleFrame == 0) 
    {
        idleFrame = 1;
        setTex(idle1);
    }

    // after 4 seconds → idle frame 2
    else if (elapsed.count() >= 4 && idleFrame == 1) 
    {
        idleFrame = 2;
        setTex(idle2);
    }
} 