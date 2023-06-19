#include "State.h"
#include "../../Logic/Game.h"

bool State::doQuit() {
    return game->isUserExit();
}

void State::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        Command* command = commandFactory->getCommand(event);
        if (command != nullptr) {
            command->execute();
            break;
        }
    }
}

void State::jump(State* state) {
    game->setState(state);
    delete this;
}

void State::resetInitTime() {
    initTime = SDL_GetTicks();
}