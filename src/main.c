
#include "raylib.h"
#include <stdio.h>
#include <string.h>
int MAXSIZESTRING = 200;

typedef struct stringData {
  const char *string;
  size_t sizeString;
  int currentIndex;
} stringData;

int getRemainingChars(const char *text, int currentFPS, int currentFrameCounter, int *currentStringIndex, int *lastIndex) {
  int sizeString = strnlen(text, MAXSIZESTRING);
  float aproximateTime = (sizeString * (1.0 / currentFPS)) * 10.0;
  *currentStringIndex = currentFrameCounter / 10;
  *lastIndex = sizeString - *currentStringIndex;
  return *lastIndex;
}
int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "V1");
  int framesCounter = 0;
  const char *test0 = TextFormat("STATUS UPDATE:");
  const char *test1 = TextFormat("%-29s V1", "MACHINE ID:");
  const char *test2 = TextFormat("%-29s APPROCHING HELL", "LOCATION:");
  const char *test3 = TextFormat("%-23s FIND A WEAPON", "CURRENT OBJECTIVE:");
  const char *array_strings[4] = {test0, test1, test2, test3};
  int currentIndex;
  int lastindex = -1;
  int numberOfStringDrawed = 0;
  int ypos = 160;
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

    if (lastindex != 0 && (numberOfStringDrawed < (sizeof(array_strings) / sizeof(array_strings[0])))) {
      DrawText(TextSubtext(array_strings[numberOfStringDrawed], 0, framesCounter / 10), 210, ypos, 20, WHITE);
      if (getRemainingChars(array_strings[numberOfStringDrawed], GetFPS(), framesCounter, &currentIndex, &lastindex) == 0) {
        numberOfStringDrawed++;
        lastindex = -1;
        framesCounter = 0;
        ypos += 20;
      }
    }
    for (int i = 0; i < numberOfStringDrawed; i++) {
      DrawText(array_strings[i], 210, 160 + (i * 20), 20, WHITE); 
    }
    EndDrawing();
  }

  CloseWindow(); 

  return 0;
}
