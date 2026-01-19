#pragma once
#include "game_object.hpp"
#include <chrono>
#include "Map.hpp"

#include <iostream>
class Player; 

class Bullet : public GameObject 
{
    public:
        Bullet(const char* textureSheet, int x, int y, float vx, float vy); 
        ~Bullet(); 

        void Update(int playerX, int playerY); 
        bool checkCollision(int playerX, int playerY); 
        bool isActive() { return active; };
        void deactivate() { active = false; };

        float getX() { return posX; };
        float getY() { return posY; }; 

    private:
        bool active = true;
        std::chrono::steady_clock::time_point hitStart;
        bool hitTimerStarted = false;
        float posX;  
        float posY;
        float vx;
        float vy;
}; 