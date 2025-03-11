#include "drawingText.h"
#include "manageAudio.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

int main(void)
{
    const int screenWidth  = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "V1");
    // Strings to draw
    const char* status    = TextFormat("STATUS UPDATE:");
    const char* machineId = TextFormat("%-29s V1", "MACHINE ID:");
    const char* location  = TextFormat("%-29s APPROCHING HELL", "LOCATION:");
    const char* objetive  = TextFormat("%-23s FIND A WEAPON", "CURRENT OBJECTIVE:");
    const char  mankind[] = "MANKIND IS DEAD.";
    const char  blood[]   = "BLOOD IS FUEL.";
    const char  hell[]    = "HELL IS FULL.";
    // Add each string to a string array
    const char* details[]     = {mankind, blood, hell};
    const char* information[] = {status, machineId, location, objetive};
    // Audio initiation and loading sound to each stringData
    InitAudioDevice();
    srand(time(NULL));
    int   sampleRate = 44100;
    int   samples    = sampleRate * 0.0186;
    Sound keySound   = generateSimpleSound(sampleRate, samples);
    // Create StringData_t structs and configure
    stringData_t data          = {0};
    stringData_t details_array = {0};
    generateStringData(4, information, &data, 210, 160, WHITE, 40, keySound);
    generateStringData(3, details, &details_array, 210, 340, RED, 40, keySound);
    // Loading images to be drawing
    Image image1 = LoadImage("../../resources/images/1.png");
    Image image2 = LoadImage("../../resources/images/2.png");
    ImageResize(&image1, image1.width / 2.5, image1.height / 2.5);
    ImageResize(&image2, image2.width / 2.5, image2.height / 2.5);
    Texture2D texture1       = LoadTextureFromImage(image1);
    Texture2D texture2       = LoadTextureFromImage(image2);
    double    lastSwitchTime = 0;
    bool      showTexture1   = true;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Select the texture to draw
        if (GetTime() - lastSwitchTime >= 0.5)
        {
            showTexture1   = !showTexture1;
            lastSwitchTime = GetTime();
        }
        //  ---------
        BeginDrawing();
        ClearBackground(BLACK);
        // Draw the strings
        if (drawSecuenceOfStrings(&data) == 0)
        {
            drawSecuenceOfStrings(&details_array);
        }
        //  ---------

        // Draw the textures
        if (showTexture1)
        {
            DrawTexture(texture1, 1000, 500, WHITE);
        }
        else
        {
            DrawTexture(texture2, 1000, 500, WHITE);
        }

        //  ---------
        EndDrawing();
    }
    freeTextureStrings(&data);
    freeTextureStrings(&details_array);
    UnloadImage(image1);
    UnloadImage(image2);
    UnloadSound(keySound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
