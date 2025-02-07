/**
 * \file game.c
 * \brief Pricipal program file for the game
 * \author Mathys Bertrand 
 * \version 0.2
 * \date December 7th 2023
 */

////////////////////////////////// INCLUDE //////////////////////////////////

#include <SDL2/SDL.h>
#include "data.h"
#include "display.h"
#include "structure.h"
#include "sdl_function.h"
#include "event.h"

////////////////////////////////// THE GAME //////////////////////////////////

void main(int argc, char* args[]){
    SDL_Event event;
    world_t world;
    ressources_t ressources;
    map_t map;
    SDL_Renderer *renderer;
    SDL_Window *window;

    init_game(&window, &renderer, &ressources, &world, &map);
    while(!is_game_over(&world)){
        
        //Event gestion
        handle_events(&event, &world);
        
        //Game data update
        update_data(&world, &map);

        //Display gestion
        refresh_graphics(renderer, &world, &ressources, &map);

        //Delay
        pause(10);
    }
    
    clean_game(window, renderer, &ressources, &world);
}