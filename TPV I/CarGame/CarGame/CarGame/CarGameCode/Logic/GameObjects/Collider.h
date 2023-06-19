#pragma once
class Car;

class Collider {

public:
    virtual bool receiveCarCollision(Car* car) {
        return false;
    };
};
