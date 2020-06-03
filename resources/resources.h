#ifndef RESOURCES_H
#define RESOURCES_H

#include<stdio.h>

// Memory
extern unsigned char memory[4096];

// Registers
extern unsigned char v[16];
extern unsigned short I;
extern unsigned char delay;
extern unsigned char sound;
extern unsigned short pc;
extern unsigned char sp;
extern unsigned short stack[16];

// Keypad
extern unsigned char keypad[16];
extern unsigned char key_press_flag;
extern unsigned char key_press_value;

// Graphics
extern int graphics_rows;
extern int graphics_cols;
extern unsigned char graphics[32][64];

// Initialization
void initialize(void);
void initialize_memory(void);
void initialize_graphics(void);
void initialize_rng(void);

// Font set
extern unsigned short font_set_address;
void load_font_set(void);

#endif
