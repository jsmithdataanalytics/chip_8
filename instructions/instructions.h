#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

unsigned short fetch(void);
void (*decode(unsigned short opcode))(unsigned short);

#endif
