#ifndef GALAGA_GAME_H
#define GALAGA_GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Game {
public:
    bool run();

private:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Window* window = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool init();
    void load_media();
    SDL_Texture* load_texture(const std::string& path);
    void close();

};


#endif //GALAGA_GAME_H
