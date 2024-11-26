
#pragma once
#include <raylib.h>
#include <rlgl.h>
#include <cmath>
#include <vector>
class Body{
    public:
    Body(){
        angle=32;
        
        x=200;
        speed={0,0};
        sizex=100;
        sizey=300;
        y=200;

    }
    Body(int x, int y, int sizex, int sizey, float angle, Vector2 speed):
    x(x), y(y), sizex(sizex), sizey(sizey), angle(angle){
        this->speed.x = speed.x;
        this->speed.y = speed.y;
    };
    Body(int x, int y, int sizex, int sizey, float angle, Vector2 speed, bool win):
    x(x), y(y), sizex(sizex), sizey(sizey), angle(angle), win(win){
        this->speed.x = speed.x;
        this->speed.y = speed.y;
    };
    void initUsingArray(std::vector<float> f){
        if(f.size()==8){
            x = f[0];
            y = f[1];
            sizex = f[2];
            sizey = f[3];
            angle = f[4];
            speed.x = f[5];
            speed.y = f[6];
            win = bool(f[7]);
        }
    }
    Body(const Body& b){
        x = b.x;
        y = b.y;
        speed = b.speed;
        angle = b.angle;
        sizex = b.sizex;
        sizey = b.sizey;
        win = b.win;
    }
    Body(const Body&& b){
        this->x = b.x;
        this->y = b.y;
        this->speed = b.speed;
        this->angle = b.angle;
        this->sizex = b.sizex;
        this->sizey = b.sizey;
        this->win = b.win;
    }
    ~Body(){

    }
    Body& operator=(Body b){
        this->x = b.x;
        this->y = b.y;
        this->speed = b.speed;
        this->angle = b.angle;
        this->sizex = b.sizex;
        this->sizey = b.sizey;
        this->win = b.win;

    }
    virtual void Update(){
    }
    virtual void Draw(){
    rlPushMatrix();
    rlTranslatef(x+sizex/2,y+sizey/2,0);
    rlRotatef(angle,0,0,1);
    DrawRectangle(-sizex/2,-sizey/2,sizex,sizey,RED);
    rlPopMatrix();
    }
    virtual Vector2 getBounds(){
        return {float(sizex/2), float(sizey/2)};
    }
    virtual void Collide(Vector2 normal){

    }
    virtual Vector2 getPos(){
        
    Vector2 res;
    res.x = x+sizex/2;
    res.y = y+sizey/2;
    return res;
    }
    void setPos(Vector2 pos){
        x = pos.x;
        y = pos.y;
    }
    virtual Vector2 getSpeed(){
        return speed;
    }
    virtual void setSpeed(Vector2 s){
        speed.x = s.x;
        speed.y = s.y;
    }
    std::vector<Vector2> getAxis();
    virtual std::vector<Vector2> getCorners();
    std::vector<bool> project(Body*);
    Color col;
    float angle;
    
    bool win=false;
    protected:
    int x;
    Vector2 speed;
    int sizex;
    int sizey;
    int y;

};