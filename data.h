/**
 * \file data.h
 * \brief Header for the world game data
 * \author Mathys Bertrand 
 * \version 0.6
 * \date December 16th 2023
*/

#ifndef DATA__H
#define DATA__H

#include <SDL2/SDL.h>
#include "structure.h"

/**
 * \brief Width of the map
*/
#define MAP_WIDTH 800

/**
 * \brief Height of the map
*/
#define MAP_HEIGHT 800

/**
 * \brief Size of one tile
*/
#define TILE_SIZE 32

/**
 * \brief Size of one sprite
*/
#define SPRITE_SIZE 26

/**
 * \brief Size of one projectile
*/
#define PROJECTILE_SIZE 8

/**
 * \brief Damage of one projectile
*/
#define PROJECTILE_DAMAGE 4

/**
 * \brief Speed of one projectile
*/
#define PROJECTILE_SPEED 10.0

/**
 * \brief Speed of one zombie
*/
#define ZOMBIE_SPEED 2.0

/**
 * \brief Health of one zombie
*/
#define ZOMBIE_HEALTH 20

/**
 * \brief Strength os one zombie
*/
#define ZOMBIE_STRENGTH 3

/**
 * \brief Size of one buff
*/
#define BUFF_SIZE 16

/**
 * \brief Width of the screen
*/
#define SCREEN_WIDTH 800

/**
 * \brief Height of the screen
*/
#define SCREEN_HEIGHT 800

/**
 * \brief Basic game speed
*/
#define BASIC_SPEED 6

/**
 * \brief Initiation of the player
 * \param player The player
 * \param x X position
 * \param y Y position
 * \param health The health of the player
*/
void init_player(player_t *player, int x, int y, int health);

/**
 * \brief Initiation of a projectile
 * \param pj_tab The projectile tab
 * \param x X position
 * \param y Y position
 * \param move_x X moving position
 * \param move_y Y moving position
 * \param type The type of projectile
 * \param dmg The damage
 * \param speed The speed
*/
void init_projectile(pjTab_t *pj_tab, int x, int y, int move_x, int move_y, int type);

/**
 * \brief Initiation of a zombie
 * \param zomb_tab The zombie tab
 * \param x X position
 * \param y Y position
 * \param type The type of zombie
*/
void init_zombie(zombTab_t *zomb_tab, int x, int y, int type);

/**
 * \brief Initiation of a buff
 * \param buff_tab The buff tab
 * \param x X position
 * \param y Y position
 * \param type The type of buff
*/
void init_buff(buffTab_t *buff_tab, int x, int y, int type);

/**
 * \brief Function to initiate game over button
 * \param world The game data
*/
void init_button(world_t *world);

/**
 * \brief Initiation of the game world (data)
 * \param world The game data
 * \param map The map
*/
void init_data(world_t *world, map_t *map);

/**
 * \brief Function to verify if the game is over
 * \param world The game data
 * \return true if the game is over, false else
*/
bool is_game_over(world_t *world);

/**
 * \brief Function to check the floor below the player
 * \param player The player
 * \param map The map
 * \return The type of floor (& wall)
*/
int get_floor_player(player_t *player, map_t *map);

/**
 * \brief Function to check the floor below the projectile
 * \param projectile The projectile
 * \param map The map
*/
int get_floor_proj(projectile_t *projectile, map_t *map);

/**
 * \brief Function that return current player speed
 * \param world The game data
 * \return The player speed
*/
int player_speed(world_t *world);

/**
 * \brief Function that add a projectile in the pj tab
 * \param world The game data
 * \param mx X movement
 * \param my Y movement
*/
void add_projectile(world_t *world, float mx, float my);

/**
 * \brief Function that remove specified projectile from the pj tab
 * \param pj_tab The projectile tab
 * \param index The position of the projectile in the tab
*/
void remove_projectile(pjTab_t *pj_tab, int index);

/**
 * \brief Function for update bullet
 * \param projectile The projectile
*/
void update_player_proj(projectile_t *projectile);

/**
 * \brief Function for shoot
 * \param world The game data
 * \param mx X Movement
 * \param my Y Movement
*/
void shoot(world_t *world, float mx, float my);

/**
 * \brief Function that add zombie in the zomb tab
 * \param world The game data;
 * \param x X spawn position
 * \param y Y spawn position
*/
void add_zombie(world_t *world, int x, int y);

/**
 * \brief Function that remove zombie from the zomb tab
 * \param zomb_tab The zombie tab
 * \param index The position of the zombie in the tab
*/
void remove_zombie(zombTab_t *zomb_tab, int index);

/**
 * \brief Function for managing zombie spawn
 * \param world The game data
 * \param map The map
*/
void spawn_zombie(world_t *world, map_t *map);

/**
 * \brief Function that add a buff in the buff tab
 * \param world The game data
 * \param x The X position
 * \param y The Y position
 * \param type The type of buff
*/
void add_buff(world_t *world, int x, int y, int type);

/**
 * \brief Function that remove a buff from the buff tab
 * \param buff_tab The buff tab
 * \param index The position of a buff in the buff tab
*/
void remove_buff(buffTab_t *buff_tab, int index);

/**
 * \brief Function for managing buff spawn
 * \param world The game data
 * \param zombie The zombie
*/
void buff_spawn(world_t *world, zombie_t *zombie);

/**
 * \brief Function that return current player speed
 * \param world The game data
 * \return The player speed
*/
void player_buff_speed(world_t *world);

/**
 * \brief Function that manage current player buff
 * \param world The game data
*/
void player_buff_proj(world_t *world);

/**
 * \brief Function for managing player pv
 * \param zombie The zombie
 * \param player The player
 * \param world The game data
*/
void player_hit(zombie_t *zombie, player_t *player, world_t *world);

/**
 * \brief Function for managing delay
 * \param world The game data
*/
void world_delay(world_t *world);

/**
 * \brief Function for managing buff
 * \param world The game data
*/
void world_buff(world_t *world);

/**
 * \brief Function that manage the wave system
 * \param world The Game data
 * \param map The map
*/
void world_wave(world_t *world, map_t *map);

/**
 * \brief Main fonction for data gestion
 * \param world The game data
 * \param map The map
*/
void update_data(world_t *world, map_t *map);

/**
 * \brief Function that clear all data
 * \param world The game data
*/
void clean_data(world_t *world);

/**
 * \brief Clean the game
 * \param window The window
 * \param renderer The renderer
 * \param ressources The ressources for the game
 * \param world the game data
*/
void clean_game(SDL_Window *window, SDL_Renderer *renderer, ressources_t *ressources, world_t *world);

/**
 * \brief Initialize the game
 * \param window The window
 * \param renderer The renderer
 * \param ressources The ressources for the game
 * \param world The game data
 * \param map The map
*/
void init_game(SDL_Window **window, SDL_Renderer **renderer, ressources_t *ressources, world_t *world, map_t *map);

/**
 * \brief Function to write some game info
 * \param world The game data
*/
void save_in_file(world_t *world);
#endif