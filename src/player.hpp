#pragma once
#include "game_object.hpp"

class Player : public GameObject {
    public:
        Player(const char* textureSheet, int x, int y);

        virtual ~Player() = default;  

        void handleKeyboardPress(Uint8 event); 
}; 