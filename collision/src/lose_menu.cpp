

#include "lose_menu.h"
// class LoseMenu{
//     LevelManager lm;
//     public:
//     LoseMenu(){}
//     void Draw(){
//         DrawText("YOU LOST! PRESS Q TO QUIT OR R TO RESTART", GetScreenHeight()/4, GetScreenWidth()/4, 50, BLACK);
//     }

//     void Update(){
//         if(IsKeyDown(KEY_Q)){
//             lm.levelIndex = 100;
//         }
//         if(IsKeyDown(KEY_R)){
//             lm.levelIndex = 0;
//         }
//     }
// };

void LoseMenu::Draw(){
    int textSize = MeasureText("YOU LOST! PRESS Q TO QUIT OR R TO RESTART", 50);  
    DrawText("YOU LOST! PRESS Q TO QUIT OR R TO RESTART", (GetScreenWidth()-textSize)/2, GetScreenHeight()/2, 50, BLACK);
}

void LoseMenu::Update(){
    if(IsKeyDown(KEY_Q)){
        CloseWindow();

        }
    if(IsKeyDown(KEY_R)){
            lm->levelIndex = 0;
        }   
}