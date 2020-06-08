#include<SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int quit;

void initialize_sdl(void);
void close_sdl(void);
void process_input(void);
void draw(void);
