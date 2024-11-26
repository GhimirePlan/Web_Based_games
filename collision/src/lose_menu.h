
#pragma once
#include <raylib.h>
#include "level_manager.h"

#include <raylib.h>
class LevelManager;
class LoseMenu{
    LevelManager *lm;
    public:
    LoseMenu(){}
    void Draw();

    void Update();
};
