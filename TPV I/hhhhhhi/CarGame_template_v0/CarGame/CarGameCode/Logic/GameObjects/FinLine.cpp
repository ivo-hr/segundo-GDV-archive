#include "FinLine.h"
#include "../Game.h"

FinLine::FinLine(Game* game) {
    this->game = game;
    texture = nullptr;

}

void FinLine::setDimension(int width, int height) {
    w = width;
    h = height;
}

void  FinLine::setPosition(double x, double y) {
    pos = Point2D<double>(x, y);
};

void FinLine::update() {

}

FinLine::~FinLine() {};

void FinLine::draw() {
    drawTexture(game->getTexture(goalTexture));
}


void FinLine::drawTexture(Texture* texture) {
    int dX = game->getOrigin().getX();
    int dY = game->getOrigin().getY();

    SDL_Rect c = getCollider();
    SDL_Rect textureBox = { c.x + dX, c.y + dY, c.w, c.h };
    texture->render(textureBox);
}


SDL_Rect FinLine::getCollider() {
    return { int(getX() - getWidth()),
             int(getY() - getHeight() / 2),
             getWidth(),
             getHeight() };
}