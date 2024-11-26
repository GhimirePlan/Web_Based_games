
#pragma once
#include <raylib.h>
#include "level_manager.h"

#include <raylib.h>
class LevelManager;
class WinMenu{
    LevelManager *lm;
    public:
    WinMenu(){}
    void Draw();

    void Update();
};
