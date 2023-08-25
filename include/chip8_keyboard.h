#ifndef CHIP8_KEYBOARD_H
#define CHIP8_KEYBOARD_H

#define CHIP8_TOTAL_KEYS        16



class Keyboard
{
public:
    Keyboard();
    void keyDown(unsigned short int);
    void keyUp(unsigned short int);
    bool isKeyDown(unsigned short int);
    unsigned short int keyboardMap(const unsigned short int*, unsigned short int);
private:
    bool keyboardArr[CHIP8_TOTAL_KEYS];
    void checkBounds(unsigned short int);
};

#endif