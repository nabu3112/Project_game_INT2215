#ifndef _BASE_FUNCTION_H
#define _BASE_FUNCTION_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

void logErrorAndExit(const char* msg, const char* error);
SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);
SDL_Renderer* createRenderer(SDL_Window* window);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void renderTexture(SDL_Texture *texture, float x, float y, SDL_Renderer* renderer);
SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);
SDL_bool SDL_HasIntersectionF(const SDL_FRect& A, const SDL_FRect& B);
SDL_Texture* createTextTexture(SDL_Renderer* renderer, const string& text, const string& fontPath, SDL_Color color, int fontSize);
Mix_Chunk* loadSoundEffect(Mix_Chunk* sound, const char *name_sound);
Mix_Music* loadBackgroundMusic(Mix_Music* music, const char *name_sound);

#endif // _BASE_FUNCTION_H


