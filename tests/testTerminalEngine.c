#include "jsonParser/parser.h"
#include "terminalEngine/v1View.h"
#include "textScheduler/scheduler.h"
#include <fcntl.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    if (argc<2){
        printf("File path not specified, closing\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1)
    {
        printf("Messages don't found, closing\n");
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
          //  scheduleFadeOutAllSkip(&dispatcher);
        }
        
        scheduleSequentially(&dispatcher,Phrases);//if one is skip==false it keep in that loop
        //scheduleAllAtTheTime(&dispatcher, Phrases);// all skip==false stay in the screen 
        terminalDispatcher_Update(&dispatcher, dt);
        terminalDispatcher_Draw(&dispatcher);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
