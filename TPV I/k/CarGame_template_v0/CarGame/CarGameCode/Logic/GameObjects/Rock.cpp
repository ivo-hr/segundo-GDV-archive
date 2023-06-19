#include "Rock.h"
#include "../Game.h"

void Rock::update() {

}


Rock::Rock(Game* game): BadObject(game)
{
    texture = nullptr;
}

Rock::~Rock() {};

void Rock::draw() {
    drawTexture(game->getTexture(rockTexture));
}

bool Rock::receiveCarCollision(Car* car)
{
    alive = false;
    car->GetHit();
    return true;
}