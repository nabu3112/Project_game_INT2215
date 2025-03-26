#ifndef _OTHER_ON_SCREEN_H
#define _OTHER_ON_SCREEN_H

#include <SDL_image.h>
#include "base_function.h"
#include "constants.h"

struct on_screen_object{
    SDL_Texture* texture_healthbar_0;
    SDL_Texture* texture_healthbar_1;
    SDL_Texture* texture_healthbar_2;
    SDL_Texture* texture_healthbar_3;
    SDL_Texture* texture_healthbar_4;
    SDL_Texture* now_texture_healthbar;
    SDL_Texture* texture_menu_upgrade;

    SDL_Rect frame_healthbar;
    SDL_Rect background_healthbar;
    SDL_FRect blood_healthbar;


    on_screen_object(SDL_Renderer* renderer){
        texture_healthbar_0 = loadTexture("Image//health_0.png", renderer);
        texture_healthbar_1 = loadTexture("Image//health_1.png", renderer);
        texture_healthbar_2 = loadTexture("Image//health_2.png", renderer);
        texture_healthbar_3 = loadTexture("Image//health_3.png", renderer);
        texture_healthbar_4 = loadTexture("Image//health_4.png", renderer);
        texture_menu_upgrade = loadTexture("Image//upgrade_menu.png", renderer);

        SDL_QueryTexture(texture_healthbar_0, NULL, NULL, &frame_healthbar.w, &frame_healthbar.h);
        frame_healthbar.x = 24;
        frame_healthbar.y = 24;
        background_healthbar = {76, 36, 378, 46};
        blood_healthbar = {76, 36, 378, 46};
    }
    ~on_screen_object(){
        SDL_DestroyTexture(texture_healthbar_0);
        texture_healthbar_0 = NULL;
        SDL_DestroyTexture(texture_healthbar_1);
        texture_healthbar_1 = NULL;
        SDL_DestroyTexture(texture_healthbar_2);
        texture_healthbar_2 = NULL;
        SDL_DestroyTexture(texture_healthbar_3);
        texture_healthbar_3 = NULL;
        SDL_DestroyTexture(texture_healthbar_4);
        texture_healthbar_4 = NULL;
        SDL_DestroyTexture(texture_menu_upgrade);
        texture_menu_upgrade = NULL;
    }

    void render_health_bar(SDL_Renderer* renderer, const int& main_hp, const int& main_energy);
    void render_menu_upgrade(SDL_Renderer* renderer);

};

#endif // _OTHER_ON_SCREEN_H
