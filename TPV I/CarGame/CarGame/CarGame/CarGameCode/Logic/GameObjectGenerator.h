#pragma once

#include "Game.h"


class GameObjectGenerator {

    Point2D<int> static generateRandomPosition(Game* game, GameObject* o) {
        // TODO
        int x = rand() % 800;
        int y = rand() % 300;
        return Point2D<int>(x, y);
    }

    void static addInRandomPosition(Game* game, GameObject* o) {
        Point2D<int> pos = generateRandomPosition(game, o);
        o->setPosition(pos.getX(), pos.getY());
        game->addObject(o);
    }
public:

    static void generate(Game* game,
        int N_ROCKS,
        int N_POWER_UPS = 0
        ) {
        srand(time(nullptr));

        for (int i = 0; i < N_ROCKS; i++)
            addInRandomPosition(game, new Rock(game));
        for (int i = 0; i < N_POWER_UPS; i++)
            addInRandomPosition(game, new PowerUp(game));
    }

};