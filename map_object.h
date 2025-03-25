#ifndef _MAP_OBJECT_H
#define _MAP_OBJECT_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <SDL_image.h>

#include "base_function.h"
#include "constants.h"

using namespace std;

struct map_object_{
    float x_map;
    float y_map;

    SDL_FRect map_index;

    int map_width;
    int map_height;

    int level=1;
    int tilemap[60][106];
    //float x_start, y_start, x_end, y_end;
    int tile_x_in_array;
    int tile_y_in_array;

    SDL_Texture* map_layer1;
    SDL_Texture* map_layer2;

    map_object_(SDL_Renderer* renderer){
        map_layer1 = loadTexture("Image//map1_layer1.png", renderer);
        map_layer2 = loadTexture("Image//map1_layer2.png", renderer);
    }

    ~map_object_(){
        SDL_DestroyTexture( map_layer2 );
        map_layer1 = NULL;
        SDL_DestroyTexture( map_layer1 );
        map_layer2 = NULL;
        cout<<2<<endl;
    }

    void init_map_coordinate(const float& x_main, const float& y_main);
    void renderTexture_Map(SDL_Renderer* renderer, int layer);
    void check_to_map(SDL_FRect& hitbox, float& x, float& y, float& dx, float& dy);
};

#endif // _MAP_OBJECT_H
