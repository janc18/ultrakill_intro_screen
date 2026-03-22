#include <stdbool.h>
#include <raylib.h>

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
/*
int fadeOutTextures(stringData_t* stringData, float alpha, bool fadingOut)
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
*/
int fadeOutTexture(Texture2D texture, float alpha, Rectangle sourceRect, Vector2 position)
{
    Color fadeColor = {255, 255, 255, (unsigned char)(alpha * 255)};
    DrawTextureRec(texture, sourceRect, position, fadeColor);
    return 0;
}
