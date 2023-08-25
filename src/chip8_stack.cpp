#include <iostream>
#include "chip8_registers.h"
#include "chip8_stack.h"



Stack::Stack() : stackArr{0} {}

void Stack::push(Registers* reg, unsigned short int address)
{
    reg->incrementSP();
    unsigned char sp = reg->getSP();
    if(sp >= 16)
    {
        std::cout << "Stack push error!: Index " << sp << " is out of bounds!" << std::endl;
        exit(0);
    }
    stackArr[reg->getSP()] = address;
    
}

unsigned short int Stack::pop(Registers* reg)
{
    unsigned char sp = reg->getSP();
    if(sp < 0)
    {
        std::cout << "Stack push error!: Index " << sp << " is out of bounds!" << std::endl;
    }
    unsigned short int address = stackArr[reg->getSP()];
    reg->decrementSP();
    return address;
}

