#include "GameObject.h"

#include "../Game.h"


GameObject::GameObject()
{
}

void GameObject::drawTexture(Texture* texture)
{
    int dX = game->getOrigin().getX();
    int dY = game->getOrigin().getY();

    SDL_Rect c = getCollider();
    SDL_Rect textureBox = { c.x + dX, c.y + dY, c.w, c.h };
    texture->render(textureBox);
}

void GameObject::drawDebug()
{
    SDL_RenderDrawRect(SDL_GetRenderer(SDL_GL_GetCurrentWindow()), &getCollider());
    SDL_RenderDrawRect(SDL_GetRenderer(SDL_GL_GetCurrentWindow()), &getCenter());
}

void GameObject::setPosition(double x, double y)
{
    pos = Point2D<double>(x, y);
}

void GameObject::setDimension(double width, double height)
{
    w = width;
    h = height;
}

SDL_Rect GameObject::getCollider()
{
    return { int(getX() - getWidth() / 2),
             int(getY() - getHeight() / 2),
             getWidth(),
             getHeight() };
}

SDL_Rect GameObject::getCenter()
{
    return { int(getX() - 1),
             int(getY() - 1),
             2,
             2 };
}

bool GameObject::collide(SDL_Rect other)
{
    return SDL_HasIntersection(&getCollider(), &other);
}
