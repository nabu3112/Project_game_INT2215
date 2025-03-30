#ifndef _BULLET_OBJECT_H
#define _BULLET_OBJECT_H

#include <SDL_image.h>
#include "base_function.h"
#include "constants.h"

struct bullet_object_{
    float x_bullet_on_map;
    float y_bullet_on_map;

    float dx=0;
    float dy=0;

    float direction_bullet_x;
    float direction_bullet_y;

    int speed=5;
    int damage=3;

    int state_frame=1;
    int bullet_size;
    int width_bullet_frame;
    int height_bullet_frame;
    float zoom_level;

    SDL_Rect frame_;
    SDL_FRect hitbox;
    SDL_FRect sprite;

    SDL_Texture* bullet_texture;
    bullet_object_(SDL_Renderer* renderer, SDL_Texture* bullet_texture_mob, const float& x_mob , const float& y_mob, const int& mob_size, const float& vector_xmob_to_main, const float& vector_ymob_to_main, const float& _zoom_level){
        bullet_texture = bullet_texture_mob;
        SDL_QueryTexture(bullet_texture, NULL, NULL, NULL, &bullet_size);

        x_bullet_on_map = x_mob + mob_size*_zoom_level/2 ;
        y_bullet_on_map = y_mob + mob_size*_zoom_level/2 ;
        hitbox = {x_bullet_on_map, y_bullet_on_map, float(x_bullet_on_map + bullet_size), float(y_bullet_on_map + bullet_size)};

        direction_bullet_x = vector_xmob_to_main;
        direction_bullet_y = vector_ymob_to_main;
        if(_zoom_level > 0){
            zoom_level = _zoom_level/2;
            damage *= zoom_level;
        }
    }

    SDL_Rect set_clips_bullet();
    void play_bullet_animation(SDL_Renderer* renderer, const float& x_mob , const float& y_mob,const float& x_main, const float& y_main, const float& mob_size);
    void bullet_move();
    bool check_bullet_to_map();
    bool daim_on_main(const SDL_FRect& main_hitbox, int& main_hp, int& main_speed, bool& main_is_paralyzed, Uint32& paralyzed_start_time, Mix_Chunk* sound1, Mix_Chunk* sound2);
};
#endif // _BULLET_OBJECT_H
