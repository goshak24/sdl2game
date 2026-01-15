#include "enemy.hpp"

Enemy::Enemy(const char* textureSheet, int health, int x, int y)
    : GameObject(textureSheet, x, y), health(health) // adds the variable for health onto the inherited attributes 
{
    lastDamageTime = std::chrono::steady_clock::now();
}

void Enemy::updateEnemyHealth(bool isHit)
{
    if (!isHit) return;

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - lastDamageTime
    );

    if (elapsed.count() >= 2000) {
        health -= 20;
        lastDamageTime = now;

        if (health < 0)
            health = 0;
    }
}

void Enemy::moveEnemy(Player* player) 
{
    // get player x and y
    // move enemy x and y closer to player x and y (but not too close, within 20 radius)

    std::cout << player->getX() << getX() << std::endl; 

    int playerX = player->getX(); 
    int enemyX = getX(); 


    if (player->getX() - getX() > 100) 
    {
        setX(getX() + 20); 
    }
} 