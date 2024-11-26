#pragma once
#include "ball.h"
#include <raylib.h>
#include <cmath>
#include <iostream>
Ball::Ball()
{
    x = 455;
    y = 455;
    speed = {-1000,-1000};
    radius = 30;
    angle = 0;
    sizex=2*radius;
    sizey = 2*radius;
    col = BLACK;
}

void Ball::Update(float time, float deltaTime)
{
    x += speed.x*deltaTime;
    y += speed.y*deltaTime;
        if (x + radius > GetScreenWidth() || x - radius < 0){
            if(ax){
                speed.x *= -1;
                ax = false;
            }else{
                if(x + radius > GetScreenWidth()){
                    x = GetScreenWidth()-radius;
                }else if(x - radius < 0){
                    x = radius;
                }
            }
        }else{
            ax = true;
        }
        if (y + radius > GetScreenHeight() || y - radius < 0){
                if(ay){
                    speed.y *= -1;
                    ay = false;
                }else{
                if(y + radius > GetScreenHeight()){
                    y = GetScreenHeight()-radius;
                }else if(y - radius < 0){
                    y = radius;
                }
            }
            }
        else{
            ay = true;
        }
    speed.x = Lerp(speed.x, 0, deltaTime*0.15);
    speed.y = Lerp(speed.y, 0, 0.15*deltaTime);
}

void Ball::Draw()
{
    DrawCircle(x, y, radius, col);
}

Vector2 Ball:: getSpeed(){
        return speed;
    }
    void Ball::setSpeed(Vector2 s){
        speed.x = s.x;
        speed.y = s.y;
    }
void Ball::Collide(Vector2 normal){
        float nmag = normal.x*normal.x+normal.y*normal.y;
        Vector2 u = {(speed.x*normal.x+speed.y*normal.y)*normal.x, (speed.x*normal.x+speed.y*normal.y)*normal.y};
        speed.x = speed.x-u.x*2;
        speed.y = speed.y-u.y*2;

}
std::vector<Vector2> Ball::getCorners(){
    std::vector<Vector2> axes = getAxis();
    Vector2 X = Vector2Scale(axes[0],(sizex/2));
    Vector2 Y = Vector2Scale(axes[1],(sizey/2));
    std::vector<Vector2> cor = {
        Vector2Add(this->getPos(),Vector2Add(X,Y)),
        Vector2Add(this->getPos(),Vector2Subtract(X,Y)),
        Vector2Subtract(this->getPos(),Vector2Add(X,Y)),
        Vector2Subtract(this->getPos(),Vector2Subtract(X,Y)),

    };
    DrawLine(this->getPos().x,this->getPos().y, cor[3].x,cor[3].y, RED);
    DrawLine(this->getPos().x,this->getPos().y, cor[2].x,cor[2].y, RED);
    DrawLine(this->getPos().x,this->getPos().y, cor[1].x,cor[1].y, RED);
    DrawLine(this->getPos().x,this->getPos().y, cor[0].x,cor[0].y, RED);
    //std::cout<<"{"<<getPos().x<<","<<getPos().y<<"}";
    return cor;
}

Vector2 Ball::getPos(){
    Vector2 res;
    res.x = x;
    res.y = y;
    return res;
}