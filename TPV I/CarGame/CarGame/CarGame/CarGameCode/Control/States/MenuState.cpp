#include "MenuState.h"

#include "../../Logic/Game.h"

MenuState::MenuState(Game* game) : State(game) {
    registerCommands();
}

void MenuState::registerCommands() {
    game->clearHelp();
    commandFactory->add(new NextStateCommand());
    commandFactory->add(new QuitCommand());
}

void MenuState::update() {
}

void MenuState::draw() {
    int x = game->getWindowWidth() / 2 - 100;
    int y = game->getWindowHeight() / 2 - 50;

    vector<string> texts = {
            "Welcome to Super Cars",
            "Press space to start",
            "Press [h] for help"
    };

    game->renderText(texts, x, y);

   // game->drawHelp();
   // game->drawStateName();
}

void MenuState::next() {
    cout << "Next State " << endl;
    game->setState(new MenuState(game));
    delete this;
}
