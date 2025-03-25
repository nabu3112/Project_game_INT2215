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

struct mainc {
    float x_on_map= 1824;
    float y_on_map= 672;

    float dx=0;
    float dy=0;

    int hp=100;
    int running_speed = 10;
    int slow_speed = 1;
    int base_speed = 10;
    int energy=0;
    int damage_punch = 5;
    int damage_kick = 10;

    SDL_Texture* main_stand;
    SDL_Texture* main_run;
    SDL_Texture* main_punch;
    SDL_Texture* main_kick;
    SDL_Texture* main_win;
    SDL_Texture* texture_now;
    SDL_Texture* paralyzed_texture;

    int size_frame=96;
    int state=0;
    int index_to_win;
    bool left_or_right=1;
    bool is_attacking=0;
    bool punch_or_kick=0;
    bool is_paralyzed = 0;
    bool deal_damage = 0;

    int stand_frame=1;
    int run_frame=1;
    int punch_frame=1;
    int kick_frame=1;
    int win_frame=1;

    int width_stand;
    int width_run;
    int width_punch;
    int width_kick;

    SDL_FRect hitbox;
    SDL_FRect punch_box;
    SDL_FRect kick_box;
    SDL_Rect sprite;
    SDL_Rect frame_;
    SDL_Rect paralyzed_frame;

    SDL_Event event;
    bool keys[SDL_NUM_SCANCODES]= {false};

    Uint32 paralyzed_start_time = 0;
    Uint32 paralyzed_durution = 2000;

    SDL_Rect stand_clip[4];
    SDL_Rect run_clip[6];
    SDL_Rect punch_clip[6];
    SDL_Rect kick_clip[4];
    SDL_Rect win_clip[3];

    mainc(SDL_Renderer* renderer, const int& n){
        main_stand = loadTexture("Image//lucario_stand.png", renderer);
        main_run = loadTexture("Image//lucario_run.png", renderer);
        main_punch = loadTexture("Image//lucario_punch.png", renderer);
        main_kick = loadTexture("Image//lucario_kick.png", renderer);
        main_win = loadTexture("Image//lucario_win.png", renderer);
        paralyzed_texture = loadTexture("Image//paralyzed2.png", renderer);

        SDL_QueryTexture(paralyzed_texture, NULL, NULL, &paralyzed_frame.w, &paralyzed_frame.h);
        paralyzed_frame.x = 72;
        paralyzed_frame.y = 90;

        SDL_QueryTexture(main_stand, NULL, NULL, &width_stand, &sprite.h);
        width_stand/=4;
        SDL_QueryTexture(main_run, NULL, NULL, &width_run, &sprite.h);
        width_run/=6;
        SDL_QueryTexture(main_punch, NULL, NULL, &width_punch, &sprite.h);
        width_punch/=6;
        SDL_QueryTexture(main_kick, NULL, NULL, &width_kick, &sprite.h);
        width_kick/=4;

        sprite.x= SCREEN_WIDTH/2 - size_frame/2;
        sprite.y= SCREEN_HEIGHT/2 - size_frame/2;

        index_to_win = n;
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

    void set_clips_stand();
    void set_clips_run();
    void set_clips_punch();
    void set_clips_kick();
    void set_clips_win();

    void playMainAnimation(SDL_Renderer* renderer);
    bool check_alive();
    void attack_to_mob(SDL_FRect& mob_hitbox, int& mob_hp);
    void render_effect_paralyzed(SDL_Renderer* renderer);
    void handle_paralyzed(SDL_Renderer* renderer);
    void play_win_animation(SDL_Renderer* renderer);
};




#endif // _MAIN_CHARACTER_H


