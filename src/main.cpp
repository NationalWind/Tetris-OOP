#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

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

int main()
{
    InitWindow(500, 620, "Tetris Game - Group 13");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font\\ttf\\houston-sport-houston-sport-regular-400.ttf", 70, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        if (EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawTextEx(font, "Score", {365, 125}, 38, 2, DARKBROWN);
        DrawTextEx(font, "Next", {370, 400}, 38, 2, DARKGREEN);
        DrawTextEx(font, "Group 13 - 22CLC10", {320, 10}, 32, 2, magenta);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {340, 555}, 45, 2, BLUE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightGreen);
        DrawTextEx(font, "Press the ESC ", {335, 480}, 35, 2, RED);
        DrawTextEx(font, "key to exit. ", {345, 510}, 35, 2, RED);
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightGreen);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}