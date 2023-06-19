#pragma once
class Game;

class Infobar {
    Game* game;
public:
    Infobar(Game* game) :game(game) {}

    void drawInfo();
    void drawHelp();
    void drawState();
};
