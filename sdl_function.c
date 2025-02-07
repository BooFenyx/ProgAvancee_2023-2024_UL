/**
 * \file sdl_function.c
 * \brief Basics sdl functions
 * \author Mathys Bertrand
 * \version 0.3
 * \date December 9th 2023
*/

#include "sdl_function.h"
#include <stdio.h>
#include <stdlib.h>

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Erreur initialisation de la SDL : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer))
    {
        fprintf(stderr, "Erreur lors de la creation de l'image et du renderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

void init_ttf(){
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
    }
}

SDL_Texture *load_image(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur pendant chargement image BMP: %s", SDL_GetError());
        return NULL;
    }
    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 255, 0, 255)); // For the transparancy
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur pendant creation de la texture liee a l'image chargee: %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

TTF_Font * load_font(const char *path, int font_size){
    TTF_Font *font = TTF_OpenFont(path, font_size);
    if(font == NULL){
        fprintf(stderr, "Erreur pendant chargement font: %s\n", SDL_GetError());
    }
    return font;
}

void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y){
    SDL_Rect dst = {0, 0, 0, 0};
    
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    dst.x = x; dst.y=y;
    
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    
}

void apply_text(SDL_Renderer *renderer,int x, int y, int w, int h, const char *text, TTF_Font *font){
    SDL_Color color = { 255, 255, 255 };
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
     
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect2 = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect2);
    
}

void clean_texture(SDL_Texture *texture){
    if(NULL != texture){
        SDL_DestroyTexture(texture);
    } 
}

void clear_renderer(SDL_Renderer *renderer){
    SDL_RenderClear(renderer);
}

void update_screen(SDL_Renderer *renderer){
    SDL_RenderPresent(renderer);
}

void pause(int time){
    SDL_Delay(time);
}

void clean_sdl(SDL_Renderer *renderer,SDL_Window *window){
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();    
}

void clean_font(TTF_Font * font){
    TTF_CloseFont(font);
}
