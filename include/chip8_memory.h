#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

#define CHIP8_MEMORY_SIZE                     4096

class Memory
{
public:
    Memory();
    unsigned char& operator[](unsigned int);

private:
    unsigned char memArr[CHIP8_MEMORY_SIZE];
    void checkBounds(unsigned int);

};

#endif