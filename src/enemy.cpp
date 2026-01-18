#include "enemy.hpp"
#include <cmath>
#include "bullet.hpp"

Enemy::Enemy(const char* textureSheet, int health, int x, int y)
    : GameObject(textureSheet, x, y), health(health) 
{
    lastDamageTime = std::chrono::steady_clock::now();
    lastShootTime = std::chrono::steady_clock::now();
}

Enemy::~Enemy()
{
    for (auto bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
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
    int dX = player->getX() - getX(); 
    int dY = player->getY() - getY(); 
    int stopRadius = 100; 

    if (std::abs(dX) <= stopRadius && std::abs(dY) <= stopRadius)
    {
        return;
    }

    if (std::abs(dX) > stopRadius)
    {
        setX(getX() + (dX > 0 ? 20 : -20)); 
    }

    if (std::abs(dY) > stopRadius)
    {
        setY(getY() + (dY > 0 ? 20 : -20)); 
    }
}

void Enemy::shootAtPlayer(Player* player)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastShootTime);

    // Shoot every 500ms
    if (elapsed.count() < 500)
        return;

    float playerX = player->getX();
    float playerY = player->getY();
    float enemyX = getX();
    float enemyY = getY();

    float dx = playerX - enemyX;
    float dy = playerY - enemyY;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance == 0) return;

    float speed = 5.0f;
    float vx = (dx / distance) * speed;
    float vy = (dy / distance) * speed;

    bullets.push_back(new Bullet("assets/bullet.png", enemyX + 40, enemyY + 20, vx, vy));
    lastShootTime = now;
}

void Enemy::updateBullets()
{
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        (*it)->Update();
        if (!(*it)->isActive()) {
            delete *it;
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
}

void Enemy::renderBullets()
{
    for (auto bullet : bullets) {
        bullet->Render();
    }
} 