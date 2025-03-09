
#include "drawingText.h"
#include <ctype.h>
#include <raylib.h>
#include <stdio.h>
#include <string.h>
int MAXSIZESTRING = 200;

int getRemainingChars(const char* text, int currentFPS, int currentFrameCounter, int* currentStringIndex, int* lastIndex)
{
    int sizeString      = strnlen(text, MAXSIZESTRING);
    *currentStringIndex = currentFrameCounter / 10;
    *lastIndex          = sizeString - *currentStringIndex;
    return *lastIndex;
}

void printStringData(stringData_t* stringData)
{
    printf("=====\n");
    printf("numberOfStrings: %zu\n", stringData->numberOfStrings);
    printf("lastIndex: %d\n", stringData->lastindex);
    printf("numberOfStringDrawed: %d\n", stringData->numberOfStringDrawed);
    printf("xPos :%d\n", stringData->xPos);
    printf("yPos :%d\n", stringData->yPos);
    printf("framesCounter :%d\n", stringData->framesCounter);
    printf("currentIndex :%d\n", stringData->currentIndex);
    printf("=====\n");
}

int drawSecuenceOfStrings(stringData_t* stringData, Color color, int sizeText)
{
    if (stringData->lastindex != 0 && (stringData->numberOfStringDrawed < stringData->numberOfStrings))
    {
        stringData->framesCounter += 3;
        DrawText(TextSubtext(stringData->strings[stringData->numberOfStringDrawed], 0, stringData->framesCounter / 10), stringData->xPos,
                 stringData->yPos, sizeText, color);
        int  getRemainingCharsValue = getRemainingChars(stringData->strings[stringData->numberOfStringDrawed], GetFPS(), stringData->framesCounter,
                                                        &stringData->currentIndex, &stringData->lastindex);
        bool isSpace                = checkIfCharacterIs(stringData->strings[stringData->numberOfStringDrawed], ' ', stringData->currentIndex);
        if (getRemainingCharsValue == 0)
        {
            stringData->numberOfStringDrawed++;
            stringData->lastindex     = -1;
            stringData->framesCounter = 0;
            stringData->yPos += sizeText;
        }

        if (stringData->framesCounter % 10 == 0 && !isSpace)
        {
            PlaySound(stringData->sound);
        }
    }
    for (int i = 0; i < stringData->numberOfStringDrawed; i++)
    {
        DrawText(stringData->strings[i], stringData->xPos, stringData->yPosStart + (i * sizeText), sizeText, color);
        if (stringData->numberOfStringDrawed == stringData->numberOfStrings)
            return 0;
    }
    return -1;
}

int drawAllStrings(stringData_t* stringData)
{
    for (int i = 0; i < stringData->numberOfStrings; i++)
    {
        DrawText(stringData->strings[i], stringData->xPos, stringData->yPosStart + (i * stringData->sizeText), stringData->sizeText,
                 stringData->color);
    }
    return 0;
}

bool checkIfCharacterIs(const char* string, char character, int indexString)
{
    if (string != NULL)
    {

        if (string[indexString] == character)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
  return false;
}

int configStringData(stringData_t* stringData, int xPos, int yPos, Color color, int sizeText)
{
    if (stringData == NULL)
    {
        return -1;
    }
    stringData->lastindex    = -1;
    stringData->xPos         = xPos;
    stringData->yPos         = yPos;
    stringData->yPosStart    = yPos;
    stringData->currentIndex = -1;
    stringData->color        = color;
    stringData->sizeText     = sizeText;
    return 0;
}
