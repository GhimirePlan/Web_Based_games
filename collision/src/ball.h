#pragma once
#include <raylib.h>
#include <body.h>
#include <raymath.h>

class Ball : public Body
{
public:
    Ball();
    void Update(float, float);
    void Draw();
    void Collide(Vector2);
    Vector2 getPos();
    Vector2 getSpeed();
    void setSpeed(Vector2);
    bool ax=true;
    bool ay=true;
    std::vector<Vector2> getCorners();

private:
    Vector2 speed;
    int radius;
};