/**
 * \file display.h
 * \brief Header for all display functions
 * \author Mathys Bertrand
 * \version 0.5
 * \date December 16th 2023
*/

#ifndef DISPLAY__H
#define DISPLAY__H

#include <SDL2/SDL.h>
#include "structure.h"

/**
 * \brief Function to initialize ressources to display
 * \param renderer The renderer
 * \param ressources The ressources
*/
void init_ressources(SDL_Renderer *renderer, ressources_t *ressources, map_t *map);

/**
 * \brief Function for managing player animation
 * \param ressources The ressources
 * \return The animation index
*/
int get_anim(ressources_t *ressources);

/**
 * \brief Function to display the buff
 * \param buff_tab The buff tab
 * \param ressources The ressources
 * \param renderer the renderer
*/
void display_buff(buffTab_t *buff_tab, ressources_t *ressources, SDL_Renderer *renderer);

/**
 * \brief Function to display the projectile
 * \param pj_tab The projectile tab
 * \param ressources The ressources
 * \param renderer The renderer
*/
void display_projectile(pjTab_t *pj_tab, ressources_t *ressources, SDL_Renderer *renderer);

/**
 * \brief Function to display the zombie
 * \param zomb_tab The zombie tab
 * \param ressources The ressources
 * \param renderer The renderer
*/
void display_zombie(zombTab_t *zomb_tab, ressources_t *ressources, SDL_Renderer *renderer);

/**
 * \brief Function to display the different messages
 * \param world The game data
 * \param ressources The ressources
 * \param renderer The renderer
*/
void display_msg(world_t *world, ressources_t *ressources, SDL_Renderer *renderer);

/**
 * \brief Function that cleans textures
 * \param ressources The ressources
*/
void clean_ressources(ressources_t *ressources);

/**
 * \brief Function to refresh the screen
 * \param renderer The renderer
 * \param world The game data
 * \param ressources The ressources
 * \param map The map
*/
void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources, map_t *map);

#endif