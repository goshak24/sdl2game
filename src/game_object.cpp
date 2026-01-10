#include "game_object.hpp"
#include "texture_manager.hpp"
#include "Map.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y) { 
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
    // movingRight = true;
}

void GameObject::Update() { 
    /** // Toggle direction when reaching (or passing) bounds
    if (xpos >= 500) {
        movingRight = false;
        Map::loadMap(2); 
    } else if (xpos <= 0) {
        movingRight = true;
    }

    // Move horizontally only (bounce between 100 and 500)
    if (movingRight) {
        xpos++;
        ypos++;
    } else {
        xpos--;
        ypos--; 
    } **/ 

    srcRect.h = 128;
    srcRect.w = 128;
    srcRect.x = 0;
    srcRect.y = 0; 

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h; 
}

void GameObject::Render() {
    // Flip horizontally when moving left to show a mirrored sprite 
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject() {
}