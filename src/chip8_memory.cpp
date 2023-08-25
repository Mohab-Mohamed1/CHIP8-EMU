#include <iostream>
#include "chip8_memory.h"


Memory::Memory() : memArr{0} {}

void Memory::checkBounds(unsigned int index)
{
    if(index >= CHIP8_MEMORY_SIZE || index < 0)
    {
        std::cout <<"Memory operation error!:" << " Index " << index << " is out of bounds!" << std::endl;
        exit(0); 
    }
}

unsigned char& Memory::operator[](unsigned int index)
{
    checkBounds(index);
    return memArr[index];
}