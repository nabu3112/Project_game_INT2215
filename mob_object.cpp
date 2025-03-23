#include "mob_object.h"

void mob_object_::mob_move(map_object_& map_game,const float& x_main,const float& y_main, float& dx_main, float& dy_main)
{
    right_with_main = (x_on_map > x_main);
    if((x_on_map - x_main) > 0){
        if(dx_main > 0) dx = running_speed;
    }else if((x_on_map - x_main) < 0){
        if(dx_main < 0) dx = -running_speed;
    }
    if((y_on_map - y_main) > 0){
        if(dy_main > 0) dy = running_speed;
    }else if((x_on_map - x_main) < 0){
        if(dy_main < 0) dy = -running_speed;
    }
    dx_main=0;
    dy_main=0;

    x_on_map += dx;
    y_on_map += dy;
    mob_hitbox= {x_on_map + 14.5, y_on_map, 29, 58};
    map_game.check_to_map(mob_hitbox, x_on_map, y_on_map, dx, dy);
    dx=0;
    dy=0;

}

SDL_Rect mob_object_::set_clips_mob(){
    if(frame_state>=1 && frame_state<6){
        frame_={58, 0, 58, 58};
        frame_state++;
    }else if(frame_state>=6 && frame_state<12){
        frame_={0, 0, 58, 58};
        frame_state++;
    }else if(frame_state>=12 && frame_state<18){
        frame_={116, 0, 58, 58};
        frame_state++;
    }else if(frame_state>=18 && frame_state<24){
        frame_={0, 0, 58, 58};
        frame_state++;
    }
    if(frame_state>=24) frame_state=1;
    return frame_;
}

void mob_object_::loadAnimationMob(SDL_Renderer* renderer, const float& x, const float& y)
{
    SDL_QueryTexture(texture_mob, NULL, NULL, &width_sheet, &height_sheet );
    sprite.w = width_sheet/3 ;
    sprite.h = height_sheet ;
    sprite.x= x_on_map - x + SCREEN_WIDTH/2 - 48;
    sprite.y= y_on_map - y + SCREEN_HEIGHT/2 - 48;
    frame_ = set_clips_mob();
    if(right_with_main){
        SDL_RenderCopyF(renderer, texture_mob, &frame_, &sprite);
    }else{
        SDL_RenderCopyExF(renderer, texture_mob, &frame_, &sprite, 0, NULL, SDL_FLIP_HORIZONTAL);
    }

}

void mob_object_::mob_attack(SDL_Renderer* renderer, const float& x_main, const float& y_main, const int& size_main)
{
    if(distance_to_main <= sqrt(SCREEN_HEIGHT*SCREEN_HEIGHT/4 + SCREEN_WIDTH*SCREEN_WIDTH/4)) attack = 1;
    if(attack)
    {
        vector_x_to_main = (x_main + size_main/2) - (x_on_map + mob_size/2);
        vector_y_to_main = (y_main + size_main/2) - (y_on_map + mob_size/2);
        distance_to_main = sqrt( vector_x_to_main*vector_x_to_main + vector_y_to_main*vector_y_to_main );
        if(distance_to_main!=0){
            vector_x_to_main/=distance_to_main;
            vector_y_to_main/=distance_to_main;
        }

        bullet_object_ mob_bullet(renderer, texture_skill, x_on_map, y_on_map, mob_size, vector_x_to_main, vector_y_to_main);
        skill.push_back(mob_bullet);
    }
}

void mob_object_::handle_bullet_move(SDL_Renderer* renderer, const float& x_main, const float& y_main, const SDL_FRect& hitbox_main, int& main_hp)
{
    for(int i=0; i<skill.size(); i++){
        skill[i].bullet_move();
        skill[i].play_bullet_animation(renderer, x_on_map, y_on_map, x_main, y_main, mob_size);
        if(skill[i].check_bullet_to_map() || skill[i].daim_on_main( hitbox_main, main_hp)){
            skill.erase(skill.begin() + i);
            cout<<main_hp<<endl;
            i--;
        }
    }
}


