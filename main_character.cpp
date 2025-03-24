#include "main_character.h"

void mainc::main_move(bool& running, map_object_& map_game)
{
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            running = false;
        }else if( event.type == SDL_KEYDOWN){
            keys[event.key.keysym.scancode]= true;
            if(event.key.keysym.sym == SDLK_RETURN) running = false;
        }else if( event.type == SDL_KEYUP){
            keys[event.key.keysym.scancode]= false;
        }
    }
    dx=0;
    dy=0;

    if(keys[SDL_SCANCODE_A]){
        state=2;
        is_attacking = 1;
        punch_or_kick = 0;
    }
    else if(keys[SDL_SCANCODE_D]){
        state=3;
        is_attacking = 1;
        punch_or_kick = 1;
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

SDL_Rect mainc::set_clips_stand()
{
    if(stand_frame>=1 && stand_frame<=4){
        frame_ = {0, 0, sprite.w, sprite.h};
        stand_frame++;
    }else if(stand_frame>=5 && stand_frame<=8){
        frame_ = {sprite.w, 0, sprite.w, sprite.h};
        stand_frame++;
    }else if(stand_frame>=9 && stand_frame<=12){
        frame_ = {2*sprite.w, 0, sprite.w, sprite.h};
        stand_frame++;
    }else if(stand_frame>=13 && stand_frame<=16){
        frame_ = {3*sprite.w, 0, sprite.w, sprite.h};
        stand_frame++;
    }
    if(stand_frame>16) stand_frame=1;
    return frame_;
}

SDL_Rect mainc::set_clips_run()
{
    if(run_frame>=1 && run_frame<=3){
        frame_ = {0, 0, sprite.w, sprite.h};
        run_frame++;
    }else if(run_frame>=4 && run_frame<=6){
        frame_ = {sprite.w, 0, sprite.w, sprite.h};
        run_frame++;
    }else if(run_frame>=7 && run_frame<=9){
        frame_ = {2*sprite.w, 0, sprite.w, sprite.h};
        run_frame++;
    }else if(run_frame>=10 && run_frame<=12){
        frame_ = {3*sprite.w, 0, sprite.w, sprite.h};
        run_frame++;
    }else if(run_frame>=13 && run_frame<=15){
        frame_ = {4*sprite.w, 0, sprite.w, sprite.h};
        run_frame++;
    }else if(run_frame>=16 && run_frame<=18){
        frame_ = {5*sprite.w, 0, sprite.w, sprite.h};
        run_frame++;
    }
    if(run_frame>18) run_frame=1;
    return frame_;
}

SDL_Rect mainc::set_clips_punch()
{
    if(punch_frame>=1 && punch_frame<=2){
        frame_ = {0, 0, sprite.w, sprite.h};
        punch_frame++;
    }else if(punch_frame>=3 && punch_frame<=4){
        frame_ = {sprite.w, 0, sprite.w, sprite.h};
        punch_frame++;
    }else if(punch_frame>=5 && punch_frame<=6){
        frame_ = {2*sprite.w, 0, sprite.w, sprite.h};
        punch_frame++;
    }else if(punch_frame>=7 && punch_frame<=8){
        frame_ = {3*sprite.w, 0, sprite.w, sprite.h};
        punch_frame++;
    }else if(punch_frame>=9 && punch_frame<=10){
        frame_ = {4*sprite.w, 0, sprite.w, sprite.h};
        punch_frame++;
    }else if(punch_frame>=11 && punch_frame<=12){
        frame_ = {5*sprite.w, 0, sprite.w, sprite.h};
        punch_frame++;
    }
    return frame_;
}

SDL_Rect mainc::set_clips_kick()
{
    if(kick_frame>=1 && kick_frame<=3){
        frame_ = {0, 0, 144, 96};
        kick_frame++;
    }else if(kick_frame>=4 && kick_frame<=6){
        frame_ = {144, 0, 144, 96};
        kick_frame++;
    }else if(kick_frame>=7 && kick_frame<=9){
        frame_ = {288, 0, 144, 96};
        kick_frame++;
    }else if(kick_frame>=10 && kick_frame<=12){
        frame_ = {432, 0, 144, 96};
        kick_frame++;
    }
    return frame_;
}

void mainc::playMainAnimation(SDL_Renderer* renderer)
{
    sprite.x= SCREEN_WIDTH/2 - sprite.w/2;
    sprite.y= SCREEN_HEIGHT/2 - sprite.h/2;
    if(state==0){
        SDL_QueryTexture(main_stand, NULL, NULL, &sprite.w, &sprite.h );
        sprite.w/=4;
        frame_ = set_clips_stand();
        texture_now = main_stand;

	}else if(state==1){
	    SDL_QueryTexture(main_run, NULL, NULL, &sprite.w, &sprite.h );
        sprite.w/=6;
        frame_ = set_clips_run();
        texture_now = main_run;

	}else if(state==2){
	    SDL_QueryTexture(main_punch, NULL, NULL, &sprite.w, &sprite.h );
        sprite.w/=6;
        frame_ = set_clips_punch();
        texture_now = main_punch;
        if(punch_frame >12){
            punch_frame=1;
            state=0;
            is_attacking = 0;
            if(energy<4) energy++;
        }
	}else if(state==3 && energy==4){
	    SDL_QueryTexture(main_kick, NULL, NULL, &sprite.w, &sprite.h );
        sprite.w/=4;
        frame_ = set_clips_kick();
        texture_now = main_kick;
        if(kick_frame > 12){
            kick_frame=1;
            state=0;
            is_attacking = 0;
            energy=0;
        }
	}
	if(left_or_right){
        SDL_RenderCopy(renderer, texture_now, &frame_, &sprite);
    }else{
        SDL_RenderCopyEx(renderer, texture_now, &frame_, &sprite, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
}

bool mainc::check_alive()
{
    if(hp<=0){
        SDL_Delay(500);
        return 0;
    }
    else return 1;
}

void mainc::attack_to_mob(SDL_FRect& mob_hitbox, int& mob_hp)
{
    if(left_or_right){
        punch_box = {x_on_map + size_frame*2/3, y_on_map + size_frame/2, size_frame/3, size_frame/4};
        kick_box = {x_on_map + 80, y_on_map + 42, 32, 44};
    }else{
        punch_box = {x_on_map , y_on_map + size_frame/2, size_frame/3, size_frame/4};
        kick_box = {x_on_map + 32, y_on_map + 42, 32, 44};
    }
    if(SDL_HasIntersectionF( punch_box, mob_hitbox) && is_attacking && !punch_or_kick && punch_frame==1){
        mob_hp -= daim_punch;
        cout<<mob_hp<<endl;
    }else if(SDL_HasIntersectionF( kick_box, mob_hitbox) && is_attacking && punch_or_kick && kick_frame==1){
        mob_hp -= daim_kick;
        cout<<mob_hp<<endl;
    }
}

void mainc::render_effect_paralyzed(SDL_Renderer* renderer)
{
    SDL_QueryTexture(paralyzed_texture, NULL, NULL, &paralyzed_frame.w, &paralyzed_frame.h);
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


