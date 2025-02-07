/**
 * \file map.c
 * \brief Map gestion
 * \author Mathys Bertrand 
 * \version 0.1
 * \date December 16th 2023
*/

////////////////////////////////// INCLUDE //////////////////////////////////

#include <math.h>
#include <time.h>
#include <stdio.h>
#include "sdl_function.h"
#include "display.h"
#include "data.h"
#include "map.h"
#include "structure.h"

////////////////////////////////// FUNCTION //////////////////////////////////

void create_map(char* file, map_t* map){
    FILE* fp; int nb;
    fp = fopen(file, "r");
    if(fp == NULL){
        printf("Failed to open the map");
        exit(1);
    }
    for(int i = 0; i<MAP_HEIGHT/TILE_SIZE; i++){
        for(int j = 0; j<MAP_WIDTH/TILE_SIZE; j++){
            fscanf(fp, "%d", &map->tile[i][j]);
        }
    }
    fclose(fp);
}

void place_spawn(world_t *world, map_t *map){
    srand(time(0));
    create_map("assets/map.txt", map);
    int rx = 0;
    int ry = 0;
    if(world->wave <= world->zomb_tab->nb_max_spanwpoint){
        for(int i = 0; i < world->wave; i++){
            while(map->tile[ry][rx] != 2 || map->tile[ry][rx] == 4){
                rx = 3 + rand() % (21 - 3 + 1);
                ry = 3 + rand() % (21 - 3 + 1);
            }
            map->tile[ry][rx] = 4;
        }
    } else{
        for(int i = 0; i < world->zomb_tab->nb_max_spanwpoint; i++){
            while(map->tile[ry][rx] != 2 || map->tile[ry][rx] == 4){
                rx = 3 + rand() % (21 - 3 + 1);
                ry = 3 + rand() % (21 - 3 + 1);
            }
            map->tile[ry][rx] = 4;
        }
    }
}

void draw_map(ressources_t *ressources, SDL_Renderer *renderer, map_t *map){
    for(int i = 0; i<MAP_HEIGHT/TILE_SIZE; i++){
        for(int j = 0; j<MAP_WIDTH/TILE_SIZE; j++){
            if(map->tile[i][j] == 0){
                apply_texture(ressources->grass_1, renderer, j * TILE_SIZE, i * TILE_SIZE);
            }
            if(map->tile[i][j] == 1){
                apply_texture(ressources->wall, renderer, j * TILE_SIZE, i * TILE_SIZE);
            }
            if(map->tile[i][j] == 2){
                apply_texture(ressources->floor_1, renderer, j * TILE_SIZE, i * TILE_SIZE);
            }
            
            //Decoration
            if(map->tile[i][j] == 3){
                apply_texture(ressources->grass_2, renderer, j * TILE_SIZE, i * TILE_SIZE);
            }
            if(map->tile[i][j] == 4){
                apply_texture(ressources->floor_2, renderer, j * TILE_SIZE, i * TILE_SIZE);
            }
            if(map->tile[i][j] == 5){
                apply_texture(ressources->floor_3, renderer, j * TILE_SIZE, i * TILE_SIZE);
            }
        }
    }
}