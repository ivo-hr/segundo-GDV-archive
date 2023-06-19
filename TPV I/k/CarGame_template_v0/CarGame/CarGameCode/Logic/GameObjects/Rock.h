
#ifndef CARGAME_ROCK_H
#define CARGAME_ROCK_H

#include "GameObject.h"
#include "BadObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Rock : public BadObject{


public:

    Rock(Game* game);
    ~Rock();

    void draw();
    void update();
    bool receiveCarCollision(Car* car) override;
};



#endif 