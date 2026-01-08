#include "game_object.hpp"
#include "texture_manager.hpp"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y) {
    renderer = ren; 
    objTexture = TextureManager::LoadTexture(texturesheet, ren);
    xpos = x;
    ypos = y;
}

void GameObject::Update() {
    xpos++;
    ypos++;

    srcRect.h = 128;
    srcRect.w = 128;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void GameObject::Render(SDL_Renderer* ren) {
    SDL_RenderCopy(ren, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject() {
}