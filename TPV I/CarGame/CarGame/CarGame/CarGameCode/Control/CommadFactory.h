#pragma once
#include <vector>

#include "QuitCommand.h"
#include "NextStateCommand.h"

class CommandFactory {

    vector<Command*> availableCommands;
    Game* game;
public:
    CommandFactory(Game* g) {
        game = g;
        game->clearHelp();
    }

    ~CommandFactory() {
        for (auto c : availableCommands)
            delete c;
    }

    Command* getCommand(SDL_Event& event) {
        for (auto c : availableCommands) {
            if (c->parse(event)) return c;
        }
        return nullptr;
    }

    void add(Command* c) {
        c->bind(game);
        availableCommands.push_back(c);
    }
};