#include "drawingText.h"
#include <raylib.h>
#include <stdbool.h>
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
        stringData->framesCounter += 2;
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
            stringData->isCharacter = true;
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
        stringData->texturePosition[i].x = stringData->xPos;
        stringData->texturePosition[i].y = calculateYPos;
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
    stringData->texturePosition    = (Vector2*)calloc(stringData->numberOfStrings, sizeof(Vector2));
    return 0;
}

int generateStringData(int numberOfStringsToDraw, const char** stringsToDraw, stringData_t* stringData, int xPos, int yPos, Color color, int sizeText,
                       Sound sound)
{
    stringData->sound           = sound;
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
    if (stringData == NULL)
    {
        return -1;
    }
    for (int i = 0; i < stringData->numberOfStrings; i++)
    {
        UnloadRenderTexture(stringData->StringTextures[i]);
    }
    free(stringData->StringTextures);
    free(stringData->textureNeedsUpdate);
    free(stringData->texturePosition);
    return 0;
}
void UpdatePosition(Vector2* position)
{
    if (IsKeyDown(KEY_RIGHT))
        position->x += 5;
    if (IsKeyDown(KEY_LEFT))
        position->x -= 5;
    if (IsKeyDown(KEY_DOWN))
        position->y += 5;
    if (IsKeyDown(KEY_UP))
        position->y -= 5;
}

void UpdateFadeOut(float* alpha, bool* fadingOut)
{
    if (fadingOut)
    {
        *alpha -= 0.01f;
        if (*alpha <= 0.0f)
        {
            *alpha     = 0.0f;
            *fadingOut = false;
        }
    }
}

int fadeOutStringTextures(stringData_t* stringData, float alpha, bool fadingOut)
{
    for (int i = 0; i < stringData->numberOfStrings; i++)
    {
        Color     fadeColor = {255, 255, 255, (unsigned char)(alpha * 255)};
        Rectangle sourceRec = {0, 0, (float)stringData->StringTextures[i].texture.width, -(float)stringData->StringTextures[i].texture.height};
        Rectangle destRec   = {stringData->texturePosition[i].x, stringData->texturePosition[i].y, stringData->StringTextures[i].texture.width,
                               stringData->StringTextures[i].texture.height};
        Vector2   origin    = {0, 0};
        DrawTexturePro(stringData->StringTextures[i].texture, sourceRec, destRec, origin, 0.0f, fadeColor);
    }
    return 0;
}

int fadeOutTexture(Texture2D texture, float alpha, Rectangle sourceRect, Vector2 position)
{
    Color fadeColor = {255, 255, 255, (unsigned char)(alpha * 255)};
    DrawTextureRec(texture, sourceRect, position, fadeColor);
    return 0;
}

int triggerEvent(stringData_t* stringData, Texture2D texture1, Texture2D texture2, Rectangle sourceRect, Vector2 position)
{
    if (stringData->isCharacter)
    {
        DrawTextureRec(texture1, sourceRect, position, WHITE);
        stringData->isCharacter = false;
    }
    else
    {
        DrawTextureRec(texture2, sourceRect, position, WHITE);
    }
    return 0;
}
int drawStringSecuenciality(int* currentIndexStructData, int* endOfASecuence, int numberOfStructs, ...)
{
    static stringData_t** array          = NULL;
    static int            totalStructs   = 0;
    static int            completedIndex = 0;
    if (numberOfStructs > 0 && array == NULL)
    {
        va_list args;
        va_start(args, numberOfStructs);

        array        = malloc(numberOfStructs * sizeof(stringData_t*));
        totalStructs = numberOfStructs;

        for (int i = 0; i < numberOfStructs; i++)
        {
            array[i] = va_arg(args, stringData_t*);
        }
        va_end(args);

        *currentIndexStructData = 0;
        *endOfASecuence         = 0;
        completedIndex          = 0;
    }
    if (array != NULL && *currentIndexStructData < totalStructs)
    {
        int result = drawSecuenceOfStrings(array[*currentIndexStructData]);
        for (int i = 0; i < completedIndex; i++)
        {
            drawStringsThatHadBeenDrawed(array[i]);
        }

        if (result == 0)
        {
            completedIndex = *currentIndexStructData + 1;
            (*currentIndexStructData)++;
            if (*currentIndexStructData >= totalStructs)
            {

                *endOfASecuence = 1;
                free(array);
                array          = NULL;
                totalStructs   = 0;
                completedIndex = 0;
                return 0;
            }
        }
    }
    else
    {
        *endOfASecuence = 1;
    }

    return 1;
}
