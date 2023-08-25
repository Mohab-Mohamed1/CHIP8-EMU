#include <iostream>
#include <fstream>
#include "SDL2/SDL.h"
#include "chip8.h"


int main(int argc, char** argv) {

    if(argc < 2)
    {
        std::cerr << "Error: you must provide a game to load!." << std::endl;
        exit(0);
    }

    char* filename = argv[1];

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    char *buffer = new char[size];
    Chip8 chip8;
    if (file.read(buffer, size)) {
        std::cout << "Loading " << size << " bytes into chip8 memory..." << std::endl;
        chip8.loadGame(buffer, size);
        std::cout << "Game is loaded successfully!." << std::endl;
    }

    delete[] buffer;
    file.close();

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(
        CHIP8_WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        CHIP8_WINDOW_WIDTH * CHIP8_WINDOW_MULTIPLIER,
        CHIP8_WINDOW_HEIGHT * CHIP8_WINDOW_MULTIPLIER, 
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

    // chip8.chip8Screen.drawSprite(10, 10, &chip8.chip8Memory[0], 5);
    // chip8.executeOpcode(0x00E0);

    bool is_running = true;
    SDL_Event event;
    while (is_running) {
        while (SDL_PollEvent(&event)) {
            switch(event.type)
            {
                case SDL_QUIT:
                    is_running = false;
                break;
                case SDL_KEYDOWN:
                {
                    unsigned short int rKey = event.key.keysym.sym;
                    unsigned short int vKey =  chip8.Chip8Keyboard.keyboardMap(keyboardMap, rKey);
                    if(vKey != -1)
                    {
                        chip8.Chip8Keyboard.keyDown(vKey);
                    }
                }
                break;
                case SDL_KEYUP:
                {
                    unsigned short int rKey = event.key.keysym.sym;
                    unsigned short int vKey =  chip8.Chip8Keyboard.keyboardMap(keyboardMap, rKey);
                    if(vKey != -1)
                    {
                        chip8.Chip8Keyboard.keyUp(vKey);
                    }
                }
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

        for (int x = 0; x < CHIP8_SCREEN_WIDTH; x++)
        {
            for (int y = 0; y < CHIP8_SCREEN_HEIGHT; y++)
            {
                if (chip8.chip8Screen.isPixelSet(x, y))
                {
                    SDL_Rect r;
                    r.x = x * CHIP8_WINDOW_MULTIPLIER;
                    r.y = y * CHIP8_WINDOW_MULTIPLIER;
                    r.w = CHIP8_WINDOW_MULTIPLIER;
                    r.h = CHIP8_WINDOW_MULTIPLIER;
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }
        SDL_RenderPresent(renderer);
        
        if(chip8.chip8Registers.getDT() > 0)
        {
            SDL_Delay(1);
            chip8.chip8Registers.decrementDT();
        }

        chip8.executeOpcode(chip8.readOpcode());
    }

    SDL_DestroyWindow(window);
    
    return 0;
}

