#ifndef CHIP8_SCREEN_H
#define CHIP8_SCREEN_H

#define CHIP8_SCREEN_WIDTH                      64
#define CHIP8_SCREEN_HEIGHT                     32

class Screen
{
public:
    Screen();
    void setPixel(int, int);
    bool isPixelSet(int, int);
    bool drawSprite(int, int, const unsigned char*, int);
    void clearScreen(void);
    void checkBounds(int, int);
private:
    bool pixels[CHIP8_SCREEN_HEIGHT][CHIP8_SCREEN_WIDTH];
};

#endif