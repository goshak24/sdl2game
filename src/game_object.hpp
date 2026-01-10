#pragma once
#include "game.hpp"

class GameObject {
public:
    GameObject(const char* textureSheet, int x, int y);
    ~GameObject();

    void Update();

    void Render(); 

    // Setters
    void setX(int x) { xpos = x; }
    void setY(int y) { ypos = y; }

    // Getter
    int getX() const { return xpos; }
    int getY() const { return ypos; }
    
private:
    int xpos;
    int ypos;
    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect; 
    // bool movingRight;
};