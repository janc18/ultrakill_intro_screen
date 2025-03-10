#include "drawingText.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int MAXSIZESTRING = 200;

int getRemainingChars(const char* text, int currentFrameCounter, int* currentStringIndex, int* lastIndex)
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

int drawSecuenceOfStrings(stringData_t* stringData)
{
    if (stringData->lastindex != 0 && (stringData->numberOfStringDrawed < stringData->numberOfStrings))
    {
        const char* stringToDraw = stringData->strings[stringData->numberOfStringDrawed];
        stringData->framesCounter += 3;
        DrawText(TextSubtext(stringToDraw, 0, stringData->framesCounter / 10), stringData->xPos, stringData->yPos, stringData->sizeText,
                 stringData->color);
        int  getRemainingCharsValue = getRemainingChars(stringToDraw, stringData->framesCounter, &stringData->currentIndex, &stringData->lastindex);
        bool isSpace                = checkIfCharacterIs(stringToDraw, ' ', stringData->currentIndex);
        if (getRemainingCharsValue == 0)
        {
            modifyValuesToDrawTheNextString(stringData);
            stringData->textureNeedsUpdate[stringData->numberOfStringDrawed - 1] = true;
        }

        if (stringData->framesCounter % 10 == 0 && !isSpace)
        {
            PlaySound(stringData->sound);
        }
    }
    int drawedAllStrings = drawStringsThatHadBeenDrawed(stringData);
    return drawedAllStrings;
}

int drawStringsThatHadBeenDrawed(stringData_t* stringData)
{
    for (int i = 0; i < stringData->numberOfStringDrawed; i++)
    {
        const char* stringToDraw = stringData->strings[i];
        if (stringData->textureNeedsUpdate[i] == true)
        {
            stringData->StringTextures[i]     = createStringTexture(stringToDraw, stringData);
            stringData->textureNeedsUpdate[i] = false;
        }
        int textWidth     = MeasureText(stringToDraw, stringData->sizeText);
        int calculateYPos = stringData->yPosStart + (i * stringData->sizeText);
        DrawTextureRec(stringData->StringTextures[i].texture, (Rectangle){0, 0, textWidth, -stringData->sizeText},
                       (Vector2){stringData->xPos, calculateYPos}, stringData->color);
    }

    return (stringData->numberOfStringDrawed == stringData->numberOfStrings) ? 0 : -1;
}

int modifyValuesToDrawTheNextString(stringData_t* stringData)
{
    stringData->numberOfStringDrawed++;
    stringData->lastindex     = -1;
    stringData->framesCounter = 0;
    stringData->yPos += stringData->sizeText;
    return 0;
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
    stringData->lastindex          = -1;
    stringData->xPos               = xPos;
    stringData->yPos               = yPos;
    stringData->yPosStart          = yPos;
    stringData->currentIndex       = -1;
    stringData->color              = color;
    stringData->sizeText           = sizeText;
    stringData->StringTextures     = (RenderTexture2D*)calloc(stringData->numberOfStrings, sizeof(RenderTexture2D));
    stringData->textureNeedsUpdate = (bool*)calloc(stringData->numberOfStrings, sizeof(bool));
    return 0;
}

int generateStringData(int numberOfStringsToDraw, const char** stringsToDraw, stringData_t* stringData, int xPos, int yPos, Color color, int sizeText)
{

    stringData->strings         = stringsToDraw;
    stringData->numberOfStrings = numberOfStringsToDraw;
    configStringData(stringData, xPos, yPos, color, sizeText);
    return 0;
}

RenderTexture2D createStringTexture(const char* string, stringData_t* stringData)
{
    stringData->lastTextWidth   = MeasureText(string, stringData->sizeText);
    RenderTexture2D textTexture = LoadRenderTexture(stringData->lastTextWidth, stringData->sizeText);
    BeginTextureMode(textTexture);
    ClearBackground(BLANK);
    DrawText(string, 0, 0, stringData->sizeText, stringData->color);
    EndTextureMode();
    return textTexture;
}

int freeTextureStrings(stringData_t* stringData)
{
    for (int i = 0; i < stringData->numberOfStrings; i++)
    {
        UnloadRenderTexture(stringData->StringTextures[i]);
    }
    free(stringData->StringTextures);
    free(stringData->textureNeedsUpdate);
}