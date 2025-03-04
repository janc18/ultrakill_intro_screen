
#include <string.h>
#include "raylib.h"

int MAXSIZESTRING = 200;

int getRemainingChars(const char* text, int currentFPS, int currentFrameCounter, int* currentStringIndex, int* lastIndex)
{
    int   sizeString     = strnlen(text, MAXSIZESTRING);
    float aproximateTime = (sizeString * (1.0 / currentFPS)) * 10.0;
    *currentStringIndex  = currentFrameCounter / 10;
    *lastIndex           = sizeString - *currentStringIndex;
    return *lastIndex;
}
