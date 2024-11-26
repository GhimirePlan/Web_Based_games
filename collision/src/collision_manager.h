#pragma once
#include <raylib.h>
#include <body.h>
#include <vector>
class CollisionManager{
    std::vector<Body*> bodies;
    public:
    bool checkCol(Body*, bool, int &levelIndex);
    void add(Body*);
    void clear(){
        bodies.clear();
    }

};