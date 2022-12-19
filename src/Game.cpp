//
// Created by Aaron on 12/18/2022.
//

#include "Game.h"
#include <iostream>

bool Game::run() {
    if (!init()) {
        close();
        return false;
    }

    if (!loadMedia()) {
        close();
        return false;
    }


//    SDL_FillRect(window_surface, nullptr, SDL_MapRGB(window_surface->format, 0xAF, 0xFF, 0xFF));

    SDL_BlitSurface(this->image_surface, nullptr, this->window_surface, nullptr);
    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                close();
                return true;
            }
        }
    }
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL couldn't initialize! SDL_Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window couldn't be created! SDL_Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    window_surface = SDL_GetWindowSurface(window);
    if (window_surface == nullptr) {
        std::cout << "Unable to obtain window surface! SDL_Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

bool Game::loadMedia() {
    image_surface = SDL_LoadBMP("../../lazyfoo/02_getting_an_image_on_the_screen/hello_world.bmp");
    if (image_surface == nullptr) {
        std::cout << "Unable to load image! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }
    return true;
}

void Game::close() {
    SDL_FreeSurface(this->image_surface);
    this->image_surface = nullptr;
    SDL_FreeSurface(this->window_surface);
    this->window_surface = nullptr;
    if (this->window != nullptr) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
    SDL_Quit();
}