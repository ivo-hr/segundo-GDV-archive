#include "Coin.h"
#include "../Game.h"

void Coin::update() {

}


Coin::Coin(Game* game): GoodObject(game)
{
	texture = nullptr;
}

Coin::~Coin() {};

void Coin::draw() {
    drawTexture(game->getTexture(coinTexture));
}

bool Coin::receiveCarCollision(Car* car)
{
	alive = false;
	car->AddPower();
	return true;
}
