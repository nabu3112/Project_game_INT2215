#ifndef _MENU_GAME_H
#define _MENU_GAME_H

#include <SDL_image.h>
#include <SDL_ttf.h>
#include "base_function.h"
#include "constants.h"

void render_start_menu(SDL_Renderer* renderer, SDL_Event& event);
void pause_game(SDL_Renderer* renderer, SDL_Event& event, bool (&keys)[SDL_NUM_SCANCODES], bool& running, bool& restart_game);
void render_pause_menu(SDL_Renderer* renderer, SDL_Rect& rect);
void render_quit_menu(SDL_Renderer* renderer, SDL_Rect& rect);
void render_tutorial_menu(SDL_Renderer* renderer, SDL_Rect& rect);
void lose_screen(SDL_Renderer* renderer, SDL_Event& event, bool& restart_game, bool (&keys)[SDL_NUM_SCANCODES]);

#endif // _MENU_GAME_H
