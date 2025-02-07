/**
 * \file display.c
 * \brief Display functions
 * \author Mathys Bertrand
 * \version 0.6
 * \date December 16th 2023
*/

////////////////////////////////// INCLUDE //////////////////////////////////

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "sdl_function.h"
#include "display.h"
#include "structure.h"
#include "data.h"
#include "map.h"

/////////////////////////////////////////////// INITIATION FUNCTION(S) ///////////////////////////////////////////////

void init_ressources(SDL_Renderer *renderer, ressources_t *ressources, map_t *map){
    //Initiation of map textures
    ressources->grass_1 = load_image("assets/grass_1.bmp", renderer);
    ressources->grass_2 = load_image("assets/grass_2.bmp", renderer);
    ressources->floor_1 = load_image("assets/floor.bmp", renderer);
    ressources->floor_2 = load_image("assets/floor_portal.bmp", renderer);
    ressources->floor_3 = load_image("assets/floor_irad.bmp", renderer);
    ressources->wall = load_image("assets/wall.bmp", renderer);

    //Initiation of projectiles textures
    ressources->projectile_p1 = load_image("assets/proj_player_1.bmp", renderer);
    ressources->projectile_p2 = load_image("assets/proj_player_2.bmp", renderer);
    ressources->projectile_p3 = load_image("assets/proj_player_3.bmp", renderer);

    //Initiation of zombies textures
    ressources->zombie_1 = load_image("assets/zombie_1.bmp", renderer);
    ressources->zombie_2 = load_image("assets/zombie_2.bmp", renderer);

    //Initiation of buffs textures
    ressources->buff_pv = load_image("assets/buff_health.bmp", renderer);
    ressources->buff_proj = load_image("assets/buff_proj.bmp", renderer);
    ressources->buff_speed = load_image("assets/buff_speed.bmp", renderer);
    ressources->debuff = load_image("assets/buff_zomb.bmp", renderer);

    //Initiation of menu textures
    ressources->bg_go = load_image("assets/bg_blood.bmp", renderer);
    ressources->bg_menu = load_image("assets/bg_grey.bmp", renderer);
    ressources->exit_button = load_image("assets/exit_button.bmp", renderer);
    ressources->retry_button = load_image("assets/retry_button.bmp", renderer);
    ressources->title = load_image("assets/title.bmp", renderer);

    //Initiation of animations textures
    ressources->animation[0] = load_image("assets/player_base.bmp", renderer);
    ressources->animation[1] = load_image("assets/player_base2.bmp", renderer);
    ressources->animation[2] = load_image("assets/player_base3.bmp", renderer);
    ressources->index_anim = 0;

    //Initiation of the map
    create_map("assets/map.txt", map);

    //Initiation of the font
    ressources->showthat = load_font("assets/Showthat.ttf", 20);
}

/////////////////////////////////////////////// DISPLAY FUNCTION(S) ///////////////////////////////////////////////

int get_anim(ressources_t *ressources){
    int i = ressources->index_anim;
    if(ressources->index_anim == 2){
        ressources->index_anim = 0;
    }
    ressources->index_anim++;
    return i;
}

void display_buff(buffTab_t *buff_tab, ressources_t *ressources, SDL_Renderer *renderer){
    for(int i = 0; i < buff_tab->buff_size; i++){
        switch(buff_tab->buff[i]->type){
            case 0:
                apply_texture(ressources->buff_pv, renderer, buff_tab->buff[i]->pos_x, buff_tab->buff[i]->pos_y);
                break;
            case 1:
                apply_texture(ressources->buff_proj, renderer, buff_tab->buff[i]->pos_x, buff_tab->buff[i]->pos_y);
                break;
            case 2:
                apply_texture(ressources->buff_speed, renderer, buff_tab->buff[i]->pos_x, buff_tab->buff[i]->pos_y);
                break;
            case 3:
                apply_texture(ressources->debuff, renderer, buff_tab->buff[i]->pos_x, buff_tab->buff[i]->pos_y);
                break;
        }
    }
}

void display_projectile(pjTab_t *pj_tab, ressources_t *ressources, SDL_Renderer *renderer){
    for(int i = 0; i < pj_tab->pj_size; i++){
        switch(pj_tab->projectile[i]->type){
            case 1:
                apply_texture(ressources->projectile_p1, renderer, pj_tab->projectile[i]->pos_x, pj_tab->projectile[i]->pos_y);
                break;
            case 2:
                apply_texture(ressources->projectile_p2, renderer, pj_tab->projectile[i]->pos_x, pj_tab->projectile[i]->pos_y);
                break;
            case 3:
                apply_texture(ressources->projectile_p3, renderer, pj_tab->projectile[i]->pos_x, pj_tab->projectile[i]->pos_y);
                break;
        }
    }
}

void display_zombie(zombTab_t *zomb_tab, ressources_t *ressources, SDL_Renderer *renderer){
    for(int i = 0; i < zomb_tab->zomb_size; i++){
        switch(zomb_tab->zombie[i]->type){
            case 1:
                apply_texture(ressources->zombie_1, renderer, zomb_tab->zombie[i]->pos_x, zomb_tab->zombie[i]->pos_y);
                break;
            case 2:
                apply_texture(ressources->zombie_2, renderer, zomb_tab->zombie[i]->pos_x, zomb_tab->zombie[i]->pos_y);
                break;
        }
    }
}

void display_msg(world_t *world, ressources_t *ressources, SDL_Renderer *renderer){
    
    //Write the differents messages
    sprintf(ressources->msg_hp, "Health: %i / 30", world->player->pv);
    sprintf(ressources->msg_wave, "Wave %i", world->wave);
    sprintf(ressources->msg_timer, "Survived for %hu s", world->timer/1000);

    apply_text(renderer, 10, 10, 200, 40, ressources->msg_wave, ressources->showthat);
    apply_text(renderer, SCREEN_WIDTH - 370, 10, 360, 40, ressources->msg_timer, ressources->showthat);
    apply_text(renderer, 10, SCREEN_HEIGHT - 50, 320, 40, ressources->msg_hp, ressources->showthat);
}

/////////////////////////////////////////////// CLEAN FUNCTION(S) ///////////////////////////////////////////////

void clean_ressources(ressources_t *ressources){
    clean_texture(ressources->grass_1);
    clean_texture(ressources->grass_2);
    clean_texture(ressources->floor_1);
    clean_texture(ressources->floor_2);
    clean_texture(ressources->floor_3);
    clean_texture(ressources->wall);
    clean_texture(ressources->animation[0]);
    clean_texture(ressources->animation[1]);
    clean_texture(ressources->animation[2]);
    clean_texture(ressources->projectile_p1);
    clean_texture(ressources->projectile_p2);
    clean_texture(ressources->projectile_p3);
    clean_texture(ressources->zombie_1);
    clean_texture(ressources->zombie_2);
    clean_texture(ressources->buff_pv);
    clean_texture(ressources->buff_speed);
    clean_texture(ressources->buff_proj);
    clean_texture(ressources->debuff);
    clean_texture(ressources->bg_go);
    clean_texture(ressources->bg_menu);
    clean_texture(ressources->retry_button);
    clean_texture(ressources->exit_button);
    clean_texture(ressources->title);    
    clean_font(ressources->showthat);
}

/////////////////////////////////////////////// PRINCIPAL FUNCTION(S) ///////////////////////////////////////////////

void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources, map_t *map){
    clear_renderer(renderer);
    
    switch (world->game_state){
    case 0:
        apply_texture(ressources->bg_menu, renderer, 0, 0);
        apply_texture(ressources->title, renderer, 100, 50);
        apply_text(renderer, 50, 550, 700, 50, "PRESS [x] TO START THE GAME", ressources->showthat);
        break;
    
    case 1:
    
        //Draw the map
        draw_map(ressources, renderer, map);
    
        //Draw the player
        apply_texture(ressources->animation[get_anim(ressources)], renderer, world->player->pos_x, world->player->pos_y);

        //Draw the buff
        display_buff(world->buff_tab, ressources, renderer);

        //Draw the projectiles
        display_projectile(world->pj_tab, ressources, renderer);

        //Draw the zombie
        display_zombie(world->zomb_tab, ressources, renderer);

        //Draw the messages
        display_msg(world, ressources, renderer);
        break;

    case 2:
        apply_texture(ressources->bg_go, renderer, 0, 0);
        apply_text(renderer, 100, 200, 600, 150, "GAME OVER", ressources->showthat);
        apply_texture(ressources->retry_button, renderer, world->button[0]->x, world->button[0]->y);
        apply_texture(ressources->exit_button, renderer, world->button[1]->x, world->button[1]->y);
        break;
    }

    update_screen(renderer);
}