#pragma once
#include "GameObject.h"

class Game;

class Road : public GameObject {
    int length;
public:
    Road(Game* game);
    ~Road() {};

    void draw() override;
    void drawDebug() override;
    void update() override {};

    void setLength(int length);
    int getLength();
};
