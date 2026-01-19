#include "bullet.hpp"
#include <iostream>
#include <cmath> 
#include <thread>
#include <iostream>

Bullet::Bullet(const char* textureSheet, int x, int y, float vx, float vy) 
    :   GameObject(textureSheet, x, y), posX(x), posY(y), vx(vx), vy(vy)
{
}

Bullet::~Bullet() {} 

void Bullet::Update(int playerX, int playerY)
{
    // Move bullet every frame
    posX += vx;
    posY += vy;
    
    // Sync with GameObject position so Render() uses updated coords
    setX((int)posX);
    setY((int)posY); 

    if (checkCollision(playerX, playerY))
    {
        active = false;
    }

    // Call parent Update to sync destRect
    GameObject::Update();
    
    // Deactivate if off-screen
    if (posX < 0 || posX > 800 || posY < 0 || posY > 600) 
        active = false; 
} 

bool Bullet::checkCollision(int playerX, int playerY)
{
    int dx = getX() - playerX;
    int dy = getY() - playerY;

    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 40.0f)
    {
        auto now = std::chrono::steady_clock::now();

        if (!hitTimerStarted)
        {
            hitStart = now;  
            hitTimerStarted = true;
        }

        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - hitStart
        ).count();

        if (elapsed >= 200)
            return true;
    }
    else
    {
        // reset if player leaves collision range
        hitTimerStarted = false;
    }

    return false;
} 