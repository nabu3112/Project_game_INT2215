#ifndef _MOB_OBJECT_H
#define _MOB_OBJECT_H

#include <iostream>
#include <cmath>
#include <SDL_image.h>
#include <vector>

#include "base_function.h"
#include "constants.h"
#include "main_character.h"
#include "map_object.h"
#include "bullet_object.h"

using namespace std;

struct mainc;

struct mob_object_{
    float x_on_map = 1700;
    float y_on_map = 500;

    float dx=0;
    float dy=0;

    float vector_x_to_main;
    float vector_y_to_main;
    float distance_to_main;

    int hp=10;
    int running_speed=5;
    int attack_speed=5;

    bool attack = 0;
    bool right_with_main=0;

    int width_sheet;
    int height_sheet;

    int frame_state=1;
    int mob_size;

    vector<bullet_object_> skill;

    SDL_Rect frame_;
    SDL_FRect mob_hitbox;
    SDL_FRect sprite;
    SDL_Texture* texture_mob;
    SDL_Texture* texture_skill;

    Uint32 last_shoot_time =0;

    mob_object_(SDL_Renderer* renderer){
        texture_mob = loadTexture("Image//rottom1.png", renderer);
        texture_skill = loadTexture("Image//electro_ball1.png", renderer);
        SDL_QueryTexture(texture_mob, NULL, NULL, NULL, &mob_size);

    }
    ~mob_object_(){
        SDL_DestroyTexture(texture_mob);
        texture_mob = NULL;
        SDL_DestroyTexture(texture_skill);
        texture_skill = NULL;
    }
    SDL_Rect set_clips_mob();
    void mob_move(map_object_& map_game, const float& x_main,const float& y_main, float& dx_main, float& dy_main);
    void loadAnimationMob(SDL_Renderer* renderer, const float& x, const float& y);
    void mob_attack(SDL_Renderer* renderer, const float& x_main, const float& y_main, const int& size_main);
    void handle_bullet_move(SDL_Renderer* renderer, const float& x_main, const float& y_main, const SDL_FRect& hitbox_main, int& main_hp);
};

#endif // _MOB_OBJECT_H
