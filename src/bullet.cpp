#include "bullet.hpp"
#include <iostream>
#include <cmath> 

Bullet::Bullet(const char* textureSheet, int x, int y, float vx, float vy) 
    :   GameObject(textureSheet, x, y), posX(x), posY(y), vx(vx), vy(vy)
{
}

Bullet::~Bullet() {} 

void Bullet::Update()
{
    // Move bullet every frame
    posX += vx;
    posY += vy;
    
    // Sync with GameObject position so Render() uses updated coords
    setX((int)posX);
    setY((int)posY);
    
    // Call parent Update to sync destRect
    GameObject::Update();
    
    // Deactivate if off-screen
    if (posX < 0 || posX > 800 || posY < 0 || posY > 600)
        active = false;
}