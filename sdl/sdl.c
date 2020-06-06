#include"sdl.h"

#include<stdio.h>
#include<SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;

SDL_Window* window = NULL;
SDL_Surface* screen_surface = NULL;

void close_sdl(void){
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

void initialize_sdl(void){

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    if (atexit(close_sdl) != 0){
        printf("Failed to register close_sdl callback\n");
        close_sdl();
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(
        "CHIP-8", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (window == NULL){
        printf("Error creating SDL window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    screen_surface = SDL_GetWindowSurface(window);
    
    printf("Initialized SDL\n");
}

void fill_white(void){
    SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
}
