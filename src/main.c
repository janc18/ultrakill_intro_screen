#include "drawingText.h"
#include "raylib.h"

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
    const char  mankind[]     = "MAKIND IS DEAD.";
    const char  blood[]       = "BLOOD IS FUEL.";
    const char  hell[]        = "HELL IS FULL.";
    const char* details[]     = {mankind, blood, hell};

    stringData_t data    = {0};
    data.strings         = information;
    data.numberOfStrings = 4;
    data.lastindex       = -1;
    data.xPos            = 210;
    data.yPos            = 160;
    data.yPosStart       = 160;
    data.currentIndex    = -1;
    data.color           = WHITE;
    data.sizeText        = 40;

    stringData_t details_array    = {0};
    details_array.strings         = details;
    details_array.numberOfStrings = 3;
    details_array.lastindex       = -1;
    details_array.xPos            = 210;
    details_array.yPos            = 340;
    details_array.yPosStart       = 340;
    details_array.currentIndex    = -1;
    details_array.color           = RED;
    details_array.sizeText        = 40;

    stringData_t arrayOfStrings[2] = {data, details_array};

    InitAudioDevice();
    Sound fxOgg         = LoadSound("../../resources/audio/terminalSound.ogg"); 
    details_array.sound = fxOgg;
    data.sound          = fxOgg;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        if (drawSecuenceOfStrings(&data, WHITE, 40) == 0)
        {
            drawAllStrings(&data);
            if (drawSecuenceOfStrings(&details_array, RED, 40) == 0)
            {
                drawAllStrings(&data);
                drawAllStrings(&details_array);
            }
        }
        EndDrawing();
    }
    UnloadSound(fxOgg);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
