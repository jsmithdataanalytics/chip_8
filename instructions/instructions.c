#include"resources.h"
#include"instructions.h"

#include<stdlib.h>
#include<string.h>

void clear_display(unsigned short opcode){
    initialize_graphics();
}

void jump(unsigned short opcode){
    pc = opcode & (unsigned short)0x0FFF;
}

void call(unsigned short opcode){
    
    if (sp > 15){
        printf("Maximum stack size exceeded\n");
        exit(EXIT_FAILURE);
    }
    
    stack[sp] = pc;
    sp++;
    pc = opcode & (unsigned short)0x0FFF;
}

void return_from_call(unsigned short opcode){
    
    if (sp < 1){
        printf("Tried to return when no function calls have been made\n");
        exit(EXIT_FAILURE);
    }
    
    sp--;
    pc = stack[sp];
}

void skip_next_if_vx_kk(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    unsigned char kk = opcode & (unsigned short)0x00FF;
    
    if (v[x] == kk) pc += 2;
}

void skip_next_if_vx_not_kk(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    unsigned char kk = opcode & (unsigned short)0x00FF;
    
    if (v[x] != kk) pc += 2;
}

void skip_next_if_vx_vy(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    int y = (opcode & (unsigned short)0x00F0) >> 4;
    
    if (v[x] == v[y]) pc += 2;
}

void load_vx_with_kk(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    unsigned char kk = opcode & (unsigned short)0x00FF;
    
    v[x] = kk;
}

void add_kk_to_vx(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    unsigned char kk = opcode & (unsigned short)0x00FF;
    
    v[x] += kk;
}

void load_vx_from_vy(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    int y = (opcode & (unsigned short)0x00F0) >> 4;
    
    v[x] = v[y];
}

void load_vx_with_vx_or_vy(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    int y = (opcode & (unsigned short)0x00F0) >> 4;
    
    v[x] |= v[y];
}

void load_vx_with_vx_and_vy(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    int y = (opcode & (unsigned short)0x00F0) >> 4;
    
    v[x] &= v[y];
}

void load_vx_with_vx_xor_vy(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    int y = (opcode & (unsigned short)0x00F0) >> 4;
    
    v[x] ^= v[y];
}

void add_vy_to_vx(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    int y = (opcode & (unsigned short)0x00F0) >> 4;
    
    v[x] += v[y];
    
    if (v[x] < v[y]){
        v[0xF] = 0x01;
    }
    
    else {
        v[0xF] = 0x00;
    }
}

void subtract_vy_from_vx(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    int y = (opcode & (unsigned short)0x00F0) >> 4;
    
    if (v[x] < v[y]){
        v[0xF] = 0x00;
    }
    
    else {
        v[0xF] = 0x01;
    }
    
    
    v[x] -= v[y];
}

void right_shift_vx(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    
    v[0xF] = v[x] & (unsigned char)0x01;
    v[x] >>= 1;
}

void set_vx_to_vy_minus_vx(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    int y = (opcode & (unsigned short)0x00F0) >> 4;
    
    if (v[x] > v[y]){
        v[0xF] = 0x00;
    }
    
    else {
        v[0xF] = 0x01;
    }
    
    
    v[x] = v[y] - v[x];
}

void left_shift_vx(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    
    v[0xF] = (v[x] & (unsigned char)0x80) >> 7;
    v[x] <<= 1;
}

void skip_next_if_vx_not_vy(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    int y = (opcode & (unsigned short)0x00F0) >> 4;
    
    if (v[x] != v[y]) pc += 2;
}

void load_i_with_nnn(unsigned short opcode){
    unsigned short nnn = opcode & (unsigned short)0x0FFF;
    I = nnn;
}

void jump_to_nnn_plus_v0(unsigned short opcode){
    unsigned short nnn = opcode & (unsigned short)0x0FFF;
    pc = nnn + (unsigned short)v[0];
}

void load_vx_with_random_and_kk(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    unsigned char kk = opcode & (unsigned short)0x00FF;
    unsigned char random = rand();
    
    v[x] = kk & random;
}

void draw_sprite(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    int y = (opcode & (unsigned short)0x00F0) >> 4;
    int n = opcode & (unsigned short)0x000F;
    
    unsigned char collision = 0;
    
    for (int i = 0; i < n; i++){
        
        if (I + i >= sizeof(memory)){
            printf("Tried to read sprite beyond memory bounds\n");
            exit(EXIT_FAILURE);
        }
        
        unsigned char row = memory[I + i];

        for (int j = 0; j < 8; j++){
            unsigned char pixel = (row >> (7 - j)) & (unsigned char)0x01;
            
            int x_coord = (v[x] + j) % graphics_cols;
            int y_coord = (v[y] + i) % graphics_rows;
            
            if (graphics[y_coord][x_coord] == 1 && pixel == 1) collision = 1;
            
            graphics[y_coord][x_coord] ^= pixel;
        }
    }
    
    v[0xF] = collision;
}

void load_vx_from_delay(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    v[x] = delay;
}

void load_delay_from_vx(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    delay = v[x];
}

void load_sound_from_vx(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    sound = v[x];
}

void skip_next_if_vx_key_pressed(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    
    if (v[x] > 15){
        printf("Register Vx doesn't specify a valid key\n");
        exit(EXIT_FAILURE);
    }
    
    if (keypad[v[x]]) pc += 2;
}

void skip_next_if_vx_key_not_pressed(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    
    if (v[x] > 15){
        printf("Register Vx doesn't specify a valid key\n");
        exit(EXIT_FAILURE);
    }
    
    if (!keypad[v[x]]) pc += 2;
}

void load_vx_with_next_key_press(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    
    if (key_press_flag) {
        v[x] = key_press_value;
    }
    
    else {
        pc -= 2;
    }
}

void add_vx_to_i(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    
    I += v[x];
    
    v[0xF] = I > 0xFFF;
}

void point_i_at_font_vx(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    
    if (v[x] > 0xF){
        printf("Register Vx doesn't identify a valid font character\n");
        exit(EXIT_FAILURE);
    }
    
    I = font_set_address + (v[x] * 5);
}

void dump_registers_v0_to_vx_at_i(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    
    if ((I > 0xFFF) || (I + x > 0xFFF)){
        printf("Tried to dump registers outside of memory bounds\n");
        exit(EXIT_FAILURE);
    }
        
    memcpy(memory + I, v, x + 1);
    
    I += x + 1;
}

void load_registers_v0_to_vx_from_i(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    
    if ((I > 0xFFF) || (I + x > 0xFFF)){
        printf("Tried to load registers from outside of memory bounds\n");
        exit(EXIT_FAILURE);
    }
    
    memcpy(v, memory + I, x + 1);
    
    I += x + 1;
}

void store_bcd_of_vx_at_i(unsigned short opcode){
    int x = (opcode & (unsigned short)0x0F00) >> 8;
    
    if ((I > 0xFFF) || (I + 2 > 0xFFF)){
        printf("Tried to write BCD outside of memory bounds\n");
        exit(EXIT_FAILURE);
    }
    
    unsigned char number = v[x];
    
    for (int i = 0; i < 3; i++){
        unsigned char digit = number % 10;
        memory[I + 2 - i] = digit;
        number = (number - digit) / 10;
    }
}

// Each row contains an opcode identifier and a mask
// If opcode AND mask = identifier, we have found a match for our opcode
unsigned short opcodes[34][2] = {
    {0x00E0, 0xFFFF},
    {0x1000, 0xF000},
    {0x2000, 0xF000},
    {0x00EE, 0xFFFF},
    {0x3000, 0xF000},
    {0x4000, 0xF000},
    {0x5000, 0xF00F},
    {0x6000, 0xF000},
    {0x7000, 0xF000},
    {0x8000, 0xF00F},
    {0x8001, 0xF00F},
    {0x8002, 0xF00F},
    {0x8003, 0xF00F},
    {0x8004, 0xF00F},
    {0x8005, 0xF00F},
    {0x8006, 0xF00F},
    {0x8007, 0xF00F},
    {0x800E, 0xF00F},
    {0x9000, 0xF00F},
    {0xA000, 0xF000},
    {0xB000, 0xF000},
    {0xC000, 0xF000},
    {0xD000, 0xF000},
    {0xF007, 0xF0FF},
    {0xF015, 0xF0FF},
    {0xF018, 0xF0FF},
    {0xE09E, 0xF0FF},
    {0xE0A1, 0xF0FF},
    {0xF00A, 0xF0FF},
    {0xF01E, 0xF0FF},
    {0xF029, 0xF0FF},
    {0xF055, 0xF0FF},
    {0xF065, 0xF0FF},
    {0xF033, 0xF0FF}
};

void (*instructions[34])(unsigned short) = {
    &clear_display,
    &jump,
    &call,
    &return_from_call,
    &skip_next_if_vx_kk,
    &skip_next_if_vx_not_kk,
    &skip_next_if_vx_vy,
    &load_vx_with_kk,
    &add_kk_to_vx,
    &load_vx_from_vy,
    &load_vx_with_vx_or_vy,
    &load_vx_with_vx_and_vy,
    &load_vx_with_vx_xor_vy,
    &add_vy_to_vx,
    &subtract_vy_from_vx,
    &right_shift_vx,
    &set_vx_to_vy_minus_vx,
    &left_shift_vx,
    &skip_next_if_vx_not_vy,
    &load_i_with_nnn,
    &jump_to_nnn_plus_v0,
    &load_vx_with_random_and_kk,
    &draw_sprite,
    &load_vx_from_delay,
    &load_delay_from_vx,
    &load_sound_from_vx,
    &skip_next_if_vx_key_pressed,
    &skip_next_if_vx_key_not_pressed,
    &load_vx_with_next_key_press,
    &add_vx_to_i,
    &point_i_at_font_vx,
    &dump_registers_v0_to_vx_at_i,
    &load_registers_v0_to_vx_from_i,
    &store_bcd_of_vx_at_i
};

unsigned short fetch(void){
    
    if (pc > sizeof(memory)){
        printf("Tried to fetch instruction from outside of memory bounds\n");
        exit(EXIT_FAILURE);
    }
    
    unsigned short opcode = ((unsigned short)memory[pc] << 8) + memory[pc + 1];
    pc += 2;
    
    return opcode;
}

void (*decode(unsigned short opcode))(unsigned short){
    
    for (int i = 0; i < 34; i++){

        if ((opcode & opcodes[i][1]) == opcodes[i][0]) return instructions[i];
    }
    
    printf("Invalid opcode: 0x%04X\n", (unsigned int)opcode);
    exit(EXIT_FAILURE);
}
