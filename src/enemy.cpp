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

    int dX = player->getX() - getX(); 
    int dY = player->getY() - getY(); 
    int stopRadius = 100; 

    if (std::abs(dX) <= stopRadius && std::abs(dY) <= stopRadius)
    {
        return;
    }

    // Move X direction 
    if (std::abs(dX) > stopRadius)
    {
        setX(getX() + (dX > 0 ? 20 : -20)); // check positive or negative direction 
    }

    // Move Y direction 
    if (std::abs(dY) > stopRadius)
    {
        setY(getY() + (dY > 0 ? 20 : -20)); 
    }
} 