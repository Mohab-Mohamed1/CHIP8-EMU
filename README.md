# CHIP-8 Emulator

This is the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)

CHIP-8 is an interpreted programming language, developed by Joseph Weisbecker made on his 1802 Microprocessor. It was initially used on the COSMAC VIP and Telmac 1800 8-bit microcomputers in the mid-1970s. CHIP-8 programs are run on a CHIP-8 virtual machine. 

This project aims to emulate the CHIP-8 virtual machine in order to be able to play the CHIP-8 games.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL2.0
  * Linux(Ubuntu): Install using `sudo apt-get install -y libsdl2-dev`
  * Mac and Windows: [Click here for installation instructions](https://wiki.libsdl.org/Installation)

## Basic Build Instructions

1. Make a build directory in the top level directory: `mkdir build && cd build`
2. Compile: `cmake .. && make`
3. Run it: `./CHIP8 ../roms/INVADERS`.

## Project Structure

```
project
|
│
└─── roms # Games that can be loaded into chip-8 program to be played  
|   
│   
│
│
└───include # directory for header files
|    │   chip8_memory.h      # Memory class to emulate chip8 memory model
|    │   chip8_stack.h     # stack class to emulate chip8 stack 
|    │   chip8_keyboard.h    # keyboard class which emulates chip8 keyboard
|    │   chip8_screen.h     # screen class which emulates the chip8 screen
│    │   chip8_registers.h  # registers class which emulates all the registers found in the chip8 system
│    │   chip8.h	    # class that contains the chip8 system composed of the other classes
│
└─── src # implementation details for classes(detailed explanation below)
│
└───CMakeLists.txt
│
└───README.md
```


### Implementation Details

Classes `Memory`, `Registers`, `Stack`, `keyboard` and `screen` are used to make up the Chip8 class which emulates the instruction set of the original chip8 in order to play its games.
in `src/main.cpp` the chip8 class is initialized with all its peripherals and an SDL graphical window is created which displays what is found in the `chip8Screen` class, the chosen game that was given as command line argument is loaded in the chip8 memory then it starts reading that game data and execute the opcodes found in the game.


### Criteria Addressed:

- The project demonstrates an understanding of C++ functions and control structures.
- The project accepts user input and processes the input.
- The project uses Object Oriented Programming techniques.
- The project demonstrates Memory management by avoiding passing by value and using passing by referance instead.
- Classes abstract implementation details from their interfaces.
- The project demonstrates encapsulation and composition concepts.

