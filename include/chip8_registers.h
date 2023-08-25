#ifndef CHIP8_REGISTERS_H
#define CHIP8_REGISTERS_H

#define CHIP8_TOTAL_GP_REGISTERS           16

//Class Registers contain all the registers that are found in the original CHIP-8 system
class Registers
{
public:
    Registers();
    unsigned char getV(unsigned int index);
    unsigned short int getI(void);
    unsigned char getDT(void);
    unsigned char getST(void);
    unsigned short int getPC(void);
    char getSP(void);

    void setV(unsigned int index, unsigned char data);
    void setI(unsigned short int data);
    void setDT(unsigned char data);
    void setST(unsigned char data);
    void setPC(unsigned short int data);
    void setSP(char data);

    void incrementSP(void);
    void decrementSP(void);

    void decrementDT(void);
    void decrementST(void);
private:
    unsigned char V[CHIP8_TOTAL_GP_REGISTERS];
    unsigned short int I;
    unsigned char delayTimer;
    unsigned char soundTimer;
    unsigned short int PC;
    char SP;
};


#endif