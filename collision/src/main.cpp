#include <raylib.h>
#include <raymath.h>
#include "ball.h"
#include "body.h"
#include <string>
#include "level_manager.h"
#include "collision_manager.h"
#include "menu.cpp"
#include <iostream>
int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    std::string s;
    Color darkGreen = Color{20, 160, 133, 255};

    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);
    InitWindow(1920, 1080, "My first RAYLIB program!");

    int levelIndex = 0;
    int clickCount = 0;
    bool isClicked = false;

    Ball ball;
    CollisionManager cm;
    LevelManager lm(&cm);
    cm.add(&ball);
    lm.loadLevel();
    SetTargetFPS(120);

    float time = GetTime();
    float deltaTime;
    bool prevCol = false;
    int i = 0;
    MainMenu *m = new MainMenu();
    while (!WindowShouldClose())
    {
        s = "Click Count: ";
        s.append(std::to_string(clickCount));
        if (i < 60)
            deltaTime = GetFrameTime();

        i++;

        if (IsKeyPressed(KEY_SPACE))
        {

            lm.levelIndex++;
            lm.endLevel();
            lm.loadLevel();
        }
        if (IsMouseButtonDown(0) && lm.levelIndex == -1)
        {
            lm.levelIndex++;
            lm.endLevel();
            lm.loadLevel();
        }
        BeginDrawing();
        ClearBackground(darkGreen);
        ball.Update(time, deltaTime);
        prevCol = cm.checkCol(&ball, prevCol, lm.levelIndex);

        if (lm.levelIndex < 0)
        {
        }
        else
        {
            ball.Draw();
            DrawText(s.c_str(), 0, 0, 50, BLACK);
        }
        lm.endLevel();
        lm.loadLevel();
        lm.drawLevel();
        Vector2 del = Vector2Subtract(ball.getPos(), GetMousePosition());
        del = Vector2Normalize(del);
        if (IsMouseButtonDown(0))
        {
            ball.setSpeed({0, 0});
            DrawLine(GetMousePosition().x, GetMousePosition().y, GetMousePosition().x + del.x * 350, GetMousePosition().y + del.y * 350, MAGENTA);
        }
        if (IsMouseButtonDown(0) && !isClicked && lm.levelIndex >= 0)
        {
            clickCount++;
            std::cout << clickCount;
            isClicked = true;
        }
        if (IsMouseButtonReleased(0))
        {
            isClicked = false;
            ball.setSpeed({del.x * 1000, del.y * 1000});
        }
        if (clickCount >= 10)
        {
            lm.endLevel();
            lm.levelIndex = -2;
            clickCount = 0;
            lm.drawLevel();
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}