//
// Created by esteban on 3/29/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_GAME_H
#define PROYECTO1DATOS2CE_CLIENTE_GAME_H
#include "SDL2/SDL.h"
#include <stdio.h>

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, , int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
};


#endif //PROYECTO1DATOS2CE_CLIENTE_GAME_H
