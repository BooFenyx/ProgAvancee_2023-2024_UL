/**
 * \file event.h
 * \brief Header for the event functions
 * \author Mathys Bertrand 
 * \version 0.1
 * \date December 16th 2023
*/

#ifndef EVENT__H
#define EVENT__H

#include <SDL2/SDL.h>
#include "structure.h"

/**
 * \brief Function for managing collide
 * \param player The player
 * \param map The map
*/
void player_collide_wall(player_t *player, map_t *map);

/**
 * \brief Function for managing player collide against buff
 * \param player The player
 * \param buff_tab The buff tab
 * \param world The game data
*/
void player_collide_buff(player_t *player, buffTab_t *buff_tab, world_t *world);

/**
 * \brief Function for managing projectile collide against wall
 * \param pj_tab The projectile tab
 * \param map The map
*/
void proj_collide_wall(pjTab_t *pj_tab, map_t *map);

/**
 * \brief Function for managing projectile collide against zombie
 * \param pj_tab The projectile tab
 * \param zomb_tab The zombie tab
 * \param world The game data
*/
void proj_collide_zombie(pjTab_t *pj_tab, zombTab_t *zomb_tab, world_t *world);

/**
 * \brief Function for managing zombie collide against player;
 * \param zomb_tab The zombie tab
 * \param player The player
 * \param world The game data
*/
void zombie_collide_player(zombTab_t *zomb_tab, player_t *player, world_t *world);

/**
 * \brief Function for check if retry button is pressed
 * \param world The game data
 * \param mx X mouse position
 * \param my Y mouse position
 * \return true if the button is clicked, false else
*/
bool retry_pressed(button_t *button, int mx, int my);

/**
 * \brief Function for check if retry button is pressed
 * \param world The game data
 * \param mx X mouse position
 * \param my Y mouse position
 * \return true if the button is clicked, false else
*/
bool exit_pressed(button_t *button, int mx, int my);

/**
 * \brief Function that manage game events
 * \param event Event settings
 * \param world The game data
*/
void handle_events(SDL_Event *event, world_t *world);

#endif