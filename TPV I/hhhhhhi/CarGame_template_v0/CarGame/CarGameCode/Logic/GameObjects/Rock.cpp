#include "Rock.h"
#include "../Game.h"

void Rock::update() {

}


Rock::Rock(Game* game) {
    this->game = game;
    texture = nullptr;
}

Rock::~Rock() {};

void Rock::draw() {
    drawTexture(game->getTexture(rockTexture));
}

bool Rock::receiveCarCollision(Car* car)
{
    car->GetHit();
    return true;
}