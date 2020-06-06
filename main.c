#include"resources.h"
#include"instructions.h"
#include"rom.h"
#include"sdl.h"

#include<stdio.h>
#include<stdlib.h>

void fetch_decode_execute(void){    
    unsigned short opcode = fetch();
    void (*instruction)(unsigned short) = decode(opcode);
    instruction(opcode);
}

void emulate_cycle(void){
    process_input();
    fetch_decode_execute();
    draw();
}

int main(int argc, char *argv[]){
    
    if (argc != 2){
        printf("Expected one argument: ROM filepath\n");
        exit(EXIT_FAILURE);
    }
    
    initialize_emulator();
    load_rom(argv[1]);
    initialize_sdl();
                        
    while(quit == 0){
        emulate_cycle();
    }
        
    return 0;
}
