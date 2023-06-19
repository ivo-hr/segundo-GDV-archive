#pragma once

#include "BadObject.h"

class Rock : public BadObject {

public:
    static const int dimension = 60;
    Rock(Game* game) : BadObject(game) {
        setDimension(dimension, dimension);
        setTexture(rockTexture);
    };
    ~Rock() = default;
    virtual bool receiveCarCollision(Car* car) override;
};
