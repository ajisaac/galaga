//
// Created by Aaron on 12/18/2022.
//

#ifndef GALAGA_GAME_H
#define GALAGA_GAME_H

#include <SDL.h>

class Game {
public:
    bool run();

private:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Window *window = nullptr;
    SDL_Surface *window_surface = nullptr;
    SDL_Surface *image_surface = nullptr;

    bool init();

    bool loadMedia();

    void close();

};


#endif //GALAGA_GAME_H
