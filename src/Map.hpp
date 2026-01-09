#pragma once
#include "game.hpp"

class Map {
    public: 
        Map(); 
        ~Map();

        void loadMap(int arr[20][25]);
        void drawMap(); 

    private:
        SDL_Rect src, dest; // hold source and destination rectangles
        
        SDL_Texture* dirt; 
        SDL_Texture* grass; 
        SDL_Texture* water; 

        int map[20][25]; // holds the map data : defines where to draw which tile type 
}; 