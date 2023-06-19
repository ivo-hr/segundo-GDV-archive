#ifndef CARGAME_GOODOBJECT_H
#define CARGAME_GOODOBJECT_H

class Game;
#include "GameObject.h"

class GoodObject : public GameObject {
protected:
    bool alive;
public:
    static int instances;
    GoodObject(Game* game) {   //???????????????????????????????????
        this->game = game;
        alive = true;
    };

    ~GoodObject() override = default;
    void update() override{};
    bool toDelete() override;

    void onEnter() override;
    void onDelete() override;
    void static reset();
};


#endif //CARGAME_GOODOBJECT_H