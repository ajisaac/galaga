#include "Game.h"
#include <iostream>

bool Game::run() {
    if (!init()) {
        close();
        return false;
    }

    loadMedia();
    image_surface = key_press_surfaces[DEFAULT];

    SDL_Event e;
    bool quit{false};
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        image_surface = key_press_surfaces[LEFT];
                        break;
                    case SDLK_RIGHT:
                        image_surface = key_press_surfaces[RIGHT];
                        break;
                    case SDLK_UP:
                        image_surface = key_press_surfaces[UP];
                        break;
                    case SDLK_DOWN:
                        image_surface = key_press_surfaces[DOWN];
                        break;
                    default:
                        image_surface = key_press_surfaces[DEFAULT];
                        break;
                }
            }
        }
        SDL_Rect stretched_rect;
        stretched_rect.x = 0;
        stretched_rect.y = 0;
        stretched_rect.w = SCREEN_WIDTH;
        stretched_rect.h = SCREEN_HEIGHT;
        SDL_BlitSurface(this->image_surface, nullptr, this->window_surface, &stretched_rect);
        SDL_UpdateWindowSurface(window);
    }

    close();
    return true;


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

void Game::loadMedia() {
    key_press_surfaces[DEFAULT] = load_surface("../../lazyfoo/04_key_presses/press.bmp");
    key_press_surfaces[UP] = load_surface("../../lazyfoo/04_key_presses/up.bmp");
    key_press_surfaces[DOWN] = load_surface("../../lazyfoo/04_key_presses/down.bmp");
    key_press_surfaces[LEFT] = load_surface("../../lazyfoo/04_key_presses/left.bmp");
    key_press_surfaces[RIGHT] = load_surface("../../lazyfoo/04_key_presses/right.bmp");
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

SDL_Surface* Game::load_surface(const std::string& path) {

    SDL_Surface* optimized_surface = nullptr;

    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (surface == nullptr) {
        std::cout << "Unable to load image: " << path << " : " << SDL_GetError() << "\n";
        return nullptr;
    }

    optimized_surface = SDL_ConvertSurface(surface, window_surface->format, 0);
    if (optimized_surface == nullptr) {
        std::cout << "Unable to optimize image: " << path << " : " << SDL_GetError() << "\n";
        SDL_FreeSurface(surface);
        return nullptr;
    }

    SDL_FreeSurface(surface); // no longer need this
    return optimized_surface;
}
