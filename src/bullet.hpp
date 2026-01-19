#pragma once
#include "game_object.hpp"
#include <chrono>

#include <iostream>
#include "player.hpp"

class Bullet : public GameObject 
{
    public:
        Bullet(const char* textureSheet, int x, int y, float vx, float vy); 
        ~Bullet(); 

        void Update(int playerX, int playerY); 
        bool checkCollision(int playerX, int playerY); 
        bool isActive() { return active; };
        void deactivate() { active = false; };

    private:
        bool active = true;
        float posX;  
        float posY;
        float vx;
        float vy;
}; 