#ifndef CHIP8_H
#define CHIP8_H

#include "chip8_memory.h"
#include "chip8_registers.h"
#include "chip8_stack.h"
#include "chip8_keyboard.h"
#include "chip8_screen.h"

// SDL window dimensions
#define CHIP8_WINDOW_WIDTH                      64
#define CHIP8_WINDOW_HEIGHT                     32
#define CHIP8_WINDOW_MULTIPLIER                 10

#define CHIP8_WINDOW_TITLE                      "Chip8-Emulator"
#define CHIP8_CHARSET_SIZE                      80
#define CHIP8_CHARSET_HEIGHT                    5
#define CHIP8_PROGRAM_START_ADDRESS             512

const unsigned short int keyboardMap[] = {
    SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5,
    SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_a, SDLK_b,
    SDLK_c, SDLK_d, SDLK_e, SDLK_f
};

class Chip8
{
public:
    Memory chip8Memory;
    Registers chip8Registers;
    Stack Chip8Stack;
    Keyboard Chip8Keyboard;
    Screen chip8Screen;

    Chip8();
    void loadCharset();
    void loadGame(const char* buf, size_t size);
    unsigned char haltUntilKeyPressed(void);
    unsigned short int readOpcode();
    void executeOpcode(unsigned short int);
    void executeComplexOpcode(unsigned short int);
    void executeComplexOpcode8(unsigned short int);
    void executeComplexOpcodeE(unsigned short int);
    void executeComplexOpcodeF(unsigned short int);
private:
    const unsigned char chip8CharacterSet[CHIP8_CHARSET_SIZE] = {
    0xf0, 0x90, 0x90, 0x90, 0xf0,
    0x20, 0x60, 0x20, 0x20, 0x70,
    0xf0, 0x10, 0xf0, 0x80, 0xf0,
    0xf0, 0x10, 0xf0, 0x10, 0xf0,
    0x90, 0x90, 0xf0, 0x10, 0x10,
    0xf0, 0x80, 0xf0, 0x10, 0xf0,
    0xf0, 0x80, 0xf0, 0x90, 0xf0,
    0xf0, 0x10, 0x20, 0x40, 0x40,
    0xf0, 0x90, 0xf0, 0x90, 0xf0,
    0xf0, 0x90, 0xf0, 0x10, 0xf0,
    0xf0, 0x90, 0xf0, 0x90, 0x90,
    0xe0, 0x90, 0xe0, 0x90, 0xe0,
    0xf0, 0x80, 0x80, 0x80, 0xf0,
    0xe0, 0x90, 0x90, 0x90, 0xe0,
    0xf0, 0x80, 0xf0, 0x80, 0xf0, 
    0xf0, 0x80, 0xf0, 0x80, 0x80
};

};

#endif