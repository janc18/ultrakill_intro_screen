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
    data.currentIndex              = -1;
    data.color                     = WHITE;
    data.sizeText                  = 20;

    stringData_t details_array    = {0};
    details_array.strings         = details;
    details_array.numberOfStrings = 3;
    details_array.lastindex       = -1;
    details_array.xPos            = 210;
    details_array.yPos            = 340;
    details_array.yPosStart       = 340;
    details_array.currentIndex    = -1;
    details_array.color           = RED;
    details_array.sizeText        = 20;
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
        if (drawSecuenceOfStrings(&data, WHITE, 20) == 0)
        {
            drawAllStrings(&data);
            if (drawSecuenceOfStrings(&details_array, RED, 20) == 0)
            {
                drawAllStrings(&data);
                drawAllStrings(&details_array);
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
