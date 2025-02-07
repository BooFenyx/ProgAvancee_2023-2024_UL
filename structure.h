/**
 * \file structure.h
 * \brief Header for the basics structures for the game
 * \author Mathys Bertrand 
 * \version 0.8sty
 * \date December 16th 2023
*/

#ifndef STRUCTURE__H
#define STRUCTURE__H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "sdl_function.h"

/**
 * \brief Player representation
*/
struct player_s{
    int pos_x;  /*!< X Position */
    int pos_y;  /*!< Y Position */
    int size;   /*!< Player size */
    int pv;     /*!< Player health */
    int speed;  /*!< Player speed */
    int invicibility_delay;  /*!< After a hit, little delay */

    //For the collide gestion
    int last_pos_x; /*!< Player last X position */
    int last_pos_y; /*!< Player last Y position */

    int buff_proj;  /*!< The current buff proj */
}; typedef struct player_s player_t;

/**
 * \brief Projectile representation
*/
struct projectile_s{
    int pos_x;  /*!< X Position */
    int pos_y;  /*!< Y Position */
    float move_x; /*!< X Moving Position */
    float move_y; /*!< Y Moving Position */
    int size;   /*!< Proj Size */
    int dmg;    /*!< Proj damage */
    int speed;  /*!< Proj Speed */
    int type;   /*!< Different type of projectile (speed / damage influence, another texture, etc...)*/
}; typedef struct projectile_s projectile_t;

/**
 * \brief Zombies representation
*/
struct zombie_s{
    int pos_x;  /*!< X Position */
    int pos_y;  /*!< Y Position */
    int size;   /*!< Zombie Size */
    int speed;  /*!< Zombie Speed */
    int health; /*!< Zombie Health */
    int strength;   /*!< Zombie Strength */
    int type;   /*!< Different type of zombie*/
}; typedef struct zombie_s zombie_t;

/**
 * \brief Buffs representation
*/
struct buff_s{
    int pos_x;  /*!< X Position */
    int pos_y;  /*!< Y Position */
    int size;   /*!< Buff Size */
    int type;   /*!< Buff Type */
}; typedef struct buff_s buff_t;

/**
 * \brief Buff Tab Representation
*/
struct buffTab_s{
    buff_t *buff[30];   /*!< Buffs */
    int buff_size;      /*!< Number of Buffs*/
}; typedef struct buffTab_s buffTab_t;

/**
 * \brief  Proj Tab Representation
*/
struct pjTab_s{
    projectile_t *projectile[50];   /*!< Projectile */
    int pj_size;                    /*!< Number of Projectile */
    int pj_shooted;                 /*!< For not spam projectiles */
}; typedef struct pjTab_s pjTab_t;

/**
 * \brief Zomb Tab Representation
*/
struct zombTab_s{
    zombie_t *zombie[100];  /*!< Zombie */
    int zombie_killed;      /*!< For save the nb of kill */
    int zomb_size;          /*!< Number of Zombie */
    int nb_max_spanwpoint;  /*!< Number of spawn point for the zombies (portal floor) */
    int nb_zombiespawn;     /*!< Number of zombie that spawn on 1 spawn point */
}; typedef struct zombTab_s zombTab_t;

/**
 * \brief Button representation
*/
struct button_s{
    int x;  /*!< X Position */
    int y;  /*!< Y Position */
    int w;  /*!< Width */ 
    int h;  /*!< Height */
}; typedef struct button_s button_t;

/**
 * \brief Game World representation
*/
struct world_s{
    int game_state; /*!< Game state (0 - Menu | 1 - Game | 2 - Select retry or return in the menu) */
    bool game_over; /*!< Game over */
    int timer;      /*!< Game timer*/
    int save_timer; /*!< If the game is reset */
    
    //Wave system
    int wave;       /*!< Number of wave */
    int wave_delay; /*!< For a little pause between wave */
    int hard_wave;  /*!< For the gestion of hard zombie spawn */
    bool wave_end;  /*!< End of a wave */

    //Player data
    int bonus_speed;    /*!< Player Speed */
    player_t *player;   /*!< Player */

    //Buff data
    buffTab_t *buff_tab;
    int buff_p_timer; /*!< Delay for the projectile buff */
    int buff_s_timer; /*!< Delay for the speed buff */
    
    //Projectile data
    pjTab_t *pj_tab;

    //Zombies data
    zombTab_t *zomb_tab;
    int as_spawned;     /*!< For checking the numbers of zombies spawn*/
    int spawn_delay;    /*!< For setup a spawning delay between zombie spawn*/

    //File data
    FILE *file;             /*!< For write game data */
    int seconds_last_wave;  /*!< For saving the last wave time */
    int wave_save;          /*!< For not write repeatedly the same wave data*/

    //Button data
    button_t *button[2];
    int mouse_pressed;

}; typedef struct world_s world_t;

/**
 * \brief Representation for visuals ressources
*/
struct ressources_s{

    //Menu texture
    SDL_Texture* bg_menu;
    SDL_Texture* bg_go;
    SDL_Texture* exit_button;
    SDL_Texture* retry_button;
    SDL_Texture* title;

    //For the map
    SDL_Texture* grass_1;
    SDL_Texture* grass_2;
    SDL_Texture* floor_1;
    SDL_Texture* floor_2;
    SDL_Texture* floor_3;
    SDL_Texture* wall;

    //All the others textures
    SDL_Texture* player;
    SDL_Texture* projectile_p1;
    SDL_Texture* projectile_p2;
    SDL_Texture* projectile_p3;
    SDL_Texture* zombie_1;
    SDL_Texture* zombie_2;
    SDL_Texture* buff_pv;
    SDL_Texture* buff_proj;
    SDL_Texture* buff_speed;
    SDL_Texture* debuff;
    
    //For the player animation
    SDL_Texture* animation[3];
    int index_anim;

    //For the font
    TTF_Font *showthat;
    char msg_hp[20];    /*!< The health message */
    char msg_wave[10];  /*!< The wave message */
    char msg_timer[20]; /*!< The timer message */

}; typedef struct ressources_s ressources_t;

/***
 * \brief Map representation
*/
struct map_s{
    int tile[48][40];
}; typedef struct map_s map_t;

#endif