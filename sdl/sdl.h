#ifndef SDL_H
#define SDL_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern int quit;

extern Mix_Chunk *beep;

void initialize_sdl(void);
void close_sdl(void);
void process_input(void);
void draw(void);

#endif
