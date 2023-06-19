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

    int yMov = 0;
    float xMov = 1;

    int currPower = INITIAL_POWER;

public:
    Car(Game* game);
    ~Car();

    void draw() override;

    void update() override;

    float getSpeed() { return xMov; };

    void MoveX(int movX);
    void MoveY(int movY);
    void GetHit();
    void AddPower();
    int Power();

    SDL_Rect getCollider() override;
};


#endif //CARGAME_CAR_H