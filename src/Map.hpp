#pragma once
#include "game.hpp"
#include <iostream> 
#include<cstdlib>

class Map {
    public: 
        Map(); 
        ~Map() = default;

        static Map* getInstance(); 

        static void loadMap(int level);
        void drawMap(); 
        static void switchMap(int lvl); 
        static void setRandomMap();
        int getCurrentLevel() { return currentLevel; }; 

    private:
        SDL_Rect src, dest; // hold source and destination rectangles
        
        SDL_Texture* dirt; 
        SDL_Texture* grass; 
        SDL_Texture* water; 

        int currentLevel = 1; // tracks which level is currently loaded

        static int map[20][25]; // holds the map data : defines where to draw which tile type
        static Map* instance; // singleton instance
}; 