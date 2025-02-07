/**
 * \file map.h
 * \brief Header for map gestion
 * \author Mathys Bertrand 
 * \version 0.1
 * \date December 16th 2023
*/

#ifndef MAP__H
#define MAP__H

#include <SDL2/SDL.h>
#include "structure.h"

/**
 * \brief Function to load the map
 * \param file The map file
 * \param map The map
*/
void create_map(char* file, map_t *map);

/**
 * \brief Function that place portal floor for zombies spawning
 * \param world The game data
 * \param map the map
*/
void place_spawn(world_t *world, map_t *map);

/**
 * \brief Function to display the map
 * \param ressources The ressources
 * \param renderer The renderer
 * \param map The map
*/
void draw_map(ressources_t *ressources, SDL_Renderer *renderer, map_t *map);

#endif