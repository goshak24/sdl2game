#pragma once
#include "game_object.hpp"
#include "player.hpp"

#include <chrono>

class Enemy : public GameObject 
{
public:
    Enemy(const char* textureSheet, int health, int x, int y); 

    void updateEnemyHealth(bool isHit); 

    void moveEnemy(Player* player); 

    // getters 
    int getHealth() { return health; };  

    // setters 
    int setHealth(int hp) { health = hp; };  

private: 
    std::chrono::steady_clock::time_point lastDamageTime;
    int health = 200; 
}; 