#include "raylib.h"

const double LINE_PRECISION = 0.001f;
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
    Vector3 b = {+2, +1, +5};

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
    camera.position = (Vector3){5.0f, 5.0f, 3.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int currentFps = 120;
    SetTargetFPS(currentFps);
    SetTraceLogLevel(LOG_ALL);
    while (!WindowShouldClose())
    {
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

        BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginMode3D(camera);

                DrawThickLine(startPos, a, LINE_THICKNESS, RED);
                DrawThickLine(startPos, b, LINE_THICKNESS, BLUE);
                DrawThickLine(startPos, TaskContext[currentContext][0], LINE_THICKNESS, DARKBROWN);
                DrawThickLine(startPos, TaskContext[currentContext][1], LINE_THICKNESS, DARKPURPLE);
                DrawGrid(30, 0.5f);

            EndMode3D();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}