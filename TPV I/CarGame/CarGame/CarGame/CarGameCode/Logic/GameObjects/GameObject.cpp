#include "GameObject.h"
#include "../Game.h"

void GameObject::drawTexture(Texture* texture) {

    int dX = game->getOrigin().getX();
    int dY = game->getOrigin().getY();

    SDL_Rect c = getCollider();
    SDL_Rect textureBox = { c.x + dX, c.y + dY, c.w, c.h };
    texture->render(textureBox);
}
void GameObject::draw()
{
    drawTexture(texture);
}

void GameObject::drawDebug() {
    Box(getCenter(), BLUE).render(game->getRenderer(), game->getOrigin());
    Box(getCollider(), RED).render(game->getRenderer(), game->getOrigin());
}


SDL_Rect GameObject::getCollider() {
    return { int(getX() - getWidth() / 2),
             int(getY() - getHeight() / 2),
             getWidth(),
             getHeight() };
}

SDL_Rect GameObject::getCenter() {
    const int s = 10;
    SDL_Rect rect = { int(getX() - s / 2),
                      int(getY() - s / 2),
                      s,
                      s };
    return rect;
}
bool GameObject::collide(SDL_Rect other) {
    SDL_Rect collider = getCollider();
    return SDL_HasIntersection(&collider, &other);
};


void GameObject::setPosition(double x, double y) {
    pos = Point2D<double>(x, y);
};

void GameObject::setDimension(double width, double height) {
    w = width;
    h = height;
};
void GameObject::setTexture(TextureName textureName)
{
    this->texture = game->getTexture(textureName);
}