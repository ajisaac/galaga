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
                    case SDLK_q:
                        quit = true;
                    default:
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 155, 1);
        SDL_RenderClear(renderer);
        SDL_Rect rect{SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_SetRenderDrawColor(renderer, 255, 18, 164, 1);
        SDL_RenderFillRect(renderer, &rect);

        //Render green outlined quad
        SDL_Rect outlineRect{SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &outlineRect);

        //Draw blue horizontal line
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

        //Draw vertical line of yellow dots
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
        for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
            SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, i);
        }

        //Update screen
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


void Game::close() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}

void Game::load_media() {
//    texture = load_texture("../../lazyfoo/07_texture_loading_and_rendering/texture.png");
//    if (texture == nullptr) {
//        std::cout << "Unable to load texture! SDL_Error: " << SDL_GetError() << "\n";
//    }
}

SDL_Texture* Game::load_texture(const std::string& path) {
    SDL_Texture* new_texture = IMG_LoadTexture(renderer, path.c_str());
    if (new_texture == nullptr) {
        std::cout << "Unable to create texture from surface: " << path << " : " << IMG_GetError() << "\n";
        return nullptr;
    }
    return new_texture;
}
