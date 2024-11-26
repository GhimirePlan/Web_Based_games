#pragma once
#include <raylib.h>
class MainMenu{
    public:
    MainMenu(){

        
    }
    void Draw(){
        int textSize = MeasureText("PRESS SPACE TO ENTER", 50);
        DrawText("PRESS SPACE TO ENTER", (GetScreenWidth()-textSize)/2, GetScreenHeight()/2,50, RED);   
    }
};