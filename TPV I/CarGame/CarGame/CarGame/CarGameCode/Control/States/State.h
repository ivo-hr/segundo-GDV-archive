#pragma once

#include "../CommadFactory.h"

class Game;
using namespace std;

class State {
protected:
    Game* game = nullptr;
    CommandFactory* commandFactory = nullptr;

    Uint32 initTime;
    Uint32 totalTime;
public:
    State(Game* game) : game(game) {
        commandFactory = new CommandFactory(game);
    };

    virtual ~State() {
        delete commandFactory;
    };
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void next() = 0;
    virtual void jump(State* state);
    bool doQuit();
    virtual string getStateName() const = 0;
    void handleEvents();
    virtual void registerCommands() = 0;

    void resetInitTime();
};