#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "base_function.h"
#include "constants.h"
#include "main_character.h"
#include "map_object.h"
#include "mob_object.h"

using namespace std;

const char* WINDOW_TITLE = "game";

Uint32 current_time = SDL_GetTicks();

void handle_mob(SDL_Renderer* renderer, map_object_& map_game, mob_object_& mob, mainc& mcharacter)
{
    mob.mob_move(map_game, mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.dx, mcharacter.dy);
    mob.loadAnimationMob(renderer, mcharacter.x_on_map, mcharacter.y_on_map);

    current_time = SDL_GetTicks();
    if (current_time > mob.last_shoot_time + 2000)
    {
        mob.mob_attack(renderer, mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.size_frame);
        mob.last_shoot_time = current_time;
    }
    mob.handle_bullet_move(renderer, mcharacter.x_on_map, mcharacter.y_on_map, mcharacter.hitbox, mcharacter.hp);
}

void handle_main(SDL_Renderer* renderer, bool& running, mainc& mcharacter, map_object_& map_game, mob_object_& mob)
{
    //mcharacter.playAttackAnimation(renderer, map_game, mob, current_time);
    mcharacter.playMoveAnimation(renderer);
    //running = mcharacter.check_alive();
}

int main(int argc, char *argv[])
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);

    mainc mcharacter(renderer);
    map_object_ map_game(renderer);
    mob_object_ mob(renderer);

    bool running = true;

    while(running){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear( renderer );

        mcharacter.main_move(running, map_game);
        map_game.init_map_coordinate(mcharacter.x_on_map, mcharacter.y_on_map);

        map_game.renderTexture_Map(renderer, 1);

        handle_main(renderer, running, mcharacter, map_game, mob);
        handle_mob(renderer, map_game, mob, mcharacter);

        map_game.renderTexture_Map(renderer, 2);

        SDL_RenderPresent( renderer );
        SDL_Delay(30);
    }

    quitSDL(window, renderer);

    return 0;
}

