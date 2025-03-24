#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "base_function.h"
#include "constants.h"
#include "main_character.h"
#include "map_object.h"
#include "mob_object.h"
#include "other_on_screen.h"

using namespace std;

const char* WINDOW_TITLE = "game";

Uint32 current_time = SDL_GetTicks();

void handle_mob(SDL_Renderer* renderer, map_object_& map_game, mob_object_& mob, mainc& mcharacter)
{
    mob.mob_move(map_game, mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.dx, mcharacter.dy, mcharacter.size_frame);
    mob.loadAnimationMob(renderer, mcharacter.x_on_map, mcharacter.y_on_map);

    current_time = SDL_GetTicks();
    if (current_time > mob.last_shoot_time + 2000)
    {
        mob.mob_attack(renderer, mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.size_frame);
        mob.last_shoot_time = current_time;
    }
    mob.handle_bullet_move(renderer, mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.hitbox, mcharacter.hp, mcharacter.running_speed, mcharacter.slow_speed, mcharacter.is_paralyzed, mcharacter.paralyzed_start_time);
}

void init_mob(vector<mob_object_>& all_mob, SDL_Renderer* renderer)
{
    for(int i=0; i<2; i++){
        mob_object_ mob(renderer, mob_coordinates[i][0], mob_coordinates[i][1], 1.5);
        all_mob.push_back(mob);

    }
}

int main(int argc, char *argv[])
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);

    mainc mcharacter(renderer);
    map_object_ map_game(renderer);

    vector <mob_object_> all_mob;
    init_mob(all_mob, renderer);

    mob_object_ mob(renderer, 720, 1824, 4);
    all_mob.push_back(mob);

    health_bar_object health_bar(renderer);

    bool running = true;

    while(running){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear( renderer );

        mcharacter.main_move(running, map_game);
        map_game.init_map_coordinate(mcharacter.x_on_map, mcharacter.y_on_map);

        map_game.renderTexture_Map(renderer, 1);

        for(int i=0; i<all_mob.size(); i++){

            mcharacter.attack_to_mob(all_mob[i].mob_hitbox, all_mob[i].hp);
            handle_mob(renderer, map_game, all_mob[i], mcharacter);
            if(all_mob[i].hp <= 0){
                all_mob.erase(all_mob.begin() + i);
                if(i!= (all_mob.size() - 1) ) i--;
            }

        }
        mcharacter.playMainAnimation(renderer);
        mcharacter.handle_paralyzed(renderer);
        //cout<<all_mob[all_mob.size() - 1].hp<<endl;

        map_game.renderTexture_Map(renderer, 2);
        health_bar.render_health_bar(renderer, mcharacter.hp, mcharacter.energy);

        SDL_RenderPresent( renderer );
        SDL_Delay(30);
    }

    quitSDL(window, renderer);

    return 0;
}

