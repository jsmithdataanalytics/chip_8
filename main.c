#include"resources.h"
#include"instructions.h"
#include"rom.h"

#include<stdio.h>

void fetch_decode_execute(void){    
    unsigned short opcode = fetch();
    void (*instruction)(unsigned short) = decode(opcode);
    instruction(opcode);
}

void emulate_cycle(void){
    fetch_decode_execute();
}

int main(void){
    initialize();
    load_rom();
                    
    while(1){
        emulate_cycle();
    }
}
