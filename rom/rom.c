#include"resources.h"
#include"rom.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void load_rom(char *filepath){
    
    FILE *file_ptr = fopen(filepath, "rb");
    
    if (file_ptr == NULL){
        printf("Failed to open ROM file");
        exit(EXIT_FAILURE);
    }
        
    int read_count = fread(memory + 0x200, 1, 3584, file_ptr);
    
    fclose(file_ptr);
    file_ptr = NULL;
    
    printf("Read ROM file (%d bytes)", read_count);
}
