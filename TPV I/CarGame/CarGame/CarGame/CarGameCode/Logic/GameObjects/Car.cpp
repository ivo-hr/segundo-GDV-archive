//
// Created by eys on 21/8/21.
//

#include "Car.h"
#include "../Game.h"

Car::Car(Game *game):GameObject(game){
    setTexture(carTexture);
    
    setDimension(100, 50);
}

void Car::update() {
    int y = getY() + verticalMove * VSPEED;
    setPosition(getX() + 1, y);
}

Car::~Car(){};



void Car::drawTexture(Texture *texture) {
    int dX = game->getOrigin().getX();
    int dY = game->getOrigin().getY();


    SDL_Rect c = getCollider();
    SDL_Rect textureBox = { c.x + dX, c.y + dY, c.w, c.h};
    texture->render(textureBox);
}


SDL_Rect Car::getCollider(){
    return { int(getX() - getWidth()),
             int(getY() - getHeight()/2),
             getWidth(),
             getHeight()};
}

void Car::setVerticalMove(int dir)
{
    verticalMove = dir;
}