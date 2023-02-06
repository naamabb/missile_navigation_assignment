#pragma once
#include "MovingObject.h"
#include <algorithm>

#define N 3

class Missile
{
public:
    Vector2f direction, location;
    double speed;
    double aMax;
    //Vector2f velocity;
    Vector2f a;
    MovingObject* target;
    Missile(float x, float y, double vm, double a_max) {
        location << x, y;
        speed = vm;
        aMax = a_max;
    }
    float move(double timeStep); // returns the lateral acceleration.
    int findTarget(std::vector<MovingObject*>&);
    bool checkCollision(MovingObject* other,double dk);
    double calculateDistance(MovingObject* other);

};

