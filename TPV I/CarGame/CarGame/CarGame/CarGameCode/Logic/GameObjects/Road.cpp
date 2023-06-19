#include "Road.h"
#include "../../View/Box.h"
#include "../Game.h"

Road::Road(Game* game) : GameObject(game) {}

int Road::getLength() {
    return length;
}
void Road::setLength(int _length) {
    length = _length;
}

void Road::draw() {
    int dX = game->getOrigin().getX();
    int dY = game->getOrigin().getY();

    SDL_Rect rect = { 0, dY, getWidth(), getHeight() };
    Box(rect, BLACK).render(game->getRenderer());

    rect = { getLength() + dX, dY, 40, getHeight() };
    game->getTexture(goalTexture)->render(rect);


}

void Road::drawDebug() {
    int dY = game->getOrigin().getY();
    int dX = game->getOrigin().getX();

    SDL_Rect rect = { getWidth() / 2, dY, 1, getHeight() };
    Box(rect, YELLOW).render(game->getRenderer());

    rect = { 0, dY + getHeight() / 2, getWidth(), 1 };
    Box(rect, YELLOW).render(game->getRenderer());

    rect = { getLength() + dX, dY, 1, getHeight() };
    Box(rect, BLACK).render(game->getRenderer());

}