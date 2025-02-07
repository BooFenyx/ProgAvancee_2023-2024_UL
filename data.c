/**
 * \file data.h
 * \brief World game data
 * \author Mathys Bertrand 
 * \version 0.8
 * \date December 16th 2023
*/

////////////////////////////////// INCLUDE //////////////////////////////////

#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "event.h"
#include "data.h"
#include "sdl_function.h"
#include "display.h"
#include "structure.h"
#include "map.h"

/////////////////////////////////////////////// INITIATION FUNCTION(S) ///////////////////////////////////////////////

void init_player(player_t *player, int x, int y, int health){
    player->pos_x = x;
    player->pos_y = y;
    player->size = SPRITE_SIZE;
    player->pv = health;
    player->speed = BASIC_SPEED;
    player->buff_proj = 1;
    player->last_pos_x = 0;
    player->last_pos_y = 0;
    player->invicibility_delay = 0;
}

void init_projectile(pjTab_t *pj_tab, int x, int y, int move_x, int move_y, int type){
    int i = pj_tab->pj_size;
    pj_tab->projectile[i] = malloc(sizeof(projectile_t));
    pj_tab->projectile[i]->pos_x = x;
    pj_tab->projectile[i]->pos_y = y;
    pj_tab->projectile[i]->size = PROJECTILE_SIZE;
    float angle = atan2(move_y - pj_tab->projectile[i]->pos_y, move_x - pj_tab->projectile[i]->pos_x);
    pj_tab->projectile[i]->move_x = cos(angle);
    pj_tab->projectile[i]->move_y = sin(angle);
    switch(type){
        case 1:
            pj_tab->projectile[i]->type = 1;
            pj_tab->projectile[i]->dmg = PROJECTILE_DAMAGE;
            pj_tab->projectile[i]->speed = PROJECTILE_SPEED;
            break;
        case 2:
            pj_tab->projectile[i]->type = 2;
            pj_tab->projectile[i]->dmg = PROJECTILE_DAMAGE + 6;
            pj_tab->projectile[i]->speed = PROJECTILE_SPEED + 5.0;
            break;
        case 3:
            pj_tab->projectile[i]->type = 3;
            pj_tab->projectile[i]->dmg = PROJECTILE_DAMAGE + 16;
            pj_tab->projectile[i]->speed = PROJECTILE_SPEED + 15.0;
            break;
    }
}


void init_zombie(zombTab_t *zomb_tab, int x, int y, int type){
    int i = zomb_tab->zomb_size;
    zomb_tab->zombie[i] = malloc(sizeof(zombie_t));
    zomb_tab->zombie[i]->pos_x = x;
    zomb_tab->zombie[i]->pos_y = y;
    zomb_tab->zombie[i]->size = SPRITE_SIZE;
    switch(type){
        case 1:
            zomb_tab->zombie[i]->type = 1;
            zomb_tab->zombie[i]->speed = ZOMBIE_SPEED;
            zomb_tab->zombie[i]->health = ZOMBIE_HEALTH;
            zomb_tab->zombie[i]->strength = ZOMBIE_STRENGTH;
            break;
        case 2:
            zomb_tab->zombie[i]->type = 2;
            zomb_tab->zombie[i]->speed = ZOMBIE_SPEED * 3.0;
            zomb_tab->zombie[i]->health = ZOMBIE_HEALTH / 2;
            zomb_tab->zombie[i]->strength = ZOMBIE_STRENGTH;
            break;
    }
}

void init_button(world_t *world){
    world->button[0] = malloc(sizeof(button_t));
    world->button[0]->x = 100;
    world->button[0]->y = 600;
    world->button[0]->w = 200;
    world->button[0]->h = 50;

    world->button[1] = malloc(sizeof(button_t));
    world->button[1]->x = 540;
    world->button[1]->y = 600;
    world->button[1]->w = 160;
    world->button[1]->h = 50;
}

void init_buff(buffTab_t *buff_tab, int x, int y, int type){
    int i = buff_tab->buff_size;
    buff_tab->buff[i] = malloc(sizeof(buff_t));
    buff_tab->buff[i]->pos_x = x;
    buff_tab->buff[i]->pos_y = y;
    buff_tab->buff[i]->size = BUFF_SIZE;
    buff_tab->buff[i]->type = type;
}

void init_data(world_t *world, map_t *map){

    //Memory Allocation
    world->player = malloc(sizeof(player_t));

    //Initiation of the projectile tab
    world->pj_tab = malloc(sizeof(pjTab_t));
    world->pj_tab->pj_size = 0;

    //Initiation of the zombie tab
    world->zomb_tab = malloc(sizeof(zombTab_t));
    world->zomb_tab->zombie_killed = 0;
    world->zomb_tab->nb_max_spanwpoint = 10;
    world->zomb_tab->nb_zombiespawn = 3;
    world->zomb_tab->zomb_size = 0;
    world->as_spawned = 0;

    //Initiation of the buff
    world->buff_tab = malloc(sizeof(buffTab_t));
    world->buff_tab->buff_size = 0;
    world->buff_p_timer = 0;
    world->buff_s_timer = 0;

    //Initiation of all sprites
    init_player(world->player, 250, 250, 30);

    //Initiation of data
    world->game_state = 0; // The menu
    world->game_over = false;
    world->bonus_speed = 1;
    
    //Initiation of wave system
    world->wave = 1;
    world->hard_wave = 1;
    world->wave_end = false;
    place_spawn(world, map);

    //Initiation of the file system
    world->file = NULL;
    world->file = fopen("Don't Die & Kill Zombie DataGame.txt", "w");
    world->seconds_last_wave = 0;

    //Initiation of the buttons
    init_button(world);
    world->mouse_pressed = 0;
}

/////////////////////////////////////////////// GET & VARIABLE FUNCTION(S) ///////////////////////////////////////////////

int get_floor_player(player_t *player, map_t *map){
    if(map->tile[player->pos_x/TILE_SIZE][player->pos_y/TILE_SIZE] == 1){
        return 1;
    } if(map->tile[(player->pos_x+SPRITE_SIZE)/TILE_SIZE][(player->pos_y+SPRITE_SIZE)/TILE_SIZE] == 1){
        return 1;
    } else{
        return map->tile[player->pos_x/TILE_SIZE][player->pos_y/TILE_SIZE];
    }
}


int get_floor_proj(projectile_t *projectile, map_t *map){
    if(map->tile[projectile->pos_x / TILE_SIZE][projectile->pos_y / TILE_SIZE] == 1){
        return 1;
    } if(map->tile[(projectile->pos_x + PROJECTILE_SIZE) / TILE_SIZE][(projectile->pos_y + PROJECTILE_SIZE) / TILE_SIZE] == 1){
        return 1;
    } else{
        return map->tile[projectile->pos_x / TILE_SIZE][projectile->pos_y / TILE_SIZE];
    }
}

bool is_game_over(world_t *world){
    return world->game_over;
}

int player_speed(world_t *world){
    int sp = world->player->speed;
    return sp * world->bonus_speed;
}

/*------------------------------------------------ PROJECTILE FUNCTIONS ------------------------------------------------*/

void add_projectile(world_t *world, float mx, float my){
    init_projectile(world->pj_tab, world->player->pos_x + SPRITE_SIZE/2, world->player->pos_y + SPRITE_SIZE/2, mx, my, world->player->buff_proj);
    world->pj_tab->pj_size++;
}

void remove_projectile(pjTab_t *pj_tab, int index){
    free(pj_tab->projectile[index]);
    for (int i = index; i<pj_tab->pj_size-1; i++) {
        pj_tab->projectile[i] = pj_tab->projectile[i+1];
    }
    pj_tab->pj_size--;
}

void update_player_proj(projectile_t *projectile){
    projectile->pos_x += projectile->move_x * projectile->speed;
    projectile->pos_y += projectile->move_y * projectile->speed;
}

void shoot(world_t *world, float mx, float my){
    add_projectile(world, mx, my);
    world->pj_tab->pj_shooted++;
}

/*------------------------------------------------ ZOMBIE FUNCTIONS ------------------------------------------------*/

void add_zombie(world_t *world, int x, int y){
    init_zombie(world->zomb_tab, x, y, world->hard_wave);
    world->zomb_tab->zomb_size++;
}

void remove_zombie(zombTab_t *zomb_tab, int index){
    free(zomb_tab->zombie[index]);
    for (int i = index; i<zomb_tab->zomb_size-1; i++) {
        zomb_tab->zombie[i] = zomb_tab->zombie[i+1];
    }
    zomb_tab->zomb_size--;
}

void update_zombie(zombie_t *zombie, player_t *player){
    float angle = atan2(player->pos_y - zombie->pos_y, player->pos_x - zombie->pos_x);
    zombie->pos_x += cos(angle) * zombie->speed;
    zombie->pos_y += sin(angle) * zombie->speed;
}

void spawn_zombie(world_t *world, map_t *map){
    for(int y = 0; y < MAP_HEIGHT/TILE_SIZE; y++){
        for(int x = 0; x < MAP_WIDTH/TILE_SIZE; x++){
            if(map->tile[y][x] == 4){
                add_zombie(world, x * TILE_SIZE, y * TILE_SIZE);
            }
        }
    }
}

/*------------------------------------------------ BUFF FUNCTIONS ------------------------------------------------*/

void add_buff(world_t *world, int x, int y, int type){
    init_buff(world->buff_tab, x, y, type);
    world->buff_tab->buff_size++;
}

void remove_buff(buffTab_t *buff_tab, int index){
    free(buff_tab->buff[index]);
    for (int i = index; i<buff_tab->buff_size-1; i++) {
        buff_tab->buff[i] = buff_tab->buff[i+1];
    }
    buff_tab->buff_size--;
}

void buff_spawn(world_t *world, zombie_t *zombie){
    if(world->buff_tab->buff_size + 1 < 30){
        int random = rand() % 99;
        if(random <= 10){
            add_buff(world, zombie->pos_x, zombie->pos_y, 0);
        } else if(random > 10 && random <= 17){
            add_buff(world, zombie->pos_x, zombie->pos_y, 1);
        } else if(random > 17 && random <= 22){
            add_buff(world, zombie->pos_x, zombie->pos_y, 2);
        } else if(random > 22 && random <= 25){
            add_buff(world, zombie->pos_x, zombie->pos_y, 3);
        }
    }
}

/////////////////////////////////////////////// DATA UPDATE FUNCTION(S) ///////////////////////////////////////////////

void player_buff_speed(world_t *world){
    if(world->bonus_speed == 1){
        world->bonus_speed = 2;
        world->buff_s_timer = 0;
    }
}

void player_buff_proj(world_t *world){
    if(world->player->buff_proj < 3){
        world->player->buff_proj++;
        world->buff_p_timer = 0;
    }
}

void player_hit(zombie_t *zombie, player_t *player, world_t *world){
    if(player->invicibility_delay > 100){
        if(player->pv - zombie->strength <= 0){
            world->game_state = 2;
        } else{
            player->pv -= zombie->strength;
            player->invicibility_delay = 0;
        }
    }
}

void world_delay(world_t *world){
    world->spawn_delay += world->timer / world->timer;
    world->wave_delay += world->timer / world->timer;
    world->player->invicibility_delay += world->timer / world->timer;
    world->buff_p_timer += world->timer / world->timer;
    world->buff_s_timer += world->timer / world->timer;
}

void world_buff(world_t *world){
    //For the projectile buff
    if(world->player->buff_proj > 1){
        if(world->buff_p_timer > 500){
            world->player->buff_proj--;
            world->buff_p_timer = 0;
        }
    }

    //For the speed buff
    if(world->bonus_speed == 2){
        if(world->buff_s_timer > 200){
            world->bonus_speed--;
        }
    }
}

void world_wave(world_t *world, map_t *map){

    //For spawning zombies
    if(world->as_spawned < world->zomb_tab->nb_zombiespawn && (world->zomb_tab->zomb_size == 0 || world->spawn_delay > 100)){
        spawn_zombie(world, map);
        world->as_spawned++;
        world->spawn_delay = 0;
    } else if(world->spawn_delay > 100){
        create_map("assets/map.txt", map);  //For hide the portal;
    }

    //When a wave is end
    if(world->zomb_tab->zomb_size == 0 && !world->wave_end){
        world->wave_end = true;
        world->wave_delay = 0;
        if(world->hard_wave == 2){
            world->hard_wave = 1;
        }
    }
    
    //For updating wave parameters
    if(world->wave_end && world->wave_delay > 200){
        world->wave++;
        place_spawn(world, map);
        world->as_spawned = 0;
        world->spawn_delay = 0;
        world->wave_end = false;
        world->wave_save = 0;
    }
}

void update_data(world_t *world, map_t *map){
    if(world->game_state == 0){
        world->save_timer = SDL_GetTicks();
    }
    if(world->game_state == 1){

        //Collide gestion
        player_collide_wall(world->player, map);
        proj_collide_wall(world->pj_tab, map);
        proj_collide_zombie(world->pj_tab, world->zomb_tab, world);
        zombie_collide_player(world->zomb_tab, world->player, world);
        player_collide_buff(world->player, world->buff_tab, world);

        //For the shoot and the spawning delay
        world->timer = SDL_GetTicks() - world->save_timer;

        //Projectile shooting
        if(world->mouse_pressed == 1){
            int mx, my;
            SDL_GetMouseState(&mx, &my);
            shoot(world, mx, my);
        }
        world->mouse_pressed = 0;

        //For updating all projectile
        for(int i = 0; i<world->pj_tab->pj_size; i++){
            update_player_proj(world->pj_tab->projectile[i]);
        }
    
        //For updating all zombies
        for(int i = 0; i < world->zomb_tab->zomb_size; i++){
            update_zombie(world->zomb_tab->zombie[i], world->player);
        }

        //For all delay
        world_delay(world);

        //For manage buff player
        world_buff(world);

        //For manage the wave system
        world_wave(world, map);

        //For write the game data in a file
        save_in_file(world);
    }
    if(world->game_state == 2){
        world->save_timer = SDL_GetTicks();
        if(world->mouse_pressed == 1){
            int mx, my;
            SDL_GetMouseState(&mx, &my);
            if(retry_pressed(world->button[0], mx, my)){
                clean_data(world);
                init_data(world, map);
                world->game_state = 1;
            }
        
            if(exit_pressed(world->button[1], mx, my)){
                world->game_over = true;
            }
            world->mouse_pressed = 0;
        }
        save_in_file(world);
    }
}

/////////////////////////////////////////////// CLEAN FUNCTION(S) ///////////////////////////////////////////////

void clean_data(world_t *world){
    free(world->player);
    free(world->button[0]);
    free(world->button[1]);
    for(int i = 0; i < world->pj_tab->pj_size; i++){
        free(world->pj_tab->projectile[i]);
    } for(int i = 0; i < world->zomb_tab->zomb_size; i++){
        free(world->zomb_tab->zombie[i]);
    } for(int i = 0; i < world->buff_tab->buff_size; i++){
        free(world->buff_tab->buff[i]);
    }
    fclose(world->file);
}

/////////////////////////////////////////////// GAME FUNCTION(S) ///////////////////////////////////////////////

void clean_game(SDL_Window *window, SDL_Renderer *renderer, ressources_t *ressources, world_t *world){
    clean_data(world);
    clean_ressources(ressources);
    clean_sdl(renderer, window);
}

void init_game(SDL_Window **window, SDL_Renderer **renderer, ressources_t *ressources, world_t *world, map_t *map){
    init_ttf();
    init_sdl(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_ressources(*renderer, ressources, map);
    init_data(world, map);
}

void save_in_file(world_t *world){
    if(world->file != NULL){
        int wave = world->wave;
        int seconds = world->timer / 1000;
        int wave_time = seconds - world->seconds_last_wave;
        
        if(world->wave_end && world->wave_save == 0){
            fprintf(world->file, "Wave %d finish in %d seconds\n", wave, wave_time);
            world->seconds_last_wave = seconds;
            world->wave_save = 1;
        } 
        
        if(world->game_over){
            fprintf(world->file, "\nGG, You killed %d zombies in %d wave(s), for a total of %d seconds of gameplay !", world->zomb_tab->zombie_killed, wave, seconds);
        }
    } else{
        printf("Can't open the file");
    }
}