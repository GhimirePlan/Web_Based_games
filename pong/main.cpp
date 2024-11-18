#include "raylib.h"

// Define game states
typedef enum GameScreen { TITLE, GAMEPLAY, HELP, SETTINGS, DEVELOPER } GameScreen;

// Button area and debouncing constants
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 100
#define DEBOUNCE_TIME 0.2f // Debounce time in seconds

int main() {
    // Initialize the screen
    const int screenWidth = 800;
    const int screenHeight = 400;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Enhanced Pong Game");

    // Load sound effects
    InitAudioDevice();
    Sound collisionSound = LoadSound("collision.wav");

    // Define paddles and ball
    Rectangle player1 = { 50, screenHeight/2 - 50, 10, 100 };
    Rectangle player2 = { screenWidth - 60, screenHeight/2 - 50, 10, 100 };
    Rectangle ball = { screenWidth/2 - 10, screenHeight/2 - 10, 20, 20 };

    Vector2 ballSpeed = { 5.0f, 5.0f };
    int player1Score = 0;
    int player2Score = 0;

    // Movement direction flags
    bool player1MovingUp = false;
    bool player1MovingDown = false;
    bool player2MovingUp = false;
    bool player2MovingDown = false;

    // Toggle states
    bool player1ToggleState = false;
    bool player2ToggleState = false;

    // Button timings
    float player1ButtonTime = 0.0f;
    float player2ButtonTime = 0.0f;

    // Game state
    GameScreen currentScreen = TITLE;
    bool singlePlayerMode = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector2 inputPos = GetMousePosition();
        float currentTime = GetTime();

        // Handle touch inputs
        bool touchPressed = IsGestureDetected(GESTURE_TAP);
        Vector2 touchPos = GetTouchPosition(0);

        // Game screen management
        switch(currentScreen) {
            case TITLE: {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || touchPressed) {
                    Vector2 clickPos = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ? inputPos : touchPos;

                    if (CheckCollisionPointRec(clickPos, (Rectangle){screenWidth/2 - 100, 120, 200, 50})) {
                        singlePlayerMode = true;
                        currentScreen = GAMEPLAY;
                    } else if (CheckCollisionPointRec(clickPos, (Rectangle){screenWidth/2 - 100, 180, 200, 50})) {
                        singlePlayerMode = false;
                        currentScreen = GAMEPLAY;
                    } else if (CheckCollisionPointRec(clickPos, (Rectangle){screenWidth/2 - 100, 240, 200, 50})) {
                        currentScreen = HELP;
                    } else if (CheckCollisionPointRec(clickPos, (Rectangle){screenWidth/2 - 100, 300, 200, 50})) {
                        currentScreen = SETTINGS;
                    } else if (CheckCollisionPointRec(clickPos, (Rectangle){screenWidth/2 - 100, 360, 200, 50})) {
                        currentScreen = DEVELOPER;
                    }
                }
            } break;
            case GAMEPLAY: {
                // Player 1 controls
                Rectangle player1Button = { 10, screenHeight - 120, BUTTON_WIDTH, BUTTON_HEIGHT };
                bool player1ButtonPressed = (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(inputPos, player1Button)) ||
                                            (touchPressed && CheckCollisionPointRec(touchPos, player1Button));
                if (player1ButtonPressed && (currentTime - player1ButtonTime) > DEBOUNCE_TIME) {
                    player1ToggleState = !player1ToggleState;
                    player1ButtonTime = currentTime;
                }
                
                player1MovingUp = player1ToggleState;
                player1MovingDown = !player1ToggleState;

                // Player 2 controls (Multiplayer mode)
                if (!singlePlayerMode) {
                    Rectangle player2Button = { screenWidth - 120, screenHeight - 120, BUTTON_WIDTH, BUTTON_HEIGHT };
                    bool player2ButtonPressed = (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(inputPos, player2Button)) ||
                                                (touchPressed && CheckCollisionPointRec(touchPos, player2Button));
                    if (player2ButtonPressed && (currentTime - player2ButtonTime) > DEBOUNCE_TIME) {
                        player2ToggleState = !player2ToggleState;
                        player2ButtonTime = currentTime;
                    }
                    
                    player2MovingUp = player2ToggleState;
                    player2MovingDown = !player2ToggleState;
                }

                // Move Player 1's paddle
                if (player1MovingUp) {
                    player1.y -= 5.0f;
                }
                if (player1MovingDown) {
                    player1.y += 5.0f;
                }

                // Move Player 2's paddle
                if (player2MovingUp) {
                    player2.y -= 5.0f;
                }
                if (player2MovingDown) {
                    player2.y += 5.0f;
                }

                // Keep paddles inside the screen
                if (player1.y <= 30) player1.y = 30;
                if (player1.y + player1.height >= screenHeight - 30) player1.y = screenHeight - 30 - player1.height;

                if (player2.y <= 30) player2.y = 30;
                if (player2.y + player2.height >= screenHeight - 30) player2.y = screenHeight - 30 - player2.height;

                // Move the ball
                ball.x += ballSpeed.x;
                ball.y += ballSpeed.y;

                // Ball collision with top and bottom walls
                if (ball.y <= 30 || ball.y + ball.height >= screenHeight - 30) {
                    ballSpeed.y *= -1.0f;
                    PlaySound(collisionSound);
                }

                // Ball collision with paddles
                if (CheckCollisionRecs(ball, player1) || CheckCollisionRecs(ball, player2)) {
                    ballSpeed.x *= -1.0f;
                    PlaySound(collisionSound);
                    if (CheckCollisionRecs(ball, player1)) player1.y += 2; // Small effect to show impact
                    else player2.y -= 2; // Small effect to show impact
                }

                // Score update
                if (ball.x + ball.width < 0) {
                    player2Score++;
                    ball = { screenWidth/2 - 10, screenHeight/2 - 10, 20, 20 };
                    ballSpeed = { 5.0f, 5.0f };
                }
                if (ball.x > screenWidth) {
                    player1Score++;
                    ball = { screenWidth/2 - 10, screenHeight/2 - 10, 20, 20 };
                    ballSpeed = { 5.0f, 5.0f };
                }

                // Drawing gameplay
                BeginDrawing();
                ClearBackground(DARKBLUE);

                // Draw border rectangle
                DrawRectangle(30, 30, screenWidth - 60, screenHeight - 60, BLACK);

                // Draw paddles
                DrawRectangleRounded(player1, 0.5f, 10, SKYBLUE);
                DrawRectangleRounded(player2, 0.5f, 10, ORANGE);

                // Draw ball
                DrawCircleV((Vector2){ball.x + ball.width / 2, ball.y + ball.height / 2}, ball.width / 2, GOLD);

                // Draw scores
                DrawText(TextFormat("%i", player1Score), screenWidth/4 - 20, 20, 60, SKYBLUE);
                DrawText(TextFormat("%i", player2Score), 3*screenWidth/4 - 20, 20, 60, ORANGE);

                // Draw control buttons for paddles
                DrawRectangleRounded(player1Button, 0.5f, 10, LIGHTGRAY);
                DrawText("P1", player1Button.x + 20, player1Button.y + 20, 40, DARKBLUE);

                if (!singlePlayerMode) {
                    Rectangle player2Button = { screenWidth - 120, screenHeight - 120, BUTTON_WIDTH, BUTTON_HEIGHT };
                    DrawRectangleRounded(player2Button, 0.5f, 10, LIGHTGRAY);
                    DrawText("P2", player2Button.x + 20, player2Button.y + 20, 40, DARKBLUE);
                }

                EndDrawing();
            } break;
            case HELP: {
                BeginDrawing();
                ClearBackground(DARKBLUE);
                DrawText("Help:\n- Use the P1 button to toggle control of the left paddle.\n- In single player mode, AI controls the right paddle.\n- In multiplayer, use the P2 button to control the right paddle.", 50, 50, 20, WHITE);
                DrawText("Press ESC to go back", 50, screenHeight - 50, 20, GRAY);
                if (IsKeyPressed(KEY_ESCAPE)) currentScreen = TITLE;
                EndDrawing();
            } break;
            case SETTINGS: {
                BeginDrawing();
                ClearBackground(DARKBLUE);
                DrawText("Settings:\n- Customize settings in future versions.", 50, 50, 20, WHITE);
                DrawText("Press ESC to go back", 50, screenHeight - 50, 20, GRAY);
                if (IsKeyPressed(KEY_ESCAPE)) currentScreen = TITLE;
                EndDrawing();
            } break;
            case DEVELOPER: {
                BeginDrawing();
                ClearBackground(DARKBLUE);
                DrawText("Developer Details:\n- Developed by Plan Ghimire.", 50, 50, 20, WHITE);
                DrawText("Press ESC to go back", 50, screenHeight - 50, 20, GRAY);
                if (IsKeyPressed(KEY_ESCAPE)) currentScreen = TITLE;
                EndDrawing();
            } break;
            default: break;
        }

        if (currentScreen == TITLE) {
            BeginDrawing();
            ClearBackground(DARKBLUE);
            DrawText("Pong Game", screenWidth/2 - MeasureText("Pong Game", 40)/2, 60, 40, WHITE);
            DrawRectangle(screenWidth/2 - 100, 120, 200, 50, LIGHTGRAY);
            DrawRectangle(screenWidth/2 - 100, 180, 200, 50, LIGHTGRAY);
            DrawRectangle(screenWidth/2 - 100, 240, 200, 50, LIGHTGRAY);
            DrawRectangle(screenWidth/2 - 100, 300, 200, 50, LIGHTGRAY);
            DrawRectangle(screenWidth/2 - 100, 360, 200, 50, LIGHTGRAY);
            DrawText("Single Player", screenWidth/2 - MeasureText("Single Player", 20)/2, 135, 20, DARKBLUE);
            DrawText("Multiplayer", screenWidth/2 - MeasureText("Multiplayer", 20)/2, 195, 20, DARKBLUE);
            DrawText("Help", screenWidth/2 - MeasureText("Help", 20)/2, 255, 20, DARKBLUE);
            DrawText("Settings", screenWidth/2 - MeasureText("Settings", 20)/2, 315, 20, DARKBLUE);
            DrawText("Developer", screenWidth/2 - MeasureText("Developer", 20)/2, 375, 20, DARKBLUE);
            EndDrawing();
        }
    }

    // Unload sound and close window
    UnloadSound(collisionSound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
