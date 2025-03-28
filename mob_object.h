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
    float distance_before_to_main;

    int max_hp=5;
    int hp=5;
    int running_speed=7;

    bool attack = 0;
    bool right_with_main=0;
    bool in_radian_of_main = 0;

    int width_sheet;
    int height_sheet;

    int frame_state=1;
    int mob_size;
    float zoom_level;
    int healthbar_height;

    vector<bullet_object_> skill;

    SDL_Rect frame_;
    SDL_FRect mob_hitbox;
    SDL_FRect sprite;
    SDL_FRect healthbar_frame;
    SDL_FRect blood_healthbar;

    SDL_Texture* texture_mob;
    SDL_Texture* texture_skill;
    SDL_Texture* texture_healthbar;

    Uint32 last_shoot_time =0;

    mob_object_(SDL_Renderer* renderer, SDL_Texture* mob_texture, SDL_Texture* bullet_texture, SDL_Texture* mob_healthbar,
                const float& _x_on_map, const float& _y_on_map, const float& _zoom_level, const float& x_main, const float& y_main, const int& size_main){

        texture_mob = mob_texture;
        texture_skill = bullet_texture;
        texture_healthbar = mob_healthbar;

        SDL_QueryTexture(texture_mob, NULL, NULL, NULL, &mob_size);
        SDL_QueryTexture(texture_healthbar, NULL, NULL, NULL, &healthbar_height);

        x_on_map = _x_on_map;
        y_on_map = _y_on_map;

        healthbar_frame.w = mob_size * _zoom_level;
        healthbar_frame.h = healthbar_height/4 * _zoom_level;
        blood_healthbar.h = healthbar_frame.h;

        if(_zoom_level > 0){
            zoom_level = _zoom_level;
            running_speed /= _zoom_level;
            max_hp *= pow(2,_zoom_level);
            hp = max_hp;
        }

        vector_x_to_main = (x_main + size_main/2) - (x_on_map + mob_size*zoom_level/2);
        vector_y_to_main = (y_main + size_main/2) - (y_on_map + mob_size*zoom_level/2);
        distance_to_main = sqrt( vector_x_to_main*vector_x_to_main + vector_y_to_main*vector_y_to_main );
    }

    SDL_Rect set_clips_mob();
    void set_distance_to_main(const float& x_main, const float& y_main, const int& size_main);
    void loadAnimationMob(SDL_Renderer* renderer, const float& x, const float& y);
    void mob_attack(SDL_Renderer* renderer, const float& x_main, const float& y_main, const int& size_main);
    void handle_bullet_move(SDL_Renderer* renderer, const float& x_main, const float& y_main, const SDL_FRect& hitbox_main
                            , int& main_hp, int& main_speed, bool& main_is_paralyzed, Uint32& paralyzed_start_time, Mix_Chunk* sound1, Mix_Chunk* sound2);
    void mob_healthbar(SDL_Renderer* renderer);
};

#endif // _MOB_OBJECT_H
