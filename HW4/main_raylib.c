#include <stdio.h>

#include "raylib.h"

const double LINE_PRECISION = 0.0001f;
const double LINE_THICKNESS = 0.015f;

void DrawThickLine(Vector3 start, Vector3 end, double thickness, Color color)
{
    if (thickness <= LINE_PRECISION) thickness = LINE_PRECISION;

    Vector3 a = {start.x, start.y, start.z};
    Vector3 b = {end.x, end.y, end.z};

    for (double i = -thickness; i <= thickness; i = i + LINE_PRECISION)
    {
        for (double j = -thickness; j <= thickness; j = j + LINE_PRECISION)
        {
            a.x = start.x + i;
            a.y = start.y + j;

            b.x = end.x + i;
            b.y = end.y + j;
            DrawLine3D(a, b, color);
        }
    }
}

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    Vector3 startPos = {0, 0, 0};

    Vector3 a = {+2, +1, +5};
    // Vector3 b = {+2, +1, +5}; // Same as a

    Vector3 Aa_1 = {+2, +1, +5};
    Vector3 Ab_1 = {+6, +3, +11};

    Vector3 Aa_2 = {-2, -1, -5};
    Vector3 Ab_2 = {+2, +1, +1};

    Vector3 Aa_3 = {+0.7071067812, +2.121320344, +5};
    Vector3 Ab_3 = {+4.707106781, +4.121320344, +11};

    Vector3 Aa_4 = {+1, +1.5, +5};
    Vector3 Ab_4 = {+5, +3.5, +11};

    Vector3 TaskContext[4][2] = {
        {Aa_1, Ab_1},
        {Aa_2, Ab_2},
        {Aa_3, Ab_3},
        {Aa_4, Ab_4}};

    int currentContext = 0;

    InitWindow(screenWidth, screenHeight, "Homework 4 - Vector Manipulation");

    Camera3D camera = {0};
    camera.position = (Vector3){-4.0f, 2.0f, -1.5f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    DisableCursor();

    int currentFps = 120;
    SetTargetFPS(currentFps);
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);
        
        if (IsKeyDown(KEY_RIGHT))
        {
            currentContext = (currentContext + 1) % 4;
            WaitTime(0.5);
        }
        if (IsKeyDown(KEY_LEFT))
        {
            currentContext = (currentContext + 3) % 4;
            WaitTime(0.5);
        }
        if (IsKeyPressed(KEY_Z)) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };

        BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginMode3D(camera);

                DrawThickLine(startPos, a, LINE_THICKNESS, RED);
                DrawThickLine(startPos, TaskContext[currentContext][0], LINE_THICKNESS, DARKBLUE);
                DrawThickLine(startPos, TaskContext[currentContext][1], LINE_THICKNESS, DARKPURPLE);
                DrawGrid(50, 0.5f);

            EndMode3D();

            DrawRectangle( 10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 93, BLUE);

            DrawText("Free camera default controls:", 20, 20, 15, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 15, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 15, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 15, DARKGRAY);

            // Task + Space + Num + \0
            char taskText[7]; // 4 + 1 + 1 + 1
            char* title = "Task";
            char num = 49 + currentContext;
            snprintf(taskText, sizeof(taskText), "%s %s", title, &num);

            DrawText(taskText, 1080, 30, 50, DARKGRAY);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}