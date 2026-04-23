#include <stdio.h>
#include <math.h>
#include <float.h>

#include "raylib.h"
#include "spot.h"

#define RGB(r, g, b) CLITERAL(Color){(r), (g), (b), 255}

typedef enum DistanceMode
{
    DISTANCE_EUCLIDEAN = 0,
    DISTANCE_MANHATTAN = 1,
    DISTANCE_CHEBYSHEV = 2,
    DISTANCE_MODE_COUNT = 3
} DistanceMode;

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 1100;

    const int gridX = 1000;
    const int gridY = 1000;
    const int gridOffsetX = 140;
    const int gridOffsetY = 50;

    Spot spots[] = {
        {118.0f, 167.0f, RGB(230, 25, 75), RGB(230, 25, 75), RGB(230, 25, 75)},
        {301.0f, 502.0f, RGB(60, 180, 75), RGB(60, 180, 75), RGB(60, 180, 75)},
        {728.0f, 391.0f, RGB(0, 130, 200), RGB(0, 130, 200), RGB(0, 130, 200)},
        {952.436806272913f, 564.7735676253427f, RGB(245, 130, 48), RGB(245, 130, 48), RGB(245, 130, 48)},
        {953.4572776589728f, 642.3309469090453f, RGB(145, 30, 180), RGB(145, 30, 180), RGB(145, 30, 180)},
        {122.0f, 984.0f, RGB(70, 240, 240), RGB(70, 240, 240), RGB(70, 240, 240)},
        {456.0f, 789.0f, RGB(240, 50, 230), RGB(240, 50, 230), RGB(240, 50, 230)},
        {789.0f, 123.0f, RGB(210, 245, 60), RGB(210, 245, 60), RGB(210, 245, 60)},
        {321.0f, 654.0f, RGB(250, 190, 20), RGB(250, 190, 20), RGB(250, 190, 20)},
        {654.0f, 321.0f, RGB(0, 128, 128), RGB(0, 128, 128), RGB(0, 128, 128)},
        {822.354283853106f, 894.496862285075f, RGB(220, 190, 255), RGB(220, 190, 255), RGB(220, 190, 255)},
        {432.0f, 876.0f, RGB(170, 110, 40), RGB(170, 110, 40), RGB(170, 110, 40)},
        {33.27566388173175f, 15.857915360708574f, RGB(255, 110, 180), RGB(255, 110, 180), RGB(255, 110, 180)},
        {609.6481427290171f, 253.9498536409811f, RGB(128, 0, 0), RGB(128, 0, 0), RGB(128, 0, 0)},
        {939.3659402373587f, 651.4922567914604f, RGB(170, 255, 195), RGB(170, 255, 195), RGB(170, 255, 195)},
        {845.6336886420079f, 966.320526900811f, RGB(0, 0, 128), RGB(0, 0, 128), RGB(0, 0, 128)},
        {249.45198409948333f, 111.70168891649135f, RGB(128, 128, 128), RGB(128, 128, 128), RGB(128, 128, 128)},
        {933.2622304108157f, 120.45266873039672f, RGB(255, 80, 5), RGB(255, 80, 5), RGB(255, 80, 5)},
        {52.18062784299005f, 259.5581725154219f, RGB(0, 95, 57), RGB(0, 95, 57), RGB(0, 95, 57)},
        {840.7237401011934f, 391.5997861625955f, RGB(50, 50, 150), RGB(50, 50, 150), RGB(50, 50, 150)},
        {169.51443546119415f, 244.0471541368028f, RGB(50, 190, 190), RGB(50, 190, 190), RGB(50, 190, 190)},
        {681.6619587331563f, 24.176773237322593f, RGB(230, 170, 30), RGB(230, 170, 30), RGB(230, 170, 30)},
        {944.8983039669414f, 14.450016392027255f, RGB(100, 60, 150), RGB(100, 60, 150), RGB(100, 60, 150)},
        {704.5162334236563f, 223.17558026252505f, RGB(180, 70, 20), RGB(180, 70, 20), RGB(180, 70, 20)},
        {461.9914568589912f, 873.954090482952f, RGB(20, 140, 100), RGB(20, 140, 100), RGB(20, 140, 100)},
        {865.3355497853111f, 578.7456358340122f, RGB(230, 80, 180), RGB(230, 80, 180), RGB(230, 80, 180)},
        {186.39817335952358f, 983.3980665591891f, RGB(90, 90, 20), RGB(90, 90, 20), RGB(90, 90, 20)},
        {943.9685335710476f, 299.7388778238278f, RGB(30, 90, 190), RGB(30, 90, 190), RGB(30, 90, 190)},
        {20.592628931571543f, 820.5699420821875f, RGB(190, 30, 30), RGB(190, 30, 30), RGB(190, 30, 30)},
        {347.021205995958f, 868.8763891087576f, RGB(40, 170, 40), RGB(40, 170, 40), RGB(40, 170, 40)}};
    const int spotCount = (int)(sizeof(spots) / sizeof(spots[0]));

    Image modeImages[DISTANCE_MODE_COUNT] = {
        GenImageColor(gridX, gridY, BLANK),
        GenImageColor(gridX, gridY, BLANK),
        GenImageColor(gridX, gridY, BLANK)};
    Color *modePixels[DISTANCE_MODE_COUNT] = {
        (Color *)modeImages[DISTANCE_EUCLIDEAN].data,
        (Color *)modeImages[DISTANCE_MANHATTAN].data,
        (Color *)modeImages[DISTANCE_CHEBYSHEV].data};

    for (int x = 0; x < gridX; x++)
    {
        for (int y = 0; y < gridY; y++)
        {
            int nearestEuclideanSpotIndex = -1;
            float nearestEuclideanSpotDistanceSquared = FLT_MAX;
            int nearestManhattanSpotIndex = -1;
            float nearestManhattanSpotDistance = FLT_MAX;
            int nearestChebyshevSpotIndex = -1;
            float nearestChebyshevSpotDistance = FLT_MAX;
            for (int z = 0; z < spotCount; z++)
            {
                float dx = spots[z].x - (float)x;
                float dy = spots[z].y - (float)y;
                float absDx = fabsf(dx);
                float absDy = fabsf(dy);
                float euclideanDistanceSquared = dx * dx + dy * dy;
                float manhattanDistance = absDx + absDy;
                float chebyshevDistance = fmaxf(absDx, absDy);

                if (euclideanDistanceSquared < nearestEuclideanSpotDistanceSquared)
                {
                    nearestEuclideanSpotDistanceSquared = euclideanDistanceSquared;
                    nearestEuclideanSpotIndex = z;
                }
                if (manhattanDistance < nearestManhattanSpotDistance)
                {
                    nearestManhattanSpotDistance = manhattanDistance;
                    nearestManhattanSpotIndex = z;
                }
                if (chebyshevDistance < nearestChebyshevSpotDistance)
                {
                    nearestChebyshevSpotDistance = chebyshevDistance;
                    nearestChebyshevSpotIndex = z;
                }
            }

            int pixelIndex = y * gridX + x;
            modePixels[DISTANCE_EUCLIDEAN][pixelIndex] = spots[nearestEuclideanSpotIndex].euclidean_color;
            modePixels[DISTANCE_MANHATTAN][pixelIndex] = spots[nearestManhattanSpotIndex].manhattan_color;
            modePixels[DISTANCE_CHEBYSHEV][pixelIndex] = spots[nearestChebyshevSpotIndex].chebyshev_color;
        }
    }

    InitWindow(screenWidth, screenHeight, "Homework 8 - Voronoi Diagram");
    Texture2D modeTextures[DISTANCE_MODE_COUNT];
    for (int i = 0; i < DISTANCE_MODE_COUNT; i++)
    {
        modeTextures[i] = LoadTextureFromImage(modeImages[i]);
        UnloadImage(modeImages[i]);
    }

    DistanceMode distanceMode = DISTANCE_EUCLIDEAN;
    SetTargetFPS(5);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ONE))
        {
            distanceMode = DISTANCE_EUCLIDEAN;
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            distanceMode = DISTANCE_MANHATTAN;
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            distanceMode = DISTANCE_CHEBYSHEV;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(modeTextures[distanceMode], gridOffsetX, gridOffsetY, WHITE);
        DrawRectangleLines(gridOffsetX, gridOffsetY, gridX, gridY, BLACK);

        for (int i = 0; i < spotCount; i++)
        {
            DrawCircleV(
                (Vector2){gridOffsetX + spots[i].x, gridOffsetY + spots[i].y},
                5.0f,
                BLACK);
        }

        EndDrawing();
    }

    for (int i = 0; i < DISTANCE_MODE_COUNT; i++)
    {
        UnloadTexture(modeTextures[i]);
    }

    CloseWindow();
    return 0;
}