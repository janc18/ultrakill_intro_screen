#include <raylib.h>

RenderTexture2D createStringTexture(const char* string, int fontSize, int xPos, int yPos, Color color)
{
    int             TextWidth   = MeasureText(string, fontSize);
    RenderTexture2D textTexture = LoadRenderTexture(TextWidth, fontSize);
    BeginTextureMode(textTexture);
    ClearBackground(BLANK);
    DrawText(string, xPos, yPos, fontSize, color);
    EndTextureMode();
    return textTexture;
}
