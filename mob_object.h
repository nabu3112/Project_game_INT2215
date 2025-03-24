#ifndef _MOB_OBJECT_H
#define _MOB_OBJECT_H

#include <iostream>
#include <cmath>
#include <SDL_image.h>
#include <vector>

#include "base_function.h"
#include "constants.h"
#include "map_object.h"
#include "bullet_object.h"

using namespace std;


struct mob_object_{
    float x_on_map ;
    float y_on_map ;

    float dx=0;
    float dy=0;

    float vector_x_to_main;
    float vector_y_to_main;
    float distance_to_main;

    int hp=5;
    int running_speed=10;
    int attack_speed=5;

    bool attack = 0;
    bool right_with_main=0;
    bool in_radian_of_main = 0;

    int width_sheet;
    int height_sheet;

    int frame_state=1;
    int mob_size;
    float zoom_level;

    vector<bullet_object_> skill;

    SDL_Rect frame_;
    SDL_FRect mob_hitbox;
    SDL_FRect sprite;
    SDL_Texture* texture_mob;
    SDL_Texture* texture_skill;

    Uint32 last_shoot_time =0;

    mob_object_(SDL_Renderer* renderer, int _x_on_map, int _y_on_map, float _zoom_level){
        texture_mob = loadTexture("Image//rotom.png", renderer);
        texture_skill = loadTexture("Image//electro_ball.png", renderer);
        SDL_QueryTexture(texture_mob, NULL, NULL, NULL, &mob_size);

        x_on_map = _x_on_map;
        y_on_map = _y_on_map;

        if(_zoom_level > 0){
            zoom_level = _zoom_level;
            running_speed /= _zoom_level;
            hp*= pow(2,_zoom_level);
        }
    }
    /*~mob_object_(){
        SDL_DestroyTexture(texture_mob);
        texture_mob = NULL;
        SDL_DestroyTexture(texture_skill);
        texture_skill = NULL;
    }*/
    SDL_Rect set_clips_mob();
    void mob_move(map_object_& map_game, const float& x_main,const float& y_main, float& dx_main, float& dy_main, const int& size_main);
    void loadAnimationMob(SDL_Renderer* renderer, const float& x, const float& y);
    void mob_attack(SDL_Renderer* renderer, const float& x_main, const float& y_main, const int& size_main);
    void handle_bullet_move(SDL_Renderer* renderer, const float& x_main, const float& y_main, const SDL_FRect& hitbox_main, int& main_hp, int& main_speed, const int& main_slow_speed, bool& main_is_paralyzed, Uint32& paralyzed_start_time);
};

#endif // _MOB_OBJECT_H
