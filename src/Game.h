#ifndef GALAGA_GAME_H
#define GALAGA_GAME_H

#include <SDL.h>
#include <string>

class Game {
public:
    bool run();

private:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    enum KeyPressSurfaces {
        DEFAULT,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        TOTAL
    };

    SDL_Window* window;
    SDL_Surface* window_surface;
    SDL_Surface* image_surface;
    SDL_Surface* key_press_surfaces[KeyPressSurfaces::TOTAL]{};

    bool init();
    void loadMedia();
    SDL_Surface* load_surface(const std::string& path);
    void close();

};


#endif //GALAGA_GAME_H
