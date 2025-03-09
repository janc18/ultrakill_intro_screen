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
    int framesCounter = 0;

    const char* status        = TextFormat("STATUS UPDATE:");
    const char* machineId     = TextFormat("%-29s V1", "MACHINE ID:");
    const char* location      = TextFormat("%-29s APPROCHING HELL", "LOCATION:");
    const char* objetive      = TextFormat("%-23s FIND A WEAPON", "CURRENT OBJECTIVE:");
    const char* information[] = {status, machineId, location, objetive};
    const char  mankind[]     = "MANKIND IS DEAD.";
    const char  blood[]       = "BLOOD IS FUEL.";
    const char  hell[]        = "HELL IS FULL.";
    const char* details[]     = {mankind, blood, hell};

    stringData_t data = {0};
    generateStringData(4, information, &data, 210, 160, WHITE, 40);
    stringData_t details_array    = {0};
    generateStringData(3, details, &details_array, 210, 340, RED, 40);
    stringData_t arrayOfStrings[2] = {data, details_array};

    InitAudioDevice();

    srand(time(NULL));
    int   SIZE = 470;
    short buffer[SIZE];
    GenerateKeyClickSound(buffer, SIZE, 100.0f, SIZE);
    Wave  wave          = {.frameCount = SIZE + 200, .sampleRate = SIZE + 600, .sampleSize = 16, .channels = 1, .data = buffer};
    Sound keySound      = LoadSoundFromWave(wave);
    details_array.sound = keySound;
    data.sound          = keySound;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        if (drawSecuenceOfStrings(&data) == 0)
        {
            drawAllStrings(&data);
            if (drawSecuenceOfStrings(&details_array) == 0)
            {
                drawAllStrings(&data);
                drawAllStrings(&details_array);
            }
        }
        EndDrawing();
    }
    UnloadSound(keySound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
