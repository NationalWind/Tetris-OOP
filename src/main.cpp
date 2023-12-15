#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

enum MenuState
{
    MAIN_MENU,
    PLAYING,
    GAME_OVER,
    CREDITS,
    INSTRUCTIONS
};

double lastUpdateTime = 0;
MenuState currentMenuState = MAIN_MENU;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void DrawMainMenu(Font font)
{
    DrawTextEx(font, "Tetris Game", {110, 100}, 100, 2, DARKBROWN);

    // Press ESC to Exit box
    DrawRectangleRounded({10, 10, 200, 50}, 1, 10, PINK);
    DrawTextEx(font, "Press ESC to Exit", {20, 20}, 30, 2, DARKGRAY);

    // Play option
    DrawRectangleRounded({80, 230, 340, 80}, 1, 10, lightGreen);
    DrawTextEx(font, "Press ENTER to Play", {135, 245}, 45, 2, WHITE);

    // Credits option
    DrawRectangleRounded({80, 330, 340, 80}, 1, 10, lightGreen);
    DrawTextEx(font, "Press C for Credits", {135, 345}, 45, 2, WHITE);

    // Instructions option
    DrawRectangleRounded({80, 430, 340, 80}, 1, 10, lightGreen);
    DrawTextEx(font, "Press I for Instructions", {100, 445}, 44, 2, WHITE);
}

void DrawCreditsMenu(Font font)
{
    // Press ESC to Exit box
    DrawRectangleRounded({10, 10, 250, 50}, 1, 10, PINK);
    DrawTextEx(font, "Press E to Return", {20, 20}, 35, 2, DARKGRAY);

    DrawTextEx(font, "Credits", {170, 80}, 70, 2, DARKBROWN);

    // Developed by
    DrawTextEx(font, "Developed by Group 13", {100, 150}, 45, 2, WHITE);

    // Individual credits
    DrawTextEx(font, "22127327 - Tran Quoc Phong", {100, 210}, 45, 2, WHITE);
    DrawTextEx(font, "22127411 - Le Thi Thanh Thuy", {100, 270}, 45, 2, WHITE);
    DrawTextEx(font, "22127461 - Dang Nguyen Vu", {100, 330}, 45, 2, WHITE);
    DrawTextEx(font, "22127468 - Tran Thi My Y", {100, 390}, 45, 2, WHITE);

    // Special thanks
    DrawTextEx(font, "Special thanks to all the teachers", {20, 450}, 45, 2, WHITE);
    // Add more credit information as needed
}

void DrawInstructionsMenu(Font font)
{
    // Press ESC to Exit box
    DrawRectangleRounded({10, 10, 250, 50}, 1, 10, PINK);
    DrawTextEx(font, "Press E to Return", {30, 20}, 35, 2, DARKGRAY);

    DrawTextEx(font, "Instructions", {140, 80}, 60, 2, DARKBROWN);

    // Draw arrow boxes
    DrawRectangleRounded({180, 180, 60, 60}, 1, 10, BLUE); // up arrow
    DrawLine(210, 180, 180, 210, WHITE);
    DrawLine(210, 180, 210, 240, WHITE);
    DrawLine(210, 180, 240, 210, WHITE);
    DrawTextEx(font, "ROTATE BLOCK", {160, 160}, 35, 2, RED);

    DrawRectangleRounded({120, 260, 60, 60}, 1, 10, BLUE); // left arrow
    DrawLine(120, 290, 150, 260, WHITE);
    DrawLine(120, 290, 210, 290, WHITE);
    DrawLine(120, 290, 150, 320, WHITE);
    DrawTextEx(font, "MOVE LEFT", {20, 290}, 35, 2, RED);

    DrawRectangleRounded({240, 260, 60, 60}, 1, 10, BLUE); // right arrow
    DrawLine(290, 290, 260, 260, WHITE);
    DrawLine(290, 290, 230, 290, WHITE);
    DrawLine(290, 290, 260, 320, WHITE);
    DrawTextEx(font, "MOVE RIGHT", {300, 290}, 35, 2, RED);

    DrawRectangleRounded({180, 260, 60, 60}, 1, 10, BLUE); // down arrow
    DrawLine(210, 320, 240, 290, WHITE);
    DrawLine(210, 320, 210, 260, WHITE);
    DrawLine(210, 320, 180, 290, WHITE);
    DrawTextEx(font, "MOVE DOWN", {170, 340}, 35, 2, RED);

    // Draw space button
    DrawRectangleRounded({280, 180, 120, 60}, 1, 10, BLUE);
    DrawTextEx(font, "SPACE", {310, 195}, 36, 2, WHITE);
    DrawTextEx(font, "RUSH DOWN", {400, 200}, 32, 2, RED);
}

int main()
{
    InitWindow(500, 620, "Tetris Game - Group 13");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font\\ttf\\houston-sport-houston-sport-regular-400.ttf", 70, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        switch (currentMenuState)
        {
        // Inside your main loop, modify the MAIN_MENU case
        case MAIN_MENU:
            if (IsKeyPressed(KEY_ENTER))
                currentMenuState = PLAYING;
            else if (IsKeyPressed(KEY_C))
                currentMenuState = CREDITS;
            else if (IsKeyPressed(KEY_I))
                currentMenuState = INSTRUCTIONS;
            else if (IsKeyPressed(KEY_ESCAPE))
                CloseWindow();
            break;

        case PLAYING:
            UpdateMusicStream(game.music);
            game.ProcessInput();
            if (EventTriggered(0.2))
            {
                game.MoveBlockDown();
            }

            if (game.gameOver)
                currentMenuState = GAME_OVER;
            break;

        case GAME_OVER:
            DrawTextEx(font, "GAME OVER", {110, 100}, 100, 2, BLUE);
            DrawTextEx(font, "Press ENTER to Replay", {250, 620 - 150}, 35, 2, RED);
            DrawTextEx(font, "Press E to Return", {250, 620 - 100}, 35, 2, RED);

            if (IsKeyPressed(KEY_ENTER))
            {
                game.Reset();
                currentMenuState = PLAYING;
            }
            else if (IsKeyPressed(KEY_E))
            {
                currentMenuState = MAIN_MENU;
            }
            break;

        case CREDITS:
            DrawCreditsMenu(font);
            if (IsKeyPressed(KEY_E))
                currentMenuState = MAIN_MENU;
            break;

        case INSTRUCTIONS:
            DrawInstructionsMenu(font);
            if (IsKeyPressed(KEY_E))
                currentMenuState = MAIN_MENU;
            break;
        }

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        if (currentMenuState == MAIN_MENU)
        {
            DrawMainMenu(font);
        }
        else if (currentMenuState == PLAYING)
        {
            DrawTextEx(font, "Score", {365, 125}, 38, 2, DARKBROWN);
            DrawTextEx(font, "Next", {370, 400}, 38, 2, DARKGREEN);
            DrawTextEx(font, "Group 13 - 22CLC10", {320, 10}, 32, 2, magenta);
            DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightGreen);
            DrawTextEx(font, "Press the ESC ", {335, 480}, 35, 2, RED);
            DrawTextEx(font, "key to exit. ", {345, 510}, 35, 2, RED);

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

            DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
            DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightGreen);
            game.Draw();
        }

        EndDrawing();
    }

    CloseWindow();
}
