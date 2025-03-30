#include "menu_game.h"

void render_start_menu(SDL_Renderer* renderer, SDL_Event& event)
{
    SDL_Texture* start_menu = loadTexture("Image//start_screen.png", renderer);
    SDL_Rect rect;
    SDL_Texture* text1 = createTextTexture(renderer, "Press any key to start", NORMAL_FONT_LINK, color, 36);
    SDL_Texture* text2 = createTextTexture(renderer, "(Note: Press [P] to pause game)", NORMAL_FONT_LINK, color, 18);

    Uint32 last_toggle_time = SDL_GetTicks();
    bool show_text = true;

    while(true)
    {
        SDL_RenderClear(renderer);

        rect={0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy (renderer, start_menu, NULL, &rect);

        if((SDL_GetTicks()/400)%2){
            SDL_QueryTexture(text1, NULL, NULL, &rect.w, &rect.h);
            rect.x = (SCREEN_WIDTH - rect.w)/2;
            rect.y = SCREEN_HEIGHT - 2*rect.h;
            SDL_RenderCopy (renderer, text1, NULL, &rect);
        }

        SDL_QueryTexture(text2, NULL, NULL, &rect.w, &rect.h);
        rect.x = (SCREEN_WIDTH - rect.w)/2;
        rect.y = SCREEN_HEIGHT - rect.h;
        SDL_RenderCopy (renderer, text2, NULL, &rect);

        SDL_RenderPresent(renderer);

        if(SDL_PollEvent(&event)!=0){
            if(event.type == SDL_KEYDOWN)
                break;
        }

        SDL_Delay(16);
    }
    SDL_DestroyTexture(start_menu);
    start_menu = NULL;
    SDL_DestroyTexture(text1);
    text1 =NULL;
    SDL_DestroyTexture(text2);
    text2 =NULL;

}

void pause_game(SDL_Renderer* renderer, SDL_Event& event, bool (&keys)[SDL_NUM_SCANCODES], bool& running, bool& restart_game, int& volume_music, int& volume_sound_effect)
{
    SDL_Rect rect;
    render_pause_menu(renderer, rect);
    memset(keys, 0 , sizeof(keys));
    bool confirm_quit = false;
    bool tutorial = false;
    bool set_volume = false;
    while(true)
    {
        if(SDL_WaitEvent(&event)!=0){
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_p && !confirm_quit && !tutorial && !set_volume) break;
                else if(event.key.keysym.sym == SDLK_q && !tutorial && !set_volume){
                    confirm_quit = true;
                    render_quit_menu(renderer, rect);
                }else if(event.key.keysym.sym == SDLK_y && confirm_quit){
                    running = false;
                    restart_game = false;
                    break;
                }else if(event.key.keysym.sym == SDLK_n && confirm_quit){
                    render_pause_menu(renderer, rect);
                    confirm_quit = false;
                }else if(event.key.keysym.sym == SDLK_t && !confirm_quit && !set_volume){
                    render_tutorial_menu(renderer, rect);
                    tutorial = true;
                }else if(event.key.keysym.sym == SDLK_b && (tutorial || set_volume)){
                    render_pause_menu(renderer, rect);
                    tutorial = false;
                    set_volume = false;
                }else if(event.key.keysym.sym == SDLK_v && !confirm_quit && !tutorial){
                    render_volume_menu(renderer, rect, volume_music, volume_sound_effect);
                    set_volume = true;
                }else if(event.key.keysym.sym == SDLK_RIGHT && set_volume){
                    if(volume_music<128) volume_music++;
                    render_volume_menu(renderer, rect, volume_music, volume_sound_effect);
                }else if(event.key.keysym.sym == SDLK_LEFT && set_volume){
                    if(volume_music>0) volume_music--;
                    render_volume_menu(renderer, rect, volume_music, volume_sound_effect);
                }else if(event.key.keysym.sym == SDLK_UP && set_volume){
                    if(volume_sound_effect<128) volume_sound_effect++;
                    render_volume_menu(renderer, rect, volume_music, volume_sound_effect);
                }else if(event.key.keysym.sym == SDLK_DOWN && set_volume){
                    if(volume_sound_effect>0) volume_sound_effect--;
                    render_volume_menu(renderer, rect, volume_music, volume_sound_effect);
                }
            }
        }
        Mix_VolumeMusic(volume_music);
        Mix_Volume(-1, volume_sound_effect);
    }
}

void render_pause_menu(SDL_Renderer* renderer, SDL_Rect& rect)
{
    rect = {(SCREEN_WIDTH-500)/2, (SCREEN_HEIGHT-300)/2, 500, 300};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_Texture* text = createTextTexture(renderer, "[P]: Cancel paused", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.y = rect.y + (300 - 7*rect.h)/2;
    rect.x = (SCREEN_WIDTH - rect.w)/2;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "[Q]: Quit", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.y += rect.h*2;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "[T]: Tutorial", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.y += rect.h*2;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "[V]: Volume", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.y += rect.h*2;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    SDL_RenderPresent(renderer);
}

void render_quit_menu(SDL_Renderer* renderer, SDL_Rect& rect)
{
    rect = {(SCREEN_WIDTH-500)/2, (SCREEN_HEIGHT-300)/2, 500, 300};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_Texture* text = createTextTexture(renderer, "Do you really want to quit?", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.y = rect.y + (300 - 3*rect.h)/2;
    rect.x = (SCREEN_WIDTH - rect.w)/2;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "[Y]: Yes   [N]: No", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.y += rect.h*2;
    rect.x = (SCREEN_WIDTH - rect.w)/2;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    SDL_RenderPresent(renderer);
}
void render_tutorial_menu(SDL_Renderer* renderer, SDL_Rect& rect)
{
    rect = {(SCREEN_WIDTH-500)/2, (SCREEN_HEIGHT-300)/2, 500, 300};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    rect.x += 50;

    SDL_Texture* text = createTextTexture(renderer, "↑ : Move up", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.y += (300 - 7*rect.h)/2;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "↓ : Move down", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.x += 210;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "← : Move left", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.x -= 210;
    rect.y += (300 - 7*rect.h)/2;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "→ : Move right", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.x += 210;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "[A]: Punch", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.x -= 210;
    rect.y += (300 - 7*rect.h)/2;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "[D]: Kick", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.x += 210;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "[B]: Back", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.x = (SCREEN_WIDTH - rect.w)/2;
    rect.y += (300 - 7*rect.h);
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    SDL_RenderPresent(renderer);
}

void lose_screen(SDL_Renderer* renderer, SDL_Event& event, bool& restart_game, bool (&keys)[SDL_NUM_SCANCODES])
{
    SDL_Texture* game_over_screen = loadTexture("Image/game_over.jpg", renderer);

    SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    SDL_RenderCopy(renderer, game_over_screen, NULL, &rect);

    SDL_Texture* text = createTextTexture(renderer, "Do you want to restart?", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.y = SCREEN_HEIGHT - 4*rect.h;
    rect.x = (SCREEN_WIDTH - rect.w)/2;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "[Y]: Yes   [N]: No", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.y += rect.h*2;
    rect.x = (SCREEN_WIDTH - rect.w)/2;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    SDL_RenderPresent(renderer);
    memset(keys, 0 , sizeof(keys));
    while(true)
    {
        if(SDL_WaitEvent(&event)!=0){
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_y) break;
                else if(event.key.keysym.sym == SDLK_n){
                    restart_game = false;
                    break;
                }
            }
        }
    }

}

void render_volume_menu(SDL_Renderer* renderer, SDL_Rect& rect, int& volume_music, int& volume_sound_effect)
{
    rect = {(SCREEN_WIDTH-500)/2, (SCREEN_HEIGHT-300)/2, 500, 300};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    rect.x += 50;

    SDL_Texture* text = createTextTexture(renderer, "Background music( ← and → )", NORMAL_FONT_LINK, color, 20);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.y = (SCREEN_HEIGHT-300)/2 + 70;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    rect.y += rect.h;
    rect.w =  volume_music/128.0 * 400;
    rect.h = 30;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    text = createTextTexture(renderer, "Sound effects( ↑ and ↓ )", NORMAL_FONT_LINK, color, 20);
    rect.y += (rect.h + 20);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    rect.y += rect.h;
    rect.w =  volume_sound_effect/128.0 * 400;
    rect.h = 30;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    text = createTextTexture(renderer, "[B]: Back", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.x = (SCREEN_WIDTH - rect.w)/2;
    rect.y = (SCREEN_HEIGHT-300)/2 + 260;
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    SDL_RenderPresent(renderer);
}
