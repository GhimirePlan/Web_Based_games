#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <body.h>
#include <iostream>
#include "collision_manager.h"

class Level{
    std::vector<Body*> bodies;
    CollisionManager cm;
    public:
    Level(Body *b){
        bodies.emplace_back(b);
    }
    Level(){}

    Level(Level& l){
        bodies = l.bodies;
    }
    
    Level(Level&& l){
        bodies = l.bodies;
    }
    ~Level(){}

    Level(std::vector<Body> bodies,Body* bd){
        this->bodies.reserve(100);
        for(int i =0;i<bodies.size();i++){
            this->bodies.push_back(bd+i);
            std::cout<<this->bodies[i]->getBounds().x;
        }
    }

    void DrawLevel(){
        for(int i = 0; i<bodies.size();i++){
            bodies[i]->Draw();
        }
    }
    std::vector<Body*> getBodies(){
        std::cout<<bodies[0]->getBounds().x;
        for(int i = 0;i<bodies.size();i++){
           std::cout<<bodies[i]->getBounds().x;
        }
        return bodies;
    }
};