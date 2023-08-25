#include <iostream>
#include "chip8_keyboard.h"


Keyboard::Keyboard(): keyboardArr {false} {}

void Keyboard::keyDown(unsigned short int vKey)
{
    if(vKey > 0 && vKey < CHIP8_TOTAL_KEYS)
    {
        keyboardArr[vKey] = true;
    }
}

void Keyboard::keyUp(unsigned short int vKey)
{
    if(vKey > 0 && vKey < CHIP8_TOTAL_KEYS)
    {
        keyboardArr[vKey] = false;
    }
}

bool Keyboard::isKeyDown(unsigned short int vKey)
{
    return keyboardArr[vKey];
}

unsigned short int Keyboard::keyboardMap(const unsigned short int* map, unsigned short int rKey)
{
    for(int idx=0; idx < CHIP8_TOTAL_KEYS; idx++)
    {
        if(map[idx] == rKey)
        {
            return idx;
        }
    }

    return -1;
}

void Keyboard::checkBounds(unsigned short int vKey)
{
    if(vKey >= CHIP8_TOTAL_KEYS || vKey < 0)
    {
        std::cout << "Virtual Key " << vKey << "not in the range of Chip8 virtuak keyboard" << std::endl;
    }
}