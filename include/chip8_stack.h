#ifndef CHIP8_STACK_H
#define CHIP8_STACK_H

#define CHIP8_STACK_DEPTH           16

class Registers;

class Stack
{
public:
    Stack();
    void push(Registers*, unsigned short int);
    unsigned short int pop(Registers*);
private:
    unsigned short int stackArr[CHIP8_STACK_DEPTH];
    void checkBounds(void);
};

#endif