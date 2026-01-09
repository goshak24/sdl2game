#include "Map.hpp"
#include "texture_manager.hpp"

int lvl1[20][25] = { // array map for level 1 
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,0,1,1,1,1},
    {1,1,1,1,0,2,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1},
    {1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,2,0,1,1,1,1,1},
    {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1}, 
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,0,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1}, 
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,2,0,1,1,0,0,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,2,0,0,1,1,0,0,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,2,0}, 
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,0,1,1,1,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1}, 
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,0,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1}, 
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
};

Map::Map()
{
    // Load texture images with texture manager 
    dirt = TextureManager::LoadTexture("assets/dirt.png"); // 0 
    grass = TextureManager::LoadTexture("assets/grass.png"); // 1
    water = TextureManager::LoadTexture("assets/water.png"); // 2

    Map::loadMap(lvl1); 

    // set source rectangles 

    src.x = src.y = 0; // double assign 
    src.w = src.h = 32; 
    dest.w = dest.h = 32; 

    dest.x = dest.y = 0; // this is changed on every draw anyway 
}

void Map::loadMap(int arr[20][25])
{
    // replace global map with our passed array 
    for (int row = 0; row < 20; row++) {
        for (int column = 0; column < 25; column++) {
            map[row][column] = arr[row][column]; // map replacing 
        }
    }  
}

void Map::drawMap() 
{
    int type = 0; 
    for (int row = 0; row < 20; row++) {
        
        for (int column = 0; column < 25; column++) {
            type = map[row][column]; // get row column type 

            // when row and column are 0 draw top left, then move 32 pixels on every increment for destination from the source 
            dest.x = column * 32; 
            dest.y = row * 32; 

            switch (type) { // load textures 
                case 0: 
                    TextureManager::Draw(dirt, src, dest); 
                    break; 
                case 1: 
                    TextureManager::Draw(grass, src, dest); 
                    break; 
                case 2:
                    TextureManager::Draw(water, src, dest); 
            } 
        }
    } 
} 