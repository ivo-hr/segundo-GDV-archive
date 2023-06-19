#include "FinLine.h"
#include "../Game.h"

FinLine::FinLine(Game* game) {
    this->game = game;
    texture = nullptr;

}

void FinLine::update() {

}

FinLine::~FinLine() {};

void FinLine::draw() {
    drawTexture(game->getTexture(goalTexture));
}