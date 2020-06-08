#include"resources.h"
#include"sdl.h"

#include<stdio.h>
#include<SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;

// Flag for whether user has clicked x
int quit = 0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Colour black = {0x00, 0x00, 0x00, 0xFF};
SDL_Colour white = {0xFF, 0xFF, 0xFF, 0xFF};

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
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (renderer == NULL){
        printf("Error creating SDL renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    printf("Initialized SDL\n");
}

void update_keypad(int sym, int type){
    
    int key_mapping[16][2] = {
        {SDLK_x, 0},
        {SDLK_1, 1},
        {SDLK_2, 2},
        {SDLK_3, 3},
        {SDLK_q, 4},
        {SDLK_w, 5},
        {SDLK_e, 6},
        {SDLK_a, 7},
        {SDLK_s, 8},
        {SDLK_d, 9},
        {SDLK_z, 10},
        {SDLK_c, 11},
        {SDLK_4, 12},
        {SDLK_r, 13},
        {SDLK_f, 14},
        {SDLK_v, 15}
    };
    
    int key_to_update = -1;
    
    for (int i = 0; i < 16; i++){
        
        if (sym == key_mapping[i][0]){
            key_to_update = key_mapping[i][1];
        }
    }
    
    if (key_to_update != -1){
        
        if (type == SDL_KEYDOWN){
            keypad[key_to_update] = 1;
            
            if (fx0a_waiting && fx0a_key_press == 0xFF) {
                fx0a_key_press = key_to_update;
            }
        }
        
        else {
            keypad[key_to_update] = 0;
        }
    }
}

void process_input(void){
    SDL_Event e;
    
    while (SDL_PollEvent(&e) != 0){
        
        if (e.type == SDL_QUIT){
            quit = 1;
        }
        
        else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
            update_keypad(e.key.keysym.sym, e.type);
        }
    }
}

void draw(void){    
    SDL_Surface *frame = SDL_CreateRGBSurfaceFrom(graphics, 64, 32, 8, 64, 0, 0, 0, 0);
    
    SDL_Colour palette[2];
    palette[0] = black;
    palette[1] = white;
    
    SDL_SetPaletteColors(frame->format->palette, palette, 0, 2);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, frame);
    
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;
    
    SDL_RenderCopy(renderer, texture, NULL, &stretchRect);
    SDL_RenderPresent(renderer);
    
    SDL_FreeSurface(frame);
    SDL_DestroyTexture(texture);
    frame = NULL;
    texture = NULL;
}
