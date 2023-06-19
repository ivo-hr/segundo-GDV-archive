#pragma once

#include <vector>
using namespace std;

class GameObject;
class Collider;

class GameObjectContainer {
    vector<GameObject*> gameObjects;
public:

    GameObjectContainer() {};
    ~GameObjectContainer();
    void update();
    void draw();
    void drawDebug();
    void add(GameObject* gameObject);
    void removeDead();
    bool hasCollision(GameObject* g);
    vector<Collider*> getCollisions(GameObject* g);
    void clear();
};