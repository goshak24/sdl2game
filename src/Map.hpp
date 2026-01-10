#pragma once
#include "game.hpp"

class Map {
    public: 
        Map(); 
        ~Map() = default;

        static void loadMap(int level);
        void drawMap(); 
        static void switchMap(int lvl); 

    private:
        SDL_Rect src, dest; // hold source and destination rectangles
        
        SDL_Texture* dirt; 
        SDL_Texture* grass; 
        SDL_Texture* water; 

        static int map[20][25]; // holds the map data : defines where to draw which tile type 
}; 