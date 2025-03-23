#ifndef _MAIN_CHARACTER_H
#define _MAIN_CHARACTER_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>

using namespace std;

#include "constants.h"
#include "base_function.h"
#include "map_object.h"
#include "mob_object.h"

struct mob_object_;

struct mainc {
    float x_on_map= 1824;
    float y_on_map= 672;

    float dx=0;
    float dy=0;

    int hp=100;
    int running_speed=10;
    int attacking_speed=10;
    int energy=0;
    int daim_punch = 5;
    int daim_kick = 10;

    SDL_Texture* main_stand;
    SDL_Texture* main_run;
    SDL_Texture* main_punch;
    SDL_Texture* main_kick;
    SDL_Texture* texture_now;

    int size_frame=96;
    int state=0;
    bool left_or_right=1;
    bool is_attacking=0;

    int stand_frame=1;
    int run_frame=1;
    int punch_frame=1;
    int kick_frame=1;

    SDL_FRect hitbox;
    SDL_FRect punch_box;
    SDL_FRect kick_box;
    SDL_Rect sprite;
    SDL_Rect frame_;

    SDL_Event event;
    bool keys[SDL_NUM_SCANCODES]= {false};

    mainc(SDL_Renderer* renderer){
        main_stand = loadTexture("Image//lucario_stand.png", renderer);
        main_run= loadTexture("Image//lucario_run.png", renderer);
        main_punch= loadTexture("Image//lucario_punch.png", renderer);
        main_kick= loadTexture("Image//lucario_kick.png", renderer);
    }

    ~mainc(){
        SDL_DestroyTexture(main_stand);
        main_stand = NULL;
        SDL_DestroyTexture(main_run);
        main_run = NULL;
        SDL_DestroyTexture(main_punch);
        main_punch=NULL;
        SDL_DestroyTexture(main_kick);
        main_kick=NULL;
    }

    void main_move(bool& running, map_object_& map_game);
    void check_to_map();

    SDL_Rect set_clips_stand();
    SDL_Rect set_clips_run();
    SDL_Rect set_clips_punch();
    SDL_Rect set_clips_kick();

    void playMoveAnimation(SDL_Renderer* renderer);
    void playAttackAnimation(SDL_Renderer* renderer, map_object_& map_game, mob_object_& mob, Uint32& current_time);
    bool check_alive();
};




#endif // _MAIN_CHARACTER_H


