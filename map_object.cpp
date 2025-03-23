#include "map_object.h"

void map_object_::init_map_coordinate(const float& x_main, const float& y_main)
{
    x_map = SCREEN_WIDTH/2 - x_main - 48;
    y_map = SCREEN_HEIGHT/2 - y_main - 48;
}

void map_object_::renderTexture_Map(SDL_Renderer* renderer, int layer)
{
    if(level==1){
        map_index.x = x_map;
        map_index.y = y_map;
        if(layer==1){
            SDL_QueryTexture(map_layer1, NULL, NULL, &map_width, &map_height);
            map_index.w= map_width*3;
            map_index.h= map_height*3;
            SDL_RenderCopyF(renderer, map_layer1, NULL, &map_index);
        }else if(layer==2){
            SDL_QueryTexture(map_layer2, NULL, NULL, &map_width, &map_height);
            map_index.w= map_width*3;
            map_index.h= map_height*3;
            SDL_RenderCopyF(renderer, map_layer2, NULL, &map_index);
        }
    }
}

void map_object_::check_to_map(SDL_FRect& hitbox, float& x, float& y, float& dx, float& dy)
{
    if(dx>0){
        for(int i=0; i<11; i++){
            if((hitbox.x - right_wall[i][0])*(hitbox.x + hitbox.w - right_wall[i][0]) < 0){
                if((hitbox.y+hitbox.h)>right_wall[i][1] && (hitbox.y+hitbox.h)<right_wall[i][3]){
                    x -= (hitbox.x + hitbox.w - right_wall[i][0]);
                    hitbox.x -= (hitbox.x + hitbox.w - right_wall[i][0]);
                }
            }
        }
    }else if(dx<0){
        for(int i=0; i<12; i++){
            if((hitbox.x - left_wall[i][0])*(hitbox.x + hitbox.w - left_wall[i][0]) < 0){
                if((hitbox.y+hitbox.h)>left_wall[i][1] && (hitbox.y+hitbox.h)<left_wall[i][3]){
                    x += (left_wall[i][0] - hitbox.x);
                    hitbox.x += (left_wall[i][0] - hitbox.x);
                }
            }
        }
    }
    if(dy>0){
        for(int i=0; i<10; i++){
            if((hitbox.y - bottom_wall[i][1])<0 && (hitbox.y + hitbox.h - bottom_wall[i][1])>0){
                if( ( hitbox.x > bottom_wall[i][0] &&  hitbox.x < bottom_wall[i][2] )
                 || ( (hitbox.x+hitbox.w) > bottom_wall[i][0] && (hitbox.x+hitbox.w) < bottom_wall[i][2] ) ){
                    y -= (hitbox.y + hitbox.h - bottom_wall[i][1]);
                    hitbox.y -= (hitbox.y + hitbox.h - bottom_wall[i][1]);
                }
            }
        }
    }else if(dy<0){
        for(int i=0; i<11; i++){
            if((hitbox.y + hitbox.h - top_wall[i][1])<0 && (hitbox.y + 2*hitbox.h - top_wall[i][1])>0){
                if( ( hitbox.x > top_wall[i][0] &&  hitbox.x < top_wall[i][2] )
                 || ( (hitbox.x+hitbox.w) > top_wall[i][0] && (hitbox.x+hitbox.w) < top_wall[i][2] ) ){
                    y += (top_wall[i][1] - hitbox.y - hitbox.h);
                    hitbox.y += (top_wall[i][1] - hitbox.y - hitbox.h);
                }
            }
        }
    }
}

