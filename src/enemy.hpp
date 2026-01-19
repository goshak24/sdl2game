#pragma once
#include "game_object.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include <chrono>
#include <vector>

class Enemy : public GameObject 
{
public:
    Enemy(const char* textureSheet, int health, int x, int y); 
    ~Enemy();

    void updateEnemyHealth(bool isHit); 
    void moveEnemy(Player* player); 
    void shootAtPlayer(Player* player);
    void setPlayer(Player* player);
    void updateBullets();
    void renderBullets();

    // getters 
    int getHealth() { return health; };  

    // setters 
    void setHealth(int hp) { health = hp; };  

private: 
    std::chrono::steady_clock::time_point lastDamageTime;
    std::chrono::steady_clock::time_point lastShootTime;
    std::vector<Bullet*> bullets;
    int health = 200;
    Player* playerPtr = nullptr; 
}; 