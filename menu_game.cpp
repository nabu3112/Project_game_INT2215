#include "menu_game.h"

void render_start_menu(SDL_Renderer* renderer, SDL_Event& event)
{
    SDL_Texture* start_menu = loadTexture("Image//start_screen.png", renderer);
    SDL_Rect rect={0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy (renderer, start_menu, NULL, &rect);

    SDL_Texture* text = createTextTexture(renderer, "Press any key to start", NORMAL_FONT_LINK, color, 36);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.x = (SCREEN_WIDTH - rect.w)/2;
    rect.y = SCREEN_HEIGHT - 2*rect.h;
    SDL_RenderCopy (renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    text = createTextTexture(renderer, "(Note: Press [P] to pause game)", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.x = (SCREEN_WIDTH - rect.w)/2;
    rect.y = SCREEN_HEIGHT - rect.h;
    SDL_RenderCopy (renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);

    SDL_RenderPresent(renderer);

    while(true)
    {
        if(SDL_WaitEvent(&event)!=0){
            if(event.type == SDL_KEYDOWN)
                break;
        }
    }
    SDL_DestroyTexture(start_menu);
    start_menu = NULL;
}

void pause_game(SDL_Renderer* renderer, SDL_Event& event, bool (&keys)[SDL_NUM_SCANCODES], bool& running)
{
    SDL_Rect rect;
    render_pause_menu(renderer, rect);
    memset(keys, 0 , sizeof(keys));
    bool confirm_quit = false;
    bool tutorial = false;
    while(true)
    {
        if(SDL_WaitEvent(&event)!=0){
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_p && !confirm_quit && !tutorial) break;
                else if(event.key.keysym.sym == SDLK_q && !tutorial){
                    confirm_quit = true;
                    render_quit_menu(renderer, rect);
                }else if(event.key.keysym.sym == SDLK_y && confirm_quit){
                    running = false;
                    break;
                }else if(event.key.keysym.sym == SDLK_n && confirm_quit){
                    render_pause_menu(renderer, rect);
                    confirm_quit = false;
                }else if(event.key.keysym.sym == SDLK_t && !confirm_quit){
                    render_tutorial_menu(renderer, rect);
                    tutorial = true;
                }else if(event.key.keysym.sym == SDLK_b && tutorial){
                    render_pause_menu(renderer, rect);
                    tutorial = false;
                }
            }
        }
    }
}

void render_pause_menu(SDL_Renderer* renderer, SDL_Rect& rect)
{
    rect = {(SCREEN_WIDTH-500)/2, (SCREEN_HEIGHT-300)/2, 500, 300};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_Texture* text = createTextTexture(renderer, "[P]: Cancel paused", NORMAL_FONT_LINK, color, 24);
    SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
    rect.y = rect.y + (300 - 5*rect.h)/2;
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

    text = createTextTexture(renderer, "← : Move left", NORMAL_FONT_LINK, color, 24);
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
