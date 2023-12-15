#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

enum MenuState
{
    MAIN_MENU,
    PLAYING,
    GAME_OVER
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

    // Adjusted rectangle dimensions
    DrawRectangleRounded({80, 230, 340, 80}, 1, 10, lightGreen);
    DrawTextEx(font, "Press ENTER to Play", {135, 245}, 45, 2, WHITE);

    // Adjusted rectangle dimensions
    DrawRectangleRounded({80, 330, 340, 80}, 1, 10, lightGreen);
    DrawTextEx(font, "Press ESC to Quit", {135, 345}, 45, 2, WHITE);

    DrawTriangle((Vector2){100, 200}, (Vector2){50, 400}, (Vector2){300, 400}, RED); // Up arrow
    // DrawTriangle((Vector2){screenWidth / 2, screenHeight * 3 / 4}, (Vector2){screenWidth / 2 - 50, screenHeight * 3 / 4 - 50}, (Vector2){screenWidth / 2 + 50, screenHeight * 3 / 4 - 50}, BLUE);   // Down arrow
    // DrawTriangle((Vector2){screenWidth / 4, screenHeight / 2}, (Vector2){screenWidth / 4 - 50, screenHeight / 2 - 50}, (Vector2){screenWidth / 4 - 50, screenHeight / 2 + 50}, GREEN);              // Left arrow
    // DrawTriangle((Vector2){screenWidth * 3 / 4, screenHeight / 2}, (Vector2){screenWidth * 3 / 4 + 50, screenHeight / 2 - 50}, (Vector2){screenWidth * 3 / 4 + 50, screenHeight / 2 + 50}, ORANGE); // Right arrow
}

int main()
{
    InitWindow(500, 620, "Tetris Game - Group 13");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font\\ttf\\houston-sport-houston-sport-regular-400.ttf", 70, 0, 0);
    Font font1 = LoadFontEx("Font\arial-unicode-ms.ttf", 70, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        switch (currentMenuState)
        {
        case MAIN_MENU:
            if (IsKeyPressed(KEY_ENTER))
                currentMenuState = PLAYING;
            if (IsKeyPressed(KEY_ESCAPE))
                CloseWindow();
            break;

        case PLAYING:
            UpdateMusicStream(game.music);
            game.HandleInput();
            if (EventTriggered(0.2))
            {
                game.MoveBlockDown();
            }

            if (game.gameOver)
                currentMenuState = GAME_OVER;
            break;

        case GAME_OVER:
            // Your existing code for displaying "GAME OVER"
            DrawTextEx(font, "GAME OVER", {339, 539}, 45, 2, BLUE);

            if (IsKeyPressed(KEY_ENTER))
            {
                game.Reset();
                currentMenuState = PLAYING;
            }
            if (IsKeyPressed(KEY_ESCAPE))
                CloseWindow();
            break;
        }

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        if (currentMenuState == MAIN_MENU)
        {
            DrawMainMenu(font);
        }
        else
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
