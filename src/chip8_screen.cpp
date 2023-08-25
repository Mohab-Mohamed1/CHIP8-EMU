#include <iostream>
#include "chip8_screen.h"

Screen::Screen(): pixels {false} {}

void Screen::setPixel(int x, int y)
{
    pixels[y][x] = true;
}

bool Screen::isPixelSet(int x, int y)
{
    return pixels[y][x];
}

void Screen::checkBounds(int x, int y)
{
    if(x >= CHIP8_SCREEN_WIDTH || x < 0 && y >= CHIP8_SCREEN_HEIGHT || x < 0)
    {
        std::cout << "Error: Pixel position out of bounds";
        exit(0);
    } 
}

bool Screen::drawSprite(int x, int y, const unsigned char* sprite, int num)
{
    bool pixelCollision = false;
    for(int ly = 0; ly < num; ly++)
    {
        char c = sprite[ly];
        for(int lx = 0; lx < 8; lx++)
        {
            if((c & (0b10000000 >> lx)) == 0)
            {
                continue;
            }
            if(pixels[(y+ly) % CHIP8_SCREEN_HEIGHT][(x+lx) % CHIP8_SCREEN_WIDTH])
            {
                pixelCollision = true;
            }
            pixels[(y+ly) % CHIP8_SCREEN_HEIGHT][(x+lx) % CHIP8_SCREEN_WIDTH] ^= true;
        }
    }
    return pixelCollision;
}

void Screen::clearScreen()
{
    for(int y = 0; y < CHIP8_SCREEN_HEIGHT; y++)
    {
        for(int x = 0; x < CHIP8_SCREEN_WIDTH; x++)
        {
            pixels[y][x] = 0;
        }
    }
}

