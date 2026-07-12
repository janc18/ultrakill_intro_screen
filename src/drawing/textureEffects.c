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

int fadeOutTexture(Texture2D texture, float alpha, Rectangle sourceRect, Vector2 position)
{
    Color fadeColor = {255, 255, 255, (unsigned char)(alpha * 255)};
    DrawTextureRec(texture, sourceRect, position, fadeColor);
    return 0;
}
