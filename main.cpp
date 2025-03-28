#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

#include "base_function.h"
#include "constants.h"
#include "main_character.h"
#include "map_object.h"
#include "mob_object.h"
#include "other_on_screen.h"
#include "menu_game.h"
#include "mixer.h"

using namespace std;

const char* WINDOW_TITLE = "game";

Uint32 current_time = SDL_GetTicks();

void handle_mob(SDL_Renderer* renderer, map_object_& map_game, mob_object_& mob, mainc& mcharacter, Mix_Chunk* sound1, Mix_Chunk* sound2)
{
    mob.mob_move(map_game, mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.dx, mcharacter.dy);
    mob.loadAnimationMob(renderer, mcharacter.x_on_map, mcharacter.y_on_map);
    mob.mob_healthbar(renderer);

    current_time = SDL_GetTicks();
    if (current_time > mob.last_shoot_time + 2000)
    {
        mob.mob_attack(renderer, mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.size_frame);
        mob.last_shoot_time = current_time;
    }
    mob.handle_bullet_move(renderer, mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.hitbox, mcharacter.hp
                           , mcharacter.running_speed, mcharacter.slow_speed, mcharacter.is_paralyzed, mcharacter.paralyzed_start_time, sound1, sound2);
}

void init_mob(vector<mob_object_>& all_mob, SDL_Renderer* renderer, SDL_Texture* mob_texture, SDL_Texture* bullet_texture, SDL_Texture* mob_healthbar_texture,const float& x_main, const float& y_main, const int& size_main)
{
    for(int i=0; i<2; i++){
        mob_object_ mob(renderer, mob_texture, bullet_texture, mob_healthbar_texture, mob_coordinates[i][0], mob_coordinates[i][1], 1.5, x_main, y_main, size_main);
        all_mob.push_back(mob);
    }
}

int main(int argc, char *argv[])
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);
    sound all_sound_effect;

    map_object_ map_game(renderer);

    mainc mcharacter(renderer);
    mcharacter.set_clips_stand();
    mcharacter.set_clips_run();
    mcharacter.set_clips_punch();
    mcharacter.set_clips_kick();

    SDL_Texture* mob_texture = loadTexture("Image/rotom.png", renderer);
    SDL_Texture* bullet_texture = loadTexture("Image/electro_ball.png", renderer);
    SDL_Texture* mob_healthbar_texture = loadTexture("Image/mob_healthbar1.png", renderer);

    vector <mob_object_> all_mob;
    init_mob(all_mob, renderer, mob_texture, bullet_texture, mob_healthbar_texture, mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.size_frame);

    mob_object_ mob(renderer, mob_texture, bullet_texture, mob_healthbar_texture, 720, 1824, 4, mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.size_frame);
    all_mob.push_back(mob);

    mcharacter.index_to_win = all_mob.size();

    on_screen_object on_screen(renderer);

    bool running = true;
    bool keys[SDL_NUM_SCANCODES]= {false};
    SDL_Event event;
    Mix_PlayMusic(all_sound_effect.background_music, -1);
    render_start_menu(renderer, event);
    Mix_HaltMusic();
    Mix_PlayMusic(all_sound_effect.in_game_music, -1);

    while(running){
        while(SDL_PollEvent(&event)){
            if( event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_p){
                    pause_game(renderer, event, keys, running);
                }
                keys[event.key.keysym.scancode]= true;
            }else if( event.type == SDL_KEYUP){
                keys[event.key.keysym.scancode]= false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear( renderer );

        mcharacter.main_move(keys, map_game);
        map_game.init_map_coordinate(mcharacter.x_on_map, mcharacter.y_on_map);

        map_game.renderTexture_Map(renderer, 1);

        for(int i =0; i< mcharacter.index_to_win; i++){
            all_mob[i].set_distance_to_main(mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.size_frame);
            if(all_mob[i].in_radian_of_main){
                handle_mob(renderer, map_game, all_mob[i], mcharacter, all_sound_effect.paralyzed_sound, all_sound_effect.basic_bullet_sound);
            }
        }
        if(mcharacter.deal_damage){
            for(int i =0; i< mcharacter.index_to_win; i++){
                if(all_mob[i].in_radian_of_main){
                    mcharacter.attack_to_mob(all_mob[i].mob_hitbox, all_mob[i].hp);
                    if(all_mob[i].hp <= 0){
                        all_mob.erase(all_mob.begin() + i);
                        mcharacter.index_to_win --;
                        i--;
                    }
                }
            }
        }
        if(mcharacter.is_hit == 1){
            Mix_PlayChannel(-1, all_sound_effect.attack_sound, 0);
        }else if(mcharacter.is_hit == 2){
            Mix_PlayChannel(-1, all_sound_effect.attack_to_air_sound, 0);
        }
        mcharacter.is_hit=0;

        if(mcharacter.index_to_win == 0){
            Mix_HaltMusic();
            Mix_PlayMusic(all_sound_effect.win_music, -1);
            mcharacter.index_to_win --;
        }

        mcharacter.playMainAnimation(renderer);
        mcharacter.handle_paralyzed(renderer);
        mcharacter.check_alive();

        map_game.renderTexture_Map(renderer, 2);
        on_screen.render_health_bar(renderer, mcharacter.hp, mcharacter.energy);

        if(mcharacter.pick_up_item(renderer, map_game.item_coordinate, on_screen, keys, event)){
            Mix_PlayChannel(-1, all_sound_effect.pick_up_item_sound, 0);
        }

        SDL_RenderPresent( renderer );
        SDL_Delay(30);
    }

    SDL_DestroyTexture(mob_texture);
    SDL_DestroyTexture(bullet_texture);
    SDL_DestroyTexture(mob_healthbar_texture);
    mob_texture = NULL;
    bullet_texture = NULL;
    mob_healthbar_texture = NULL;

    quitSDL(window, renderer);
    Mix_Quit();

    return 0;
}
