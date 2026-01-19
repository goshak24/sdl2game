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

Player::~Player() {
    for (auto bullet : playerBullets) {
        delete bullet;
    }
    playerBullets.clear();
}

void Player::handleKeyboardPress(const Uint8* keystate) 
{
    bool moved = false;

    if (keystate[SDL_SCANCODE_W]) {
        setY(getY() - 10);
        setFacing(2); 
        updateMove(walkUp);
        moved = true;
    }

    if (keystate[SDL_SCANCODE_S]) {
        setY(getY() + 10);
        setFacing(0); 
        updateMove(walkDown);
        moved = true;
    }

    if (keystate[SDL_SCANCODE_A]) {
        setFacing(1); 
        setX(getX() - 10);
        moved = true;
    }

    if (keystate[SDL_SCANCODE_D]) {
        setFacing(3); 
        setX(getX() + 10);
        moved = true;
    }

    if (keystate[SDL_SCANCODE_E]) {
        shootBullet(keystate); 
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

void Player::shootBullet(const Uint8* keystate)
{
    float speed = 5.0f; 
    float vx = 0.0f;
    float vy = 0.0f;

    // Check for vertical movement (W = Up, S = Down)
    if (keystate[SDL_SCANCODE_W]) {
        vy = -speed;  // Up
    }
    if (keystate[SDL_SCANCODE_S]) {
        vy = speed;   // Down
    }

    // Check for horizontal movement (A = Left, D = Right)
    if (keystate[SDL_SCANCODE_A]) {
        vx = -speed;  // Left
    }
    if (keystate[SDL_SCANCODE_D]) {
        vx = speed;   // Right
    }

    // Normalize diagonal movement so it's not faster than cardinal directions
    if (vx != 0.0f && vy != 0.0f) {
        vx *= 0.707f;  // 1/sqrt(2) ≈ 0.707
        vy *= 0.707f;
    }

    // If no direction keys pressed, use last facing direction
    if (vx == 0.0f && vy == 0.0f) {
        switch(facingDirection) {
            case 0:  // Down
                vy = speed;
                break;
            case 1:  // Left
                vx = -speed;
                break;
            case 2:  // Up
                vy = -speed;
                break;
            case 3:  // Right
                vx = speed;
                break;
        }
    }

    playerBullets.push_back(new Bullet("assets/bullet.png", getX()+20, getY() + 20, vx, vy)); // creates a pointer to bullet object because of "new" keyword 
}

void Player::updateBullets()
{ 
    for (auto it = playerBullets.begin(); it != playerBullets.end(); ) {
        (*it)->Update(0, 0);
        if (!(*it)->isActive()) {
            delete *it;
            it = playerBullets.erase(it);
        } else {
            ++it;
        }
    }
}

void Player::renderBullets() 
{
    for (auto bullet : playerBullets)
    {
        bullet->Render(); 
    }
}