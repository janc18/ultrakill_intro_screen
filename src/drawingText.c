
#include "drawingText.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>
int MAXSIZESTRING = 200;

int getRemainingChars(const char* text, int currentFPS, int currentFrameCounter, int* currentStringIndex, int* lastIndex)
{
    int sizeString      = strnlen(text, MAXSIZESTRING);
    *currentStringIndex = currentFrameCounter / 10;
    *lastIndex          = sizeString - *currentStringIndex;
    printf("Current string :%s, lastindex:%d, framesCounter:%d\n", text, *lastIndex, currentFrameCounter);
    return *lastIndex;
}

void printStringData(stringData_t* stringData)
{
    printf("numberOfStrings: %zu\n", stringData->numberOfStrings);
    printf("lastIndex: %d\n", stringData->lastindex);
    printf("numberOfStringDrawed: %d\n", stringData->numberOfStringDrawed);
    printf("xPos :%d\n", stringData->xPos);
    printf("yPos :%d\n", stringData->yPos);
    printf("framesCounter :%d\n", stringData->framesCounter);
    printf("currentIndex :%d\n", stringData->currentIndex);
}

int drawSecuenceOfStrings(stringData_t* stringData, Color color, int sizeText)
{
    if (stringData->lastindex != 0 && (stringData->numberOfStringDrawed < stringData->numberOfStrings))
    {
        stringData->framesCounter++;
        DrawText(TextSubtext(stringData->strings[stringData->numberOfStringDrawed], 0, stringData->framesCounter / 10), stringData->xPos,
                 stringData->yPos, sizeText, color);

        if (getRemainingChars(stringData->strings[stringData->numberOfStringDrawed], GetFPS(), stringData->framesCounter, &stringData->currentIndex,
                              &stringData->lastindex) == 0)
        {
            stringData->numberOfStringDrawed++;
            stringData->lastindex     = -1;
            stringData->framesCounter = 0;
            stringData->yPos += sizeText;
        }
    }
    printStringData(stringData);

    for (int i = 0; i < stringData->numberOfStringDrawed; i++)
    {
        DrawText(stringData->strings[i], stringData->xPos, stringData->yPosStart + (i * sizeText), sizeText, color);
    }

    return 0;
}
