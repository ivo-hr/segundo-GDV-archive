#include "InfoBar.h"

#include "../Logic/Game.h"

void Infobar::drawInfo() {
    int x = game->font->getSize() / 2;
    int y = game->font->getSize() / 2;
    int inc = game->getWindowWidth() / 7;

    SDL_Rect rect = { 0, 0, game->getWindowWidth(),
                     int(game->font->getSize() * 1.8) };
    Box(rect, BLACK).render(game->renderer);

    string s = "Pos: " + to_string(int(game->car->getX())) + " "
        + to_string(int(game->car->getY()));
    game->renderText(s, x, y);


    // TODO


    x += inc;
    s = "Objs: [" + to_string(GoodObject::instances) + ", " + to_string(BadObject::instances) + "]";
    game->renderText(s, x, y);

}

void Infobar::drawHelp() {
    int x = game->font->getSize() / 2;
    int y = game->font->getSize() * 2;

    for (auto a : game->helpInfo) {
        game->renderText(a, x, y);
        y += game->font->getSize();
    }
}

void Infobar::drawState() {
    // TODO
}