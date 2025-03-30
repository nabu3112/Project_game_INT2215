#ifndef _MIXER_H
#define _MIXER_H

#include "SDL_mixer.h"
#include "base_function.h"

struct sound{
    Mix_Music* background_music = NULL;
    Mix_Music* in_game_music = NULL;
    Mix_Music* win_music = NULL;
    Mix_Chunk* pick_up_item_sound = NULL;
    Mix_Chunk* attack_sound = NULL;
    Mix_Chunk* attack_to_air_sound = NULL;
    Mix_Chunk* paralyzed_sound = NULL;
    Mix_Chunk* basic_bullet_sound = NULL;
    int volume_music = 8;
    int volume_sound_effect = 8;

    sound(){
        background_music = loadBackgroundMusic(background_music, "Sounds/Pokemon_Red_Blue_Opening.mp3");
        in_game_music = loadBackgroundMusic(in_game_music, "Sounds/in_game_music.mp3");
        win_music = loadBackgroundMusic(win_music, "Sounds/win_music.mp3");
        pick_up_item_sound = loadSoundEffect(pick_up_item_sound, "Sounds/pick_up_item.mp3");
        attack_sound = loadSoundEffect(attack_sound, "Sounds/attack.mp3");
        attack_to_air_sound = loadSoundEffect(attack_to_air_sound, "Sounds/attack_to_air.mp3");
        paralyzed_sound = loadSoundEffect(paralyzed_sound, "Sounds/paralyzed.mp3");
        basic_bullet_sound = loadSoundEffect(basic_bullet_sound, "Sounds/basic_bullet.mp3");
    }
    ~sound(){
        Mix_FreeMusic(background_music);
        background_music = NULL;
        Mix_FreeMusic(in_game_music);
        in_game_music = NULL;
        Mix_FreeMusic(win_music);
        win_music = NULL;
        Mix_FreeChunk(pick_up_item_sound);
        pick_up_item_sound = NULL;
        Mix_FreeChunk(attack_sound);
        attack_sound = NULL;
        Mix_FreeChunk(attack_to_air_sound);
        attack_to_air_sound = NULL;
        Mix_FreeChunk(paralyzed_sound);
        paralyzed_sound = NULL;
        Mix_FreeChunk(basic_bullet_sound);
        basic_bullet_sound = NULL;
    }
};


#endif // _MIXER_H
