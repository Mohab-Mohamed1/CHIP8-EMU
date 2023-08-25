#include <iostream>
#include "chip8_registers.h"

Registers::Registers(): V{0}, I(0), delayTimer(0), soundTimer(0), PC(0),SP(-1) {} 

unsigned char Registers::getV(unsigned int index)
{
    if (index >= 16 || index < 0)
    {
        std::cout <<"General purpose register read error!:" << " Index " << index << " is out of bounds!" << std::endl;
        exit(0); 
    }
    return V[index];
}

unsigned short int Registers::getI(void) {return I;}
unsigned char Registers::getDT(void) {return delayTimer;}
unsigned char Registers::getST(void) {return soundTimer;}
unsigned short int Registers::getPC(void) {return PC;}
char Registers::getSP(void) {return SP;}


void Registers::setV(unsigned int index, unsigned char data)
{
    if (index >= 16 || index < 0)
    {
        std::cout <<"General purpose register write error!:" << " Index " << index << " is out of bounds!" << std::endl;
        exit(0); 
    }
    V[index] = data;
}
void Registers::setI(unsigned short int data) {I = data;}
void Registers::setDT(unsigned char data) {delayTimer = data;}
void Registers::setST(unsigned char data) {soundTimer = data;}
void Registers::setPC(unsigned short int data) {PC = data;}
void Registers::setSP(char data) {SP = data;}

void Registers::incrementSP() {SP += 1;}
void Registers::decrementSP() {SP -= 1;}

void Registers::decrementDT() {delayTimer -= 1;}
void Registers::decrementST() {soundTimer -= 1;}