#include "main_character.h"

void mainc::main_move(bool keys[], map_object_& map_game)
{
    dx=0;
    dy=0;

    //if(keys[SDL_SCANCODE_P]) is_pause=true;
    if(index_to_win <=0){
        state = 4;
    }
    else if(keys[SDL_SCANCODE_D] && energy ==4){
        state = 3;
        is_attacking = 1;
        punch_or_kick = 1;
    }
    else if(keys[SDL_SCANCODE_A]){
        state = 2;
        is_attacking = 1;
        punch_or_kick = 0;
    }
    else if(!is_attacking){
        state=0;

        if(keys[SDL_SCANCODE_UP]){
            dy -= running_speed;
            state=1;
        }
        if(keys[SDL_SCANCODE_DOWN]){
            dy += running_speed;
            state=1;
        }
        if(keys[SDL_SCANCODE_LEFT]){
            dx -= running_speed;
            state=1;
            left_or_right=0;
        }
        if(keys[SDL_SCANCODE_RIGHT]){
            dx += running_speed;
            state=1;
            left_or_right=1;
        }
        if(!((keys[SDL_SCANCODE_UP] && keys[SDL_SCANCODE_DOWN]) || (keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_RIGHT]))){
            if(keys[SDL_SCANCODE_UP] && keys[SDL_SCANCODE_LEFT] ){
                dy+=running_speed*(1 - 1/sqrt(2));
                state=1;
                left_or_right=0;
            }
            if(keys[SDL_SCANCODE_UP] && keys[SDL_SCANCODE_RIGHT]){
                dx-=running_speed*(1 - 1/sqrt(2));
                dy+=running_speed*(1 - 1/sqrt(2));
                state=1;
                left_or_right=1;
            }
            if(keys[SDL_SCANCODE_DOWN] && keys[SDL_SCANCODE_LEFT]){
                dx+=running_speed*(1 - 1/sqrt(2));
                dy-=running_speed*(1 - 1/sqrt(2));
                state=1;
                left_or_right=0;
            }
            if(keys[SDL_SCANCODE_DOWN] && keys[SDL_SCANCODE_RIGHT]){
                dx-=running_speed*(1 - 1/sqrt(2));
                dy-=running_speed*(1 - 1/sqrt(2));
                state=1;
                left_or_right=1;
            }
        }
        if((keys[SDL_SCANCODE_UP] && keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT])
           || (!keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN] && keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_RIGHT])
           || (keys[SDL_SCANCODE_UP] && keys[SDL_SCANCODE_DOWN] && keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_RIGHT]))
                state=0;

        x_on_map+=dx;
        y_on_map+=dy;
        hitbox = {x_on_map + size_frame/4, y_on_map, size_frame/2, size_frame};
        map_game.check_to_map(hitbox, x_on_map, y_on_map, dx, dy);
    }
}

void mainc::set_clips_stand()
{
    for(int i=0; i<4; i++){
        stand_clip[i] = {i*width_stand, 0, width_stand, sprite.h};
    }
}

void mainc::set_clips_run()
{
    for(int i=0; i<6; i++){
        run_clip[i] = {i*width_run, 0, width_run, sprite.h};
    }
}

void mainc::set_clips_punch()
{
    for(int i=0; i<6; i++){
        punch_clip[i] = {i*width_punch, 0, width_punch, sprite.h};
    }
}

void mainc::set_clips_kick()
{
    for(int i=0; i<4; i++){
        kick_clip[i] = {i*width_kick, 0, width_kick, sprite.h};
    }
}

void mainc::playMainAnimation(SDL_Renderer* renderer)
{
    sprite.x= SCREEN_WIDTH/2 - size_frame/2;

    if(state == 4)
    {
        sprite.w = size_frame;
        sprite.h = size_frame;

        frame_ = run_clip[(win_frame - 1)/3];
        win_frame++;
        if(win_frame > 9) win_frame = 1;

        SDL_RenderCopy(renderer, main_win, &frame_, &sprite);

    }else{
        if(state == 0){
            frame_ = stand_clip[(stand_frame-1)/4];
            sprite.w = width_stand;
            stand_frame++;
            if(stand_frame>16) stand_frame=1;
            texture_now = main_stand;

        }else if(state == 1){
            frame_ = run_clip[(run_frame-1)/3];
            sprite.w = width_run;
            run_frame++;
            if(run_frame>18) run_frame=1;
            texture_now = main_run;

        }else if(state == 2){
            frame_ = punch_clip[(punch_frame-1)/2];
            sprite.w = width_punch;
            punch_frame++;
            texture_now = main_punch;
            if(punch_frame >12){
                punch_frame=1;
                state=0;
                is_attacking = 0;
                if(energy<4) energy++;
            }
            if(punch_frame == 6) deal_damage =1;

        }else if(state == 3 && energy == 4){
            frame_ = kick_clip[(kick_frame-1)/3];
            sprite.w = width_kick;
            if(!left_or_right){
                sprite.x = SCREEN_WIDTH/2 - size_frame/2 - (width_kick - size_frame);
            }
            kick_frame++;
            texture_now = main_kick;
            if(kick_frame > 12){
                kick_frame=1;
                state=0;
                is_attacking = 0;
                energy=0;
            }
            if(kick_frame == 12) deal_damage =1;
        }
        if(left_or_right){
            SDL_RenderCopy(renderer, texture_now, &frame_, &sprite);
        }else{
            SDL_RenderCopyEx(renderer, texture_now, &frame_, &sprite, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
}

void mainc::check_alive()
{
    if(hp<=0){
        x_on_map = x_check_point;
        y_on_map = x_check_point;
        hp = max_hp;
        //is_paralyzed = 0;
    }
}

void mainc::attack_to_mob(SDL_FRect& mob_hitbox, int& mob_hp)
{
    if(left_or_right){
        punch_box = {x_on_map + size_frame*2/3, y_on_map + size_frame/2, size_frame/3, size_frame/4};
        kick_box = {x_on_map + 80, y_on_map + 42, 64, 44};
    }else{
        punch_box = {x_on_map , y_on_map + size_frame/2, size_frame/3, size_frame/4};
        kick_box = {x_on_map + 32 -(width_kick - size_frame), y_on_map + 42, 64, 44};
    }
    if(!punch_or_kick){
        if(SDL_HasIntersectionF( punch_box, mob_hitbox) ){
            mob_hp -= damage_punch;
        }
    }else{
        if(SDL_HasIntersectionF( kick_box, mob_hitbox) ){
            mob_hp -= damage_kick;
        }
    }
    deal_damage =0;
}

void mainc::render_effect_paralyzed(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, paralyzed_texture, NULL, &paralyzed_frame);
}

void mainc::handle_paralyzed(SDL_Renderer* renderer)
{
    if (is_paralyzed){
        render_effect_paralyzed(renderer);
    }
    if(is_paralyzed && (SDL_GetTicks() >= paralyzed_start_time + paralyzed_durution)){
        running_speed = base_speed;
        is_paralyzed = 0;
    }
}


void mainc::set_clips_win()
{
    for(int i=0; i<3; i++){
        win_clip[i] = {i*size_frame, 0, size_frame, size_frame};
    }
}

void mainc::play_win_animation(SDL_Renderer* renderer)
{
    sprite.x = SCREEN_WIDTH/2 - size_frame/2;

    sprite.w = size_frame;
    sprite.h = size_frame;

    frame_ = run_clip[(win_frame - 1)/2];

    SDL_RenderCopy(renderer, main_win, &frame_, &sprite);
}

void mainc::pick_up_item(SDL_Renderer* renderer, vector<SDL_FRect>& item_coordinate, on_screen_object& on_screen, bool (&keys)[SDL_NUM_SCANCODES], SDL_Event& event)
{
    hitbox.y += size_frame;
    hitbox.h -= size_frame;
    for(int i=item_coordinate.size()-1; i>=0; i--){
        if(SDL_HasIntersectionF(hitbox, item_coordinate[i])){
            on_screen.render_menu_upgrade(renderer);
            x_check_point = item_coordinate[i].x;
            y_check_point = item_coordinate[i].y;
            memset(keys, 0 , sizeof(keys));
            while(true)
            {
                if(SDL_PollEvent(&event)){
                    if(event.key.keysym.sym == SDLK_1){
                        hp = min(hp+20, max_hp);
                        break;
                    }else if(event.key.keysym.sym == SDLK_2){
                        running_speed += 1;
                        base_speed += 1;
                        break;
                    }else if(event.key.keysym.sym == SDLK_3){
                        damage_punch +=2;
                        damage_kick = damage_punch*2;
                        break;
                    }
                }
            }
            item_coordinate.erase(item_coordinate.begin() + i);
        }
    }
    hitbox.y -= size_frame;
    hitbox.h += size_frame;
}
