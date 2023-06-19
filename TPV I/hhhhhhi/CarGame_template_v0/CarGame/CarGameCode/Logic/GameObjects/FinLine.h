
#ifndef CARGAME_FINLINE_H
#define CARGAME_FINLINE_H


class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class FinLine {

private:

    Point2D<double> pos;
    int w, h;
    Game* game;
    Texture* texture;

public:
    FinLine(Game* game);
    ~FinLine();

    void draw();
    void update();
    void drawTexture(Texture* texture);

    void setDimension(int width, int height);

    double getX() { return pos.getX(); };
    double getY() { return pos.getY(); };
    int getWidth() { return w; };
    int getHeight() { return h; };

    void setPosition(double x, double y);

    SDL_Rect getCollider();
};


#endif 