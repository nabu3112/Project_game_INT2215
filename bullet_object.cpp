#include "bullet_object.h"

SDL_Rect bullet_object_::set_clips_bullet()
{
    if(state_frame==1){
        frame_={0, 0, bullet_size, bullet_size};
        state_frame++;
    }else if(state_frame==2){
        frame_={bullet_size, 0, bullet_size, bullet_size};
        state_frame++;
    }else if(state_frame==3){
        frame_={2*bullet_size, 0, bullet_size, bullet_size};
        state_frame++;
    }else if(state_frame==4){
        frame_={3*bullet_size, 0, bullet_size, bullet_size};
        state_frame=1;
    }
    return frame_;
}

void bullet_object_::play_bullet_animation(SDL_Renderer* renderer, const float& x_mob , const float& y_mob,const float& x_main, const float& y_main, const float& mob_size)
{
    SDL_QueryTexture(bullet_texture, NULL, NULL, &width_bullet_frame, &height_bullet_frame);
    sprite.w = float(width_bullet_frame/4);
    sprite.h = float(height_bullet_frame);
    sprite.x = x_bullet_on_map - x_main + SCREEN_WIDTH/2 - 48 ;
    sprite.y = y_bullet_on_map - y_main + SCREEN_HEIGHT/2 - 48 ;
    frame_ = set_clips_bullet();

    SDL_RenderCopyF(renderer, bullet_texture, &frame_, &sprite);
}

void bullet_object_::bullet_move()
{
    dx = direction_bullet_x*speed;
    dy = direction_bullet_y*speed;

    x_bullet_on_map += dx;
    y_bullet_on_map += dy;

    hitbox = {x_bullet_on_map, y_bullet_on_map, bullet_size, bullet_size};
}
bool bullet_object_::check_bullet_to_map()
{
    if(dx>0){
        for(int i=0; i<11; i++){
            if((hitbox.x - right_wall[i][0] )*(hitbox.x + hitbox.w - right_wall[i][0] ) < 0 ){
                if((hitbox.y+hitbox.h)>right_wall[i][1] && (hitbox.y+hitbox.h)<right_wall[i][3]){
                    return 1;
                }
            }
        }
    }else if(dx<0){
        for(int i=0; i<12; i++){
            if((hitbox.x - left_wall[i][0])*(hitbox.x + hitbox.w - left_wall[i][0]) < 0){
                if((hitbox.y+hitbox.h)>left_wall[i][1] && (hitbox.y+hitbox.h)<left_wall[i][3]){
                    return 1;
                }
            }
        }
    }
    if(dy>0){
        for(int i=0; i<10; i++){
            if((hitbox.y - bottom_wall[i][1])<0 && (hitbox.y + hitbox.h - bottom_wall[i][1])>0){
                if( ( hitbox.x > bottom_wall[i][0] &&  hitbox.x < bottom_wall[i][2] )
                 || ( (hitbox.x+hitbox.w) > bottom_wall[i][0] && (hitbox.x+hitbox.w) < bottom_wall[i][2] ) ){
                    return 1;
                }
            }
        }
    }else if(dy<0){
        for(int i=0; i<11; i++){
            if((hitbox.y + hitbox.h - top_wall[i][1])<0 && (hitbox.y + 2*hitbox.h - top_wall[i][1])>0){
                if( ( hitbox.x > top_wall[i][0] &&  hitbox.x < top_wall[i][2] )
                 || ( (hitbox.x+hitbox.w) > top_wall[i][0] && (hitbox.x+hitbox.w) < top_wall[i][2] ) ){
                    return 1;
                }
            }
        }
    }
    dx=0;
    dy=0;
    return 0;
}

bool bullet_object_::daim_on_main(const SDL_FRect& main_hitbox, int& main_hp)
{
    if(SDL_HasIntersectionF(main_hitbox, hitbox)){
        main_hp -= daim;
        return 1;
    }else{
        return 0;
    }
}



