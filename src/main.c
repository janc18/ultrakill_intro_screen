#include "drawingText.h"
#include "raylib.h"

int main(void)
{
    const int screenWidth  = 800;
    const int screenHeight = 450;
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

    const char** arrayOfStrings[2] = {information, details};
    stringData_t data              = {0};
    data.strings                   = information;
    data.numberOfStrings           = 4;
    data.lastindex                 = -1;
    data.xPos                      = 210;
    data.yPos                      = 160;
    data.yPosStart                 = 160;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_SPACE))
            framesCounter += 8;
        else
            framesCounter++;

        if (IsKeyPressed(KEY_ENTER))
            framesCounter = 0;
        BeginDrawing();
        ClearBackground(BLACK);
        drawSecuenceOfStrings(&data, WHITE, 20);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
