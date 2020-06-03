#include"resources.h"
#include"rom.h"

#include<string.h>

void load_rom(void){
    
    unsigned char rom[] = {
        0x00, 0x00
    };
    
    memcpy(memory + 0x200, rom, sizeof(rom));
}
