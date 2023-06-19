//
// Created by eys on 20/8/21.
//

#ifndef CARGAME_VIEWCONTROLLER_H
#define CARGAME_VIEWCONTROLLER_H

#include "SDL.h"

#include "../Logic/Game.h"
#include "CommadFactory.h"

const int FRAME_RATE = 30;

class ViewController {
private:
    Game *game;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    CommandFactory* commandFactory;

    void initSDL();
public:
    ViewController(Game *game);

    ~ViewController();

    void run();
    void handleEvents();
    void clearBackground();

    unsigned int frameDuration();
};


#endif //CARGAME_VIEWCONTROLLER_H
