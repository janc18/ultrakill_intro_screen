#include "terminalEngine/v1View.h"
#include "audio/manageAudio.h"
#include "movement/keysMovement.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    const int screenWidth  = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "V1");
  
    // Audio initiation and loading sound to each stringData
    InitAudioDevice();
    srand(time(NULL));
    int   sampleRate = 44100;
    int   samples    = sampleRate * 0.0186;
    Sound keySound   = generateSimpleSound(sampleRate, samples);
    // Create StringData_t structs and configure
    ChangeDirectory("../");
    Image image1 = LoadImage("./resources/images/1.png");
    Image image2 = LoadImage("./resources/images/2.png");
    ImageResize(&image1, image1.width / 2.5, image1.height / 2.5);
    ImageResize(&image2, image2.width / 2.5, image2.height / 2.5);
    Texture2D texture1       = LoadTextureFromImage(image1);
    Texture2D texture2       = LoadTextureFromImage(image2);
    double    lastSwitchTime = 0;
    bool      showTexture1   = true;
    Vector2   position       = {504, 500};
    Rectangle sourceRect     = {0, 0, texture1.width, texture1.height};
    float     alpha          = 1.0f; 
    bool      fadingOut      = true;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        UpdatePosition(&position);
        BeginDrawing();
        DrawTexture(texture1,position.x,position.y,WHITE);
        ClearBackground(BLACK);
        EndDrawing();

    }
        //  ---------
    UnloadImage(image1);
    UnloadImage(image2);
    UnloadSound(keySound);
    CloseAudioDevice();

    CloseWindow();

    return 0;
}
