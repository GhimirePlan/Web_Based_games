
#include "level_manager.h"
#include <fstream>
#include <string>
#include <IOSTREAM>
using namespace std;
int LevelManager::levelIndex = -1;
void LevelManager::initialize()
{
    for (int i = 0; i < data.size(); i++)
    {
        Body bd;
        for (int j = 0; j < data[i].size(); j++)
        {

            bd.initUsingArray(data[i][j]);

            b[i].push_back(bd);
        }
        levels.reserve(100);
        Level l(b[i], b[i].data());
        levels.emplace_back(l);
    }
}
LevelManager::LevelManager()
{
    ifile.open("levels.data", ios::in);
    if (!ifile)
    {
        cout << "NOT WORKING";
    }
    levelIndex = -1;
}
LevelManager::LevelManager(CollisionManager *cm)
{
    data = {
        {{200, 200, 100, 300, 32, 0, 0, 0},
         {200, 100, 10, 120, 45, 0, 0, 0},
         {100, 100, 120, 40, 20, 0, 0, 0},
         {1000, 350, 300, 90, 22, 0, 0, 1},
         {100, 650, 300, 90, 22, 0, 0, 0}},
        {{200, 200, 100, 300, 32, 0, 0, 1},
         {200, 100, 10, 120, 45, 0, 0, 0}},
        {{500, 200, 100, 300, 32, 0, 0, 1}},
        {{200, 200, 100, 300, 32, 0, 0, 0},
         {1600, 350, 300, 90, 22, 0, 0, 1}}};
    b.resize(50);
    for (int i = 0; i < 50; i++)
    {

        b[i].reserve(100);
    }
    levelIndex = -1;

    initialize();
    cout << b[0].at(3).getBounds().x;
    this->cm = cm;
}
void LevelManager::loadLevel()
{
    if (levelIndex > -1 && levelIndex < levels.size())
    {
        endLevel();
        for (int j = 0; j < levels[levelIndex].getBodies().size(); j++)
        {
            cm->add(levels[levelIndex].getBodies()[j]);
            cout << levels[levelIndex].getBodies()[j]->getBounds().x;
        }
    }
    else if (levelIndex >= levels.size() && levelIndex > 0)
    {
        LoseMenu l;
        l.Draw();
        l.Update();
    }
    else if (levelIndex == -1)
    {
    }
}
void LevelManager::drawLevel()
{
    if (levelIndex == -1)
    {
        MainMenu m;
        m.Draw();
    }
    else if (levelIndex == -2)
    {

        LoseMenu l;
        l.Draw();
        l.Update();
    }
    else
    {
        levels[levelIndex].DrawLevel();
    }
}

void LevelManager::endLevel()
{
    cm->clear();
}