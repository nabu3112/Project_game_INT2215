#include "other_on_screen.h"


void health_bar_object::render_health_bar(SDL_Renderer* renderer, const int& main_hp, const int& main_energy)
{
    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
    SDL_RenderFillRect(renderer, &background_healthbar);

    blood_healthbar.w = main_hp/100.0 * 378;
    if(main_hp >= 0){
        SDL_SetRenderDrawColor(renderer, 255, 70, 70, 255);
        SDL_RenderFillRectF(renderer, &blood_healthbar);
    }
    switch (main_energy)
    {
    case 0:
        now_texture_healthbar = texture_healthbar_0;
        break;
    case 1:
        now_texture_healthbar = texture_healthbar_1;
        break;
    case 2:
        now_texture_healthbar = texture_healthbar_2;
        break;
    case 3:
        now_texture_healthbar = texture_healthbar_3;
        break;
    case 4:
        now_texture_healthbar = texture_healthbar_4;
        break;
    }
    SDL_RenderCopy(renderer, now_texture_healthbar, NULL, &frame_healthbar);
}

