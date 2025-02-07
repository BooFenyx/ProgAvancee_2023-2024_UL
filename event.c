/**
 * \file event.c
 * \brief Zvent functions
 * \author Mathys Bertrand 
 * \version 0.1
 * \date December 16th 2023
*/

////////////////////////////////// INCLUDE //////////////////////////////////

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "event.h"
#include "data.h"
#include "sdl_function.h"
#include "display.h"
#include "structure.h"
#include "map.h"

////////////////////////////////// FUNCTION //////////////////////////////////

void player_collide_wall(player_t *player, map_t *map){
    if(get_floor_player(player, map) == 1){
        player->pos_x = player->last_pos_x;
        player->pos_y = player->last_pos_y;
    }
}

void player_collide_buff(player_t *player, buffTab_t *buff_tab, world_t *world){
    for(int i = 0; i < buff_tab->buff_size; i++){
        //Get the position of each buff and the projectile

        //Buff:
        int bleft = buff_tab->buff[i]->pos_x;
        int bright = buff_tab->buff[i]->pos_x + buff_tab->buff[i]->size;
        int btop = buff_tab->buff[i]->pos_y;
        int bbottom = buff_tab->buff[i]->pos_y + buff_tab->buff[i]->size;

        //Player:
        int pleft = player->pos_x;
        int pright = player->pos_x + player->size;
        int ptop = player->pos_y;
        int pbottom = player->pos_y + player->size;
        if(!(bbottom < ptop || btop > pbottom || bright < pleft || bleft > pright)){
            switch(buff_tab->buff[i]->type){
                case 0:
                    if(player->pv + 3 <= 30){
                        player->pv += 3;
                    } else{
                        player->pv += 30 - player->pv;
                    }
                    break;
                case 1:
                    player_buff_proj(world);
                    break;
                case 2:
                    player_buff_speed(world);
                    break;
                case 3:
                    world->hard_wave = 2;
                    break;
            }
            remove_buff(buff_tab, i);
        }
    }
}

void proj_collide_wall(pjTab_t *pj_tab, map_t *map){
    for(int i = 0; i < pj_tab->pj_size; i++){
        if(get_floor_proj(pj_tab->projectile[i], map) == 1){
            remove_projectile(pj_tab, i);
        }
    }
}

void proj_collide_zombie(pjTab_t *pj_tab, zombTab_t *zomb_tab, world_t *world){
    for(int i = 0; i < pj_tab->pj_size; i++){
        for(int j = 0; j < zomb_tab->zomb_size; j++){
            //Get the position of each zombie and projectile
            
            //Zombie:
            int zleft = zomb_tab->zombie[j]->pos_x;
            int zright = zomb_tab->zombie[j]->pos_x + zomb_tab->zombie[j]->size;
            int ztop = zomb_tab->zombie[j]->pos_y;
            int zbottom = zomb_tab->zombie[j]->pos_y + zomb_tab->zombie[j]->size;

            //Projectile:
            int pleft = pj_tab->projectile[i]->pos_x;
            int pright = pj_tab->projectile[i]->pos_x + pj_tab->projectile[i]->size;
            int ptop = pj_tab->projectile[i]->pos_y;
            int pbottom = pj_tab->projectile[i]->pos_y + pj_tab->projectile[i]->size;

            if(!(zbottom < ptop || ztop > pbottom || zright < pleft || zleft > pright)){
                zomb_tab->zombie[j]->health -= pj_tab->projectile[i]->dmg;
                remove_projectile(pj_tab, i);
                if(zomb_tab->zombie[j]->health <= 0){
                    buff_spawn(world, zomb_tab->zombie[j]);
                    remove_zombie(zomb_tab, j);
                    zomb_tab->zombie_killed ++;
                }
            }
        }
    }
}

void zombie_collide_player(zombTab_t *zomb_tab, player_t *player, world_t *world){
    for(int i = 0; i < zomb_tab->zomb_size; i++){
        //Get the position of each zombie and the player

        //Zombie:
        int zleft = zomb_tab->zombie[i]->pos_x;
        int zright = zomb_tab->zombie[i]->pos_x + zomb_tab->zombie[i]->size;
        int ztop = zomb_tab->zombie[i]->pos_y;
        int zbottom = zomb_tab->zombie[i]->pos_y + zomb_tab->zombie[i]->size;

        //Player:
        int pleft = player->pos_x;
        int pright = player->pos_x + player->size;
        int ptop = player->pos_y;
        int pbottom = player->pos_y + player->size;

        if(!(zbottom < ptop || ztop > pbottom || zright < pleft || zleft > pright)){
            player_hit(zomb_tab->zombie[i], player, world);
        }
    }
}

bool retry_pressed(button_t *button, int mx, int my){
    if(my < button->y + button->h && my > button->y && mx < button->x + button->w && mx > button->x){
        return true;
    } else{
        return false;
    }
}

bool exit_pressed(button_t *button, int mx, int my){
    if(my < button->y + button->h && my > button->y && mx < button->x + button->w && mx > button->x){
        return true;
    } else{
        return false;
    }
}

void handle_events(SDL_Event *event, world_t *world){
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    world->player->last_pos_x = world->player->pos_x;
    world->player->last_pos_y = world->player->pos_y;
    
    while(SDL_PollEvent(event)){
        
        //When the user close the window
        if(event->type == SDL_QUIT){
            world->game_over = true;
        }
        
        //When key is toggle
        else if(event->type == SDL_KEYDOWN){
            if(event->key.keysym.sym == SDLK_ESCAPE){   //When escape is pressed
                world->game_over = true;
            }
            if(keystates[SDL_SCANCODE_W]){  //When Z (and not w) is pressed
                world->player->pos_y -= player_speed(world);
            }
            if(keystates[SDL_SCANCODE_A]){  //When Q (and not a) is pressed
                world->player->pos_x -= player_speed(world);
            }
            if(keystates[SDL_SCANCODE_S]){  //When S is pressed
                world->player->pos_y += player_speed(world);
            }
            if(keystates[SDL_SCANCODE_D]){  //When D is pressed
                world->player->pos_x += player_speed(world);
            }
            if(keystates[SDL_SCANCODE_X]){  //When X is pressed
                world->game_state = 1;
            }
        } else if(event->type == SDL_MOUSEBUTTONDOWN){
            if(event->button.button == SDL_BUTTON_LEFT){
                world->mouse_pressed = 1;
            }
        }
    }
}