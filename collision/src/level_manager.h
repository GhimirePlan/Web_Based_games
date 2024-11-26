#pragma once
#include <raylib.h>
#include <fstream>
#include <raymath.h>
#include <vector>
#include <array>
#include "collision_manager.h"
#include "level.h"
#include "body.h"
#include "menu.cpp"
#include "lose_menu.h"
#include "win_menu.h"
class LoseMenu;
class LevelManager
{
    std::vector<Level> levels;
    std::vector<Body *> l1bodies;
    std::vector<Body *> l2bodies;
    std::vector<Body *> l3bodies;
    CollisionManager *cm;
    std::vector<std::vector<Body>> b;
    std::vector<Body> b2;
    std::vector<Body> b3;
    Body bb;

public:
    std::vector<std::vector<std::vector<float>>> data;
    static int levelIndex;
    std::fstream ifile;

    void initialize();
    LevelManager();
    void LoadLevelFromFile();
    char *SaveLevelToFile();
    LevelManager(CollisionManager *cm);
    void loadLevel();
    void drawLevel();

    void endLevel();
};