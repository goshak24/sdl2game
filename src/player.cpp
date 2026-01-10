#include "player.hpp" 

Player::Player(const char* textureSheet, int x, int y)
    : GameObject(textureSheet, x, y)
{
}; 

void Player::handleKeyboardPress(Uint8 event) {
    switch (event) {
        case SDL_SCANCODE_W: 
            setY(getY() - 10); 
            break; 
        case SDL_SCANCODE_S: 
            setY(getY() + 10); 
            break; 
        case SDL_SCANCODE_A: 
            setX(getX() + 10); 
            break; 
        case SDL_SCANCODE_D: 
            setX(getX() - 10); 
            break;
        default: 
            break;
        }
}