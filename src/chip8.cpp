#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SDL2/SDL.h"
#include "chip8.h"


Chip8::Chip8()
{
    loadCharset();
}

void Chip8::loadCharset()
{
    for(int idx = 0; idx < CHIP8_CHARSET_SIZE; idx++)
    {
        chip8Memory[idx] = chip8CharacterSet[idx];
    }
}

void Chip8::loadGame(const char* buf, size_t size)
{
    if(size+CHIP8_PROGRAM_START_ADDRESS > CHIP8_MEMORY_SIZE)
    {
        std::cerr << "Game of size " << size << " is too large for CHIP8!.";
        exit(0);
    }
    for(size_t i = 0; i < size; i++)
    {
        chip8Memory[CHIP8_PROGRAM_START_ADDRESS + i] = buf[i];
    }
    chip8Registers.setPC(CHIP8_PROGRAM_START_ADDRESS);
}

unsigned char Chip8::haltUntilKeyPressed()
{
    SDL_Event event;
    while(SDL_WaitEvent(&event))
    {
        if(event.type != SDL_KEYDOWN) continue;

        unsigned char rKey = event.key.keysym.sym;
        unsigned char vKey = Chip8Keyboard.keyboardMap(keyboardMap, rKey);
        if(vKey != -1)
        {
            return vKey;
        }
    }
    return -1;
}

unsigned short int Chip8::readOpcode()
{
    unsigned char firstByte = chip8Memory[chip8Registers.getPC()];
    unsigned char secByte = chip8Memory[chip8Registers.getPC()+1];
    chip8Registers.setPC(chip8Registers.getPC()+2);
    return firstByte << 8 | secByte;
}

// Implementing the instruction set of the Chip8
void Chip8::executeOpcode(unsigned short int opcode)
{
    switch(opcode)
    {
        //CLS: Clear the display
        case 0x00E0:
            chip8Screen.clearScreen();
        break;
        //Ret: Return from subroutine
        case 0X00EE:
            chip8Registers.setPC(Chip8Stack.pop(&chip8Registers));
        break;
        default:
            executeComplexOpcode(opcode);

    }
}

void Chip8::executeComplexOpcode(unsigned short int opcode)
{
    unsigned short int nnn = opcode & 0x0FFF;
    unsigned char x = (opcode & 0x0F00) >> 8;
    unsigned char kk = (opcode & 0x00FF);
    unsigned char y = (opcode & 0x00F0) >> 4;
    unsigned char n = opcode & 0x000F;
    switch(opcode & 0xF000)
    {
        //Jmp: Jump to location stored in nnn
        case 0x1000:
            chip8Registers.setPC(nnn);
        break;
        //CALL: Call subroutine ate nnn
        case 0x2000:
            Chip8Stack.push(&chip8Registers, chip8Registers.getPC());
            chip8Registers.setPC(nnn);
        break;
        //SE: Skip next instruction if Vx = kk 
        case 0x3000:
            if(chip8Registers.getV(x) == kk)
            {
                chip8Registers.setPC(chip8Registers.getPC()+2);
            }
        break;
        //SNE: Skip next instruction if Vx != kk 
        case 0x4000:
            if(chip8Registers.getV(x) != kk)
            {
                chip8Registers.setPC(chip8Registers.getPC()+2);
            }
        break;
        //SE Vx, Vy: Skip next instruction if Vx = Vy 
        case 0x5000:
            if(chip8Registers.getV(x) == chip8Registers.getV(y))
            {
                chip8Registers.setPC(chip8Registers.getPC()+2);
            }
        break;
        //LD: load kk into Vx
        case 0x6000:
            chip8Registers.setV(x, kk);
        break;
        //ADD: add kk to the value in Vx
        case 0x7000:
            chip8Registers.setV(x, chip8Registers.getV(x)+kk);
        break;
        case 0x8000:
            executeComplexOpcode8(opcode);
        break;
        //9xy0 - SNE Vx, Vy: Skip next instruction if Vx != Vy.
        case 0x9000:
            if(chip8Registers.getV(x) != chip8Registers.getV(y))
            {
                chip8Registers.setPC(chip8Registers.getPC()+2);
            }
        break;
        //Annn - LD I, addr: Set I = nnn.
        case 0xA000:
            chip8Registers.setI(nnn);
        break;
        //Bnnn - JP V0, addr: Jump to location nnn + V0.
        case 0xB000:
            chip8Registers.setPC(nnn + chip8Registers.getV(0));
        break;
        //Cxkk - RND Vx, byte: Set Vx = random byte AND kk.
        case 0xC000:
            srand(time(0)); // seed the random number generator
            chip8Registers.setV(x, (rand() % 256) & kk);
        break;
        //Dxyn - DRW Vx, Vy, nibble: Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
        case 0xD000:
            chip8Registers.setV(0x0F, chip8Screen.drawSprite(chip8Registers.getV(x), chip8Registers.getV(y), &chip8Memory[chip8Registers.getI()], n));
        break;
        case 0xE000:
            executeComplexOpcodeE(opcode);
        break;
        case 0xF000:
            executeComplexOpcodeF(opcode);
        break;

    }
}

void Chip8::executeComplexOpcode8(unsigned short int opcode)
{
    unsigned char x = (opcode & 0x0F00) >> 8;
    unsigned char y = (opcode & 0x00F0) >> 4;
    unsigned char opcodeLowestnibble = opcode & 0x000F;

    unsigned short int temp = 0;
    switch(opcodeLowestnibble)
    {
        //8xy0 - LD Vx, Vy: Set Vx = Vy.
        case 0x0000:
            chip8Registers.setV(x, chip8Registers.getV(y));
        break;
        //8xy1 - OR Vx, Vy: Set Vx = Vx OR Vy.
        case 0x0001:
            chip8Registers.setV(x, chip8Registers.getV(x) | chip8Registers.getV(y));
        break;
        //8xy2 - AND Vx, Vy: Set Vx = Vx AND Vy.
        case 0x0002:
            chip8Registers.setV(x, chip8Registers.getV(x) & chip8Registers.getV(y));
        break;
        //8xy3 - XOR Vx, Vy: Set Vx = Vx XOR Vy.
        case 0x0003:
            chip8Registers.setV(x, chip8Registers.getV(x) ^ chip8Registers.getV(y));
        break;
        //8xy4 - ADD Vx, Vy: Set Vx = Vx + Vy, set VF = carry.
        case 0x0004:
        {
            temp = chip8Registers.getV(x) + chip8Registers.getV(y);
            bool carry = temp > 0xFF;
            chip8Registers.setV(x, temp);
            chip8Registers.setV(0x0F, carry);
        }
        break;
        //8xy5 - SUB Vx, Vy: Set Vx = Vx - Vy, set VF = NOT borrow.
        case 0x0005:
        {
            temp = chip8Registers.getV(x) - chip8Registers.getV(y);
            bool noBorrow = chip8Registers.getV(x) > chip8Registers.getV(y);
            chip8Registers.setV(x, temp);
            chip8Registers.setV(0x0F, noBorrow);
        }
        break;
        //8xy6 - SHR Vx {, Vy}: Set Vx = Vx SHR 1.
        case 0x0006:
            chip8Registers.setV(0x0F, chip8Registers.getV(x) & 0x01);
            chip8Registers.setV(x, chip8Registers.getV(x) >> 1);
        break;
        //8xy7 - SUBN Vx, Vy: Set Vx = Vy - Vx, set VF = NOT borrow.
        case 0x0007:
        {
            temp = chip8Registers.getV(y) - chip8Registers.getV(x);
            bool noBorrow = chip8Registers.getV(y) > chip8Registers.getV(x);
            chip8Registers.setV(x, temp);
            chip8Registers.setV(0x0F, noBorrow);
        }
        break;
        //8xyE - SHL Vx {, Vy}: Set Vx = Vx SHL 1.
        case 0x000E:
            chip8Registers.setV(0x0F, (chip8Registers.getV(x) & 0x80)>>7);
            chip8Registers.setV(x, chip8Registers.getV(x) << 1);
        break;
    }

}

void Chip8::executeComplexOpcodeE(unsigned short int opcode)
{
    unsigned char x = (opcode & 0x0F00) >> 8;
    switch(opcode & 0x00FF)
    {
        //Ex9E - SKP Vx: Skip next instruction if key with the value of Vx is pressed.
        case 0x009E:
            if(Chip8Keyboard.isKeyDown(chip8Registers.getV(x)))
            {
                chip8Registers.setPC(chip8Registers.getPC()+2);
            }
        break;
        //ExA1 - SKNP Vx: Skip next instruction if key with the value of Vx is not pressed.
        case 0x00A1:
            if(!Chip8Keyboard.isKeyDown(chip8Registers.getV(x)))
            {
                chip8Registers.setPC(chip8Registers.getPC()+2);
            }
        break;
    }
}

void Chip8::executeComplexOpcodeF(unsigned short int opcode)
{
    unsigned char x = (opcode & 0x0F00) >> 8;
    switch(opcode & 0x00FF)
    {
        //Fx07 - LD Vx, DT: Set Vx = delay timer value.
        case 0x0007:
            chip8Registers.setV(x, chip8Registers.getDT());
        break;
        //Fx0A - LD Vx, K: Wait for a key press, store the value of the key in Vx.
        case 0x000A:
            chip8Registers.setV(x, haltUntilKeyPressed());
        break;
        //Fx15 - LD DT, Vx: Set delay timer = Vx.
        case 0x0015:
            chip8Registers.setDT(chip8Registers.getV(x));
        break;
        //Fx18 - LD ST, Vx: Set sound timer = Vx.
        case 0x0018:
            chip8Registers.setST(chip8Registers.getV(x));
        break;
        //Fx1E - ADD I, Vx: Set I = I + Vx.
        case 0x001E:
            chip8Registers.setI(chip8Registers.getI() + chip8Registers.getV(x));
        break;
        //Fx29 - LD F, Vx: Set I = location of sprite for digit Vx.
        case 0x0029:
            chip8Registers.setI(chip8Registers.getV(x) * CHIP8_CHARSET_HEIGHT);
        break;
        //Fx33 - LD B, Vx: Store BCD representation of Vx in memory locations I, I+1, and I+2.
        case 0x0033:
        {
            unsigned char hundreds = chip8Registers.getV(x) / 100;
            unsigned char tens = chip8Registers.getV(x) / 10 % 10;
            unsigned char units = chip8Registers.getV(x) % 10;

            chip8Memory[chip8Registers.getI()] = hundreds;
            chip8Memory[chip8Registers.getI()+1] = tens;
            chip8Memory[chip8Registers.getI()+2] = units;
        }
        break;
        //Fx55 - LD [I], Vx: Store registers V0 through Vx in memory starting at location I.
        case 0x0055:
            for(unsigned char i = 0; i < x; i++)
            {
                chip8Memory[chip8Registers.getI()+i] = chip8Registers.getV(i);
            }
        break;
        //Fx65 - LD Vx, [I]: Read registers V0 through Vx from memory starting at location I.
        case 0x0065:
            for( unsigned char i = 0; i < x; i ++)
            {
                chip8Registers.setV(i, chip8Memory[chip8Registers.getI()]);
            }
        break;
    }
}