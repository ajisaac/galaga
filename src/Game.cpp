#include "Game.h"
#include <iostream>

bool Game::run() {
    if (!init()) {
        close();
        return false;
    }

    load_media();

    SDL_Event e;
    bool quit{false};
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    default:
                        break;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    close();
    return true;


}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL couldn't initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window couldn't be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    int img_init = IMG_INIT_PNG;
    int init = IMG_Init(img_init) & img_init;
    if (!init) {
        std::cout << "Unable to init IMG_Init! SDL_Error: " << IMG_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Unable to create renderer! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 255, 45, 45, 1);

    return true;
}

void Game::load_media() {
    texture = load_texture("../../lazyfoo/07_texture_loading_and_rendering/texture.png");
    if (texture == nullptr) {
        std::cout << "Unable to load texture! SDL_Error: " << SDL_GetError() << "\n";
    }
}

void Game::close() {

    SDL_DestroyTexture(texture);
    texture = nullptr;
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}

SDL_Texture* Game::load_texture(const std::string& path) {
    SDL_Texture* new_texture;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        std::cout << "Unable to load image: " << path << " : " << IMG_GetError() << "\n";
        return nullptr;
    }
    new_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (new_texture == nullptr) {
        std::cout << "Unable to create texture from surface: " << path << " : " << SDL_GetError() << "\n";
        return nullptr;
    }
    SDL_FreeSurface(surface);
    return new_texture;
}
