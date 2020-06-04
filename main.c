#include"resources.h"
#include"instructions.h"
#include"rom.h"

#include<stdio.h>
#include<stdlib.h>

void fetch_decode_execute(void){    
    unsigned short opcode = fetch();
    void (*instruction)(unsigned short) = decode(opcode);
    instruction(opcode);
}

void emulate_cycle(void){
    fetch_decode_execute();
}

int main(int argc, char *argv[]){
    
    if (argc != 2) exit(-1);
    
    initialize();
    load_rom(argv[1]);
                    
    while(1){
        emulate_cycle();
    }
}
