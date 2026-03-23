#include "jsonParser/parser.h"
#include "terminalEngine/v1View.h"
#include <fcntl.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{

    int fd = open("inputMessages.json", O_RDWR);
    if (fd == -1)
    {
        exit(1);
    }
    char json[2048];
    int  bytesRead = read(fd, json, sizeof(json));

    phrase_t Phrases[10];
    int      PhrasesDetected = 0;
    int      status          = getPhrases(json, Phrases, &PhrasesDetected, 10);
    if (status < 0)
    {
        return 0;
    }
    const int screenWidth  = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);
    terminalMessages_t dispatcher;
    terminalDispatcher_Init(&dispatcher, PhrasesDetected);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        float dt = GetFrameTime();
        ClearBackground(BLACK);
        if (IsKeyPressed(KEY_LEFT))
        {
            scheduleFadeOutAllSkip(&dispatcher);
        }
        // scheduleSequentially(&dispatcher,Phrases);
        scheduleAllAtTheTime(&dispatcher, Phrases);
        terminalDispatcher_Update(&dispatcher, dt);
        terminalDispatcher_Draw(&dispatcher);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
