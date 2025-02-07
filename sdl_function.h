/**
 * \file sdl_function.h
 * \brief Header for basics sdl functions
 * \author Mathys Bertrand
 * \version 0.3
 * \date December 7th 2023
*/

#ifndef SDL_FUNCTION__H
#define SDL_FUNCTION__H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * \brief Init the windows and the renderer
 * \param window The game window
 * \param renderer The renderer
 * \param width Screen width
 * \param height Screen height
 * \return -1 in case of error, 0 else
*/
int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

/**
 * \brief Init the TTF environment
*/
void init_ttf();

/**
 * \brief Function to loading an image
 * \param path the path of the bmp file
 * \param renderer the renderer
 * \return The sdl surface with the image inside
*/
SDL_Texture *load_image(const char path[], SDL_Renderer *renderer);

/**
 * \brief Function to loafing a font
 * \param path the path of the font file
 * \param font_size The size font
 * \return The font load
*/

TTF_Font * load_font(const char* path, int font_size);

/**
 * \brief Function to apply texture in the renderer
 * \param texture The texture to apply
 * \param renderer The renderer
 * \param x X position
 * \param y Y position
*/
void apply_texture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);

/**
 * \brief Function to apply text in the renderer
 * \param renderer The renderer
 * \param x X position of the text
 * \param y Y position of the text
 * \param w The weight of the text
 * \param h The height of the text
 * \param text The text to display
 * \param font The font
*/
void apply_text(SDL_Renderer *renderer,int x, int y, int w, int h, const char *text, TTF_Font *font);

/**
 * \brief Function that clean texture in memory
 * \param texture The texture
*/
void clean_texture(SDL_Texture *texture);

/**
 * Function to clear the renderer
 * \param renderer The renderer
*/
void clear_renderer(SDL_Renderer *renderer);

/**
 * Function to update the renderer
 * \param renderer The renderer
*/
void update_screen(SDL_Renderer *renderer);

/**
 * \brief Function to pause
 * \param time The time to pause
*/
void pause(int time);

/**
 * \brief Clean the window and the renderer
 * \param renderer The renderer
 * \param window The window
*/
void clean_sdl(SDL_Renderer *renderer,SDL_Window *window);

/**
 * \brief Clean the font
 * \param font The font
*/
void clean_font(TTF_Font * font);

#endif