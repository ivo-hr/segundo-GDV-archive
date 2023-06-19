//
// Created by eys on 21/8/21.
//

#ifndef CARGAME_CAR_H
#define CARGAME_CAR_H


class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"
#include "GameObject.h"

class Car : public GameObject {

private:

    const double ACCELERATION = 1.3;
    const double DECELERATION = 0.9;
    const int VSPEED = 5;
    const int MAX_SPEED = 10;
    const int INITIAL_POWER = 3;

    int verticalMove;

public:
    Car(Game *game);
    ~Car();

    void update();

    void setVerticalMove(int dir);

    SDL_Rect getCollider();
    void drawTexture(Texture* texture) override;
};


#endif //CARGAME_CAR_H
