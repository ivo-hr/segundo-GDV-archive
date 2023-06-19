#include "GameObjectContainer.h"
#include "GameObjects/GameObject.h"

void GameObjectContainer::update() {
    for (auto g : gameObjects)
        g->update();
    removeDead();
}

void GameObjectContainer::draw() {
    for (auto g : gameObjects)
        g->draw();
}

void GameObjectContainer::drawDebug() {
    for (auto g : gameObjects)
        g->drawDebug();
}

GameObjectContainer::~GameObjectContainer() {
    for (auto g : gameObjects)
        delete g;
    gameObjects.clear();
}

void GameObjectContainer::add(GameObject* gameObject) {
    gameObjects.push_back(gameObject);
    gameObject->onEnter();
}

void GameObjectContainer::removeDead() {
    vector<GameObject*> tmp;
    for (auto g : gameObjects) {
        if (g->toDelete()) {
            g->onDelete();
            delete g;
        }

        else
            tmp.push_back(g);
        gameObjects = tmp;
    }
}

bool GameObjectContainer::hasCollision(GameObject* g) {
    // TODO
    return false;
}

vector<Collider*> GameObjectContainer::getCollisions(GameObject* g) {
    vector<Collider*> collisions;
    // TODO
    return collisions;
}

void GameObjectContainer::clear() {
 // TODO
}
