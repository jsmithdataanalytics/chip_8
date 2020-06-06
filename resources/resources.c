#include"resources.h"

#include<stdlib.h>
#include<time.h>
#include<string.h>

// Memory
unsigned char memory[4096];

// Registers
unsigned char v[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned short I = 0;
unsigned char delay = 0;
unsigned char sound = 0;
unsigned short pc = 0x200;
unsigned char sp = 0;
unsigned short stack[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Keypad
unsigned char keypad[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char key_press_flag = 0;
unsigned char key_press_value = 0;

// Graphics
int graphics_rows = 32;
int graphics_cols = 64;
unsigned char graphics[32][64];

// Initialization
void initialize_emulator(void){
    initialize_memory();
    initialize_graphics();
    initialize_rng();
    load_font_set();
    
    printf("Initialized CHIP-8\n");
}

void initialize_memory(void){
    for (int i = 0; i < sizeof(memory); i++) memory[i] = 0;
}

void initialize_graphics(void){
        
    for (int i = 0; i < graphics_rows; i++){
        for (int j = 0; j < graphics_cols; j++) graphics[i][j] = 0;
    }
}

void initialize_rng(void){
    srand(time(0));
}

// Font set
unsigned short font_set_address = 0x050;

void load_font_set(void){
    
    unsigned char font_set[] = {
        0xF0, 0X90, 0X90, 0X90, 0XF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    
    memcpy(memory + font_set_address, font_set, sizeof(font_set));
}
